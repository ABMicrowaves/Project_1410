#word WREG0 = 0x000

#word WREG1 = 0x002

#word WREG2 = 0x004

#word WREG3 = 0x006

#word WREG4 = 0x008

#word WREG5 = 0x00A

#word WREG6 = 0x00C

#word WREG7 = 0x00E

#word WREG8 = 0x010

#word WREG9 = 0x012

#word WREG10 = 0x014

#word WREG11 = 0x016

#word WREG12 = 0x018

#word WREG13 = 0x01A

#word WREG14 = 0x01C

#word WREG15 = 0x01E

#word SPLIM = 0x020

#word PCL = 0x02E

#word PCH = 0x030

#word TBLPAG = 0x032

#word PSVPAG = 0x034

#word RCOUNT = 0x036

union  {
      struct {
         unsigned int C:1;
         unsigned int Z:1;
         unsigned int OV:1;
         unsigned int N:1;
         unsigned int RA:1;
         unsigned int IPL0:1;
         unsigned int IPL1:1;
         unsigned int IPL2:1;
         unsigned int DC:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int IPL:3;
         unsigned int :1;
      };
} SR;
#word SR = 0x042

struct  {
   unsigned int :2;
   unsigned int PSV:1;
   unsigned int IPL3:1;
} CORCON;
#word CORCON = 0x044

#word DISICNT = 0x052

struct  {
   unsigned int CN0PDE:1;
   unsigned int CN1PDE:1;
   unsigned int CN2PDE:1;
   unsigned int CN3PDE:1;
   unsigned int CN4PDE:1;
   unsigned int CN5PDE:1;
   unsigned int CN6PDE:1;
   unsigned int CN7PDE:1;
   unsigned int CN8PDE:1;
   unsigned int CN9PDE:1;
   unsigned int CN10PDE:1;
   unsigned int CN11PDE:1;
   unsigned int CN12PDE:1;
   unsigned int CN13PDE:1;
   unsigned int CN14PDE:1;
   unsigned int CN15PDE:1;
} CNPD1;
#word CNPD1 = 0x054

struct  {
   unsigned int CN16PDE:1;
   unsigned int CN17PDE:1;
   unsigned int CN18PDE:1;
   unsigned int CN19PDE:1;
   unsigned int CN20PDE:1;
   unsigned int CN21PDE:1;
   unsigned int CN22PDE:1;
   unsigned int CN23PDE:1;
   unsigned int CN24PDE:1;
   unsigned int CN25PDE:1;
   unsigned int CN26PDE:1;
   unsigned int CN27PDE:1;
   unsigned int CN28PDE:1;
   unsigned int CN29PDE:1;
   unsigned int CN30PDE:1;
   unsigned int CN31PDE:1;
} CNPD2;
#word CNPD2 = 0x056

struct  {
   unsigned int CN32PDE:1;
   unsigned int CN33PDE:1;
   unsigned int CN34PDE:1;
   unsigned int CN35PDE:1;
   unsigned int CN36PDE:1;
   unsigned int CN37PDE:1;
   unsigned int CN38PDE:1;
   unsigned int CN39PDE:1;
   unsigned int CN40PDE:1;
   unsigned int CN41PDE:1;
   unsigned int CN42PDE:1;
   unsigned int CN43PDE:1;
   unsigned int CN44PDE:1;
   unsigned int CN45PDE:1;
   unsigned int CN46PDE:1;
   unsigned int CN47PDE:1;
} CNPD3;
#word CNPD3 = 0x058

struct  {
   unsigned int CN48PDE:1;
   unsigned int CN49PDE:1;
   unsigned int CN50PDE:1;
   unsigned int CN51PDE:1;
   unsigned int CN52PDE:1;
   unsigned int CN53PDE:1;
   unsigned int CN54PDE:1;
   unsigned int CN55PDE:1;
   unsigned int CN56PDE:1;
   unsigned int CN57PDE:1;
   unsigned int CN58PDE:1;
   unsigned int CN59PDE:1;
   unsigned int CN60PDE:1;
   unsigned int CN61PDE:1;
   unsigned int CN62PDE:1;
   unsigned int CN63PDE:1;
} CNPD4;
#word CNPD4 = 0x05A

struct  {
   unsigned int CN64PDE:1;
   unsigned int CN65PDE:1;
   unsigned int CN66PDE:1;
   unsigned int CN67PDE:1;
   unsigned int CN68PDE:1;
   unsigned int CN69PDE:1;
   unsigned int CN70PDE:1;
   unsigned int CN71PDE:1;
   unsigned int :2;
   unsigned int CN74PDE:1;
   unsigned int CN75PDE:1;
   unsigned int CN76PDE:1;
   unsigned int CN77PDE:1;
   unsigned int CN78PDE:1;
   unsigned int CN79PDE:1;
} CNPD5;
#word CNPD5 = 0x05C

struct  {
   unsigned int CN80PDE:1;
   unsigned int CN81PDE:1;
   unsigned int CN82PDE:1;
} CNPD6;
#word CNPD6 = 0x05E

struct  {
   unsigned int CN0IE:1;
   unsigned int CN1IE:1;
   unsigned int CN2IE:1;
   unsigned int CN3IE:1;
   unsigned int CN4IE:1;
   unsigned int CN5IE:1;
   unsigned int CN6IE:1;
   unsigned int CN7IE:1;
   unsigned int CN8IE:1;
   unsigned int CN9IE:1;
   unsigned int CN10IE:1;
   unsigned int CN11IE:1;
   unsigned int CN12IE:1;
   unsigned int CN13IE:1;
   unsigned int CN14IE:1;
   unsigned int CN15IE:1;
} CNEN1;
#word CNEN1 = 0x060

struct  {
   unsigned int CN16IE:1;
   unsigned int CN17IE:1;
   unsigned int CN18IE:1;
   unsigned int CN19IE:1;
   unsigned int CN20IE:1;
   unsigned int CN21IE:1;
   unsigned int CN22IE:1;
   unsigned int CN23IE:1;
   unsigned int CN24IE:1;
   unsigned int CN25IE:1;
   unsigned int CN26IE:1;
   unsigned int CN27IE:1;
   unsigned int CN28IE:1;
   unsigned int CN29IE:1;
   unsigned int CN30IE:1;
   unsigned int CN31IE:1;
} CNEN2;
#word CNEN2 = 0x062

struct  {
   unsigned int CN32IE:1;
   unsigned int CN33IE:1;
   unsigned int CN34IE:1;
   unsigned int CN35IE:1;
   unsigned int CN36IE:1;
   unsigned int CN37IE:1;
   unsigned int CN38IE:1;
   unsigned int CN39IE:1;
   unsigned int CN40IE:1;
   unsigned int CN41IE:1;
   unsigned int CN42IE:1;
   unsigned int CN43IE:1;
   unsigned int CN44IE:1;
   unsigned int CN45IE:1;
   unsigned int CN46IE:1;
   unsigned int CN47IE:1;
} CNEN3;
#word CNEN3 = 0x064

struct  {
   unsigned int CN48IE:1;
   unsigned int CN49IE:1;
   unsigned int CN50IE:1;
   unsigned int CN51IE:1;
   unsigned int CN52IE:1;
   unsigned int CN53IE:1;
   unsigned int CN54IE:1;
   unsigned int CN55IE:1;
   unsigned int CN56IE:1;
   unsigned int CN57IE:1;
   unsigned int CN58IE:1;
   unsigned int CN59IE:1;
   unsigned int CN60IE:1;
   unsigned int CN61IE:1;
   unsigned int CN62IE:1;
   unsigned int CN63IE:1;
} CNEN4;
#word CNEN4 = 0x066

struct  {
   unsigned int CN64IE:1;
   unsigned int CN65IE:1;
   unsigned int CN66IE:1;
   unsigned int CN67IE:1;
   unsigned int CN68IE:1;
   unsigned int CN69IE:1;
   unsigned int CN70IE:1;
   unsigned int CN71IE:1;
   unsigned int :2;
   unsigned int CN74IE:1;
   unsigned int CN75IE:1;
   unsigned int CN76IE:1;
   unsigned int CN77IE:1;
   unsigned int CN78IE:1;
   unsigned int CN79IE:1;
} CNEN5;
#word CNEN5 = 0x068

struct  {
   unsigned int CN80IE:1;
   unsigned int CN81IE:1;
   unsigned int CN82IE:1;
} CNEN6;
#word CNEN6 = 0x06A

struct  {
   unsigned int CN0PUE:1;
   unsigned int CN1PUE:1;
   unsigned int CN2PUE:1;
   unsigned int CN3PUE:1;
   unsigned int CN4PUE:1;
   unsigned int CN5PUE:1;
   unsigned int CN6PUE:1;
   unsigned int CN7PUE:1;
   unsigned int CN8PUE:1;
   unsigned int CN9PUE:1;
   unsigned int CN10PUE:1;
   unsigned int CN11PUE:1;
   unsigned int CN12PUE:1;
   unsigned int CN13PUE:1;
   unsigned int CN14PUE:1;
   unsigned int CN15PUE:1;
} CNPU1;
#word CNPU1 = 0x06C

struct  {
   unsigned int CN16PUE:1;
   unsigned int CN17PUE:1;
   unsigned int CN18PUE:1;
   unsigned int CN19PUE:1;
   unsigned int CN20PUE:1;
   unsigned int CN21PUE:1;
   unsigned int CN22PUE:1;
   unsigned int CN23PUE:1;
   unsigned int CN24PUE:1;
   unsigned int CN25PUE:1;
   unsigned int CN26PUE:1;
   unsigned int CN27PUE:1;
   unsigned int CN28PUE:1;
   unsigned int CN29PUE:1;
   unsigned int CN30PUE:1;
   unsigned int CN31PUE:1;
} CNPU2;
#word CNPU2 = 0x06E

struct  {
   unsigned int CN32PUE:1;
   unsigned int CN33PUE:1;
   unsigned int CN34PUE:1;
   unsigned int CN35PUE:1;
   unsigned int CN36PUE:1;
   unsigned int CN37PUE:1;
   unsigned int CN38PUE:1;
   unsigned int CN39PUE:1;
   unsigned int CN40PUE:1;
   unsigned int CN41PUE:1;
   unsigned int CN42PUE:1;
   unsigned int CN43PUE:1;
   unsigned int CN44PUE:1;
   unsigned int CN45PUE:1;
   unsigned int CN46PUE:1;
   unsigned int CN47PUE:1;
} CNPU3;
#word CNPU3 = 0x070

struct  {
   unsigned int CN48PUE:1;
   unsigned int CN49PUE:1;
   unsigned int CN50PUE:1;
   unsigned int CN51PUE:1;
   unsigned int CN52PUE:1;
   unsigned int CN53PUE:1;
   unsigned int CN54PUE:1;
   unsigned int CN55PUE:1;
   unsigned int CN56PUE:1;
   unsigned int CN57PUE:1;
   unsigned int CN58PUE:1;
   unsigned int CN59PUE:1;
   unsigned int CN60PUE:1;
   unsigned int CN61PUE:1;
   unsigned int CN62PUE:1;
   unsigned int CN63PUE:1;
} CNPU4;
#word CNPU4 = 0x072

struct  {
   unsigned int CN64PUE:1;
   unsigned int CN65PUE:1;
   unsigned int CN66PUE:1;
   unsigned int CN67PUE:1;
   unsigned int CN68PUE:1;
   unsigned int CN69PUE:1;
   unsigned int CN70PUE:1;
   unsigned int CN71PUE:1;
   unsigned int :2;
   unsigned int CN74PUE:1;
   unsigned int CN75PUE:1;
   unsigned int CN76PUE:1;
   unsigned int CN77PUE:1;
   unsigned int CN78PUE:1;
   unsigned int CN79PUE:1;
} CNPU5;
#word CNPU5 = 0x074

struct  {
   unsigned int CN80PUE:1;
   unsigned int CN81PUE:1;
   unsigned int CN82PUE:1;
} CNPU6;
#word CNPU6 = 0x076

struct  {
   unsigned int :1;
   unsigned int OSCFAIL:1;
   unsigned int STKERR:1;
   unsigned int ADDRERR:1;
   unsigned int MATHERR:1;
   unsigned int :10;
   unsigned int NSTDIS:1;
} INTCON1;
#word INTCON1 = 0x080

struct  {
   unsigned int INT0EP:1;
   unsigned int INT1EP:1;
   unsigned int INT2EP:1;
   unsigned int INT3EP:1;
   unsigned int INT4EP:1;
   unsigned int :9;
   unsigned int DISI:1;
   unsigned int ALTIVT:1;
} INTCON2;
#word INTCON2 = 0x082

struct  {
   unsigned int INT0IF:1;
   unsigned int IC1IF:1;
   unsigned int OC1IF:1;
   unsigned int T1IF:1;
   unsigned int :1;
   unsigned int IC2IF:1;
   unsigned int OC2IF:1;
   unsigned int T2IF:1;
   unsigned int T3IF:1;
   unsigned int SPF1IF:1;
   unsigned int SPI1IF:1;
   unsigned int U1RXIF:1;
   unsigned int U1TXIF:1;
   unsigned int AD1IF:1;
} IFS0;
#word IFS0 = 0x084

struct  {
   unsigned int SI2C1IF:1;
   unsigned int MI2C1IF:1;
   unsigned int CMIF:1;
   unsigned int CNIF:1;
   unsigned int INT1IF:1;
   unsigned int :1;
   unsigned int IC7IF:1;
   unsigned int IC8IF:1;
   unsigned int :1;
   unsigned int OC3IF:1;
   unsigned int OC4IF:1;
   unsigned int T4IF:1;
   unsigned int T5IF:1;
   unsigned int INT2IF:1;
   unsigned int U2RXIF:1;
   unsigned int U2TXIF:1;
} IFS1;
#word IFS1 = 0x086

struct  {
   unsigned int SPF2IF:1;
   unsigned int SPI2IF:1;
   unsigned int :3;
   unsigned int IC3IF:1;
   unsigned int IC4IF:1;
   unsigned int IC5IF:1;
   unsigned int IC6IF:1;
   unsigned int OC5IF:1;
   unsigned int OC6IF:1;
   unsigned int OC7IF:1;
   unsigned int OC8IF:1;
   unsigned int PMPIF:1;
} IFS2;
#word IFS2 = 0x088

struct  {
   unsigned int :1;
   unsigned int SI2C2IF:1;
   unsigned int MI2C2IF:1;
   unsigned int :2;
   unsigned int INT3IF:1;
   unsigned int INT4IF:1;
   unsigned int :7;
   unsigned int RTCIF:1;
} IFS3;
#word IFS3 = 0x08A

struct  {
   unsigned int :1;
   unsigned int U1ERIF:1;
   unsigned int U2ERIF:1;
   unsigned int CRCIF:1;
   unsigned int :4;
   unsigned int LVDIF:1;
   unsigned int :4;
   unsigned int CTMUIF:1;
} IFS4;
#word IFS4 = 0x08C

struct  {
   unsigned int :1;
   unsigned int U3ERIF:1;
   unsigned int U3RXIF:1;
   unsigned int U3TXIF:1;
   unsigned int SI2C3IF:1;
   unsigned int MI2C3IF:1;
   unsigned int USB1IF:1;
   unsigned int U4ERIF:1;
   unsigned int U4RXIF:1;
   unsigned int U4TXIF:1;
   unsigned int SPF3IF:1;
   unsigned int SPI3IF:1;
   unsigned int OC9IF:1;
   unsigned int IC9IF:1;
} IFS5;
#word IFS5 = 0x08E

struct  {
   unsigned int INT0IE:1;
   unsigned int IC1IE:1;
   unsigned int OC1IE:1;
   unsigned int T1IE:1;
   unsigned int :1;
   unsigned int IC2IE:1;
   unsigned int OC2IE:1;
   unsigned int T2IE:1;
   unsigned int T3IE:1;
   unsigned int SPF1IE:1;
   unsigned int SPI1IE:1;
   unsigned int U1RXIE:1;
   unsigned int U1TXIE:1;
   unsigned int AD1IE:1;
} IEC0;
#word IEC0 = 0x094

struct  {
   unsigned int SI2C1IE:1;
   unsigned int MI2C1IE:1;
   unsigned int CMIE:1;
   unsigned int CNIE:1;
   unsigned int INT1IE:1;
   unsigned int :1;
   unsigned int IC7IE:1;
   unsigned int IC8IE:1;
   unsigned int :1;
   unsigned int OC3IE:1;
   unsigned int OC4IE:1;
   unsigned int T4IE:1;
   unsigned int T5IE:1;
   unsigned int INT2IE:1;
   unsigned int U2RXIE:1;
   unsigned int U2TXIE:1;
} IEC1;
#word IEC1 = 0x096

struct  {
   unsigned int SPF2IE:1;
   unsigned int SPI2IE:1;
   unsigned int :3;
   unsigned int IC3IE:1;
   unsigned int IC4IE:1;
   unsigned int IC5IE:1;
   unsigned int IC6IE:1;
   unsigned int OC5IE:1;
   unsigned int OC6IE:1;
   unsigned int OC7IE:1;
   unsigned int OC8IE:1;
   unsigned int PMPIE:1;
} IEC2;
#word IEC2 = 0x098

struct  {
   unsigned int :1;
   unsigned int SI2C2IE:1;
   unsigned int MI2C2IE:1;
   unsigned int :2;
   unsigned int INT3IE:1;
   unsigned int INT4IE:1;
   unsigned int :7;
   unsigned int RTCIE:1;
} IEC3;
#word IEC3 = 0x09A

