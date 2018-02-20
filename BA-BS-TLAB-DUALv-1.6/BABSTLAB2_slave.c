
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
  CMD_CONTRT = 0x100,
  CMD_CONTRM = 0x200,
  CMD_BACKLT = 0x300,
  CMD_BACKLM = 0x400,
  CMD_SELCOM = 0x500,
  CMD_LEDTOP = 0x600,
  CMD_LEDBOT = 0x700
};// COMMANDS;

UINT pace_slave_comm = 0;

UCHAR getsst = 1;

#define COMMAND_Q_LEN 32

UINT command_queue[COMMAND_Q_LEN];
UINT command_in = 0;
UINT command_count = 0;
UINT command_out = 0;

void send_command(UINT command)
  {
//  UINT idx;
  UCHAR ack;
  iic_start();
  ack = IIC_WriteByte(0xA0);
  ack = IIC_WriteByte(make8(command, 1));
  ack = IIC_WriteByte(make8(command, 0));
  ack = IIC_WriteByte(make8(command, 1));
  ack = IIC_WriteByte(make8(command, 0));
  iic_stop();
  }

UINT get_status(void)
  {
  UINT  status;
  UCHAR s[8], ack;
  iic_start();
  ack = IIC_WriteByte(0xA1);
  s[0] = iic_readbyte(1);
  s[1] = iic_readbyte(1);
  s[2] = iic_readbyte(1);
  s[3] = iic_readbyte(0);
  iic_stop();
  status = s[2];
  return status;
  }

void slave_session(void)
  {
  UINT status, slave_command;
  if (TMR_1mS_SLAVE)
    {
    TMR_1mS_SLAVE = 0;
    if (++pace_slave_comm >= 50)
      {
      if (command_count)
        {
        slave_command = command_queue[command_out];
        if (++command_out >= COMMAND_Q_LEN)
          command_out = 0;
        command_count--;
        send_command(slave_command);
        }
      else
        {
        if (getsst)
          {
          status = get_status();
          if (status)
            put_keypad(status & 255);
          }
        else
          send_command(0x1234);
        }
      if (command_count)
        pace_slave_comm = 25;
      else
        pace_slave_comm = 0;
      }
    }
  }

void enque_command(UINT command, UINT param)
  {
  command |= param;
  command_queue[command_in] = command;
  if (++command_in >= COMMAND_Q_LEN)
    command_in = 0;
  if (command_count >= COMMAND_Q_LEN)
    command_out = command_in;
  else
    command_count++;
  if (pace_slave_comm < 45)
    pace_slave_comm = 45;
  }

void set_selected_channel_led(void)
  {
  enque_command(CMD_LEDTOP, selected_channel == 0);
  enque_command(CMD_LEDBOT, selected_channel == 1);
  }
