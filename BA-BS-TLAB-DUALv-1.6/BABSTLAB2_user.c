//==============================================================
void disp_header_inc_number(UCHAR *str, UINT num)
  {
  UCHAR buf[30];
  sprintf(buf, "%s %lu", str, num);
  TLCD_ClearSCR();
  TLCD_DspStr(buf);
  }

//==============================================================
void disp_error(UCHAR *Str)
  {
  TLCD_ClearScr();
  TLCD_Position(0, 1);
  TLCD_DspStr(str);
  delay_ms(2000);
  TLCD_ClearSCR();
  }

//==============================================================
void init_user(void)
  {
  }

//----------------------------------------------------------------------------
#separate
void skip_spc(UCHAR &pos)
  {
  while (comm_buf[pos] >= ' ' && comm_buf[pos] < '0')
    pos++;
  }

//----------------------------------------------------------------------------
#separate
UINT get_int(UCHAR &pos)
  {
  UINT num;
  skip_spc(pos);
  if (comm_buf[pos])
    {
    num = 0;
    while (isdigit(comm_buf[pos]))
      num = (num * 10) + (comm_buf[pos++] - '0');
    }
  skip_spc(pos);
  return num;
  }

//----------------------------------------------------------------------------
#separate
ULONG str_to_long(UCHAR &pos)
  {
  ULONG num;
  skip_spc(pos);
  if (comm_buf[pos])
    {
    num = 0;
    while (isdigit(comm_buf[pos]))
      num = (num * 10) + (comm_buf[pos++] - '0');
    }
  skip_spc(pos);
  return num;
  }

//----------------------------------------------------------------------------
void press_space_to_continue(void)
  {
  printf("\r\n Press Space to continue...");
  while (!COM1_rcnt)
    restart_wdt();
  COM1_get_chr();
  printf("\r\n");
  }


//----------------------------------------------------------------------------
// command format:
//   $<cmd><rcvr> <number><cr>
// where:
//    <cmd>       a one letter operation specifier
//    <rcvr>      1 or 2 for receiver selection
//    <number>    value to be used in operation
//    <cr>        0x0D character ending command string
//
bit process_setup(void)
  {
  UCHAR chr, idx, receiver;
  ULONG freq;
  chr = 2;
  receiver = comm_buf[0];
  if (receiver == '1' || receiver == '2')
    {
    receiver -= '1';
    switch (toupper(comm_buf[0]))
      {
      case 'H': case '?':
        list_help();
        break;
      case 'W': // bandwidth
        idx = get_int(chr);
        if (idx >= 2)
          return 0;
        global_setup.loop_bw[receiver] = idx & 1;
        break;
      case 'F': // frequency
        freq = get_int(chr);
        if (freq >= FREQ_BASE / FREQ_STEP)
          global_setup.Frequencies[receiver] = freq;
        else
          return 0;
        break;
      case 'G': // gain
        idx = get_int(chr);
        if (idx <= 100)
          global_setup.gain[receiver] = idx;
        else
          return 0;
        break;
      case 'M': // modulation
        idx = get_int(chr);
        if (idx < 16)
          global_setup.modulation[receiver] = idx;
        else
          return 0;
        break;
      case 'S': // return status
        break;
      default:
        return 0;
      }
    return 1;
    }
  return 0;
  }

//----------------------------------------------------------------------------
#separate
void comm_handler(void)
  {
  UCHAR chr;

  switch (comm_state)
    {
    case COMM_INIT:
      comm_ridx = 0;
      comm_state++;
      break;
    case COMM_WAIT_DLR:
      if (COM1_rcnt)
        if (COM1_get_chr() == '$')
          {
          comm_timeout = 0;
          }
    case COMM_WAIT_CR:
      if (COM1_rcnt)
        {
        comm_timeout = 0;
        chr = COM1_get_chr();
        if (chr == 13)
          {
          if (process_setup())
            {
            store_setup();
            update_all();
            printf("OK\r\n");
            }
          else
            printf("ERROR\r\n");
          comm_state = 0;
          }
        }

      if (TMR_100MS_COMM_TO)
        {
        TMR_100MS_COMM_TO = 0;
        if (++comm_timeout > 100) // time out after 10 seconds from last char
          comm_state = 0;
        }
    case COMM_DELAY:
    }
  }


