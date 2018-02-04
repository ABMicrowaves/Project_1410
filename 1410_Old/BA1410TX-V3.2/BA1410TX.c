#include <BA1410TX.h>
//#include <stdlib.h>
#include <ctype.h>
#include "PIC18F45K22_registers.h"

#define VERSION " BA1410TX V3.2"

//--------- frequency constants --------------------------------
#define FREQ_P_MULT           32L
#define FREQ_BASE        2185000L       // in KHz
#define FREQ_TOP         2400000L       // in KHz
#define FREQ_STEP            100L       // in KHz
#define FREQ_OSC           10000L       // in KHz
#define FREQ_MOD              ((FREQ_OSC / FREQ_STEP) / RFdiv)

//========== power =============================================
UINT low_power_level, power_level, power_control;
UINT manual_power = 0xFFFF;
UINT manual_negative = 0xFFFF;

#define A2D_POWER 5
#define A2D_PREV  4
#define A2D_TEMP  6
#define A2D_Vdd   0

#define DAC_POS_VOLT 0
#define DAC_NEG_VOLT 1

#define FREQ_LOW_THRESH   22570
#define FREQ_HIGH_THRESH  23290

#define DEADBAND 6

UINT  manual_pos = 0xFFFF;

//========== timer =============================================
UCHAR  TMR_1mS_Flags;
UCHAR  TMR_1mS_Count;
UCHAR  TMR_1mS_Cnt;
UCHAR  TMR_10mS_Count;
UCHAR  TMR_10mS_Flags;
UCHAR  TMR_10mS_Cnt;
UCHAR  TMR_100mS_Flags;
UCHAR  TMR_100mS_Cnt;
UCHAR  TMR_1sec_Flags;

#bit TMR_1MS_KEYPAD     = TMR_1mS_Flags.0
#bit TMR_1MS_DELAY      = TMR_1mS_Flags.1

#bit TMR_100mS_BLINK    = TMR_100mS_Flags.0
#bit TMR_100MS_COMM_TO  = TMR_100mS_Flags.1
#bit TMR_100MS_LEDS     = TMR_100mS_Flags.2
#bit TMR_100MS_POWER    = TMR_100mS_Flags.3

#bit TMR_1sec_DISP_STAT =  TMR_1sec_Flags.0
#bit TMR_1sec_RSSI      =  TMR_1sec_Flags.1
#bit TMR_1Sec_TEMP      =  TMR_1sec_Flags.2

//============= I/O PIN assignments ============================

#define PLL_LAT  PIN_C1
#define PLL_CLK  PIN_C2
#define PLL_DAT  PIN_C3
#define PLL_LD   PIN_C0

#define CSN       PIN_B2  // FPGA

#define RS485_EN  PIN_D5

//#define POWER_CTL PIN_D4

#define LED1      PIN_B4
#define LED2      PIN_B5

#define D2A_RESET PIN_B3
#define D2A_CSB   PIN_B1
#define D2A_MOSI  PIN_D4
#define D2A_MISO  PIN_D1
#define D2A_SCLK  PIN_D0

#define POWER_EN PIN_D6
#define HILO     PIN_D2
#define STANDBY  PIN_D7

//========== COM1 variables ====================================
#define COM1_RX_LEN 32

UCHAR COM1_rcnt;
UCHAR COM1_rxi;
UCHAR COM1_rxo;
UCHAR COM1_rbuf[COM1_RX_LEN];

#define COMM_INIT       0
#define COMM_WAIT_DLR   1
#define COMM_WAIT_CR    2
#define COMM_DELAY      3


#define WAIT_ACK_TO 20 // 200mS wait for ack

UCHAR comm_state;
UCHAR comm_ridx;
UCHAR comm_buf[80];
UINT  comm_timeout;

//======= misc =================================================

//----------- setup ----------------------------------------
struct {
       UINT  bitrate;
	   UINT  pwr;
       UCHAR mode;
       UCHAR clock_polarity;
       UCHAR data_polarity;
       UCHAR clock_source;
       UCHAR data_source;
       UCHAR internal_pattern;
       UCHAR randomizer;
       UCHAR power_high;
       UCHAR SOQPSK;
       UCHAR power_amp;
       UINT  frequency;
       UINT  power_level;
       UCHAR phase_offset;
       UINT  negative_voltage[3];
       UINT  power_in[21];
       UINT  year;
       UCHAR week;
       UINT  unit_ID;
       UINT  power_low_level;
	   UINT  cot;
	   UINT  rc;
	   UINT  rp;
} setup;

UINT allow_write = 0;
UINT a=2, b=2;

