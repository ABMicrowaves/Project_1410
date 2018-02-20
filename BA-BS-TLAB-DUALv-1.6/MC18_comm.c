
//==================================================================
// Slave communication functions and message processing
// Description:
//  The master slave communication between the PIC24 and the PIC18 is
//  based on a master clock line and a bidirectional data line.
//  Communication is initiated by the PIC24 by pulling the clock line high
//  and waiting for the PIC18 to assert the data line high for 10 uS as
//  indication of a READY state. The PIC24 will timeout after 5mS.
//  The PIC24 then sends 32 clocks (data is sampled on falling edge).
//  The first 16 clocks are for  data sent from PIC24 to PIC18.
//  The PIC24 will insert a 100uS delay between clock 16 and 17 to allow
//  PIC18 to prepare data for transmission.
//  The next 16 clocks are for receiving data from PIC18.
//  Data is sent from MSb to LSb.
//  Communication bit rate is 50Kbps.
//  The PIC24 will initiate communications every 50mS.
//==================================================================

enum {
  CMD_CONTRT = 1,    // contrast text LCD
  CMD_CONTRM,        // contrast column LCD
  CMD_BACKLT,        // text LCD backlight
  CMD_BACKLM,        // column LCD backlight
  CMD_SELCOM,        // select RS232/RS485 channel (1=RS232, 0=RS485)
  CMD_LEDTOP,        // Top LED control
  CMD_LEDBOT         // Bottom LED control
};// COMMANDS;

bit check_start(void)
  {
  if (input(SCOMM_CLK))
    {
    delay_us(20);
    if (input(SCOMM_CLK))
      {
      delay_us(20);
      output_drive(SCOMM_DAT);
      output_high(SCOMM_DAT);
      delay_us(10);
      output_float(SCOMM_DAT);
      return 1;
      }
    }
  return 0;
  }

UINT communicate(void)
  {
  UCHAR count;
  UINT  datain, dataout;
  output_float(SCOMM_DAT);
  for (count = 0; count < 16; count++)
    {
    while (!input(SCOMM_CLK)); // wait for clock to rise
    datain <<= 1;
    if (input(SCOMM_DAT))
      datain |= 1;
    while (input(SCOMM_CLK)); // wait for clock to fall
    }

  if (btnc)
    dataout = get_button() | ((UINT)btnc << 8);
  else
    dataout = 0;
  output_drive(SCOMM_DAT);
  for (count = 0; count < 16; count++)
    {
    while (!input(SCOMM_CLK)); // wait for clock to rise
    if (dataout & 0x8000)
      output_high(SCOMM_DAT);
    else
      output_low(SCOMM_DAT);
    dataout <<= 1;
    while (input(SCOMM_CLK)); // wait for clock to fall
    }
  output_low(SCOMM_DAT);
  return datain;
  }

void parse_command()
  {
  UINT param;
  param = i2cbuf[1];
  switch(i2cbuf[0])
    {
    case CMD_CONTRT:
      update_MCP4261(2, param);
      break;
    case CMD_CONTRM:
      update_MCP4261(3, param);
      break;
    case CMD_BACKLT:
      if (param & 1)
        output_low(PIN_C2);
      else
        output_high(PIN_C2);
      break;
    case CMD_BACKLM:
      if (param & 1)
        output_low(PIN_C1);
      else
        output_high(PIN_C1);
      break;
    case CMD_SELCOM:
      if (param & 1)
        output_low(PIN_C0);
      else
        output_high(PIN_C0);
      break;
    case CMD_LEDTOP:
      break;
    case CMD_LEDBOT:
      if (param & 1)
        {
        output_high(PIN_B2);
        output_low(PIN_B3);
        }
      else
        {
        output_low(PIN_B2);
        output_high(PIN_B3);
        }
      break;
    }
  }

void handle_comm(void)
  {
  UINT command;
  if (check_start())
    {
    command = communicate();
    parse_command();
    }

  }