struct  {
   unsigned int :1;
   unsigned int U1ERIE:1;
   unsigned int U2ERIE:1;
   unsigned int CRCIE:1;
   unsigned int :4;
   unsigned int LVDIE:1;
   unsigned int :4;
   unsigned int CTMUIE:1;
} IEC4;
#word IEC4 = 0x09C

struct  {
   unsigned int :1;
   unsigned int U3ERIE:1;
   unsigned int U3RXIE:1;
   unsigned int U3TXIE:1;
   unsigned int SI2C3IE:1;
   unsigned int MI2C3IE:1;
   unsigned int USB1IE:1;
   unsigned int U4ERIE:1;
   unsigned int U4RXIE:1;
   unsigned int U4TXIE:1;
   unsigned int SPF3IE:1;
   unsigned int SPI3IE:1;
   unsigned int OC9IE:1;
   unsigned int IC9IE:1;
} IEC5;
#word IEC5 = 0x09E

union  {
      struct {
         unsigned int INT0IP0:1;
         unsigned int INT0IP1:1;
         unsigned int INT0IP2:1;
         unsigned int :1;
         unsigned int IC1IP0:1;
         unsigned int IC1IP1:1;
         unsigned int IC1IP2:1;
         unsigned int :1;
         unsigned int OC1IP0:1;
         unsigned int OC1IP1:1;
         unsigned int OC1IP2:1;
         unsigned int :1;
         unsigned int T1IP0:1;
         unsigned int T1IP1:1;
         unsigned int T1IP2:1;
      };
      struct {
         unsigned int INT0IP:3;
         unsigned int :1;
         unsigned int IC1IP:3;
         unsigned int :1;
         unsigned int OC1IP:3;
         unsigned int :1;
         unsigned int T1IP:3;
      };
} IPC0;
#word IPC0 = 0x0A4

union  {
      struct {
         unsigned int :4;
         unsigned int IC2IP0:1;
         unsigned int IC2IP1:1;
         unsigned int IC2IP2:1;
         unsigned int :1;
         unsigned int OC2IP0:1;
         unsigned int OC2IP1:1;
         unsigned int OC2IP2:1;
         unsigned int :1;
         unsigned int T2IP0:1;
         unsigned int T2IP1:1;
         unsigned int T2IP2:1;
      };
      struct {
         unsigned int :4;
         unsigned int IC2IP:3;
         unsigned int :1;
         unsigned int OC2IP:3;
         unsigned int :1;
         unsigned int T2IP:3;
      };
} IPC1;
#word IPC1 = 0x0A6

union  {
      struct {
         unsigned int T3IP0:1;
         unsigned int T3IP1:1;
         unsigned int T3IP2:1;
         unsigned int :1;
         unsigned int SPF1IP0:1;
         unsigned int SPF1IP1:1;
         unsigned int SPF1IP2:1;
         unsigned int :1;
         unsigned int SPI1IP0:1;
         unsigned int SPI1IP1:1;
         unsigned int SPI1IP2:1;
         unsigned int :1;
         unsigned int U1RXIP0:1;
         unsigned int U1RXIP1:1;
         unsigned int U1RXIP2:1;
      };
      struct {
         unsigned int T3IP:3;
         unsigned int :1;
         unsigned int SPF1IP:3;
         unsigned int :1;
         unsigned int SPI1IP:3;
         unsigned int :1;
         unsigned int U1RXIP:3;
      };
} IPC2;
#word IPC2 = 0x0A8

union  {
      struct {
         unsigned int U1TXIP0:1;
         unsigned int U1TXIP1:1;
         unsigned int U1TXIP2:1;
         unsigned int :1;
         unsigned int AD1IP0:1;
         unsigned int AD1IP1:1;
         unsigned int AD1IP2:1;
      };
      struct {
         unsigned int U1TXIP:3;
         unsigned int :1;
         unsigned int AD1IP:3;
      };
} IPC3;
#word IPC3 = 0x0AA

union  {
   union {
      struct {
         unsigned int SI2C1P0:1;
         unsigned int SI2C1P1:1;
         unsigned int SI2C1P2:1;
         unsigned int :1;
         unsigned int MI2C1P0:1;
         unsigned int MI2C1P1:1;
         unsigned int MI2C1P2:1;
         unsigned int :1;
         unsigned int CMIP0:1;
         unsigned int CMIP1:1;
         unsigned int CMIP2:1;
         unsigned int :1;
         unsigned int CNIP0:1;
         unsigned int CNIP1:1;
         unsigned int CNIP2:1;
      };
      struct {
         unsigned int SI2C1P:3;
         unsigned int :1;
         unsigned int MI2C1P:3;
         unsigned int :1;
         unsigned int CMIP:3;
         unsigned int :1;
         unsigned int CNIP:3;
      };

   union {
      struct {
         unsigned int SI2C1IP0:1;
         unsigned int SI2C1IP1:1;
         unsigned int SI2C1IP2:1;
         unsigned int :1;
         unsigned int MI2C1IP0:1;
         unsigned int MI2C1IP1:1;
         unsigned int MI2C1IP2:1;
         unsigned int :1;
         unsigned int CMIP0:1;
         unsigned int CMIP1:1;
         unsigned int CMIP2:1;
         unsigned int :1;
         unsigned int CNIP0:1;
         unsigned int CNIP1:1;
         unsigned int CNIP2:1;
      };
   };
      struct {
         unsigned int SI2C1IP:3;
         unsigned int :1;
         unsigned int MI2C1IP:3;
         unsigned int :1;
         unsigned int CMIP:3;
         unsigned int :1;
         unsigned int CNIP:3;
      };

      struct {
         unsigned int SI2C1P0:1;
         unsigned int SI2C1P1:1;
         unsigned int SI2C1P2:1;
         unsigned int :1;
         unsigned int MI2C1P0:1;
         unsigned int MI2C1P1:1;
         unsigned int MI2C1P2:1;
      };
   };
      struct {
         unsigned int SI2C1P:3;
         unsigned int :1;
         unsigned int MI2C1P:3;
      };
} IPC4;
#word IPC4 = 0x0AC

union  {
      struct {
         unsigned int INT1IP0:1;
         unsigned int INT1IP1:1;
         unsigned int INT1IP2:1;
         unsigned int :5;
         unsigned int IC7IP0:1;
         unsigned int IC7IP1:1;
         unsigned int IC7IP2:1;
         unsigned int :1;
         unsigned int IC8IP0:1;
         unsigned int IC8IP1:1;
         unsigned int IC8IP2:1;
      };
      struct {
         unsigned int INT1IP:3;
         unsigned int :5;
         unsigned int IC7IP:3;
         unsigned int :1;
         unsigned int IC8IP:3;
      };
} IPC5;
#word IPC5 = 0x0AE

union  {
      struct {
         unsigned int :4;
         unsigned int OC3IP0:1;
         unsigned int OC3IP1:1;
         unsigned int OC3IP2:1;
         unsigned int :1;
         unsigned int OC4IP0:1;
         unsigned int OC4IP1:1;
         unsigned int OC4IP2:1;
         unsigned int :1;
         unsigned int T4IP0:1;
         unsigned int T4IP1:1;
         unsigned int T4IP2:1;
      };
      struct {
         unsigned int :4;
         unsigned int OC3IP:3;
         unsigned int :1;
         unsigned int OC4IP:3;
         unsigned int :1;
         unsigned int T4IP:3;
      };
} IPC6;
#word IPC6 = 0x0B0

union  {
      struct {
         unsigned int T5IP0:1;
         unsigned int T5IP1:1;
         unsigned int T5IP2:1;
         unsigned int :1;
         unsigned int INT2IP0:1;
         unsigned int INT2IP1:1;
         unsigned int INT2IP2:1;
         unsigned int :1;
         unsigned int U2RXIP0:1;
         unsigned int U2RXIP1:1;
         unsigned int U2RXIP2:1;
         unsigned int :1;
         unsigned int U2TXIP0:1;
         unsigned int U2TXIP1:1;
         unsigned int U2TXIP2:1;
      };
      struct {
         unsigned int T5IP:3;
         unsigned int :1;
         unsigned int INT2IP:3;
         unsigned int :1;
         unsigned int U2RXIP:3;
         unsigned int :1;
         unsigned int U2TXIP:3;
      };
} IPC7;
#word IPC7 = 0x0B2

union  {
      struct {
         unsigned int SPF2IP0:1;
         unsigned int SPF2IP1:1;
         unsigned int SPF2IP2:1;
         unsigned int :1;
         unsigned int SPI2IP0:1;
         unsigned int SPI2IP1:1;
         unsigned int SPI2IP2:1;
      };
      struct {
         unsigned int SPF2IP:3;
         unsigned int :1;
         unsigned int SPI2IP:3;
      };
} IPC8;
#word IPC8 = 0x0B4

union  {
      struct {
         unsigned int :4;
         unsigned int IC3IP0:1;
         unsigned int IC3IP1:1;
         unsigned int IC3IP2:1;
         unsigned int :1;
         unsigned int IC4IP0:1;
         unsigned int IC4IP1:1;
         unsigned int IC4IP2:1;
         unsigned int :1;
         unsigned int IC5IP0:1;
         unsigned int IC5IP1:1;
         unsigned int IC5IP2:1;
      };
      struct {
         unsigned int :4;
         unsigned int IC3IP:3;
         unsigned int :1;
         unsigned int IC4IP:3;
         unsigned int :1;
         unsigned int IC5IP:3;
      };
} IPC9;
#word IPC9 = 0x0B6

union  {
      struct {
         unsigned int IC6IP0:1;
         unsigned int IC6IP1:1;
         unsigned int IC6IP2:1;
         unsigned int :1;
         unsigned int OC5IP0:1;
         unsigned int OC5IP1:1;
         unsigned int OC5IP2:1;
         unsigned int :1;
         unsigned int OC6IP0:1;
         unsigned int OC6IP1:1;
         unsigned int OC6IP2:1;
         unsigned int :1;
         unsigned int OC7IP0:1;
         unsigned int OC7IP1:1;
         unsigned int OC7IP2:1;
      };
      struct {
         unsigned int IC6IP:3;
         unsigned int :1;
         unsigned int OC5IP:3;
         unsigned int :1;
         unsigned int OC6IP:3;
         unsigned int :1;
         unsigned int OC7IP:3;
      };
} IPC10;
#word IPC10 = 0x0B8

union  {
      struct {
         unsigned int OC8IP0:1;
         unsigned int OC8IP1:1;
         unsigned int OC8IP2:1;
         unsigned int :1;
         unsigned int PMPIP0:1;
         unsigned int PMPIP1:1;
         unsigned int PMPIP2:1;
      };
      struct {
         unsigned int OC8IP:3;
         unsigned int :1;
         unsigned int PMPIP:3;
      };
} IPC11;
#word IPC11 = 0x0BA

union  {
   union {
      struct {
         unsigned int :4;
         unsigned int SI2C2P0:1;
         unsigned int SI2C2P1:1;
         unsigned int SI2C2P2:1;
         unsigned int :1;
         unsigned int MI2C2P0:1;
         unsigned int MI2C2P1:1;
         unsigned int MI2C2P2:1;
      };
      struct {
         unsigned int :4;
         unsigned int SI2C2P:3;
         unsigned int :1;
         unsigned int MI2C2P:3;
      };

   union {
      struct {
         unsigned int :4;
         unsigned int SI2C2IP0:1;
         unsigned int SI2C2IP1:1;
         unsigned int SI2C2IP2:1;
         unsigned int :1;
         unsigned int MI2C2IP0:1;
         unsigned int MI2C2IP1:1;
         unsigned int MI2C2IP2:1;
      };
   };
      struct {
         unsigned int :4;
         unsigned int SI2C2IP:3;
         unsigned int :1;
         unsigned int MI2C2IP:3;
      };

   union {
      struct {
         unsigned int :4;
         unsigned int SI2C2P0:1;
         unsigned int SI2C2P1:1;
         unsigned int SI2C2P2:1;
         unsigned int :1;
         unsigned int MI2C2P0:1;
         unsigned int MI2C2P1:1;
         unsigned int MI2C2P2:1;
      };
   };
      struct {
         unsigned int :4;
         unsigned int SI2C2P:3;
         unsigned int :1;
         unsigned int MI2C2P:3;
      };

      struct {
         unsigned int :4;
         unsigned int SI2C2IP0:1;
         unsigned int SI2C2IP1:1;
         unsigned int SI2C2IP2:1;
         unsigned int :1;
         unsigned int MI2C2IP0:1;
         unsigned int MI2C2IP1:1;
         unsigned int MI2C2IP2:1;
      };
   };
      struct {
         unsigned int :4;
         unsigned int SI2C2IP:3;
         unsigned int :1;
         unsigned int MI2C2IP:3;
      };
} IPC12;
#word IPC12 = 0x0BC

union  {
      struct {
         unsigned int :4;
         unsigned int INT3IP0:1;
         unsigned int INT3IP1:1;
         unsigned int INT3IP2:1;
         unsigned int :1;
         unsigned int INT4IP0:1;
         unsigned int INT4IP1:1;
         unsigned int INT4IP2:1;
      };
      struct {
         unsigned int :4;
         unsigned int INT3IP:3;
         unsigned int :1;
         unsigned int INT4IP:3;
      };
} IPC13;
#word IPC13 = 0x0BE

union  {
      struct {
         unsigned int :8;
         unsigned int RTCIP0:1;
         unsigned int RTCIP1:1;
         unsigned int RTCIP2:1;
      };
      struct {
         unsigned int :8;
         unsigned int RTCIP:3;
      };
} IPC15;
#word IPC15 = 0x0C2

union  {
      struct {
         unsigned int :4;
         unsigned int U1ERIP0:1;
         unsigned int U1ERIP1:1;
         unsigned int U1ERIP2:1;
         unsigned int :1;
         unsigned int U2ERIP0:1;
         unsigned int U2ERIP1:1;
         unsigned int U2ERIP2:1;
         unsigned int :1;
         unsigned int CRCIP0:1;
         unsigned int CRCIP1:1;
         unsigned int CRCIP2:1;
      };
      struct {
         unsigned int :4;
         unsigned int U1ERIP:3;
         unsigned int :1;
         unsigned int U2ERIP:3;
         unsigned int :1;
         unsigned int CRCIP:3;
      };
} IPC16;
#word IPC16 = 0x0C4

union  {
      struct {
         unsigned int LVDIP0:1;
         unsigned int LVDIP1:1;
         unsigned int LVDIP2:1;
      };
      struct {
         unsigned int LVDIP:3;
      };
} IPC18;
#word IPC18 = 0x0C8

union  {
      struct {
         unsigned int :4;
         unsigned int CTMUIP0:1;
         unsigned int CTMUIP1:1;
         unsigned int CTMUIP2:1;
      };
      struct {
         unsigned int :4;
         unsigned int CTMUIP:3;
      };
} IPC19;
#word IPC19 = 0x0CA

union  {
      struct {
         unsigned int :4;
         unsigned int U3ERIP0:1;
         unsigned int U3ERIP1:1;
         unsigned int U3ERIP2:1;
         unsigned int :1;
         unsigned int U3RXIP0:1;
         unsigned int U3RXIP1:1;
         unsigned int U3RXIP2:1;
         unsigned int :1;
         unsigned int U3TXIP0:1;
         unsigned int U3TXIP1:1;
         unsigned int U3TXIP2:1;
      };
      struct {
         unsigned int :4;
         unsigned int U3ERIP:3;
         unsigned int :1;
         unsigned int U3RXIP:3;
         unsigned int :1;
         unsigned int U3TXIP:3;
      };
} IPC20;
#word IPC20 = 0x0CC

union  {
      struct {
         unsigned int SI2C3P0:1;
         unsigned int SI2C3P1:1;
         unsigned int SI2C3P2:1;
         unsigned int :1;
         unsigned int MI2C3P0:1;
         unsigned int MI2C3P1:1;
         unsigned int MI2C3P2:1;
         unsigned int :1;
         unsigned int USB1IP0:1;
         unsigned int USB1IP1:1;
         unsigned int USB1IP2:1;
         unsigned int :1;
         unsigned int U4ERIP0:1;
         unsigned int U4ERIP1:1;
         unsigned int U4ERIP2:1;
      };
      struct {
         unsigned int SI2C3P:3;
         unsigned int :1;
         unsigned int MI2C3P:3;
         unsigned int :1;
         unsigned int USB1IP:3;
         unsigned int :1;
         unsigned int U4ERIP:3;
      };
} IPC21;
#word IPC21 = 0x0CE

union  {
      struct {
         unsigned int U4RXIP0:1;
         unsigned int U4RXIP1:1;
         unsigned int U4RXIP2:1;
         unsigned int :1;
         unsigned int U4TXIP0:1;
         unsigned int U4TXIP1:1;
         unsigned int U4TXIP2:1;
         unsigned int :1;
         unsigned int SPF3IP0:1;
         unsigned int SPF3IP1:1;
         unsigned int SPF3IP2:1;
         unsigned int :1;
         unsigned int SPI3IP0:1;
         unsigned int SPI3IP1:1;
         unsigned int SPI3IP2:1;
      };
      struct {
         unsigned int U4RXIP:3;
         unsigned int :1;
         unsigned int U4TXIP:3;
         unsigned int :1;
         unsigned int SPF3IP:3;
         unsigned int :1;
         unsigned int SPI3IP:3;
      };
} IPC22;
#word IPC22 = 0x0D0

