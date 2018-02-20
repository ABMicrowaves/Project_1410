#define SYNC_CLOCK 120000000.00

UCHAR FPGA_status[2][8];

//--------------------------------------------------------------------------
void send_command_to_FPGA1(UCHAR length, UCHAR *data)
  {
  UCHAR xbyte;
  UINT cnt;
  output_low(BS1_CS);
  delay_us(5);
  while (length--)
    {
    xbyte = *data++;
    for (cnt = 0; cnt < 8; cnt++)
      {
      if (xbyte & 0x80)
        output_high(BS1_MOSI);
      else
        output_low(BS1_MOSI);
      delay_us(5);
      output_high(BS1_SCK);
      delay_us(5);
      output_low(BS1_SCK);
      delay_us(5);
      xbyte <<= 1;
      }
    }
    /*
  output_low(BS1_MOSI);
  for (bytes = 0; bytes < 5; bytes++)
    {
    for (xbyte = 0, cnt = 0; cnt < 8; cnt++)
      {
      xbyte <<= 1;
      delay_us(5);
      output_high(BS1_SCK);
      delay_us(3);
      if (input(BS1_MISO))
        {
        xbyte |= 1;
        delay_us(2);
        }
      delay_us(2);
      output_low(BS1_SCK);
      delay_us(3);
      }
    FPGA_status[0][bytes] = xbyte;
    }
    */
  output_high(BS1_CS);
  }

//--------------------------------------------------------------------------
void send_command_to_FPGA2(UCHAR length, UCHAR *data)
  {
  UCHAR xbyte;
  UINT cnt;
  output_low(BS2_CS);
  delay_us(5);
  while (length--)
    {
    xbyte = *data++;
    for (cnt = 0; cnt < 8; cnt++)
      {
      if (xbyte & 0x80)
        output_high(BS2_MOSI);
      else
        output_low(BS2_MOSI);
      delay_us(5);
      output_high(BS2_SCK);
      delay_us(5);
      output_low(BS2_SCK);
      delay_us(5);
      xbyte <<= 1;
      }
    }
    /*
  output_low(BS2_MOSI);
  for (bytes = 0; bytes < 5; bytes++)
    {
    for (xbyte = 0, cnt = 0; cnt < 8; cnt++)
      {
      xbyte <<= 1;
      delay_us(5);
      output_high(BS2_SCK);
      delay_us(3);
      if (input(BS2_MISO))
        {
        xbyte |= 1;
        delay_us(2);
        }
      delay_us(2);
      output_low(BS2_SCK);
      delay_us(3);
      }
    FPGA_status[1][bytes] = xbyte;
    }
    */
  output_high(BS2_CS);
  }


//--------------------------------------------------------------------------
//BR(31:0)=Round(2^32 * (bit rate)/93.333MHz)
ULONG compute_bitrate_coefficient(ULONG bitrate)
  {
  float bitspersec, temp;
  bitspersec = (float)bitrate;
  temp = bitspersec / SYNC_CLOCK;
  temp *= 65536.0;
  temp *= 65536.0;
  return (ULONG)temp - 1;
  }

//--------------------------------------------------------------------------
void set_bitrate(UINT synchronizer, UINT bitrate)
  {
  UCHAR buf[7];
  ULONG bitf;
  bitf = compute_bitrate_coefficient((ULONG)bitrate * 1000000L);
  buf[0] = 0;
  buf[1] = make8(bitf, 0);
  buf[2] = make8(bitf, 1);
  buf[3] = make8(bitf, 2);
  buf[4] = make8(bitf, 3);
  if (synchronizer == 1)
    send_command_to_FPGA1(5, buf);
  else
    send_command_to_FPGA2(5, buf);
  }

//--------------------------------------------------------------------------
void set_synchronizer_params(UINT synchronizer, UINT bitrate)
  {
  UCHAR buf[9], clock_phase, randl;
  const UCHAR xlat_cp[] = { 1,2,3,0 };
  ULONG bitf;
 // clock_phase = xlat_cp[setup[synchronizer-1].output_clock_phase];
  bitf = compute_bitrate_coefficient((ULONG)setup[synchronizer-1].bitrate * 10000L);
  buf[0] = 0;
  buf[1] = make8(bitf, 0);
  buf[2] = make8(bitf, 1);
  buf[3] = make8(bitf, 2);
  buf[4] = make8(bitf, 3);
  buf[5] = setup[synchronizer-1].loop_bw;
  buf[6] = setup[synchronizer-1].input_enc;
/*if (setup[synchronizer-1].random_length)
    randl = 3;
  else 
    randl = 0;
 */

  buf[7] = setup[synchronizer-1].random_length |
           (setup[synchronizer-1].input_polarity << 2) |
           (setup[synchronizer-1].output_clock_phase << 3) |
           (setup[synchronizer-1].filter_select << 5);
  if (synchronizer == 1)
    send_command_to_FPGA1(8, buf);
  else
    send_command_to_FPGA2(8, buf);
  }

//--------------------------------------------------------------------------
UCHAR get_register_from_FPGA1(UCHAR addr)
  {
  UCHAR xbyte;
  UINT cnt;
  output_low(BS1_CS);
  delay_us(5);
  xbyte = addr;
  for (cnt = 0; cnt < 8; cnt++)
    {
    if (xbyte & 0x80)
      output_high(BS1_MOSI);
    else
      output_low(BS1_MOSI);
    delay_us(5);
    output_high(BS1_SCK);
    delay_us(5);
    output_low(BS1_SCK);
    delay_us(5);
    xbyte <<= 1;
    }
  output_low(BS1_MOSI);
  for (xbyte = 0, cnt = 0; cnt < 8; cnt++)
    {
    xbyte <<= 1;
    delay_us(5);
    output_high(BS1_SCK);
    delay_us(3);
    if (input(BS1_MISO))
      {
      xbyte |= 1;
      delay_us(2);
      }
    delay_us(2);
    output_low(BS1_SCK);
    delay_us(3);
    }
  FPGA_status[0][0] = xbyte;
  output_high(BS1_CS);
  return xbyte;
  }

//--------------------------------------------------------------------------
UCHAR get_register_from_FPGA2(UCHAR addr)
  {
  UCHAR xbyte;
  UINT cnt;
  output_low(BS2_CS);
  delay_us(5);
  xbyte = addr;
  for (cnt = 0; cnt < 8; cnt++)
    {
    if (xbyte & 0x80)
      output_high(BS2_MOSI);
    else
      output_low(BS2_MOSI);
    delay_us(5);
    output_high(BS2_SCK);
    delay_us(5);
    output_low(BS2_SCK);
    delay_us(5);
    xbyte <<= 1;
    }
  output_low(BS2_MOSI);
  for (xbyte = 0, cnt = 0; cnt < 8; cnt++)
    {
    xbyte <<= 1;
    delay_us(5);
    output_high(BS2_SCK);
    delay_us(3);
    if (input(BS2_MISO))
      {
      xbyte |= 1;
      delay_us(2);
      }
    delay_us(2);
    output_low(BS2_SCK);
    delay_us(3);
    }
  FPGA_status[0][0] = xbyte;
  output_high(BS2_CS);
  return xbyte;
  }
