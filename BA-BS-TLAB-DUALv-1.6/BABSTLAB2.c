 /*
 * BA-BS-TLAB-DUAL functionality:
 * 2 x Synchronizer through J2 and J7
 * RS232 to PC
 * RS232 to DownConverter
 * main LCD - user interface
 * secondary LCD - RSSI from DownConverter
 * up to 1.5 - new pcb
 * UP TO 1.6 - NEW BITSYNCHRONIZER
 */


#include "BABSTLAB2.h"

#include "24FJ128GB110_registers.h"

#define VERSION "BA-BS-TLAB-DUAL V1.6"

#include <stdlib.h>

//----------- setup ----------------------------------------
typedef struct {
       UINT  bitrate;
       UCHAR loop_bw;
       UCHAR sp1;
       UCHAR input_enc;
       UCHAR random_length;
       UCHAR input_polarity;
       UCHAR sp2;
       UCHAR output_clock_phase;
       UCHAR filter_select;
       UCHAR input_select;
       UCHAR sp3;
       UCHAR impedance;
} SETUP_REC;

UCHAR spare[50];

SETUP_REC setup[2];

typedef struct {
       UCHAR id;
       UCHAR year;
       UCHAR week;
} UNIT_IDENT;

UNIT_IDENT unit_id;

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
#bit TMR_1mS_SLAVE      = TMR_1mS_Flags.2

#bit TMR_100MS_COMM_TO  = TMR_100mS_Flags.0

#bit TMR_1sec_DISP_STAT =  TMR_1sec_Flags.0
#bit TMR_1sec_RSSI      =  TMR_1sec_Flags.1
#bit TMR_1Sec_TEMP      =  TMR_1sec_Flags.2



//------- COM1 variables -----------------------------------

#define PC_COM_BUF_SIZE 128

UCHAR comm_buf[PC_COM_BUF_SIZE];
UCHAR comm_buf2[PC_COM_BUF_SIZE];
UCHAR comm_state;
#define COM1_RX_LEN 128

UCHAR COM1_rcnt;
UCHAR COM1_rxi;
UCHAR COM1_rxo;
UCHAR COM1_rbuf[COM1_RX_LEN];

//UINT up_char;

//UINT  packet_idx;
UINT  comm_ptr, comm_ridx, comm_timeout;

UINT  selected_channel = 0;
UCHAR FPGA_bits[2];

//---------- prototypes -----------------------------------
void CAL_attn2(UCHAR onoff, UCHAR level);
void CAL_attn3(UCHAR onoff, UCHAR level);
#separate
void PLL1_calibrate(UCHAR onoff);
UCHAR main_code(void);
void put_keypad(UINT key);
void update_all(void);
void store_setup(void);
void set_signal_lock_leds(void);


#include "BABSTLAB2_attn.c"
#include "BABSTLAB2_i2c.c"
#include "BABSTLAB2_sync.c"
#include "BABSTLAB2_intr.c"
#include "BABSTLAB2_slave.c"
#include "BABSTLAB2_serial.c"
#include "BABSTLAB2_lcd.c"
#include "BABSTLAB2_ui.c"
#include "BABSTLAB2_app.c"


//--------------------------------------------------------------
void store_setup(void)
  {
  UINT e,w;
  e = getenv("FLASH_ERASE_SIZE");
  w = getenv("FLASH_WRITE_SIZE");
  write_program_memory(0x10000L, &setup[0].bitrate, w); // write code to Flash
  write_program_memory(0x10100L, &setup[1].bitrate, w); // write code to Flash
  write_program_memory(0x12800L, &unit_id.id,  w); // write code to Flash
  write_program_memory(0x10300L, &setup[0].random_length, w); // write code to Flash
  write_program_memory(0x10400L, &setup[1].random_length, w); // write code to Flash
  write_program_memory(0x10500L, &setup[0].loop_bw, w); // write code to Flash
  write_program_memory(0x10600L, &setup[1].loop_bw, w); // write code to Flash
  write_program_memory(0x10700L, &setup[0].output_clock_phase, w); // write code to Flash
  write_program_memory(0x10800L, &setup[1].output_clock_phase, w); // write code to Flash
  write_program_memory(0x10900L, &setup[0].input_polarity, w); // write code to Flash
  write_program_memory(0x11000L, &setup[1].input_polarity, w); // write code to Flash
 // write_program_memory(0x12010L, &setup[0].impedance, w); // write code to Flash
 // write_program_memory(0x12120L, &setup[1].impedance, w); // write code to Flash
  }