//========== function prototypes ===============================
void set_bitrate(UINT bitrate);
void send_FPGA_command(UCHAR length, UCHAR *data);
UCHAR get_FPGA_register(UCHAR addr, UCHAR *data);
UCHAR read_D2A(UCHAR addr);
UCHAR write_D2A(UCHAR addr, UCHAR din);
void read_setup(void);
void write_setup(void);
void update_all(void);
void update_FPGA(UCHAR addr, UCHAR value);
void FPGA_set_reg0(void);
void FPGA_set_reg6(void);
void FPGA_set_bitrate(void);
void init_system(void);
void power_output(void);

//========== include source files ==============================
#include "AD5312.c"
#include "AD9746.c"
#include "ADF4350.c"
#include "BA1410TX_intr.c"
#include "BA1410TX_serial.c"


//========== functions =========================================

//=============================================================================
//=============================================================================
void send_FPGA_command(UCHAR length, UCHAR *data)
  {
  UCHAR xbyte, cnt;
//  output_high(D2A_SCLK);
//  delay_us(10);
  output_low(CSN);
  delay_us(10);
  while (length--)
    {
    xbyte = *data++;
    for (cnt = 0; cnt < 8; cnt++, xbyte <<= 1)
      {
      if (xbyte & 0x80)
        output_high(D2A_MOSI);
      else
        output_low(D2A_MOSI);
      delay_us(1);
      output_high(D2A_SCLK);
      delay_us(1);
      output_low(D2A_SCLK);
      delay_us(1);
      }
    }
  delay_us(10);
  output_high(CSN);
  }

//=============================================================================
UCHAR get_FPGA_register(UCHAR addr, UCHAR *data)
  {
  UCHAR xbyte, cnt;
  output_low(CSN);
  for (cnt = 0; cnt < 8; cnt++, addr <<= 1)
    {
    if (addr & 0x80)
      output_high(D2A_MOSI);
    else
      output_low(D2A_MOSI);
    delay_us(5);
    output_high(D2A_SCLK);
    delay_us(5);
    output_low(D2A_SCLK);
    delay_us(5);
    }
  for (xbyte = 0, cnt = 0; cnt < 8; cnt++)
    {
    xbyte <<= 1;
    delay_us(5);
    output_high(D2A_SCLK);
    delay_us(3);
    if (input(D2A_MISO))
      {
      xbyte |= 1;
      delay_us(2);
      }
    delay_us(2);
    output_low(D2A_SCLK);
    delay_us(3);
    }
  *data = xbyte;
  output_high(CSN);
  output_low(D2A_SCLK);
  return xbyte;
  }


//=============================================================================
//BR(31:0)=Round(2^32 * (bit rate)/240.0MHz)
ULONG compute_bitrate_coefficient(ULONG bitrate)
  {
  float bitspersec, temp;
  bitspersec = (float)bitrate;
  temp = bitspersec / 240000000.0;
  temp *= 65536.0;
  temp *= 65536.0;
  return (ULONG)temp - 1;
  }

//=============================================================================
void update_FPGA(UCHAR addr, UCHAR value)
  {
  UCHAR buf[3];
  buf[0] = addr;
  buf[1] = value;
  send_FPGA_command(2, buf);
  }

//=============================================================================
void set_bitrate(UINT bitrate)
  {
  UCHAR buf[7];
  ULONG bitf;
  bitf = compute_bitrate_coefficient((ULONG)bitrate * 10000L);
  buf[0] = 2;
  buf[1] = make8(bitf, 0);
  buf[2] = make8(bitf, 1);
  buf[3] = make8(bitf, 2);
  buf[4] = make8(bitf, 3);
  send_FPGA_command(5, buf);
  }

//=============================================================================
void FPGA_set_reg0(void)
  {
  UCHAR buf[8], idx;
  buf[0] = 0;
  buf[1] = setup.mode |
           (setup.clock_polarity << 4) |
           (setup.data_polarity  << 5) |
           (setup.randomizer     << 6) |
           (setup.SOQPSK         << 7);
  send_FPGA_command(2, buf);
  }

//=============================================================================
void FPGA_set_reg6(void)
  {
  UCHAR buf[8], idx;
  buf[0] = 6;
  buf[1] = setup.clock_source |
           (setup.data_source << 1) |
           (setup.internal_pattern << 2);
  send_FPGA_command(2, buf);
  }