union  {
      struct {
         unsigned int OC9IP0:1;
         unsigned int OC9IP1:1;
         unsigned int OC9IP2:1;
         unsigned int :1;
         unsigned int IC9IP0:1;
         unsigned int IC9IP1:1;
         unsigned int IC9IP2:1;
      };
      struct {
         unsigned int OC9IP:3;
         unsigned int :1;
         unsigned int IC9IP:3;
      };
} IPC23;
#word IPC23 = 0x0D2

union  {
      struct {
         unsigned int VECNUM0:1;
         unsigned int VECNUM1:1;
         unsigned int VECNUM2:1;
         unsigned int VECNUM3:1;
         unsigned int VECNUM4:1;
         unsigned int VECNUM5:1;
         unsigned int :2;
         unsigned int ILR0:1;
         unsigned int ILR1:1;
         unsigned int ILR2:1;
         unsigned int ILR3:1;
         unsigned int :2;
         unsigned int TMODE:1;
         unsigned int IRQtoCPU:1;
      };
      struct {
         unsigned int VECNUM:6;
         unsigned int :2;
         unsigned int ILR:4;
         unsigned int :2;
         unsigned int :1;
         unsigned int :1;
      };
} INTTREG;
#word INTTREG = 0x0E0

#word TMR1 = 0x100

#word PR1 = 0x102

union  {
      struct {
         unsigned int :1;
         unsigned int TCS:1;
         unsigned int TSYNC:1;
         unsigned int :1;
         unsigned int TCKPS0:1;
         unsigned int TCKPS1:1;
         unsigned int TGATE:1;
         unsigned int :6;
         unsigned int TSIDL:1;
         unsigned int :1;
         unsigned int TON:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int TCKPS:2;
         unsigned int :1;
         unsigned int :6;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} T1CON;
#word T1CON = 0x104

#word TMR2 = 0x106

#word TMR3HLD = 0x108

#word TMR3 = 0x10A

#word PR2 = 0x10C

#word PR3 = 0x10E

union  {
      struct {
         unsigned int :1;
         unsigned int TCS:1;
         unsigned int :1;
         unsigned int T3:1;
         unsigned int TCKPS0:1;
         unsigned int TCKPS1:1;
         unsigned int TGATE:1;
         unsigned int :6;
         unsigned int TSIDL:1;
         unsigned int :1;
         unsigned int TON:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int TCKPS:2;
         unsigned int :1;
         unsigned int :6;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} T2CON;
#word T2CON = 0x110

union  {
      struct {
         unsigned int :1;
         unsigned int TCS:1;
         unsigned int :2;
         unsigned int TCKPS0:1;
         unsigned int TCKPS1:1;
         unsigned int TGATE:1;
         unsigned int :6;
         unsigned int TSIDL:1;
         unsigned int :1;
         unsigned int TON:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int TCKPS:2;
         unsigned int :1;
         unsigned int :6;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} T3CON;
#word T3CON = 0x112

#word TMR4 = 0x114

#word TMR5HLD = 0x116

#word TMR5 = 0x118

#word PR4 = 0x11A

#word PR5 = 0x11C

union  {
      struct {
         unsigned int :1;
         unsigned int TCS:1;
         unsigned int :1;
         unsigned int T3:1;
         unsigned int TCKPS0:1;
         unsigned int TCKPS1:1;
         unsigned int TGATE:1;
         unsigned int :6;
         unsigned int TSIDL:1;
         unsigned int :1;
         unsigned int TON:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int TCKPS:2;
         unsigned int :1;
         unsigned int :6;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} T4CON;
#word T4CON = 0x11E

union  {
      struct {
         unsigned int :1;
         unsigned int TCS:1;
         unsigned int :2;
         unsigned int TCKPS0:1;
         unsigned int TCKPS1:1;
         unsigned int TGATE:1;
         unsigned int :6;
         unsigned int TSIDL:1;
         unsigned int :1;
         unsigned int TON:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int TCKPS:2;
         unsigned int :1;
         unsigned int :6;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} T5CON;
#word T5CON = 0x120

union  {
      struct {
         unsigned int ICM0:1;
         unsigned int ICM1:1;
         unsigned int ICM2:1;
         unsigned int ICBNE:1;
         unsigned int ICOV:1;
         unsigned int ICI0:1;
         unsigned int ICI1:1;
         unsigned int :3;
         unsigned int ICTSEL0:1;
         unsigned int ICTSEL1:1;
         unsigned int ICTSEL2:1;
         unsigned int ICSIDL:1;
      };
      struct {
         unsigned int ICM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int ICI:2;
         unsigned int :3;
         unsigned int ICTSEL:3;
         unsigned int :1;
      };
} IC1CON1;
#word IC1CON1 = 0x140

union  {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :1;
         unsigned int TRIGSTAT:1;
         unsigned int ICTRIG:1;
         unsigned int IC32:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} IC1CON2;
#word IC1CON2 = 0x142

#word IC1BUF = 0x144

#word IC1TMR = 0x146

union  {
      struct {
         unsigned int ICM0:1;
         unsigned int ICM1:1;
         unsigned int ICM2:1;
         unsigned int ICBNE:1;
         unsigned int ICOV:1;
         unsigned int ICI0:1;
         unsigned int ICI1:1;
         unsigned int :3;
         unsigned int ICTSEL0:1;
         unsigned int ICTSEL1:1;
         unsigned int ICTSEL2:1;
         unsigned int ICSIDL:1;
      };
      struct {
         unsigned int ICM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int ICI:2;
         unsigned int :3;
         unsigned int ICTSEL:3;
         unsigned int :1;
      };
} IC2CON1;
#word IC2CON1 = 0x148

union  {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :1;
         unsigned int TRIGSTAT:1;
         unsigned int ICTRIG:1;
         unsigned int IC32:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} IC2CON2;
#word IC2CON2 = 0x14A

#word IC2BUF = 0x14C

#word IC2TMR = 0x14E

union  {
      struct {
         unsigned int ICM0:1;
         unsigned int ICM1:1;
         unsigned int ICM2:1;
         unsigned int ICBNE:1;
         unsigned int ICOV:1;
         unsigned int ICI0:1;
         unsigned int ICI1:1;
         unsigned int :3;
         unsigned int ICTSEL0:1;
         unsigned int ICTSEL1:1;
         unsigned int ICTSEL2:1;
         unsigned int ICSIDL:1;
      };
      struct {
         unsigned int ICM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int ICI:2;
         unsigned int :3;
         unsigned int ICTSEL:3;
         unsigned int :1;
      };
} IC3CON1;
#word IC3CON1 = 0x150

union  {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :1;
         unsigned int TRIGSTAT:1;
         unsigned int ICTRIG:1;
         unsigned int IC32:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} IC3CON2;
#word IC3CON2 = 0x152

#word IC3BUF = 0x154

#word IC3TMR = 0x156

union  {
      struct {
         unsigned int ICM0:1;
         unsigned int ICM1:1;
         unsigned int ICM2:1;
         unsigned int ICBNE:1;
         unsigned int ICOV:1;
         unsigned int ICI0:1;
         unsigned int ICI1:1;
         unsigned int :3;
         unsigned int ICTSEL0:1;
         unsigned int ICTSEL1:1;
         unsigned int ICTSEL2:1;
         unsigned int ICSIDL:1;
      };
      struct {
         unsigned int ICM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int ICI:2;
         unsigned int :3;
         unsigned int ICTSEL:3;
         unsigned int :1;
      };
} IC4CON1;
#word IC4CON1 = 0x158

union  {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :1;
         unsigned int TRIGSTAT:1;
         unsigned int ICTRIG:1;
         unsigned int IC32:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} IC4CON2;
#word IC4CON2 = 0x15A

#word IC4BUF = 0x15C

#word IC4TMR = 0x15E

union  {
      struct {
         unsigned int ICM0:1;
         unsigned int ICM1:1;
         unsigned int ICM2:1;
         unsigned int ICBNE:1;
         unsigned int ICOV:1;
         unsigned int ICI0:1;
         unsigned int ICI1:1;
         unsigned int :3;
         unsigned int ICTSEL0:1;
         unsigned int ICTSEL1:1;
         unsigned int ICTSEL2:1;
         unsigned int ICSIDL:1;
      };
      struct {
         unsigned int ICM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int ICI:2;
         unsigned int :3;
         unsigned int ICTSEL:3;
         unsigned int :1;
      };
} IC5CON1;
#word IC5CON1 = 0x160

union  {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :1;
         unsigned int TRIGSTAT:1;
         unsigned int ICTRIG:1;
         unsigned int IC32:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} IC5CON2;
#word IC5CON2 = 0x162

#word IC5BUF = 0x164

#word IC5TMR = 0x166

union  {
      struct {
         unsigned int ICM0:1;
         unsigned int ICM1:1;
         unsigned int ICM2:1;
         unsigned int ICBNE:1;
         unsigned int ICOV:1;
         unsigned int ICI0:1;
         unsigned int ICI1:1;
         unsigned int :3;
         unsigned int ICTSEL0:1;
         unsigned int ICTSEL1:1;
         unsigned int ICTSEL2:1;
         unsigned int ICSIDL:1;
      };
      struct {
         unsigned int ICM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int ICI:2;
         unsigned int :3;
         unsigned int ICTSEL:3;
         unsigned int :1;
      };
} IC6CON1;
#word IC6CON1 = 0x168

union  {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :1;
         unsigned int TRIGSTAT:1;
         unsigned int ICTRIG:1;
         unsigned int IC32:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} IC6CON2;
#word IC6CON2 = 0x16A

#word IC6BUF = 0x16C

#word IC6TMR = 0x16E

union  {
      struct {
         unsigned int ICM0:1;
         unsigned int ICM1:1;
         unsigned int ICM2:1;
         unsigned int ICBNE:1;
         unsigned int ICOV:1;
         unsigned int ICI0:1;
         unsigned int ICI1:1;
         unsigned int :3;
         unsigned int ICTSEL0:1;
         unsigned int ICTSEL1:1;
         unsigned int ICTSEL2:1;
         unsigned int ICSIDL:1;
      };
      struct {
         unsigned int ICM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int ICI:2;
         unsigned int :3;
         unsigned int ICTSEL:3;
         unsigned int :1;
      };
} IC7CON1;
#word IC7CON1 = 0x170

union  {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :1;
         unsigned int TRIGSTAT:1;
         unsigned int ICTRIG:1;
         unsigned int IC32:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} IC7CON2;
#word IC7CON2 = 0x172

#word IC7BUF = 0x174

#word IC7TMR = 0x176

union  {
      struct {
         unsigned int ICM0:1;
         unsigned int ICM1:1;
         unsigned int ICM2:1;
         unsigned int ICBNE:1;
         unsigned int ICOV:1;
         unsigned int ICI0:1;
         unsigned int ICI1:1;
         unsigned int :3;
         unsigned int ICTSEL0:1;
         unsigned int ICTSEL1:1;
         unsigned int ICTSEL2:1;
         unsigned int ICSIDL:1;
      };
      struct {
         unsigned int ICM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int ICI:2;
         unsigned int :3;
         unsigned int ICTSEL:3;
         unsigned int :1;
      };
} IC8CON1;
#word IC8CON1 = 0x178

union  {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :1;
         unsigned int TRIGSTAT:1;
         unsigned int ICTRIG:1;
         unsigned int IC32:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} IC8CON2;
#word IC8CON2 = 0x17A

#word IC8BUF = 0x17C

#word IC8TMR = 0x17E

union  {
      struct {
         unsigned int ICM0:1;
         unsigned int ICM1:1;
         unsigned int ICM2:1;
         unsigned int ICBNE:1;
         unsigned int ICOV:1;
         unsigned int ICI0:1;
         unsigned int ICI1:1;
         unsigned int :3;
         unsigned int ICTSEL0:1;
         unsigned int ICTSEL1:1;
         unsigned int ICTSEL2:1;
         unsigned int ICSIDL:1;
      };
      struct {
         unsigned int ICM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int ICI:2;
         unsigned int :3;
         unsigned int ICTSEL:3;
         unsigned int :1;
      };
} IC9CON1;
#word IC9CON1 = 0x180

union  {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :1;
         unsigned int TRIGSTAT:1;
         unsigned int ICTRIG:1;
         unsigned int IC32:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} IC9CON2;
#word IC9CON2 = 0x182

#word IC9BUF = 0x184

#word IC9TMR = 0x186

union  {
   union {
      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int TRIGMODE:1;
         unsigned int OCFLT0:1;
         unsigned int :2;
         unsigned int ENFLT0:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
         unsigned int OCSIDL:1;
      };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
         unsigned int :1;
      };

      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int :1;
         unsigned int OCFLT:1;
         unsigned int :2;
         unsigned int ENFLT:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
      };
   };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
      };
} OC1CON1;
#word OC1CON1 = 0x190

union  {
   union {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int OCTRIS:1;
         unsigned int TRIGSTAT:1;
         unsigned int OCTRIG:1;
         unsigned int OC32:1;
         unsigned int :3;
         unsigned int OCINV:1;
         unsigned int FLTTRIEN:1;
         unsigned int FLTOUT:1;
         unsigned int FLTMD:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :10;
         unsigned int FLTMODE:1;
      };
   };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :10;
         unsigned int :1;
      };
} OC1CON2;
#word OC1CON2 = 0x192

#word OC1RS = 0x194

#word OC1R = 0x196

#word OC1TMR = 0x198

union  {
   union {
      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int TRIGMODE:1;
         unsigned int OCFLT0:1;
         unsigned int :2;
         unsigned int ENFLT0:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
         unsigned int OCSIDL:1;
      };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
         unsigned int :1;
      };

      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int :1;
         unsigned int OCFLT:1;
         unsigned int :2;
         unsigned int ENFLT:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
      };
   };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
      };
} OC2CON1;
#word OC2CON1 = 0x19A

union  {
   union {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int OCTRIS:1;
         unsigned int TRIGSTAT:1;
         unsigned int OCTRIG:1;
         unsigned int OC32:1;
         unsigned int :3;
         unsigned int OCINV:1;
         unsigned int FLTTRIEN:1;
         unsigned int FLTOUT:1;
         unsigned int FLTMD:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :10;
         unsigned int FLTMODE:1;
      };
   };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :10;
         unsigned int :1;
      };
} OC2CON2;
#word OC2CON2 = 0x19C

#word OC2RS = 0x19E

#word OC2R = 0x1A0

#word OC2TMR = 0x1A2

union  {
   union {
      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int TRIGMODE:1;
         unsigned int OCFLT0:1;
         unsigned int :2;
         unsigned int ENFLT0:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
         unsigned int OCSIDL:1;
      };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
         unsigned int :1;
      };

      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int :1;
         unsigned int OCFLT:1;
         unsigned int :2;
         unsigned int ENFLT:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
      };
   };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
      };
} OC3CON1;
#word OC3CON1 = 0x1A4

union  {
   union {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int OCTRIS:1;
         unsigned int TRIGSTAT:1;
         unsigned int OCTRIG:1;
         unsigned int OC32:1;
         unsigned int :3;
         unsigned int OCINV:1;
         unsigned int FLTTRIEN:1;
         unsigned int FLTOUT:1;
         unsigned int FLTMD:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :10;
         unsigned int FLTMODE:1;
      };
   };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :10;
         unsigned int :1;
      };
} OC3CON2;
#word OC3CON2 = 0x1A6

#word OC3RS = 0x1A8

#word OC3R = 0x1AA

#word OC3TMR = 0x1AC

union  {
   union {
      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int TRIGMODE:1;
         unsigned int OCFLT0:1;
         unsigned int :2;
         unsigned int ENFLT0:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
         unsigned int OCSIDL:1;
      };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
         unsigned int :1;
      };

      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int :1;
         unsigned int OCFLT:1;
         unsigned int :2;
         unsigned int ENFLT:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
      };
   };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
      };
} OC4CON1;
#word OC4CON1 = 0x1AE

union  {
   union {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int OCTRIS:1;
         unsigned int TRIGSTAT:1;
         unsigned int OCTRIG:1;
         unsigned int OC32:1;
         unsigned int :3;
         unsigned int OCINV:1;
         unsigned int FLTTRIEN:1;
         unsigned int FLTOUT:1;
         unsigned int FLTMD:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :10;
         unsigned int FLTMODE:1;
      };
   };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :10;
         unsigned int :1;
      };
} OC4CON2;
#word OC4CON2 = 0x1B0

#word OC4RS = 0x1B2

#word OC4R = 0x1B4

#word OC4TMR = 0x1B6

union  {
   union {
      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int TRIGMODE:1;
         unsigned int OCFLT0:1;
         unsigned int :2;
         unsigned int ENFLT0:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
         unsigned int OCSIDL:1;
      };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
         unsigned int :1;
      };

      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int :1;
         unsigned int OCFLT:1;
         unsigned int :2;
         unsigned int ENFLT:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
      };
   };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
      };
} OC5CON1;
#word OC5CON1 = 0x1B8

union  {
   union {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int OCTRIS:1;
         unsigned int TRIGSTAT:1;
         unsigned int OCTRIG:1;
         unsigned int OC32:1;
         unsigned int :3;
         unsigned int OCINV:1;
         unsigned int FLTTRIEN:1;
         unsigned int FLTOUT:1;
         unsigned int FLTMD:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :10;
         unsigned int FLTMODE:1;
      };
   };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :10;
         unsigned int :1;
      };
} OC5CON2;
#word OC5CON2 = 0x1BA

#word OC5RS = 0x1BC

#word OC5R = 0x1BE

#word OC5TMR = 0x1C0

