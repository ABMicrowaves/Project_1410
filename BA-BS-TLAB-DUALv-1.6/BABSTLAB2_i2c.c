
#define EE_DEVICE_ADDR 0xA0

#define  SDA    PIN_C13
#define  SCL    PIN_D9

#define  IIC_READ 1

//--------------------------------------------------------------------------
void IIC_Delay(void)
  {
  delay_us(2);
  }

//--------------------------------------------------------------------------
void  init_i2c(void)
  {
  output_drive(SCL);
  output_drive(SDA);
  Output_high(SCL);
  Output_high(SDA);
  }

//--------------------------------------------------------------------------
// Sends ack to I2C device
//--------------------------------------------------------------------------
void IIC_SendAck(void)
  {
  output_low(SDA);
  IIC_Delay();
  output_high(SCL);
  IIC_Delay();
  output_low(SCL);
  IIC_Delay();
  output_high(SDA);
  }

//--------------------------------------------------------------------------
// Sends one unsigned to I2C device
//--------------------------------------------------------------------------
void IIC_SendOne(void)
  {
  output_high(SDA);
  IIC_Delay();
  output_high(SCL);
  IIC_Delay();
  output_low(SCL);
  }

//--------------------------------------------------------------------------
// Sends 8 bits to I2C device
// Gets the byte to send from W register
//--------------------------------------------------------------------------
bit IIC_WriteByte(UCHAR  send_bits)
  {
  UINT count;
  bit   Ack;
  output_drive(SCL);
  output_drive(SDA);
  for (count = 0; count < 8; count++)
    {
    if (send_bits & 0x80)
      Output_high(SDA);
    else
      Output_low(SDA);
    send_bits <<= 1;

    output_high(SCL);
    IIC_Delay();
    output_low(SCL);
    }
  output_high(SDA);
  
  output_float(SDA);
  IIC_Delay();
  output_high(SCL);
  IIC_Delay();
  Ack = input(SDA);
  output_low(SCL);
  output_float(SDA);
//  output_float(SCL);
  delay_us(50);
  return !Ack;
  }

//--------------------------------------------------------------------------
// Receives 8 bits from I2C device
// returns the received byte in the W reg.
//--------------------------------------------------------------------------
UCHAR IIC_ReadByte(UCHAR ack)
  {
  UCHAR rec_bits = 0;
  UINT count;
  output_drive(SCL);
  output_high(SDA);
  output_float(SDA);
  IIC_Delay();
  for (count = 0; count < 8; count++)
    {
    rec_bits <<= 1;
    output_high(SCL);
    IIC_Delay();
    if (input(SDA))
      rec_bits |= 1;
    output_low(SCL);
    IIC_Delay();
    }
  output_drive(SDA);
  output_high(SDA);
  if (ack)
    IIC_SendAck();
  delay_us(50);
  return rec_bits;
  }

//--------------------------------------------------------------------------
// Sends start unsigned to I2C device
//--------------------------------------------------------------------------
void IIC_Start(void)
  {
  output_high(SDA);
  IIC_Delay();
  IIC_Delay();
  output_high(SCL);
  IIC_Delay();
  IIC_Delay();
  output_low(SDA);
  IIC_Delay();
  IIC_Delay();
  output_low(SCL);
  IIC_Delay();
  IIC_Delay();
  }

//--------------------------------------------------------------------------
// Sends stop unsigned to I2C device
//--------------------------------------------------------------------------
void IIC_Stop(void)
  {
  output_drive(SDA);
  output_low(SDA);
  IIC_Delay();
  IIC_Delay();
  output_high(SCL);
  IIC_Delay();
  IIC_Delay();
  output_high(SDA);
  IIC_Delay();
  }


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void IIC_PacketPreamble(UINT Address)
  {
//  IIC_Polling();
  IIC_Start();
  IIC_WriteByte(EE_DEVICE_ADDR);
  IIC_WriteByte(make8(Address, 1));
  IIC_WriteByte(make8(Address, 0));
  }

//--------------------------------------------------------------------------
void IIC_PrepareToRead(UINT Address)
  {
  IIC_PacketPreamble(Address);
  IIC_Stop();
  IIC_Start();
  IIC_WriteByte(EE_DEVICE_ADDR | IIC_READ);
  }

//--------------------------------------------------------------------------
void IIC_CloseRead(void)
  {
  IIC_ReadByte(0);
  IIC_SendOne();
  IIC_Stop();
  }

//--------------------------------------------------------------------------
void IIC_ReadBytes(UINT Address, UCHAR *bufptr, UINT n_Len)
  {
  IIC_PrepareToRead(Address);
  while (n_Len--)
    {
    *bufptr++ = IIC_ReadByte(0);
    IIC_SendAck();
    }
  IIC_CloseRead();
  }

//--------------------------------------------------------------------------
void IIC_WriteBytes(UINT Address,UCHAR *bufptr,  UINT n_Len)
  {
  IIC_PacketPreamble(Address);
#ignore_warnings 203 // the following loop IS an endless loop
  while (1)
    {
#ignore_warnings none // the following loop IS an endless loop
    IIC_WriteByte(*bufptr++);
    ++Address;
    if (!--n_Len)
      break;
    }
  IIC_Stop();
  }