//=============================================================================
void FPGA_set_bitrate(void)
  {
  UCHAR buf[8], idx;
  ULONG bitf;
  bitf = compute_bitrate_coefficient((ULONG)setup.bitrate * 10000L);
  buf[0] = 2; buf[1] = make8(bitf, 0);
  send_FPGA_command(2, buf); delay_ms(10);
  buf[0] = 3; buf[1] = make8(bitf, 1);
  send_FPGA_command(2, buf); delay_ms(10);
  buf[0] = 4; buf[1] = make8(bitf, 2);
  send_FPGA_command(2, buf); delay_ms(10);
  buf[0] = 5; buf[1] = make8(bitf, 3);
  send_FPGA_command(2, buf); delay_ms(10);
  }

//=============================================================================
void set_synchronizer_params(void)
  {
  UCHAR buf[8], idx;
  ULONG bitf;
  bitf = compute_bitrate_coefficient((ULONG)setup.bitrate * 10000L);
  buf[0] = setup.mode |
/*           (setup.clock_polarity << 4) |*/
           (setup.data_polarity  << 5) |
           (setup.randomizer     << 6) |
           (setup.SOQPSK         << 7);
  buf[1] = setup.phase_offset;
  buf[2] = make8(bitf, 0);
  buf[3] = make8(bitf, 1);
  buf[4] = make8(bitf, 2);
  buf[5] = make8(bitf, 3);
  buf[6] = setup.clock_source |
           (setup.data_source << 1) |
           (setup.internal_pattern << 2);
  for (idx = 0; idx < 7; idx++)
    {
    update_FPGA(idx, buf[idx]);
    delay_ms(5);
    }
  }

//=============================================================================
void write_int_eeprom(UINT addr, UCHAR *data, UINT size)
  {
  while (size--)
    write_eeprom(addr++, *data++);
  }

//=============================================================================
void read_int_eeprom(UINT addr, UCHAR *data, UINT size)
  {
  while (size--)
    *data++ = read_eeprom(addr++);
  }

//=============================================================================
void write_setup(void)
  {
  if (allow_write == 2975)
    write_int_eeprom(0, &setup, sizeof(setup));
  allow_write = 0;
  }

//=============================================================================
void read_setup(void)
  {
  read_int_eeprom(0, &setup, sizeof(setup));
  if (setup.clock_source == 0xFF || setup.data_source == 0xFF)
    memset(&setup, 0, sizeof(setup));
  }

//--------------------------------------------------------------
void power_output(void)
  {
  UINT power, level;
  if (manual_pos != 0xFFFF)
    {
    if (TMR_100MS_POWER)
      {
      TMR_100MS_POWER = 0;
      set_AD5312(DAC_POS_VOLT, manual_pos);
      set_adc_channel(A2D_POWER); // select forward power input
      delay_us(20);
      power = read_adc();
      }
    return;
    }
    
     if (input(STANDBY) && setup.cot ==0)
    {
    if (setup.pwr == 1)
      {
      output_high(POWER_EN);
      a++;
       if(a==1)
	{
	output_high(POWER_EN);
	delay_ms(50);
	update_all();
	}
	break;
      if(a>60000)
      {
      a=2;
      }
      }  
    else
    	{
      	output_low(POWER_EN);
     	a=0;
    	} 	
    }
    else if(!input(STANDBY) && setup.cot ==0)
      {
       if(setup.pwr == 1)
       	{
         output_low(POWER_EN); 
         a=0;
        }
       else
       {
         output_high(POWER_EN);
          a++;
       }   
       if(a==1)
	{

	output_high(POWER_EN);
	delay_ms(50);
	update_all();
	}
	break;
      if(a>60000)
      {
      a=2;
      }
      BREAK;
      } 
      { 
}


if (!input(STANDBY) && setup.cot ==1)
    {
    if (setup.pwr == 1)
      {
      output_high(POWER_EN);
      b++;
       if(b==1)
	{

	output_high(POWER_EN);
	delay_ms(60);
	update_all();
	}
	break;
      if(b>60000)
      {
      b=2;
      }
      }  
    if(setup.pwr == 0)
    	{
      	output_low(POWER_EN);
     	set_AD5312(DAC_POS_VOLT, 0);
     	b=0;
     	} 	
    }
    else if(input(STANDBY) && setup.cot ==1)
      {
       if(setup.pwr == 1)
       	{
         output_low(POWER_EN); 
         set_AD5312(DAC_POS_VOLT, 0);
         b=0;
        }
       if(setup.pwr == 0)
       {
	       if(b==1)
	       {

         output_high(POWER_EN);
         	delay_ms(60);
			update_all();
          b++;
        }  
       }   
       if(b==1)
	{
	output_high(POWER_EN);
	delay_ms(50);
	update_all();
	}
	break;
      if(a>60000)
      {
      b=2;
      }
      
      } 
      break;
      { 
    }
    
     if (setup.frequency < FREQ_LOW_THRESH)
    set_AD5312(DAC_NEG_VOLT, setup.negative_voltage[0]);
  else if (setup.frequency < FREQ_HIGH_THRESH)
    set_AD5312(DAC_NEG_VOLT, setup.negative_voltage[1]);
  else
    set_AD5312(DAC_NEG_VOLT, setup.negative_voltage[2]);

  set_adc_channel(A2D_POWER); // select forward power input
  delay_us(20);
  power = read_adc();
 
    
if(setup.rc == 1)
{     
	 if (input(HILO) && setup.rp == 1)
	 {
    level = power_level;  //SV
     }  
  else if (input(HILO) && setup.rp == 0)
    {
    level = low_power_level; //VL
    }
    else if(!input(HILO) && setup.rp == 0)
    {
    level = power_level;  //SV
    }
  else
  {
    level = low_power_level;  // VL
  }  
}
	
	if(setup.rc == 0)
	{
	  if (input(HILO) && setup.rp == 0)
	    {
    level = power_level;  //SV 
        }   
  else if (!input(HILO) && setup.rp == 1)
    {
    level = power_level;
    }
    else if(input(HILO) && setup.rp == 1)
    {
    level = low_power_level;
    }
  else
    level = low_power_level; // VL
}



    
  if (power > level + DEADBAND || power < level - DEADBAND)
    {
    if (power < level)
      {
      if (power_control >= 150)
        power_control -= DEADBAND / 2;
      }
    else if (power_control <= 1010)
      {
      power_control += DEADBAND / 2;
      }
    set_AD5312(DAC_POS_VOLT, power_control);
    }	


  }