union  {
   union {
      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int TRIGMODE:1;
         unsigned int OCFLT0:1;
         unsigned int :2;
         unsigned int ENFLT0:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
         unsigned int OCSIDL:1;
      };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
         unsigned int :1;
      };

      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int :1;
         unsigned int OCFLT:1;
         unsigned int :2;
         unsigned int ENFLT:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
      };
   };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
      };
} OC6CON1;
#word OC6CON1 = 0x1C2

union  {
   union {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int OCTRIS:1;
         unsigned int TRIGSTAT:1;
         unsigned int OCTRIG:1;
         unsigned int OC32:1;
         unsigned int :3;
         unsigned int OCINV:1;
         unsigned int FLTTRIEN:1;
         unsigned int FLTOUT:1;
         unsigned int FLTMD:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :10;
         unsigned int FLTMODE:1;
      };
   };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :10;
         unsigned int :1;
      };
} OC6CON2;
#word OC6CON2 = 0x1C4

#word OC6RS = 0x1C6

#word OC6R = 0x1C8

#word OC6TMR = 0x1CA

union  {
   union {
      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int TRIGMODE:1;
         unsigned int OCFLT0:1;
         unsigned int :2;
         unsigned int ENFLT0:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
         unsigned int OCSIDL:1;
      };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
         unsigned int :1;
      };

      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int :1;
         unsigned int OCFLT:1;
         unsigned int :2;
         unsigned int ENFLT:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
      };
   };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
      };
} OC7CON1;
#word OC7CON1 = 0x1CC

union  {
   union {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int OCTRIS:1;
         unsigned int TRIGSTAT:1;
         unsigned int OCTRIG:1;
         unsigned int OC32:1;
         unsigned int :3;
         unsigned int OCINV:1;
         unsigned int FLTTRIEN:1;
         unsigned int FLTOUT:1;
         unsigned int FLTMD:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :10;
         unsigned int FLTMODE:1;
      };
   };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :10;
         unsigned int :1;
      };
} OC7CON2;
#word OC7CON2 = 0x1CE

#word OC7RS = 0x1D0

#word OC7R = 0x1D2

#word OC7TMR = 0x1D4

union  {
   union {
      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int TRIGMODE:1;
         unsigned int OCFLT0:1;
         unsigned int :2;
         unsigned int ENFLT0:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
         unsigned int OCSIDL:1;
      };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
         unsigned int :1;
      };

      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int :1;
         unsigned int OCFLT:1;
         unsigned int :2;
         unsigned int ENFLT:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
      };
   };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
      };
} OC8CON1;
#word OC8CON1 = 0x1D6

union  {
   union {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int OCTRIS:1;
         unsigned int TRIGSTAT:1;
         unsigned int OCTRIG:1;
         unsigned int OC32:1;
         unsigned int :3;
         unsigned int OCINV:1;
         unsigned int FLTTRIEN:1;
         unsigned int FLTOUT:1;
         unsigned int FLTMD:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :10;
         unsigned int FLTMODE:1;
      };
   };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :10;
         unsigned int :1;
      };
} OC8CON2;
#word OC8CON2 = 0x1D8

#word OC8RS = 0x1DA

#word OC8R = 0x1DC

#word OC8TMR = 0x1DE

union  {
   union {
      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int TRIGMODE:1;
         unsigned int OCFLT0:1;
         unsigned int :2;
         unsigned int ENFLT0:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
         unsigned int OCSIDL:1;
      };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
         unsigned int :1;
      };

      struct {
         unsigned int OCM0:1;
         unsigned int OCM1:1;
         unsigned int OCM2:1;
         unsigned int :1;
         unsigned int OCFLT:1;
         unsigned int :2;
         unsigned int ENFLT:1;
         unsigned int :2;
         unsigned int OCTSEL0:1;
         unsigned int OCTSEL1:1;
         unsigned int OCTSEL2:1;
      };
   };
      struct {
         unsigned int OCM:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :2;
         unsigned int OCTSEL:3;
      };
} OC9CON1;
#word OC9CON1 = 0x1E0

union  {
   union {
      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int OCTRIS:1;
         unsigned int TRIGSTAT:1;
         unsigned int OCTRIG:1;
         unsigned int OC32:1;
         unsigned int :3;
         unsigned int OCINV:1;
         unsigned int FLTTRIEN:1;
         unsigned int FLTOUT:1;
         unsigned int FLTMD:1;
      };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int SYNCSEL0:1;
         unsigned int SYNCSEL1:1;
         unsigned int SYNCSEL2:1;
         unsigned int SYNCSEL3:1;
         unsigned int SYNCSEL4:1;
         unsigned int :10;
         unsigned int FLTMODE:1;
      };
   };
      struct {
         unsigned int SYNCSEL:5;
         unsigned int :10;
         unsigned int :1;
      };
} OC9CON2;
#word OC9CON2 = 0x1E2

#word OC9RS = 0x1E4

#word OC9R = 0x1E6

#word OC9TMR = 0x1E8

#word I2C1RCV = 0x200

#word I2C1TRN = 0x202

#word I2C1BRG = 0x204

struct  {
   unsigned int SEN:1;
   unsigned int RSEN:1;
   unsigned int PEN:1;
   unsigned int RCEN:1;
   unsigned int ACKEN:1;
   unsigned int ACKDT:1;
   unsigned int STREN:1;
   unsigned int GCEN:1;
   unsigned int SMEN:1;
   unsigned int DISSLW:1;
   unsigned int A10M:1;
   unsigned int IPMIEN:1;
   unsigned int SCLREL:1;
   unsigned int I2CSIDL:1;
   unsigned int :1;
   unsigned int I2CEN:1;
} I2C1CON;
#word I2C1CON = 0x206

struct  {
   union {
      struct {
         unsigned int TBF:1;
         unsigned int RBF:1;
         unsigned int R:1;
         unsigned int S:1;
         unsigned int P:1;
         unsigned int D:1;
         unsigned int I2COV:1;
         unsigned int IWCOL:1;
         unsigned int ADD:1;
         unsigned int GCSTAT:1;
         unsigned int BCL:1;
         unsigned int :3;
         unsigned int TRSTAT:1;
         unsigned int ACKSTAT:1;
      };

   union {
      struct {
         unsigned int :2;
         unsigned int R_W:1;
         unsigned int :2;
         unsigned int D_A:1;
      };
   };

      struct {
         unsigned int TBF:1;
         unsigned int RBF:1;
         unsigned int R:1;
         unsigned int S:1;
         unsigned int P:1;
         unsigned int D:1;
         unsigned int I2COV:1;
         unsigned int IWCOL:1;
         unsigned int ADD:1;
         unsigned int GCSTAT:1;
         unsigned int BCL:1;
         unsigned int :3;
         unsigned int TRSTAT:1;
         unsigned int ACKSTAT:1;
      };
   };
} I2C1STAT;
#word I2C1STAT = 0x208

#word I2C1ADD = 0x20A

#word I2C1MSK = 0x20C

#word I2C2RCV = 0x210

#word I2C2TRN = 0x212

#word I2C2BRG = 0x214

struct  {
   unsigned int SEN:1;
   unsigned int RSEN:1;
   unsigned int PEN:1;
   unsigned int RCEN:1;
   unsigned int ACKEN:1;
   unsigned int ACKDT:1;
   unsigned int STREN:1;
   unsigned int GCEN:1;
   unsigned int SMEN:1;
   unsigned int DISSLW:1;
   unsigned int A10M:1;
   unsigned int IPMIEN:1;
   unsigned int SCLREL:1;
   unsigned int I2CSIDL:1;
   unsigned int :1;
   unsigned int I2CEN:1;
} I2C2CON;
#word I2C2CON = 0x216

struct  {
   union {
      struct {
         unsigned int TBF:1;
         unsigned int RBF:1;
         unsigned int R:1;
         unsigned int S:1;
         unsigned int P:1;
         unsigned int D:1;
         unsigned int I2COV:1;
         unsigned int IWCOL:1;
         unsigned int ADD:1;
         unsigned int GCSTAT:1;
         unsigned int BCL:1;
         unsigned int :3;
         unsigned int TRSTAT:1;
         unsigned int ACKSTAT:1;
      };

   union {
      struct {
         unsigned int :2;
         unsigned int R_W:1;
         unsigned int :2;
         unsigned int D_A:1;
      };
   };

      struct {
         unsigned int TBF:1;
         unsigned int RBF:1;
         unsigned int R:1;
         unsigned int S:1;
         unsigned int P:1;
         unsigned int D:1;
         unsigned int I2COV:1;
         unsigned int IWCOL:1;
         unsigned int ADD:1;
         unsigned int GCSTAT:1;
         unsigned int BCL:1;
         unsigned int :3;
         unsigned int TRSTAT:1;
         unsigned int ACKSTAT:1;
      };
   };
} I2C2STAT;
#word I2C2STAT = 0x218

#word I2C2ADD = 0x21A

#word I2C2MSK = 0x21C

union  {
      struct {
         unsigned int STSEL:1;
         unsigned int PDSEL0:1;
         unsigned int PDSEL1:1;
         unsigned int BRGH:1;
         unsigned int RXINV:1;
         unsigned int ABAUD:1;
         unsigned int LPBACK:1;
         unsigned int WAKE:1;
         unsigned int UEN0:1;
         unsigned int UEN1:1;
         unsigned int :1;
         unsigned int RTSMD:1;
         unsigned int IREN:1;
         unsigned int USIDL:1;
         unsigned int :1;
         unsigned int UARTEN:1;
      };
      struct {
         unsigned int :1;
         unsigned int PDSEL:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int UEN:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} U1MODE;
#word U1MODE = 0x220

union  {
      struct {
         unsigned int URXDA:1;
         unsigned int OERR:1;
         unsigned int FERR:1;
         unsigned int PERR:1;
         unsigned int RIDLE:1;
         unsigned int ADDEN:1;
         unsigned int URXISEL0:1;
         unsigned int URXISEL1:1;
         unsigned int TRMT:1;
         unsigned int UTXBF:1;
         unsigned int UTXEN:1;
         unsigned int UTXBRK:1;
         unsigned int :1;
         unsigned int UTXISEL0:1;
         unsigned int UTXINV:1;
         unsigned int UTXISEL1:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int URXISEL:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int UTXISEL:1;
         unsigned int :1;
         unsigned int :1;
      };
} U1STA;
#word U1STA = 0x222

union  {
      struct {
         unsigned int UTXREG0:1;
         unsigned int UTXREG1:1;
         unsigned int UTXREG2:1;
         unsigned int UTXREG3:1;
         unsigned int UTXREG4:1;
         unsigned int UTXREG5:1;
         unsigned int UTXREG6:1;
         unsigned int UTXREG7:1;
         unsigned int UTXREG8:1;
      };
      struct {
         unsigned int UTXREG:9;
      };
} U1TXREG;
#word U1TXREG = 0x224

union  {
      struct {
         unsigned int URXREG0:1;
         unsigned int URXREG1:1;
         unsigned int URXREG2:1;
         unsigned int URXREG3:1;
         unsigned int URXREG4:1;
         unsigned int URXREG5:1;
         unsigned int URXREG6:1;
         unsigned int URXREG7:1;
         unsigned int URXREG8:1;
      };
      struct {
         unsigned int URXREG:9;
      };
} U1RXREG;
#word U1RXREG = 0x226

#word U1BRG = 0x228

union  {
      struct {
         unsigned int STSEL:1;
         unsigned int PDSEL0:1;
         unsigned int PDSEL1:1;
         unsigned int BRGH:1;
         unsigned int RXINV:1;
         unsigned int ABAUD:1;
         unsigned int LPBACK:1;
         unsigned int WAKE:1;
         unsigned int UEN0:1;
         unsigned int UEN1:1;
         unsigned int :1;
         unsigned int RTSMD:1;
         unsigned int IREN:1;
         unsigned int USIDL:1;
         unsigned int :1;
         unsigned int UARTEN:1;
      };
      struct {
         unsigned int :1;
         unsigned int PDSEL:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int UEN:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} U2MODE;
#word U2MODE = 0x230

union  {
      struct {
         unsigned int URXDA:1;
         unsigned int OERR:1;
         unsigned int FERR:1;
         unsigned int PERR:1;
         unsigned int RIDLE:1;
         unsigned int ADDEN:1;
         unsigned int URXISEL0:1;
         unsigned int URXISEL1:1;
         unsigned int TRMT:1;
         unsigned int UTXBF:1;
         unsigned int UTXEN:1;
         unsigned int UTXBRK:1;
         unsigned int :1;
         unsigned int UTXISEL0:1;
         unsigned int UTXINV:1;
         unsigned int UTXISEL1:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int URXISEL:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int UTXISEL:1;
         unsigned int :1;
         unsigned int :1;
      };
} U2STA;
#word U2STA = 0x232

union  {
      struct {
         unsigned int UTXREG0:1;
         unsigned int UTXREG1:1;
         unsigned int UTXREG2:1;
         unsigned int UTXREG3:1;
         unsigned int UTXREG4:1;
         unsigned int UTXREG5:1;
         unsigned int UTXREG6:1;
         unsigned int UTXREG7:1;
         unsigned int UTXREG8:1;
      };
      struct {
         unsigned int UTXREG:9;
      };
} U2TXREG;
#word U2TXREG = 0x234

union  {
      struct {
         unsigned int URXREG0:1;
         unsigned int URXREG1:1;
         unsigned int URXREG2:1;
         unsigned int URXREG3:1;
         unsigned int URXREG4:1;
         unsigned int URXREG5:1;
         unsigned int URXREG6:1;
         unsigned int URXREG7:1;
         unsigned int URXREG8:1;
      };
      struct {
         unsigned int URXREG:9;
      };
} U2RXREG;
#word U2RXREG = 0x236

#word U2BRG = 0x238

union  {
      struct {
         unsigned int SPIRBF:1;
         unsigned int SPITBF:1;
         unsigned int SISEL0:1;
         unsigned int SISEL1:1;
         unsigned int SISEL2:1;
         unsigned int SRXMPT:1;
         unsigned int SPIROV:1;
         unsigned int SRMPT:1;
         unsigned int SPIBEC0:1;
         unsigned int SPIBEC1:1;
         unsigned int SPIBEC2:1;
         unsigned int :2;
         unsigned int SPISIDL:1;
         unsigned int :1;
         unsigned int SPIEN:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int SISEL:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int SPIBEC:3;
         unsigned int :2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} SPI1STAT;
#word SPI1STAT = 0x240

union  {
      struct {
         unsigned int PPRE0:1;
         unsigned int PPRE1:1;
         unsigned int SPRE0:1;
         unsigned int SPRE1:1;
         unsigned int SPRE2:1;
         unsigned int MSTEN:1;
         unsigned int CKP:1;
         unsigned int SSEN:1;
         unsigned int CKE:1;
         unsigned int SMP:1;
         unsigned int MODE:1;
         unsigned int DISSDO:1;
         unsigned int DISSCK:1;
      };
      struct {
         unsigned int PPRE:2;
         unsigned int SPRE:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} SPI1CON1;
#word SPI1CON1 = 0x242

struct  {
   unsigned int SPIBEN:1;
   unsigned int SPIFE:1;
   unsigned int :11;
   unsigned int SPIFPOL:1;
   unsigned int SPIFSD:1;
   unsigned int FRMEN:1;
} SPI1CON2;
#word SPI1CON2 = 0x244

#word SPI1BUF = 0x248

union  {
      struct {
         unsigned int STSEL:1;
         unsigned int PDSEL0:1;
         unsigned int PDSEL1:1;
         unsigned int BRGH:1;
         unsigned int RXINV:1;
         unsigned int ABAUD:1;
         unsigned int LPBACK:1;
         unsigned int WAKE:1;
         unsigned int UEN0:1;
         unsigned int UEN1:1;
         unsigned int :1;
         unsigned int RTSMD:1;
         unsigned int IREN:1;
         unsigned int USIDL:1;
         unsigned int :1;
         unsigned int UARTEN:1;
      };
      struct {
         unsigned int :1;
         unsigned int PDSEL:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int UEN:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} U3MODE;
#word U3MODE = 0x250

union  {
      struct {
         unsigned int URXDA:1;
         unsigned int OERR:1;
         unsigned int FERR:1;
         unsigned int PERR:1;
         unsigned int RIDLE:1;
         unsigned int ADDEN:1;
         unsigned int URXISEL0:1;
         unsigned int URXISEL1:1;
         unsigned int TRMT:1;
         unsigned int UTXBF:1;
         unsigned int UTXEN:1;
         unsigned int UTXBRK:1;
         unsigned int :1;
         unsigned int UTXISEL0:1;
         unsigned int UTXINV:1;
         unsigned int UTXISEL1:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int URXISEL:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int UTXISEL:1;
         unsigned int :1;
         unsigned int :1;
      };
} U3STA;
#word U3STA = 0x252

union  {
      struct {
         unsigned int UTXREG0:1;
         unsigned int UTXREG1:1;
         unsigned int UTXREG2:1;
         unsigned int UTXREG3:1;
         unsigned int UTXREG4:1;
         unsigned int UTXREG5:1;
         unsigned int UTXREG6:1;
         unsigned int UTXREG7:1;
         unsigned int UTXREG8:1;
      };
      struct {
         unsigned int UTXREG:9;
      };
} U3TXREG;
#word U3TXREG = 0x254

union  {
      struct {
         unsigned int URXREG0:1;
         unsigned int URXREG1:1;
         unsigned int URXREG2:1;
         unsigned int URXREG3:1;
         unsigned int URXREG4:1;
         unsigned int URXREG5:1;
         unsigned int URXREG6:1;
         unsigned int URXREG7:1;
         unsigned int URXREG8:1;
      };
      struct {
         unsigned int URXREG:9;
      };
} U3RXREG;
#word U3RXREG = 0x256

#word U3BRG = 0x258

union  {
      struct {
         unsigned int SPIRBF:1;
         unsigned int SPITBF:1;
         unsigned int SISEL0:1;
         unsigned int SISEL1:1;
         unsigned int SISEL2:1;
         unsigned int SRXMPT:1;
         unsigned int SPIROV:1;
         unsigned int SRMPT:1;
         unsigned int SPIBEC0:1;
         unsigned int SPIBEC1:1;
         unsigned int SPIBEC2:1;
         unsigned int :2;
         unsigned int SPISIDL:1;
         unsigned int :1;
         unsigned int SPIEN:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int SISEL:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int SPIBEC:3;
         unsigned int :2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} SPI2STAT;
#word SPI2STAT = 0x260

union  {
      struct {
         unsigned int PPRE0:1;
         unsigned int PPRE1:1;
         unsigned int SPRE0:1;
         unsigned int SPRE1:1;
         unsigned int SPRE2:1;
         unsigned int MSTEN:1;
         unsigned int CKP:1;
         unsigned int SSEN:1;
         unsigned int CKE:1;
         unsigned int SMP:1;
         unsigned int MODE:1;
         unsigned int DISSDO:1;
         unsigned int DISSCK:1;
      };
      struct {
         unsigned int PPRE:2;
         unsigned int SPRE:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} SPI2CON1;
#word SPI2CON1 = 0x262

struct  {
   unsigned int SPIBEN:1;
   unsigned int SPIFE:1;
   unsigned int :11;
   unsigned int SPIFPOL:1;
   unsigned int SPIFSD:1;
   unsigned int FRMEN:1;
} SPI2CON2;
#word SPI2CON2 = 0x264

#word SPI2BUF = 0x268

#word I2C3RCV = 0x270

#word I2C3TRN = 0x272

#word I2C3BRG = 0x274

struct  {
   unsigned int SEN:1;
   unsigned int RSEN:1;
   unsigned int PEN:1;
   unsigned int RCEN:1;
   unsigned int ACKEN:1;
   unsigned int ACKDT:1;
   unsigned int STREN:1;
   unsigned int GCEN:1;
   unsigned int SMEN:1;
   unsigned int DISSLW:1;
   unsigned int A10M:1;
   unsigned int IPMIEN:1;
   unsigned int SCLREL:1;
   unsigned int I2CSIDL:1;
   unsigned int :1;
   unsigned int I2CEN:1;
} I2C3CON;
#word I2C3CON = 0x276

struct  {
   union {
      struct {
         unsigned int TBF:1;
         unsigned int RBF:1;
         unsigned int R:1;
         unsigned int S:1;
         unsigned int P:1;
         unsigned int D:1;
         unsigned int I2COV:1;
         unsigned int IWCOL:1;
         unsigned int ADD:1;
         unsigned int GCSTAT:1;
         unsigned int BCL:1;
         unsigned int :3;
         unsigned int TRSTAT:1;
         unsigned int ACKSTAT:1;
      };

