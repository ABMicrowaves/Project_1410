#include <24FJ128GB110.h>
#device pass_strings=in_ram
#device  ICD=2
#device ADC=10

#FUSES NOWDT
#FUSES WPOSTS16               //Watch Dog Timer PostScalar 1:16
#FUSES ICSP2                  //ICD uses PGC2/PGD2 pins
#FUSES DEBUG                  //Debug mode for use with ICD
#FUSES NOJTAG                 //JTAG disabled
#FUSES NOIOL1WAY              //Allows multiple reconfigurations of peripheral pins
#FUSES OSCIO                  //OSC2 is general purpose output
#FUSES CKSFSM                 //Clock Switching is enabled, fail Safe clock monitor is enabled
#FUSES FRC_PLL                //Internal Fast RC oscillator with PLL
#FUSES PLL1                   //No PLL PreScaler
#FUSES NOOSCIO                //RC13 & RC14 are general purpose I/O pins

#use delay(clock=32000000)

#include "BABSTLAB2_io.h"

#PIN_SELECT U1TX=RS232TX
#PIN_SELECT U1RX=RS232RX
#PIN_SELECT U2TX=MAINTX
#PIN_SELECT U2RX=MAINRX

#use rs232(UART1,baud=38400,parity=N,bits=8,stream=PORT1)
#use rs232(UART2,baud=38400,parity=N,bits=8,stream=PORT2)
/*
#define SMALLPIC_CLK PIN_D9
#define SMALLPIC_DAT PIN_C13
*/
//#use I2C(master, scl=PIN_D9, sda=PIN_C13, force_sw, fast=400000)

#define UINT  unsigned int16
#define SINT  signed int16
#define UCHAR unsigned int8
#define ICHAR signed int8
#define bit   int1
#define ULONG unsigned int32
#define SLONG signed int32

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)
#use fast_io(f)
#use fast_io(g)