//--------------------------------------------------------------
void load_setup(void)
  {
  read_program_memory(0x10000L, &setup[0].bitrate, sizeof(setup[0])); // write code to Flash
  read_program_memory(0x10100L, &setup[1].bitrate, sizeof(setup[1])); // write code to Flash
  read_program_memory(0x12800L, &unit_id.id,  2); // write code to Flash
//  read_program_memory(0x10300L, &setup[0].random_length, 1); // write code to Flash
//  read_program_memory(0x10400L, &setup[1].random_length, 1); // write code to Flash
 // read_program_memory(0x10500L, &setup[0].loop_bw, sizeof(setup[0])); // write code to Flash
 // read_program_memory(0x10600L, &setup[1].loop_bw, sizeof(setup[1])); // write code to Flash
 // read_program_memory(0x10700L, &setup[0].output_clock_phase, sizeof(setup[0])); // write code to Flash
 // read_program_memory(0x10800L, &setup[1].output_clock_phase, sizeof(setup[1])); // write code to Flash
//  read_program_memory(0x10900L, &setup[0].input_polarity, sizeof(setup[0])); // write code to Flash
//  read_program_memory(0x11000L, &setup[1].input_polarity, sizeof(setup[1])); // write code to Flash
 // read_program_memory(0x11010L, &setup[0].impedance, sizeof(setup[0])); // write code to Flash
 // read_program_memory(0x11020L, &setup[1].impedance, sizeof(setup[1])); // write code to Flash
   if (setup[0].bitrate == 0xFFFF && setup[0].loop_bw == 0xFF) // uninitialized?
    {
    memset(&setup[0], 0, sizeof(setup));
    setup[0].bitrate = 100;
    setup[1].bitrate = 100;
    store_setup();
    }
  }

//--------------------------------------------------------------
void init_ports(void)
  {
  output_a(0);
  output_b(0);
  output_c(0);
  output_d(0);
  output_e(0);
  output_f(0);
  output_g(0);
  set_tris_a(0x1000);
  set_tris_b(0x0000);
  set_tris_c(0);
  set_tris_d(0x0004);
  set_tris_e(0x0002);
  set_tris_f(0);
  set_tris_g(0);
  }

//--------------------------------------------------------------
void init_system(void)
  {
  init_ports();
  setup_adc_ports(sAN0 | sAN1 | sAN2 | sAN3);
  setup_adc(ADC_CLOCK_DIV_8 | ADC_TAD_MUL_16);
  setup_timer2(TMR_INTERNAL |TMR_DIV_BY_64 ,250);
  setup_timer4(TMR_DISABLED |TMR_DIV_BY_1 ,0);
  setup_timer3(TMR_DISABLED |TMR_DIV_BY_1 ,0);
  setup_timer5(TMR_DISABLED |TMR_DIV_BY_1 ,0);
  enable_interrupts(INT_TIMER2);

  enable_interrupts(INTR_GLOBAL);

  output_high(LCD_RESET);

  COM1_init();
  }

//--------------------------------------------------------------
void main(void)
  {
  UINT blink, count = 0, np = 0;
  UCHAR nx = 0, ny = 2;

  init_system();
  
  init_i2c();

  TLCD_init();
  MLCD_init();

  load_setup();

  output_high(SYNC1_PWR_EN);
  output_high(SYNC2_PWR_EN);
  output_high(LED_PWR_EN);

  delay_ms(250);

  update_all();

  send_two_lines();
  COM1_send_str(VERSION);
  send_two_lines();

  user_interface();

  set_selected_channel_led();

#ignore_warnings 203
  while (1)
    {
    restart_wdt();
    comm_handler();
    slave_session();

      if (!++blink)
        {
        output_toggle(LED1);
        output_toggle(LED2);
        output_toggle(LED3);
        output_toggle(LED4);
        TLCD_clearSCR();
        MLCD_clearSCR();

//        TLCD_position(2, 1);
        TLCD_home();
//        TLCD_clearEOL();
        TLCD_DspStr("QWERTY");
        OUT_init();
        OUT_string(" NUMBER ");
        OUT_integer(count++, 'U');
        if (np)
          TLCD_position(nx, ny);
        TLCD_DspStr(out_buffer);

        /*
        MLCD_position(0,0);
        MLCD_DspStr("xxxxxxxx");
        MLCD_position(0,1);
        MLCD_DspStr("  ooooo123456789");
        */
        display_rssi_columns(6, 9);
        }
    }
  return;
  }