   union {
      struct {
         unsigned int :2;
         unsigned int R_W:1;
         unsigned int :2;
         unsigned int D_A:1;
      };
   };

      struct {
         unsigned int TBF:1;
         unsigned int RBF:1;
         unsigned int R:1;
         unsigned int S:1;
         unsigned int P:1;
         unsigned int D:1;
         unsigned int I2COV:1;
         unsigned int IWCOL:1;
         unsigned int ADD:1;
         unsigned int GCSTAT:1;
         unsigned int BCL:1;
         unsigned int :3;
         unsigned int TRSTAT:1;
         unsigned int ACKSTAT:1;
      };
   };
} I2C3STAT;
#word I2C3STAT = 0x278

#word I2C3ADD = 0x27A

#word I2C3MSK = 0x27C

union  {
      struct {
         unsigned int SPIRBF:1;
         unsigned int SPITBF:1;
         unsigned int SISEL0:1;
         unsigned int SISEL1:1;
         unsigned int SISEL2:1;
         unsigned int SRXMPT:1;
         unsigned int SPIROV:1;
         unsigned int SRMPT:1;
         unsigned int SPIBEC0:1;
         unsigned int SPIBEC1:1;
         unsigned int SPIBEC2:1;
         unsigned int :2;
         unsigned int SPISIDL:1;
         unsigned int :1;
         unsigned int SPIEN:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int SISEL:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int SPIBEC:3;
         unsigned int :2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} SPI3STAT;
#word SPI3STAT = 0x280

union  {
      struct {
         unsigned int PPRE0:1;
         unsigned int PPRE1:1;
         unsigned int SPRE0:1;
         unsigned int SPRE1:1;
         unsigned int SPRE2:1;
         unsigned int MSTEN:1;
         unsigned int CKP:1;
         unsigned int SSEN:1;
         unsigned int CKE:1;
         unsigned int SMP:1;
         unsigned int MODE:1;
         unsigned int DISSDO:1;
         unsigned int DISSCK:1;
      };
      struct {
         unsigned int PPRE:2;
         unsigned int SPRE:3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} SPI3CON1;
#word SPI3CON1 = 0x282

struct  {
   unsigned int SPIBEN:1;
   unsigned int SPIFE:1;
   unsigned int :11;
   unsigned int SPIFPOL:1;
   unsigned int SPIFSD:1;
   unsigned int FRMEN:1;
} SPI3CON2;
#word SPI3CON2 = 0x284

#word SPI3BUF = 0x288

union  {
      struct {
         unsigned int STSEL:1;
         unsigned int PDSEL0:1;
         unsigned int PDSEL1:1;
         unsigned int BRGH:1;
         unsigned int RXINV:1;
         unsigned int ABAUD:1;
         unsigned int LPBACK:1;
         unsigned int WAKE:1;
         unsigned int UEN0:1;
         unsigned int UEN1:1;
         unsigned int :1;
         unsigned int RTSMD:1;
         unsigned int IREN:1;
         unsigned int USIDL:1;
         unsigned int :1;
         unsigned int UARTEN:1;
      };
      struct {
         unsigned int :1;
         unsigned int PDSEL:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int UEN:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} U4MODE;
#word U4MODE = 0x2B0

union  {
      struct {
         unsigned int URXDA:1;
         unsigned int OERR:1;
         unsigned int FERR:1;
         unsigned int PERR:1;
         unsigned int RIDLE:1;
         unsigned int ADDEN:1;
         unsigned int URXISEL0:1;
         unsigned int URXISEL1:1;
         unsigned int TRMT:1;
         unsigned int UTXBF:1;
         unsigned int UTXEN:1;
         unsigned int UTXBRK:1;
         unsigned int :1;
         unsigned int UTXISEL0:1;
         unsigned int UTXINV:1;
         unsigned int UTXISEL1:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int URXISEL:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int UTXISEL:1;
         unsigned int :1;
         unsigned int :1;
      };
} U4STA;
#word U4STA = 0x2B2

union  {
      struct {
         unsigned int UTXREG0:1;
         unsigned int UTXREG1:1;
         unsigned int UTXREG2:1;
         unsigned int UTXREG3:1;
         unsigned int UTXREG4:1;
         unsigned int UTXREG5:1;
         unsigned int UTXREG6:1;
         unsigned int UTXREG7:1;
         unsigned int UTXREG8:1;
      };
      struct {
         unsigned int UTXREG:9;
      };
} U4TXREG;
#word U4TXREG = 0x2B4

union  {
      struct {
         unsigned int URXREG0:1;
         unsigned int URXREG1:1;
         unsigned int URXREG2:1;
         unsigned int URXREG3:1;
         unsigned int URXREG4:1;
         unsigned int URXREG5:1;
         unsigned int URXREG6:1;
         unsigned int URXREG7:1;
         unsigned int URXREG8:1;
      };
      struct {
         unsigned int URXREG:9;
      };
} U4RXREG;
#word U4RXREG = 0x2B6

#word U4BRG = 0x2B8

union  {
      struct {
         unsigned int TRISA0:1;
         unsigned int TRISA1:1;
         unsigned int TRISA2:1;
         unsigned int TRISA3:1;
         unsigned int TRISA4:1;
         unsigned int TRISA5:1;
         unsigned int TRISA6:1;
         unsigned int TRISA7:1;
         unsigned int :1;
         unsigned int TRISA9:1;
         unsigned int TRISA10:1;
         unsigned int :3;
         unsigned int TRISA14:1;
         unsigned int TRISA15:1;
      };
      struct {
         unsigned int TRISA:8;
         unsigned int :1;
         unsigned int :2;
         unsigned int :3;
         unsigned int :2;
      };
} TRISA;
#word TRISA = 0x2C0

union  {
      struct {
         unsigned int RA0:1;
         unsigned int RA1:1;
         unsigned int RA2:1;
         unsigned int RA3:1;
         unsigned int RA4:1;
         unsigned int RA5:1;
         unsigned int RA6:1;
         unsigned int RA7:1;
         unsigned int :1;
         unsigned int RA9:1;
         unsigned int RA10:1;
         unsigned int :3;
         unsigned int RA14:1;
         unsigned int RA15:1;
      };
      struct {
         unsigned int RA:8;
         unsigned int :1;
         unsigned int :2;
         unsigned int :3;
         unsigned int :2;
      };
} PORTA;
#word PORTA = 0x2C2

union  {
      struct {
         unsigned int LATA0:1;
         unsigned int LATA1:1;
         unsigned int LATA2:1;
         unsigned int LATA3:1;
         unsigned int LATA4:1;
         unsigned int LATA5:1;
         unsigned int LATA6:1;
         unsigned int LATA7:1;
         unsigned int :1;
         unsigned int LATA9:1;
         unsigned int LATA10:1;
         unsigned int :3;
         unsigned int LATA14:1;
         unsigned int LATA15:1;
      };
      struct {
         unsigned int LATA:8;
         unsigned int :1;
         unsigned int :2;
         unsigned int :3;
         unsigned int :2;
      };
} LATA;
#word LATA = 0x2C4

union  {
      struct {
         unsigned int ODA0:1;
         unsigned int ODA1:1;
         unsigned int ODA2:1;
         unsigned int ODA3:1;
         unsigned int ODA4:1;
         unsigned int ODA5:1;
         unsigned int ODA6:1;
         unsigned int ODA7:1;
         unsigned int :1;
         unsigned int ODA9:1;
         unsigned int ODA10:1;
         unsigned int :3;
         unsigned int ODA14:1;
         unsigned int ODA15:1;
      };
      struct {
         unsigned int ODA:8;
         unsigned int :1;
         unsigned int :2;
         unsigned int :3;
         unsigned int :2;
      };
} ODCA;
#word ODCA = 0x2C6

union  {
      struct {
         unsigned int TRISB0:1;
         unsigned int TRISB1:1;
         unsigned int TRISB2:1;
         unsigned int TRISB3:1;
         unsigned int TRISB4:1;
         unsigned int TRISB5:1;
         unsigned int TRISB6:1;
         unsigned int TRISB7:1;
         unsigned int TRISB8:1;
         unsigned int TRISB9:1;
         unsigned int TRISB10:1;
         unsigned int TRISB11:1;
         unsigned int TRISB12:1;
         unsigned int TRISB13:1;
         unsigned int TRISB14:1;
         unsigned int TRISB15:1;
      };
      struct {
         unsigned int TRISB:16;
      };
} TRISB;
#word TRISB = 0x2C8

union  {
      struct {
         unsigned int RB0:1;
         unsigned int RB1:1;
         unsigned int RB2:1;
         unsigned int RB3:1;
         unsigned int RB4:1;
         unsigned int RB5:1;
         unsigned int RB6:1;
         unsigned int RB7:1;
         unsigned int RB8:1;
         unsigned int RB9:1;
         unsigned int RB10:1;
         unsigned int RB11:1;
         unsigned int RB12:1;
         unsigned int RB13:1;
         unsigned int RB14:1;
         unsigned int RB15:1;
      };
      struct {
         unsigned int RB:16;
      };
} PORTB;
#word PORTB = 0x2CA

union  {
      struct {
         unsigned int LATB0:1;
         unsigned int LATB1:1;
         unsigned int LATB2:1;
         unsigned int LATB3:1;
         unsigned int LATB4:1;
         unsigned int LATB5:1;
         unsigned int LATB6:1;
         unsigned int LATB7:1;
         unsigned int LATB8:1;
         unsigned int LATB9:1;
         unsigned int LATB10:1;
         unsigned int LATB11:1;
         unsigned int LATB12:1;
         unsigned int LATB13:1;
         unsigned int LATB14:1;
         unsigned int LATB15:1;
      };
      struct {
         unsigned int LATB:16;
      };
} LATB;
#word LATB = 0x2CC

union  {
      struct {
         unsigned int ODB0:1;
         unsigned int ODB1:1;
         unsigned int ODB2:1;
         unsigned int ODB3:1;
         unsigned int ODB4:1;
         unsigned int ODB5:1;
         unsigned int ODB6:1;
         unsigned int ODB7:1;
         unsigned int ODB8:1;
         unsigned int ODB9:1;
         unsigned int ODB10:1;
         unsigned int ODB11:1;
         unsigned int ODB12:1;
         unsigned int ODB13:1;
         unsigned int ODB14:1;
         unsigned int ODB15:1;
      };
      struct {
         unsigned int ODB:16;
      };
} ODCB;
#word ODCB = 0x2CE

struct  {
   unsigned int :1;
   unsigned int TRISC0:1;
   unsigned int TRISC1:1;
   unsigned int TRISC2:1;
   unsigned int TRISC4:1;
   unsigned int :7;
   unsigned int TRISC11:1;
   unsigned int TRISC12:1;
   unsigned int TRISC13:1;
   unsigned int TRISC15:1;
} TRISC;
#word TRISC = 0x2D0

struct  {
   unsigned int :1;
   unsigned int RC0:1;
   unsigned int RC1:1;
   unsigned int RC2:1;
   unsigned int RC4:1;
   unsigned int :7;
   unsigned int RC11:1;
   unsigned int RC12:1;
   unsigned int RC13:1;
   unsigned int RC15:1;
} PORTC;
#word PORTC = 0x2D2

struct  {
   unsigned int :1;
   unsigned int LATC0:1;
   unsigned int LATC1:1;
   unsigned int LATC2:1;
   unsigned int LATC4:1;
   unsigned int :7;
   unsigned int LATC11:1;
   unsigned int LATC12:1;
   unsigned int LATC13:1;
   unsigned int LATC15:1;
} LATC;
#word LATC = 0x2D4

struct  {
   unsigned int :1;
   unsigned int ODC0:1;
   unsigned int ODC1:1;
   unsigned int ODC2:1;
   unsigned int ODC4:1;
   unsigned int :7;
   unsigned int ODC11:1;
   unsigned int ODC12:1;
   unsigned int ODC13:1;
   unsigned int ODC15:1;
} ODCC;
#word ODCC = 0x2D6

union  {
      struct {
         unsigned int TRISD0:1;
         unsigned int TRISD1:1;
         unsigned int TRISD2:1;
         unsigned int TRISD3:1;
         unsigned int TRISD4:1;
         unsigned int TRISD5:1;
         unsigned int TRISD6:1;
         unsigned int TRISD7:1;
         unsigned int TRISD8:1;
         unsigned int TRISD9:1;
         unsigned int TRISD10:1;
         unsigned int TRISD11:1;
         unsigned int TRISD12:1;
         unsigned int TRISD13:1;
         unsigned int TRISD14:1;
         unsigned int TRISD15:1;
      };
      struct {
         unsigned int TRISD:16;
      };
} TRISD;
#word TRISD = 0x2D8

union  {
      struct {
         unsigned int RD0:1;
         unsigned int RD1:1;
         unsigned int RD2:1;
         unsigned int RD3:1;
         unsigned int RD4:1;
         unsigned int RD5:1;
         unsigned int RD6:1;
         unsigned int RD7:1;
         unsigned int RD8:1;
         unsigned int RD9:1;
         unsigned int RD10:1;
         unsigned int RD11:1;
         unsigned int RD12:1;
         unsigned int RD13:1;
         unsigned int RD14:1;
         unsigned int RD15:1;
      };
      struct {
         unsigned int RD:16;
      };
} PORTD;
#word PORTD = 0x2DA

union  {
      struct {
         unsigned int LATD0:1;
         unsigned int LATD1:1;
         unsigned int LATD2:1;
         unsigned int LATD3:1;
         unsigned int LATD4:1;
         unsigned int LATD5:1;
         unsigned int LATD6:1;
         unsigned int LATD7:1;
         unsigned int LATD8:1;
         unsigned int LATD9:1;
         unsigned int LATD10:1;
         unsigned int LATD11:1;
         unsigned int LATD12:1;
         unsigned int LATD13:1;
         unsigned int LATD14:1;
         unsigned int LATD15:1;
      };
      struct {
         unsigned int LATD:16;
      };
} LATD;
#word LATD = 0x2DC

union  {
      struct {
         unsigned int ODD0:1;
         unsigned int ODD1:1;
         unsigned int ODD2:1;
         unsigned int ODD3:1;
         unsigned int ODD4:1;
         unsigned int ODD5:1;
         unsigned int ODD6:1;
         unsigned int ODD7:1;
         unsigned int ODD8:1;
         unsigned int ODD9:1;
         unsigned int ODD10:1;
         unsigned int ODD11:1;
         unsigned int ODD12:1;
         unsigned int ODD13:1;
         unsigned int ODD14:1;
         unsigned int ODD15:1;
      };
      struct {
         unsigned int ODD:16;
      };
} ODCD;
#word ODCD = 0x2DE

union  {
      struct {
         unsigned int TRISE0:1;
         unsigned int TRISE1:1;
         unsigned int TRISE2:1;
         unsigned int TRISE3:1;
         unsigned int TRISE4:1;
         unsigned int TRISE5:1;
         unsigned int TRISE6:1;
         unsigned int TRISE7:1;
         unsigned int TRISE8:1;
         unsigned int TRISE9:1;
      };
      struct {
         unsigned int TRISE:10;
      };
} TRISE;
#word TRISE = 0x2E0

union  {
      struct {
         unsigned int RE0:1;
         unsigned int RE1:1;
         unsigned int RE2:1;
         unsigned int RE3:1;
         unsigned int RE4:1;
         unsigned int RE5:1;
         unsigned int RE6:1;
         unsigned int RE7:1;
         unsigned int RE8:1;
         unsigned int RE9:1;
      };
      struct {
         unsigned int RE:10;
      };
} PORTE;
#word PORTE = 0x2E2

union  {
      struct {
         unsigned int LATE0:1;
         unsigned int LATE1:1;
         unsigned int LATE2:1;
         unsigned int LATE3:1;
         unsigned int LATE4:1;
         unsigned int LATE5:1;
         unsigned int LATE6:1;
         unsigned int LATE7:1;
         unsigned int LATE8:1;
         unsigned int LATE9:1;
      };
      struct {
         unsigned int LATE:10;
      };
} LATE;
#word LATE = 0x2E4

union  {
      struct {
         unsigned int ODE0:1;
         unsigned int ODE1:1;
         unsigned int ODE2:1;
         unsigned int ODE3:1;
         unsigned int ODE4:1;
         unsigned int ODE5:1;
         unsigned int ODE6:1;
         unsigned int ODE7:1;
         unsigned int ODE8:1;
         unsigned int ODE9:1;
      };
      struct {
         unsigned int ODE:10;
      };
} ODCE;
#word ODCE = 0x2E6

union  {
      struct {
         unsigned int TRISF0:1;
         unsigned int TRISF1:1;
         unsigned int TRISF2:1;
         unsigned int TRISF3:1;
         unsigned int TRISF4:1;
         unsigned int TRISF5:1;
         unsigned int :2;
         unsigned int TRISF8:1;
         unsigned int :3;
         unsigned int TRISF12:1;
         unsigned int TRISF13:1;
      };
      struct {
         unsigned int TRISF:6;
         unsigned int :2;
         unsigned int :1;
         unsigned int :3;
         unsigned int :2;
      };
} TRISF;
#word TRISF = 0x2E8

union  {
      struct {
         unsigned int RF0:1;
         unsigned int RF1:1;
         unsigned int RF2:1;
         unsigned int RF3:1;
         unsigned int RF4:1;
         unsigned int RF5:1;
         unsigned int :2;
         unsigned int RF8:1;
         unsigned int :3;
         unsigned int RF12:1;
         unsigned int RF13:1;
      };
      struct {
         unsigned int RF:6;
         unsigned int :2;
         unsigned int :1;
         unsigned int :3;
         unsigned int :2;
      };
} PORTF;
#word PORTF = 0x2EA

union  {
      struct {
         unsigned int LATF0:1;
         unsigned int LATF1:1;
         unsigned int LATF2:1;
         unsigned int LATF3:1;
         unsigned int LATF4:1;
         unsigned int LATF5:1;
         unsigned int :2;
         unsigned int LATF8:1;
         unsigned int :3;
         unsigned int LATF12:1;
         unsigned int LATF13:1;
      };
      struct {
         unsigned int LATF:6;
         unsigned int :2;
         unsigned int :1;
         unsigned int :3;
         unsigned int :2;
      };
} LATF;
#word LATF = 0x2EC

union  {
      struct {
         unsigned int ODF0:1;
         unsigned int ODF1:1;
         unsigned int ODF2:1;
         unsigned int ODF3:1;
         unsigned int ODF4:1;
         unsigned int ODF5:1;
         unsigned int :2;
         unsigned int ODF8:1;
         unsigned int :3;
         unsigned int ODF12:1;
         unsigned int ODF13:1;
      };
      struct {
         unsigned int ODF:6;
         unsigned int :2;
         unsigned int :1;
         unsigned int :3;
         unsigned int :2;
      };
} ODCF;
#word ODCF = 0x2EE

union  {
      struct {
         unsigned int TRISG0:1;
         unsigned int TRISG1:1;
         unsigned int TRISG2:1;
         unsigned int TRISG3:1;
         unsigned int :2;
         unsigned int TRISG6:1;
         unsigned int TRISG7:1;
         unsigned int TRISG8:1;
         unsigned int TRISG9:1;
         unsigned int :2;
         unsigned int TRISG12:1;
         unsigned int TRISG13:1;
         unsigned int TRISG14:1;
         unsigned int TRISG15:1;
      };
      struct {
         unsigned int TRISG:4;
         unsigned int :2;
         unsigned int :4;
         unsigned int :2;
         unsigned int :4;
      };
} TRISG;
#word TRISG = 0x2F0

union  {
      struct {
         unsigned int RG0:1;
         unsigned int RG1:1;
         unsigned int RG2:1;
         unsigned int RG3:1;
         unsigned int :2;
         unsigned int RG6:1;
         unsigned int RG7:1;
         unsigned int RG8:1;
         unsigned int RG9:1;
         unsigned int :2;
         unsigned int RG12:1;
         unsigned int RG13:1;
         unsigned int RG14:1;
         unsigned int RG15:1;
      };
      struct {
         unsigned int RG:4;
         unsigned int :2;
         unsigned int :4;
         unsigned int :2;
         unsigned int :4;
      };
} PORTG;
#word PORTG = 0x2F2

union  {
      struct {
         unsigned int LATG0:1;
         unsigned int LATG1:1;
         unsigned int LATG2:1;
         unsigned int LATG3:1;
         unsigned int :2;
         unsigned int LATG6:1;
         unsigned int LATG7:1;
         unsigned int LATG8:1;
         unsigned int LATG9:1;
         unsigned int :2;
         unsigned int LATG12:1;
         unsigned int LATG13:1;
         unsigned int LATG14:1;
         unsigned int LATG15:1;
      };
      struct {
         unsigned int LATG:4;
         unsigned int :2;
         unsigned int :4;
         unsigned int :2;
         unsigned int :4;
      };
} LATG;
#word LATG = 0x2F4

union  {
      struct {
         unsigned int ODG0:1;
         unsigned int ODG1:1;
         unsigned int ODG2:1;
         unsigned int ODG3:1;
         unsigned int :2;
         unsigned int ODG6:1;
         unsigned int ODG7:1;
         unsigned int ODG8:1;
         unsigned int ODG9:1;
         unsigned int :2;
         unsigned int ODG12:1;
         unsigned int ODG13:1;
         unsigned int ODG14:1;
         unsigned int ODG15:1;
      };
      struct {
         unsigned int ODG:4;
         unsigned int :2;
         unsigned int :4;
         unsigned int :2;
         unsigned int :4;
      };
} ODCG;
#word ODCG = 0x2F6

struct  {
   union {
      struct {
         unsigned int PMPTTL:1;
         unsigned int RTSECSEL:1;
      };