//=============================================================================
#separate
void delay_mst(UINT delay)
  {
  TMR_1MS_DELAY = 0;
  while (delay)
    {
    if (TMR_1MS_DELAY)
      {
      TMR_1MS_DELAY = 0;
      delay--;
      }
    }
  }

//=============================================================================
void init_io_ports(void)
  {
  output_a(0);
  output_b(0);
  output_c(0);
  output_d(0);
  output_e(0);
  set_tris_a(0b11100001);
  set_tris_b(0b11000001);
  set_tris_c(0b11110001);
  set_tris_d(0b10001110);
  set_tris_e(0b11111011);
  }

//=============================================================================
void init_system(void)
  {

  setup_timer_2(T2_DIV_BY_4,99,10);    // 1.0 ms interrupt

  setup_timer_3(T3_DISABLED | T3_DIV_BY_1);

  setup_timer_4(T4_DIV_BY_4,99,1);     // 100 us interrupt

  setup_timer_5(T5_DISABLED | T5_DIV_BY_1);

  setup_timer_6(T6_DISABLED,0,1);

  init_io_ports();

  setup_adc_ports(sAN0|sAN4|sAN5|sAN6);
  setup_adc(ADC_CLOCK_DIV_16|ADC_TAD_MUL_8);

  setup_comparator(NC_NC_NC_NC);

  COM1_init();
  enable_interrupts(INT_TIMER2);
  enable_interrupts(GLOBAL);
  }


//=============================================================================
void update_all(void)
  {
  UINT freq, bitr;
  freq = setup.frequency;
  delay_ms(5);
  PLL_compute_freq_parameters(freq);
  delay_ms(5);
  PLL_update();
  delay_ms(5);
  FPGA_set_reg0();
  delay_ms(5);
  FPGA_set_reg6();
  delay_ms(5);
  FPGA_set_bitrate();
  bitr = setup.bitrate;
  power_control = 1000;
  }

//=============================================================================
void main(void)
  {
  int16 vouta = 1000;
  init_system(); 
  output_high(D2A_CSB);
  delay_ms(100);
  read_setup();

  power_level = setup.power_in[setup.power_level];
  low_power_level = setup.power_in[setup.power_low_level];
  power_control = 1000;
  power_output();
  

  PLL_initialize();
  delay_ms(50);
  update_all();

  output_high(D2A_RESET);
  delay_ms(50);
  output_low(D2A_RESET);

  COM1_send_str("\r\n");
  COM1_send_str(VERSION);
  COM1_send_str("\r\n");

  set_AD5312(DAC_POS_VOLT, vouta);


  delay_ms(500);
  output_high(POWER_EN);

update_all();
#ignore_warnings 203
  while (1)
    {
    restart_wdt();
    if (TMR_100mS_BLINK)
      {
      TMR_100mS_BLINK = 0;
      output_toggle(LED1);
      delay_us(1);
      }
    comm_handler();
    power_output();
    }
  }



