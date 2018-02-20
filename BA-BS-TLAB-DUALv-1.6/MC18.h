#include <18F24K22.h>
#device adc=10

#FUSES NOWDT                   //No Watch Dog Timer
#FUSES WDT128                  //Watch Dog Timer uses 1:128 Postscale
#FUSES INTRC_IO                //Internal RC Osc, no CLKOUT
#FUSES NOBROWNOUT              //No brownout reset
#FUSES WDT_NOSLEEP             //Watch Dog Timer, disabled during SLEEP
#FUSES NOLVP                   //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                 //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#fuses NOPUT

#use delay(int=16000000,RESTART_WDT)
#use I2C(slave,sda=PIN_C4,scl=PIN_C3, address=0xa0,mask=0xFE, FORCE_HW)


#use fast_io(a)
#use fast_io(b)
#use fast_io(c)

#define UINT  int16
#define SINT  signed int16
#define UCHAR int8
#define ICHAR signed int8
#define bit   int1
#define ULONG int32
#define SLONG signed int32