      struct {
         unsigned int :1;
         unsigned int RTSECSEL0:1;
      };
   };
} PADCFG1;
#word PADCFG1 = 0x2FC

#word ADC1BUF0 = 0x300

#word ADC1BUF1 = 0x302

#word ADC1BUF2 = 0x304

#word ADC1BUF3 = 0x306

#word ADC1BUF4 = 0x308

#word ADC1BUF5 = 0x30A

#word ADC1BUF6 = 0x30C

#word ADC1BUF7 = 0x30E

#word ADC1BUF8 = 0x310

#word ADC1BUF9 = 0x312

#word ADC1BUFA = 0x314

#word ADC1BUFB = 0x316

#word ADC1BUFC = 0x318

#word ADC1BUFD = 0x31A

#word ADC1BUFE = 0x31C

#word ADC1BUFF = 0x31E

union  {
      struct {
         unsigned int DONE:1;
         unsigned int SAMP:1;
         unsigned int ASAM:1;
         unsigned int :2;
         unsigned int SSRC0:1;
         unsigned int SSRC1:1;
         unsigned int SSRC2:1;
         unsigned int FORM0:1;
         unsigned int FORM1:1;
         unsigned int :3;
         unsigned int ADSIDL:1;
         unsigned int :1;
         unsigned int ADON:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int SSRC:3;
         unsigned int FORM:2;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} AD1CON1;
#word AD1CON1 = 0x320

union  {
      struct {
         unsigned int ALTS:1;
         unsigned int BUFM:1;
         unsigned int SMPI0:1;
         unsigned int SMPI1:1;
         unsigned int SMPI2:1;
         unsigned int SMPI3:1;
         unsigned int :1;
         unsigned int BUFS:1;
         unsigned int :2;
         unsigned int CSCNA:1;
         unsigned int :1;
         unsigned int OFFCAL:1;
         unsigned int VCFG0:1;
         unsigned int VCFG1:1;
         unsigned int VCFG2:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int SMPI:4;
         unsigned int :1;
         unsigned int :1;
         unsigned int :2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int VCFG:3;
      };
} AD1CON2;
#word AD1CON2 = 0x322

union  {
      struct {
         unsigned int ADCS0:1;
         unsigned int ADCS1:1;
         unsigned int ADCS2:1;
         unsigned int ADCS3:1;
         unsigned int ADCS4:1;
         unsigned int ADCS5:1;
         unsigned int ADCS6:1;
         unsigned int ADCS7:1;
         unsigned int SAMC0:1;
         unsigned int SAMC1:1;
         unsigned int SAMC2:1;
         unsigned int SAMC3:1;
         unsigned int SAMC4:1;
         unsigned int :2;
         unsigned int ADRC:1;
      };
      struct {
         unsigned int ADCS:8;
         unsigned int SAMC:5;
         unsigned int :2;
         unsigned int :1;
      };
} AD1CON3;
#word AD1CON3 = 0x324

union  {
      struct {
         unsigned int CH0SA0:1;
         unsigned int CH0SA1:1;
         unsigned int CH0SA2:1;
         unsigned int CH0SA3:1;
         unsigned int CH0SA4:1;
         unsigned int :2;
         unsigned int CH0NA:1;
         unsigned int CH0SB0:1;
         unsigned int CH0SB1:1;
         unsigned int CH0SB2:1;
         unsigned int CH0SB3:1;
         unsigned int CH0SB4:1;
         unsigned int :2;
         unsigned int CH0NB:1;
      };
      struct {
         unsigned int CH0SA:5;
         unsigned int :2;
         unsigned int :1;
         unsigned int CH0SB:5;
         unsigned int :2;
         unsigned int :1;
      };
} AD1CHS;
#word AD1CHS = 0x328

struct  {
   unsigned int PCFG0:1;
   unsigned int PCFG17:1;
} AD1PCFGH;
#word AD1PCFGH = 0x32A

union  {
      struct {
         unsigned int PCFG0:1;
         unsigned int PCFG1:1;
         unsigned int PCFG2:1;
         unsigned int PCFG3:1;
         unsigned int PCFG4:1;
         unsigned int PCFG5:1;
         unsigned int PCFG6:1;
         unsigned int PCFG7:1;
         unsigned int PCFG8:1;
         unsigned int PCFG9:1;
         unsigned int PCFG10:1;
         unsigned int PCFG11:1;
         unsigned int PCFG12:1;
         unsigned int PCFG13:1;
         unsigned int PCFG14:1;
         unsigned int PCFG15:1;
      };
      struct {
         unsigned int PCFG:16;
      };
} AD1PCFGL;
#word AD1PCFGL = 0x32C

union  {
      struct {
         unsigned int CSSL0:1;
         unsigned int CSSL1:1;
         unsigned int CSSL2:1;
         unsigned int CSSL3:1;
         unsigned int CSSL4:1;
         unsigned int CSSL5:1;
         unsigned int CSSL6:1;
         unsigned int CSSL7:1;
         unsigned int CSSL8:1;
         unsigned int CSSL9:1;
         unsigned int CSSL10:1;
         unsigned int CSSL11:1;
         unsigned int CSSL12:1;
         unsigned int CSSL13:1;
         unsigned int CSSL14:1;
         unsigned int CSSL15:1;
      };
      struct {
         unsigned int CSSL:16;
      };
} AD1CSS;
#word AD1CSSL = 0x330

struct  {
   unsigned int CSSL0:1;
   unsigned int CSSL17:1;
} AD1CSSH;
#word AD1CSSH = 0x332

union  {
      struct {
         unsigned int EDG1STAT:1;
         unsigned int EDG2STAT:1;
         unsigned int EDG1SEL0:1;
         unsigned int EDG1SEL1:1;
         unsigned int EDG1POL:1;
         unsigned int EDG2SEL0:1;
         unsigned int EDG2SEL1:1;
         unsigned int EDG2POL:1;
         unsigned int CTTRIG:1;
         unsigned int IDISSEN:1;
         unsigned int EDGSEQEN:1;
         unsigned int EDGEN:1;
         unsigned int TGEN:1;
         unsigned int CTMUSIDL:1;
         unsigned int :1;
         unsigned int CTMUEN:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int EDG1SEL:2;
         unsigned int :1;
         unsigned int EDG2SEL:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} CTMUCON;
#word CTMUCON = 0x33C

union  {
      struct {
         unsigned int :8;
         unsigned int IRNG0:1;
         unsigned int IRNG1:1;
         unsigned int ITRIM0:1;
         unsigned int ITRIM1:1;
         unsigned int ITRIM2:1;
         unsigned int ITRIM3:1;
         unsigned int ITRIM4:1;
         unsigned int ITRIM5:1;
      };
      struct {
         unsigned int :8;
         unsigned int IRNG:2;
         unsigned int ITRIM:6;
      };
} CTMUICON;
#word CTMUICON = 0x33E

struct  {
   unsigned int VBUSVDIF:1;
   unsigned int :1;
   unsigned int SESENDIF:1;
   unsigned int SESVDIF:1;
   unsigned int ACTVIF:1;
   unsigned int LSTATEIF:1;
   unsigned int T1MSECIF:1;
   unsigned int IDIF:1;
} U1OTGIR;
#word U1OTGIR = 0x480

struct  {
   unsigned int VBUSVDIE:1;
   unsigned int :1;
   unsigned int SESENDIE:1;
   unsigned int SESVDIE:1;
   unsigned int ACTVIE:1;
   unsigned int LSTATEIE:1;
   unsigned int T1MSECIE:1;
   unsigned int IDIE:1;
} U1OTGIE;
#word U1OTGIE = 0x482

struct  {
   unsigned int VBUSVD:1;
   unsigned int :1;
   unsigned int SESEND:1;
   unsigned int SESVD:1;
   unsigned int :1;
   unsigned int LSTATE:1;
   unsigned int :1;
   unsigned int ID:1;
} U1OTGSTAT;
#word U1OTGSTAT = 0x484

struct  {
   unsigned int VBUSDIS:1;
   unsigned int VBUSCHG:1;
   unsigned int OTGEN:1;
   unsigned int VBUSON:1;
   unsigned int DMPULDWN:1;
   unsigned int DPPULDWN:1;
   unsigned int DMPULUP:1;
   unsigned int DPPULUP:1;
} U1OTGCON;
#word U1OTGCON = 0x486

struct  {
   union {
      struct {
         unsigned int USBPWR:1;
         unsigned int USUSPEND:1;
         unsigned int :2;
         unsigned int USLPGRD:1;
         unsigned int :2;
         unsigned int UACTPND:1;
      };

      struct {
         unsigned int :1;
         unsigned int USUSPND:1;
      };
   };
} U1PWRC;
#word U1PWRC = 0x488

struct  {
   union {
      struct {
         unsigned int URSTIF:1;
         unsigned int UERRIF:1;
         unsigned int SOFIF:1;
         unsigned int TRNIF:1;
         unsigned int IDLEIF:1;
         unsigned int RESUMEIF:1;
         unsigned int ATTACHIF:1;
         unsigned int STALLIF:1;
      };

      struct {
         unsigned int DETACHIF:1;
      };
   };
} U1IR;
#word U1IR = 0x48A

struct  {
   union {
      struct {
         unsigned int URSTIE:1;
         unsigned int UERRIE:1;
         unsigned int SOFIE:1;
         unsigned int TRNIE:1;
         unsigned int IDLEIE:1;
         unsigned int RESUMEIE:1;
         unsigned int ATTACHIE:1;
         unsigned int STALLIE:1;
      };

      struct {
         unsigned int DETACHIE:1;
      };
   };
} U1IE;
#word U1IE = 0x48C

struct  {
   union {
      struct {
         unsigned int PIDEF:1;
         unsigned int CRC5EF:1;
         unsigned int CRC16EF:1;
         unsigned int DFN8EF:1;
         unsigned int BTOEF:1;
         unsigned int DMAEF:1;
         unsigned int :1;
         unsigned int BTSEF:1;
      };

      struct {
         unsigned int :1;
         unsigned int EOFEF:1;
      };
   };
} U1EIR;
#word U1EIR = 0x48E

struct  {
   union {
      struct {
         unsigned int PIDEE:1;
         unsigned int CRC5EE:1;
         unsigned int CRC16EE:1;
         unsigned int DFN8EE:1;
         unsigned int BTOEE:1;
         unsigned int DMAEE:1;
         unsigned int :1;
         unsigned int BTSEE:1;
      };

