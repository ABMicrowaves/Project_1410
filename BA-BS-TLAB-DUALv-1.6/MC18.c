#include <MC18.h>
#include "PIC18F24K22_registers.h"

//======= 1mS timer variables ==================================
bit comm_tmr_flag;
UCHAR TMR_1mS_flags, TMR_10mS_flags;
UCHAR TMR_10mS_Cnt;
UCHAR TMR_100mS_Cnt;
UCHAR TMR_100mS_flags;

#bit TMR_1ms_RUN          = TMR_1mS_flags.0
#bit TMR_1ms_ANALOG       = TMR_1mS_flags.1
#bit TMR_1MS_KEYPAD       = TMR_1mS_flags.2

#bit TMR_10mS_ONBOARD_LED = TMR_10mS_flags.1

#bit TMR_100mS_HOLD       = TMR_100mS_flags.0
#bit TMR_100MS_USER_TO    = TMR_100mS_flags.1


//======== variables ===========================================
UCHAR address; // i2c address
UCHAR i2cbuf[32];
UCHAR button_buf[8];

UCHAR command_received = 0;

//====== I/O pin definitions ===================================
#define LED_T  PIN_B2
#define LED_B  PIN_B3

#define BKLT_T PIN_C2
#define BKLT_M PIN_C1

#define SELCOM PIN_C0

#define SCOMM_CLK PIN_C3
#define SCOMM_DAT PIN_C4

UCHAR blink_led = 0;

void update_MCP4261(UINT channel, UINT value);


#include "MC18_kpd.c"
#include "MC18_comm.c"

//===================================================================================
#int_TIMER2
void  TIMER2_isr(void)
  {
  comm_tmr_flag = 1;                             // set communication 1mS timeout flag
  TMR_1mS_flags = 0xFF;                          // set 1ms timing flags
  if (++TMR_10mS_Cnt >= 10)                      // if 10mS passed then
    {
    TMR_10mS_Cnt = 0;                            // reset 10 ms counter
    TMR_10mS_flags = 0xFF;                       // and set 10mS flags
    if (++TMR_100mS_Cnt >= 10)                   // if 100mS passed
      {                                          // then
      TMR_100mS_Cnt = 0;                         // reset 100ms counter
      TMR_100mS_flags = 0xFF;                    // and set 100mS flags
      }
    }
  }


//==================================================================================
UCHAR i2c_count, i2c_rw, i2c_states[32], i2cx = 0;

#INT_SSP
void ssp_interrupt(void)
  {
  UCHAR incoming, state, x;

  state = i2c_isr_state();
  i2c_states[i2cx++] = state;
  if (!state || state == 0x80)                    //Master is sending data
    {
    incoming = i2c_read();
    address = 0;
    if (incoming == 0xA1) // read
      {
      i2c_count = 0;
      i2c_rw = 1;
      i2c_write(button_buf[address++]);
      button_buf[address++] = 0;
      }
    else
      {
      i2c_rw = 0; // this is a write op
      }
    }
  else if (state > 0x80)
    {
    i2c_write(button_buf[address]);
    button_buf[address++] = 0;
    }
  else if (state < 0x80)
    {
    i2cbuf[address++] = i2c_read();
    if (address > 3)
      command_received = 1;
    x++;
    x++;
    }
  x++;
  x++;
  }

/*
state = i2c_isr_state();
if((state== 0 ) || (state== 0x80))
        i@c_read();
if(state >= 0x80)
         i2c_write(send_buffer[state - 0x80]);
else if(state > 0)
         rcv_buffer[state - 1] = i2c_read();
*/

void init_i2c_slave(void)
  {
  enable_interrupts(INT_SSP);
  }

//==================================================================================
// MCP4261 driver
void update_MCP4261(UINT channel, UINT value)
  {
  UCHAR idx;
  UINT dataout;
  dataout = channel << 12;
  output_low(PIN_B0);
  dataout |= (UINT)value;
  output_low(PIN_B4); // clock
  output_low(PIN_B5); // CS
  for (idx = 0; idx < 16; idx++)
    {
    if (dataout & 0x8000)
      output_high(PIN_C5);
    else
      output_low(PIN_C5);
    output_high(PIN_B4); // clock
    delay_us(1);
    output_low(PIN_B4); // clock
    dataout <<= 1;
    }
  delay_us(10);
  output_high(PIN_B5); // CS
  }

//==================================================================================
void init_system(void)
  {
  set_tris_a(0b11101111);
  set_tris_b(0b11000010);
  set_tris_c(0b11111000);
  output_high(SELCOM); // select RS232 continuously
  setup_adc_ports(NO_ANALOGS);
  setup_timer_2(T2_DIV_BY_1,249,16);    //62.5 us overflow, 1.0 ms interrupt

  setup_timer_3(T3_DISABLED | T3_DIV_BY_1);
  setup_timer_4(T4_DISABLED,0,1);
  setup_timer_5(T5_DISABLED | T5_DIV_BY_1);
  setup_timer_6(T6_DISABLED,0,1);

  setup_comparator(NC_NC_NC_NC);// This device COMP currently not supported by the PICWizard

  init_i2c_slave();

  enable_interrupts(INT_TIMER2);
  enable_interrupts(GLOBAL);
  }

void main(void)
  {
  ULONG delay;
  UCHAR contrast = 0;
  init_system();
  output_high(LED_T);
  output_low(LED_B);
  init_buttons();
  button_buf[0] = 0;
  button_buf[1] = 0;
  button_buf[2] = 0;
//  init_comm1();
  while (TRUE)
    {
//    handle_comm();
    scan_buttons();
    if (command_received)
      parse_command();
    if (!button_buf[1] && btnc)
      {
      button_buf[1] = get_button();
      button_buf[2] = button_buf[1];
      button_buf[3] = button_buf[1];
      }
      
    if (++delay > 30000)
      {
      delay = 0;
//      output_toggle(LED_T);
//      output_toggle(LED_B);
      }
    }
  }