      struct {
         unsigned int :1;
         unsigned int EOFEE:1;
      };
   };
} U1EIE;
#word U1EIE = 0x490

union  {
      struct {
         unsigned int :2;
         unsigned int PPBI:1;
         unsigned int DIR:1;
         unsigned int ENDPT0:1;
         unsigned int ENDPT1:1;
         unsigned int ENDPT2:1;
         unsigned int ENDPT3:1;
      };
      struct {
         unsigned int :2;
         unsigned int :1;
         unsigned int :1;
         unsigned int ENDPT:4;
      };
} U1STAT;
#word U1STAT = 0x492

struct  {
   union {
      struct {
         unsigned int USBEN:1;
         unsigned int PPBRST:1;
         unsigned int RESUME:1;
         unsigned int HOSTEN:1;
         unsigned int RESET:1;
         unsigned int PKTDIS:1;
         unsigned int SE:1;
         unsigned int JSTATE:1;
      };

      struct {
         unsigned int SOFEN:1;
         unsigned int :3;
         unsigned int USBRST:1;
         unsigned int TOKBUSY:1;
      };
   };
} U1CON;
#word U1CON = 0x494

union  {
   union {
      struct {
         unsigned int ADDR0:1;
         unsigned int ADDR1:1;
         unsigned int ADDR2:1;
         unsigned int ADDR3:1;
         unsigned int ADDR4:1;
         unsigned int ADDR5:1;
         unsigned int ADDR6:1;
         unsigned int LSPDEN:1;
      };
      struct {
         unsigned int ADDR:7;
         unsigned int :1;
      };

      struct {
         unsigned int DEVADDR0:1;
         unsigned int DEVADDR1:1;
         unsigned int DEVADDR2:1;
         unsigned int DEVADDR3:1;
         unsigned int DEVADDR4:1;
         unsigned int DEVADDR5:1;
         unsigned int DEVADDR6:1;
         unsigned int LOWSPDEN:1;
      };
   };
      struct {
         unsigned int DEVADDR:7;
         unsigned int :1;
      };
} U1ADDR;
#word U1ADDR = 0x496

struct  {
   union {
      struct {
         unsigned int :1;
         unsigned int BDTBA0:1;
         unsigned int BDTBA1:1;
         unsigned int BDTBA2:1;
         unsigned int BDTBA3:1;
         unsigned int BDTBA4:1;
         unsigned int BDTBA5:1;
         unsigned int BDTBA15:1;
      };

      struct {
         unsigned int :1;
         unsigned int BDTPTRL0:1;
         unsigned int BDTPTRL1:1;
         unsigned int BDTPTRL2:1;
         unsigned int BDTPTRL3:1;
         unsigned int BDTPTRL4:1;
         unsigned int BDTPTRL5:1;
         unsigned int BDTPTRL6:1;
      };
   };
      struct {
         unsigned int :1;
         unsigned int BDTPTRL:7;
      };
} U1BDTP1;
#word U1BDTP1 = 0x498

union  {
      struct {
         unsigned int FRM0:1;
         unsigned int FRM1:1;
         unsigned int FRM2:1;
         unsigned int FRM3:1;
         unsigned int FRM4:1;
         unsigned int FRM5:1;
         unsigned int FRM6:1;
         unsigned int FRM7:1;
      };
      struct {
         unsigned int FRM:8;
      };
} U1FRM;
#word U1FRML = 0x49A

struct  {
   unsigned int FRM0:1;
   unsigned int FRM1:1;
   unsigned int FRM2:1;
   unsigned int FRM3:1;
   unsigned int FRM4:1;
   unsigned int FRM5:1;
   unsigned int FRM6:1;
   unsigned int FRM15:1;
} U1FRMH;
#word U1FRMH = 0x49C

union  {
      struct {
         unsigned int EP0:1;
         unsigned int EP1:1;
         unsigned int EP2:1;
         unsigned int EP3:1;
         unsigned int PID0:1;
         unsigned int PID1:1;
         unsigned int PID2:1;
         unsigned int PID3:1;
      };
      struct {
         unsigned int EP:4;
         unsigned int PID:4;
      };
} U1TOK;
#word U1TOK = 0x49E

union  {
      struct {
         unsigned int CNT0:1;
         unsigned int CNT1:1;
         unsigned int CNT2:1;
         unsigned int CNT3:1;
         unsigned int CNT4:1;
         unsigned int CNT5:1;
         unsigned int CNT6:1;
         unsigned int CNT7:1;
      };
      struct {
         unsigned int CNT:8;
      };
} U1SOF;
#word U1SOF = 0x4A0

union  {
      struct {
         unsigned int PPB0:1;
         unsigned int PPB1:1;
         unsigned int :2;
         unsigned int USBSIDL:1;
         unsigned int :1;
         unsigned int UOEMON:1;
         unsigned int UTEYE:1;
      };
      struct {
         unsigned int PPB:2;
         unsigned int :2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} U1CNFG1;
#word U1CNFG1 = 0x4A6

struct  {
   unsigned int UTRDIS:1;
   unsigned int UVCMPDIS:1;
   unsigned int UVBUSDIS:1;
   unsigned int EXTI2CEN:1;
   unsigned int PUVBUS:1;
} U1CNFG2;
#word U1CNFG2 = 0x4A8

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
         unsigned int :1;
         unsigned int RETRYDIS:1;
         unsigned int LSPD:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
         unsigned int :3;
         unsigned int LOWSPD:1;
      };
   };
} U1EP0;
#word U1EP0 = 0x4AA

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP1;
#word U1EP1 = 0x4AC

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP2;
#word U1EP2 = 0x4AE

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP3;
#word U1EP3 = 0x4B0

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP4;
#word U1EP4 = 0x4B2

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP5;
#word U1EP5 = 0x4B4

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP6;
#word U1EP6 = 0x4B6

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP7;
#word U1EP7 = 0x4B8

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP8;
#word U1EP8 = 0x4BA

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP9;
#word U1EP9 = 0x4BC

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP10;
#word U1EP10 = 0x4BE

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP11;
#word U1EP11 = 0x4C0

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP12;
#word U1EP12 = 0x4C2

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP13;
#word U1EP13 = 0x4C4

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP14;
#word U1EP14 = 0x4C6

struct  {
   union {
      struct {
         unsigned int EPHSHK:1;
         unsigned int EPSTALL:1;
         unsigned int EPTXEN:1;
         unsigned int EPRXEN:1;
         unsigned int EPCONDIS:1;
      };

      struct {
         unsigned int :2;
         unsigned int EPINEN:1;
         unsigned int EPOUTEN:1;
      };
   };
} U1EP15;
#word U1EP15 = 0x4C8

union  {
   union {
      struct {
         unsigned int PER0:1;
         unsigned int PER1:1;
         unsigned int PER2:1;
         unsigned int PER3:1;
         unsigned int PER4:1;
         unsigned int PER5:1;
         unsigned int PER6:1;
         unsigned int PER7:1;
         unsigned int DC0:1;
         unsigned int DC1:1;
         unsigned int DC2:1;
         unsigned int DC3:1;
         unsigned int DC4:1;
         unsigned int DC5:1;
         unsigned int DC6:1;
         unsigned int DC7:1;
      };
      struct {
         unsigned int PER:8;
         unsigned int DC:8;
      };

   union {
      struct {
         unsigned int USBRS0:1;
         unsigned int USBRS1:1;
         unsigned int USBRS2:1;
         unsigned int USBRS3:1;
         unsigned int USBRS4:1;
         unsigned int USBRS5:1;
         unsigned int USBRS6:1;
         unsigned int USBRS7:1;
         unsigned int USBR0:1;
         unsigned int USBR1:1;
         unsigned int USBR2:1;
         unsigned int USBR3:1;
         unsigned int USBR4:1;
         unsigned int USBR5:1;
         unsigned int USBR6:1;
         unsigned int USBR7:1;
      };
   };
      struct {
         unsigned int USBRS:8;
         unsigned int USBR:8;
      };

      struct {
         unsigned int PER0:1;
         unsigned int PER1:1;
         unsigned int PER2:1;
         unsigned int PER3:1;
         unsigned int PER4:1;
         unsigned int PER5:1;
         unsigned int PER6:1;
         unsigned int PER7:1;
         unsigned int DC0:1;
         unsigned int DC1:1;
         unsigned int DC2:1;
         unsigned int DC3:1;
         unsigned int DC4:1;
         unsigned int DC5:1;
         unsigned int DC6:1;
         unsigned int DC7:1;
      };
   };
      struct {
         unsigned int PER:8;
         unsigned int DC:8;
      };
} U1PWMRRS;
#word U1PWMRRS = 0x4CC

union  {
      struct {
         unsigned int :8;
         unsigned int CNTEN:1;
         unsigned int PWMPOL:1;
         unsigned int USBTSEL0:1;
         unsigned int USBTSEL1:1;
         unsigned int USBTSEL2:1;
         unsigned int :2;
         unsigned int PWMEN:1;
      };
      struct {
         unsigned int :8;
         unsigned int :1;
         unsigned int :1;
         unsigned int USBTSEL:3;
         unsigned int :2;
         unsigned int :1;
      };
} U1PWMCON;
#word U1PWMCON = 0x4CE

union  {
      struct {
         unsigned int RDSP:1;
         unsigned int WRSP:1;
         unsigned int BEP:1;
         unsigned int CS1P:1;
         unsigned int CS2P:1;
         unsigned int ALP:1;
         unsigned int CSF0:1;
         unsigned int CSF1:1;
         unsigned int PTRDEN:1;
         unsigned int PTWREN:1;
         unsigned int PTBEEN:1;
         unsigned int ADRMUX0:1;
         unsigned int ADRMUX1:1;
         unsigned int PSIDL:1;
         unsigned int :1;
         unsigned int PMPEN:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int CSF:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int ADRMUX:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} PMCON;
#word PMCON = 0x600

union  {
   union {
      struct {
         unsigned int WAITE0:1;
         unsigned int WAITE1:1;
         unsigned int WAITM0:1;
         unsigned int WAITM1:1;
         unsigned int WAITM2:1;
         unsigned int WAITM3:1;
         unsigned int WAITB0:1;
         unsigned int WAITB1:1;
         unsigned int MODE0:1;
         unsigned int MODE1:1;
         unsigned int MODE2:1;
         unsigned int INCM0:1;
         unsigned int INCM1:1;
         unsigned int IRQM0:1;
         unsigned int IRQM1:1;
         unsigned int BUSY:1;
      };
      struct {
         unsigned int WAITE:2;
         unsigned int WAITM:4;
         unsigned int WAITB:2;
         unsigned int MODE:2;
         unsigned int :1;
         unsigned int INCM:2;
         unsigned int IRQM:2;
         unsigned int :1;
      };

   union {
      struct {
         unsigned int WAIT0:1;
         unsigned int WAIT1:1;
         unsigned int WAIT2:3;
         unsigned int WAIT3:2;
         unsigned int MODE0:1;
         unsigned int MODE1:1;
         unsigned int INCM0:1;
         unsigned int INCM1:1;
         unsigned int IRCM0:1;
         unsigned int IRCM1:1;
         unsigned int _8_:1;
         unsigned int BUSY:1;
      };
   };
      struct {
         unsigned int WAIT:2;
         unsigned int :3;
         unsigned int :2;
         unsigned int MODE:2;
         unsigned int INCM:2;
         unsigned int IRCM:2;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int WAITE0:1;
         unsigned int WAITE1:1;
         unsigned int WAITM0:1;
         unsigned int WAITM1:1;
         unsigned int WAITM2:1;
         unsigned int WAITM3:1;
         unsigned int WAITB0:1;
         unsigned int WAITB1:1;
         unsigned int MODE0:1;
         unsigned int MODE1:1;
         unsigned int :1;
         unsigned int INCM0:1;
         unsigned int INCM1:1;
         unsigned int IRQM0:1;
         unsigned int IRQM1:1;
      };
   };
      struct {
         unsigned int WAITE:2;
         unsigned int WAITM:4;
         unsigned int WAITB:2;
         unsigned int MODE:2;
         unsigned int :1;
         unsigned int INCM:2;
         unsigned int IRQM:2;
      };
} PMMODE;
#word PMMODE = 0x602

union  {
   union {
      struct {
         unsigned int ADDR0:1;
         unsigned int ADDR1:1;
         unsigned int ADDR2:1;
         unsigned int ADDR3:1;
         unsigned int ADDR4:1;
         unsigned int ADDR5:1;
         unsigned int ADDR6:1;
         unsigned int ADDR7:1;
         unsigned int ADDR8:1;
         unsigned int ADDR9:1;
         unsigned int ADDR10:1;
         unsigned int ADDR11:1;
         unsigned int ADDR12:1;
         unsigned int ADDR13:1;
         unsigned int CS0:1;
         unsigned int CS1:1;
      };
      struct {
         unsigned int ADDR:14;
         unsigned int CS:2;
      };

      struct {
         unsigned int ADDR0:1;
         unsigned int ADDR1:1;
         unsigned int ADDR2:1;
         unsigned int ADDR3:1;
         unsigned int ADDR4:1;
         unsigned int ADDR5:1;
         unsigned int ADDR6:1;
         unsigned int ADDR7:1;
         unsigned int ADDR8:1;
         unsigned int ADDR9:1;
         unsigned int ADDR10:1;
         unsigned int ADDR11:1;
         unsigned int ADDR12:1;
         unsigned int ADDR13:1;
         unsigned int CS14:1;
         unsigned int CS2:1;
      };
   };
      struct {
         unsigned int ADDR:14;
         unsigned int :2;
      };
} PMADDR;
#word PMADDR = 0x604

#word PMDOUT2 = 0x606

#word PMDIN1 = 0x608

#word PMDIN2 = 0x60A

union  {
      struct {
         unsigned int PTEN0:1;
         unsigned int PTEN1:1;
         unsigned int PTEN2:1;
         unsigned int PTEN3:1;
         unsigned int PTEN4:1;
         unsigned int PTEN5:1;
         unsigned int PTEN6:1;
         unsigned int PTEN7:1;
         unsigned int PTEN8:1;
         unsigned int PTEN9:1;
         unsigned int PTEN10:1;
         unsigned int PTEN11:1;
         unsigned int PTEN12:1;
         unsigned int PTEN13:1;
         unsigned int PTEN14:1;
         unsigned int PTEN15:1;
      };
      struct {
         unsigned int PTEN:16;
      };
} PMAEN;
#word PMAEN = 0x60C

struct  {
   unsigned int OB0E:1;
   unsigned int OB1E:1;
   unsigned int OB2E:1;
   unsigned int OB3E:1;
   unsigned int :2;
   unsigned int OBUF:1;
   unsigned int OBE:1;
   unsigned int IB0F:1;
   unsigned int IB1F:1;
   unsigned int IB2F:1;
   unsigned int IB3F:1;
   unsigned int :2;
   unsigned int IBOV:1;
   unsigned int IBF:1;
} PMSTAT;
#word PMSTAT = 0x60E

#word ALRMVAL = 0x620

union  {
      struct {
         unsigned int ARPT0:1;
         unsigned int ARPT1:1;
         unsigned int ARPT2:1;
         unsigned int ARPT3:1;
         unsigned int ARPT4:1;
         unsigned int ARPT5:1;
         unsigned int ARPT6:1;
         unsigned int ARPT7:1;
         unsigned int ALRMPTR0:1;
         unsigned int ALRMPTR1:1;
         unsigned int AMASK0:1;
         unsigned int AMASK1:1;
         unsigned int AMASK2:1;
         unsigned int AMASK3:1;
         unsigned int CHIME:1;
         unsigned int ALRMEN:1;
      };
      struct {
         unsigned int ARPT:8;
         unsigned int ALRMPTR:2;
         unsigned int AMASK:4;
         unsigned int :1;
         unsigned int :1;
      };
} ALCFGRPT;
#word ALCFGRPT = 0x622

#word RTCVAL = 0x624

union  {
      struct {
         unsigned int CAL0:1;
         unsigned int CAL1:1;
         unsigned int CAL2:1;
         unsigned int CAL3:1;
         unsigned int CAL4:1;
         unsigned int CAL5:1;
         unsigned int CAL6:1;
         unsigned int CAL7:1;
         unsigned int RTCPTR0:1;
         unsigned int RTCPTR1:1;
         unsigned int RTCOE:1;
         unsigned int HALFSEC:1;
         unsigned int RTCSYNC:1;
         unsigned int RTCWREN:1;
         unsigned int :1;
         unsigned int RTCEN:1;
      };
      struct {
         unsigned int CAL:8;
         unsigned int RTCPTR:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} RCFGCAL;
#word RCFGCAL = 0x626

struct  {
   unsigned int C1OUT:1;
   unsigned int C2OUT:1;
   unsigned int C3OUT:1;
   unsigned int C4OUT:1;
   unsigned int C5OUT:1;
   unsigned int C6OUT:1;
   unsigned int :2;
   unsigned int C1EVT:1;
   unsigned int C2EVT:1;
   unsigned int C3EVT:1;
   unsigned int C4EVT:1;
   unsigned int C5EVT:1;
   unsigned int C6EVT:1;
   unsigned int :1;
   unsigned int CMIDL:1;
} CMSTAT;
#word CMSTAT = 0x630

union  {
      struct {
         unsigned int CVR0:1;
         unsigned int CVR1:1;
         unsigned int CVR2:1;
         unsigned int CVR3:1;
         unsigned int CVRSS:1;
         unsigned int CVRR:1;
         unsigned int CVROE:1;
         unsigned int CVREN:1;
      };
      struct {
         unsigned int CVR:4;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };
} CVRCON;
#word CVRCON = 0x632

union  {
   union {
      struct {
         unsigned int CCH0:1;
         unsigned int CCH1:1;
         unsigned int :2;
         unsigned int CREF:1;
         unsigned int :1;
         unsigned int EVPOL0:1;
         unsigned int EVPOL1:1;
         unsigned int COUT:1;
         unsigned int CEVT:1;
         unsigned int :3;
         unsigned int CPOL:1;
         unsigned int COE:1;
         unsigned int CON:1;
      };
      struct {
         unsigned int CCH:2;
         unsigned int :2;
         unsigned int :1;
         unsigned int :1;
         unsigned int EVPOL:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int CCH0:1;
         unsigned int CCH1:1;
         unsigned int :4;
         unsigned int EVPOL0:1;
         unsigned int EVPOL1:1;
         unsigned int :7;
         unsigned int CEN:1;
      };
   };
      struct {
         unsigned int CCH:2;
         unsigned int :4;
         unsigned int EVPOL:2;
         unsigned int :7;
         unsigned int :1;
      };
} CM1CON;
#word CM1CON = 0x634

union  {
   union {
      struct {
         unsigned int CCH0:1;
         unsigned int CCH1:1;
         unsigned int :2;
         unsigned int CREF:1;
         unsigned int :1;
         unsigned int EVPOL0:1;
         unsigned int EVPOL1:1;
         unsigned int COUT:1;
         unsigned int CEVT:1;
         unsigned int :3;
         unsigned int CPOL:1;
         unsigned int COE:1;
         unsigned int CON:1;
      };
      struct {
         unsigned int CCH:2;
         unsigned int :2;
         unsigned int :1;
         unsigned int :1;
         unsigned int EVPOL:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int CCH0:1;
         unsigned int CCH1:1;
         unsigned int :4;
         unsigned int EVPOL0:1;
         unsigned int EVPOL1:1;
         unsigned int :7;
         unsigned int CEN:1;
      };
   };
      struct {
         unsigned int CCH:2;
         unsigned int :4;
         unsigned int EVPOL:2;
         unsigned int :7;
         unsigned int :1;
      };
} CM2CON;
#word CM2CON = 0x636

union  {
   union {
      struct {
         unsigned int CCH0:1;
         unsigned int CCH1:1;
         unsigned int :2;
         unsigned int CREF:1;
         unsigned int :1;
         unsigned int EVPOL0:1;
         unsigned int EVPOL1:1;
         unsigned int COUT:1;
         unsigned int CEVT:1;
         unsigned int :3;
         unsigned int CPOL:1;
         unsigned int COE:1;
         unsigned int CON:1;
      };
      struct {
         unsigned int CCH:2;
         unsigned int :2;
         unsigned int :1;
         unsigned int :1;
         unsigned int EVPOL:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int CCH0:1;
         unsigned int CCH1:1;
         unsigned int :4;
         unsigned int EVPOL0:1;
         unsigned int EVPOL1:1;
         unsigned int :7;
         unsigned int CEN:1;
      };
   };
      struct {
         unsigned int CCH:2;
         unsigned int :4;
         unsigned int EVPOL:2;
         unsigned int :7;
         unsigned int :1;
      };
} CM3CON;
#word CM3CON = 0x638

union  {
      struct {
         unsigned int PLEN0:1;
         unsigned int PLEN1:1;
         unsigned int PLEN2:1;
         unsigned int PLEN3:1;
         unsigned int CRCGO:1;
         unsigned int :1;
         unsigned int CRCMPT:1;
         unsigned int CRCFUL:1;
         unsigned int VWORD0:1;
         unsigned int VWORD1:1;
         unsigned int VWORD2:1;
         unsigned int VWORD3:1;
         unsigned int VWORD4:1;
         unsigned int CSIDL:1;
      };
      struct {
         unsigned int PLEN:4;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int VWORD:5;
         unsigned int :1;
      };
} CRCCON;
#word CRCCON = 0x640

struct  {
   unsigned int :1;
   unsigned int X0:1;
   unsigned int X1:1;
   unsigned int X2:1;
   unsigned int X3:1;
   unsigned int X4:1;
   unsigned int X5:1;
   unsigned int X6:1;
   unsigned int X7:1;
   unsigned int X8:1;
   unsigned int X9:1;
   unsigned int X10:1;
   unsigned int X11:1;
   unsigned int X12:1;
   unsigned int X13:1;
   unsigned int X15:1;
} CRCXOR;
#word CRCXOR = 0x642

#word CRCDAT = 0x644

#word CRCWDAT = 0x646

struct {
   unsigned int :8;
   unsigned int INT1R:6;
} RPINR0;
#word RPINR0 = 0x680

      struct {
         unsigned int INT2R:6;
         unsigned int :2;
         unsigned int INT3R:6;
} RPINR1;
#word RPINR1 = 0x682

      struct {
         unsigned int INT4R:6;
         unsigned int :2;
         unsigned int T1CKR:6;
} RPINR2;
#word RPINR2 = 0x684

      struct {
         unsigned int T2CKR:6;
         unsigned int :2;
         unsigned int T3CKR:6;
} RPINR3;
#word RPINR3 = 0x686

      struct {
         unsigned int T4CKR:6;
         unsigned int :2;
         unsigned int T5CKR:6;
} RPINR4;
#word RPINR4 = 0x688

      struct {
         unsigned int IC1R:6;
         unsigned int :2;
         unsigned int IC2R:6;
} RPINR7;
#word RPINR7 = 0x68E

      struct {
         unsigned int IC3R:6;
         unsigned int :2;
         unsigned int IC4R:6;
} RPINR8;
#word RPINR8 = 0x690

      struct {
         unsigned int IC5R:6;
         unsigned int :2;
         unsigned int IC6R:6;
} RPINR9;
#word RPINR9 = 0x692

      struct {
         unsigned int IC7R:6;
         unsigned int :2;
         unsigned int IC8R:6;
} RPINR10;
#word RPINR10 = 0x694

      struct {
         unsigned int OCFAR:6;
         unsigned int :2;
         unsigned int OCFBR:6;
} RPINR11;
#word RPINR11 = 0x696

      struct {
         unsigned int :8;
         unsigned int IC9R:6;
} RPINR15;
#word RPINR15 = 0x69E

      struct {
         unsigned int :8;
         unsigned int U3RXR:6;
} RPINR17;
#word RPINR17 = 0x6A2

      struct {
         unsigned int U1RXR:6;
         unsigned int :2;
         unsigned int U1CTSR:6;
} RPINR18;
#word RPINR18 = 0x6A4

      struct {
         unsigned int U2RXR:6;
         unsigned int :2;
         unsigned int U2CTSR:6;
} RPINR19;
#word RPINR19 = 0x6A6

      struct {
         unsigned int SDI1R:6;
         unsigned int :2;
         unsigned int SCK1R:6;
} RPINR20;
#word RPINR20 = 0x6A8

      struct {
         unsigned int SS1R:6;
         unsigned int :2;
         unsigned int U3CTSR:6;
} RPINR21;
#word RPINR21 = 0x6AA

      struct {
         unsigned int SDI2R:6;
         unsigned int :2;
         unsigned int SCK2R:6;
} RPINR22;
#word RPINR22 = 0x6AC

      struct {
         unsigned int SS2R:6;
} RPINR23;
#word RPINR23 = 0x6AE

      struct {
         unsigned int U4RXR:6;
         unsigned int :2;
         unsigned int U4CTSR:6;
} RPINR27;
#word RPINR27 = 0x6B6

      struct {
         unsigned int SDI3R:6;
         unsigned int :2;
         unsigned int SCK3R:6;
} RPINR28;
#word RPINR28 = 0x6B8

      struct {
         unsigned int SS3R:6;
} RPINR29;
#word RPINR29 = 0x6BA

      struct {
         unsigned int RP0R:6;
         unsigned int :2;
         unsigned int RP1R:6;
} RPOR0;
#word RPOR0 = 0x6C0

      struct {
         unsigned int RP2R:6;
         unsigned int :2;
         unsigned int RP3R:6;
} RPOR1;
#word RPOR1 = 0x6C2

      struct {
         unsigned int RP4R:6;
         unsigned int :2;
         unsigned int RP5R:6;
} RPOR2;
#word RPOR2 = 0x6C4

      struct {
         unsigned int RP6R:6;
         unsigned int :2;
         unsigned int RP7R:6;
} RPOR3;
#word RPOR3 = 0x6C6

      struct {
         unsigned int RP8R:6;
         unsigned int :2;
         unsigned int RP9R:6;
} RPOR4;
#word RPOR4 = 0x6C8

      struct {
         unsigned int RP10R:6;
         unsigned int :2;
         unsigned int RP11R:6;
} RPOR5;
#word RPOR5 = 0x6CA

      struct {
         unsigned int RP12R:6;
         unsigned int :2;
         unsigned int RP13R:6;
} RPOR6;
#word RPOR6 = 0x6CC

      struct {
         unsigned int RP14R:6;
         unsigned int :2;
         unsigned int RP15R:6;
} RPOR7;
#word RPOR7 = 0x6CE

      struct {
         unsigned int RP16R:6;
         unsigned int :2;
         unsigned int RP17R:6;
} RPOR8;
#word RPOR8 = 0x6D0

      struct {
         unsigned int RP18R:6;
         unsigned int :2;
         unsigned int RP19R:6;
} RPOR9;
#word RPOR9 = 0x6D2

      struct {
         unsigned int RP20R:6;
         unsigned int :2;
         unsigned int RP21R:6;
} RPOR10;
#word RPOR10 = 0x6D4

      struct {
         unsigned int RP22R:6;
         unsigned int :2;
         unsigned int RP23R:6;
} RPOR11;
#word RPOR11 = 0x6D6

      struct {
         unsigned int RP24R:6;
         unsigned int :2;
         unsigned int RP25R:6;
} RPOR12;
#word RPOR12 = 0x6D8

      struct {
         unsigned int RP26R:6;
         unsigned int :2;
         unsigned int RP27R:6;
} RPOR13;
#word RPOR13 = 0x6DA

      struct {
         unsigned int RP28R:6;
         unsigned int :2;
         unsigned int RP29R:6;
} RPOR14;
#word RPOR14 = 0x6DC

      struct {
         unsigned int RP30R:6;
         unsigned int :2;
         unsigned int RP31R:6;
} RPOR15;
#word RPOR15 = 0x6DE

struct  {
   union {
      struct {
         unsigned int POR:1;
         unsigned int BOR:1;
         unsigned int IDLE:1;
         unsigned int SLEEP:1;
         unsigned int WDTO:1;
         unsigned int SWDTEN:1;
         unsigned int SWR:1;
         unsigned int EXTR:1;
         unsigned int VREGS:1;
         unsigned int CM:1;
         unsigned int :4;
         unsigned int IOPUWR:1;
         unsigned int TRAPR:1;
      };

      struct {
         unsigned int :8;
         unsigned int PMSLP:1;
      };
   };
} RCON;
#word RCON = 0x740

union  {
   union {
      struct {
         unsigned int OSWEN:1;
         unsigned int SOSCEN:1;
         unsigned int POSCEN:1;
         unsigned int CF:1;
         unsigned int :1;
         unsigned int LOCK:1;
         unsigned int IOLOCK:1;
         unsigned int CLKLOCK:1;
         unsigned int NOSC0:1;
         unsigned int NOSC1:1;
         unsigned int NOSC2:1;
         unsigned int :1;
         unsigned int COSC0:1;
         unsigned int COSC1:1;
         unsigned int COSC2:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int NOSC:3;
         unsigned int :1;
         unsigned int COSC:3;
      };

      struct {
         unsigned int :1;
         unsigned int LPOSCEN:1;
         unsigned int :6;
         unsigned int NOSC0:1;
         unsigned int NOSC1:1;
         unsigned int NOSC2:1;
         unsigned int :1;
         unsigned int COSC0:1;
         unsigned int COSC1:1;
         unsigned int COSC2:1;
      };
   };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :6;
         unsigned int NOSC:3;
         unsigned int :1;
         unsigned int COSC:3;
      };
} OSCCON;
#word OSCCON = 0x742

union  {
   union {
      struct {
         unsigned int :6;
         unsigned int CPDIV0:1;
         unsigned int CPDIV1:1;
         unsigned int RCDIV0:1;
         unsigned int RCDIV1:1;
         unsigned int RCDIV2:1;
         unsigned int DOZEN:1;
         unsigned int DOZE0:1;
         unsigned int DOZE1:1;
         unsigned int DOZE2:1;
         unsigned int ROI:1;
      };
      struct {
         unsigned int :6;
         unsigned int CPDIV:2;
         unsigned int RCDIV:3;
         unsigned int :1;
         unsigned int DOZE:3;
         unsigned int :1;
      };

      struct {
         unsigned int :6;
         unsigned int USBDOZE0:1;
         unsigned int USBDOZE1:1;
      };
   };
      struct {
         unsigned int :6;
         unsigned int USBDOZE:2;
      };
} CLKDIV;
#word CLKDIV = 0x744

union  {
      struct {
         unsigned int TUN0:1;
         unsigned int TUN1:1;
         unsigned int TUN2:1;
         unsigned int TUN3:1;
         unsigned int TUN4:1;
         unsigned int TUN5:1;
      };
      struct {
         unsigned int TUN:6;
      };
} OSCTUN;
#word OSCTUN = 0x748

union  {
   union {
      struct {
         unsigned int :8;
         unsigned int RODIV0:1;
         unsigned int RODIV1:1;
         unsigned int RODIV2:1;
         unsigned int RODIV3:1;
         unsigned int ROSEL:1;
         unsigned int ROSSLP:1;
         unsigned int :1;
         unsigned int ROEN:1;
      };
      struct {
         unsigned int :8;
         unsigned int RODIV:4;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int :8;
         unsigned int RODIV0:1;
         unsigned int RODIV1:1;
         unsigned int RODIV2:1;
         unsigned int RODIV3:1;
         unsigned int :3;
         unsigned int ROON:1;
      };
   };
      struct {
         unsigned int :8;
         unsigned int RODIV:4;
         unsigned int :3;
         unsigned int :1;
      };
} REFOCON;
#word REFOCON = 0x74E

union  {
   union {
      struct {
         unsigned int NVMOP0:1;
         unsigned int NVMOP1:1;
         unsigned int NVMOP2:1;
         unsigned int NVMOP3:1;
         unsigned int :2;
         unsigned int ERASE:1;
         unsigned int :6;
         unsigned int WRERR:1;
         unsigned int WREN:1;
         unsigned int WR:1;
      };
      struct {
         unsigned int NVMOP:4;
         unsigned int :2;
         unsigned int :1;
         unsigned int :6;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
      };

      struct {
         unsigned int PROGOP0:1;
         unsigned int PROGOP1:1;
         unsigned int PROGOP2:1;
         unsigned int PROGOP3:1;
      };
   };
      struct {
         unsigned int PROGOP:4;
      };
} NVMCON;
#word NVMCON = 0x760

#word NVMKEY = 0x766

struct  {
   unsigned int ADC1MD:1;
   unsigned int :2;
   unsigned int SPI1MD:1;
   unsigned int SPI2MD:1;
   unsigned int U1MD:1;
   unsigned int U2MD:1;
   unsigned int I2C1MD:1;
   unsigned int :3;
   unsigned int T1MD:1;
   unsigned int T2MD:1;
   unsigned int T3MD:1;
   unsigned int T4MD:1;
   unsigned int T5MD:1;
} PMD1;
#word PMD1 = 0x770

struct  {
   unsigned int OC1MD:1;
   unsigned int OC2MD:1;
   unsigned int OC3MD:1;
   unsigned int OC4MD:1;
   unsigned int OC5MD:1;
   unsigned int OC6MD:1;
   unsigned int OC7MD:1;
   unsigned int OC8MD:1;
   unsigned int IC1MD:1;
   unsigned int IC2MD:1;
   unsigned int IC3MD:1;
   unsigned int IC4MD:1;
   unsigned int IC5MD:1;
   unsigned int IC6MD:1;
   unsigned int IC7MD:1;
   unsigned int IC8MD:1;
} PMD2;
#word PMD2 = 0x772

struct  {
   union {
      struct {
         unsigned int :1;
         unsigned int I2C2MD:1;
         unsigned int I2C3MD:1;
         unsigned int U3MD:1;
         unsigned int :3;
         unsigned int CRCMD:1;
         unsigned int PMPMD:1;
         unsigned int RTCCMD:1;
         unsigned int CMPMD:1;
      };

      struct {
         unsigned int :7;
         unsigned int CRCPMD:1;
      };
   };
} PMD3;
#word PMD3 = 0x774

struct  {
   unsigned int USB1MD:1;
   unsigned int LVDMD:1;
   unsigned int CTMUMD:1;
   unsigned int REFOMD:1;
   unsigned int :1;
   unsigned int U4MD:1;
   unsigned int UPWMMD:1;
} PMD4;
#word PMD4 = 0x776

struct  {
   unsigned int OC9MD:1;
   unsigned int :7;
   unsigned int IC9MD:1;
} PMD5;
#word PMD5 = 0x778

struct  {
   unsigned int SPI3MD:1;
} PMD6;
#word PMD6 = 0x77A

