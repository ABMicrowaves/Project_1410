
UCHAR comm_ptr, ttccp = 1, debug_mode = 0;
UCHAR FPGA_image[32],D2A_image[20];
UCHAR ttccp_error_message[40];
UCHAR ttccp_login = 0;
UCHAR rp_command = setup.rp ,  pwr_command = setup.pwr;

//-----------------------------------------------------------------------------
UCHAR COM1_get_chr(void)
  {
  UCHAR x;
  x = COM1_rbuf[COM1_rxo];
  if (++COM1_rxo >= COM1_RX_LEN)
    COM1_rxo = 0;
  if (COM1_rcnt)
    COM1_rcnt--;
  return x;
  }

//-----------------------------------------------------------------------------
void COM1_send_str(UCHAR *str)
  {
  UCHAR x, pos, tab_stop;
  disable_interrupts(int_RDA);
  output_high(RS485_EN);
  delay_us(100);
  pos = 0;
  while (*str)
    {
    x = *str++;
    if (x != '\t')
      {
      TXREG1 = x;
      pos++;
      delay_us(300);
      x = RCREG1;
      }
    else
      {
      tab_stop = 32;
      if (pos >= tab_stop)
        tab_stop = pos + 2;
      while (pos < tab_stop)
        {
        TXREG1 = ' ';
        pos++;
        delay_us(300);
        x = RCREG1;
        }
      }
    }
  delay_us(100);
  output_low(RS485_EN);
  x = RCREG1;
  enable_interrupts(int_RDA);
  }

//-----------------------------------------------------------------------------
void COM1_init(void)
  {
  ttccp_error_message[0] = 0;
  COM1_rxi = COM1_rxo = COM1_rcnt = 0;
  comm_state = COMM_INIT;
  enable_interrupts(int_RDA);
  }

//----------------------------------------------------------------------------
#separate
UINT get_char(void)
  {
  return comm_buf[comm_ptr++];
  }

//----------------------------------------------------------------------------
#separate
UINT peek_char(void)
  {
//  skip_spc();
  return comm_buf[comm_ptr];
  }

//----------------------------------------------------------------------------
#separate
void skip_spc(void)
  {
  while (comm_buf[comm_ptr] && (comm_buf[comm_ptr] == ',' || comm_buf[comm_ptr] == ' '))
    comm_ptr++;
  }

//----------------------------------------------------------------------------
#separate
SINT get_int(void)
  {
  SINT num, sign = 1;
  skip_spc();
  if (comm_buf[comm_ptr])
    {
    num = 0;
    if (peek_char() == '-')
      {
      sign = -1;
      get_char();
      }
    while (isdigit(comm_buf[comm_ptr]))
      num = (num * 10) + (comm_buf[comm_ptr++] - '0');
    }
//  skip_spc();
  return num * sign;
  }

//----------------------------------------------------------------------------
#separate
ULONG str_to_long(void)
  {
  ULONG num;
  skip_spc();
  if (comm_buf[comm_ptr])
    {
    num = 0;
    while (isdigit(comm_buf[comm_ptr]))
      num = (num * 10) + (comm_buf[comm_ptr++] - '0');
    }
//  skip_spc();
  return num;
  }

//----------------------------------------------------------------------------
#separate
ULONG get_hex(void)
  {
  ULONG num;
  UCHAR chr;
  skip_spc();
  if (peek_char())
    {
    num = 0;
    while (isxdigit(peek_char()))
      {
      chr = get_char();
      chr = toupper(chr);
      if (chr <= '9')
        chr -= '0';
      else
        chr = chr - ('A' - 10);
      num = num * 16 + (ULONG)chr;
      }
    }
  return num;
  }

//----------------------------------------------------------------------------
UINT get_frequency(void)
  {
  UINT freq;
  freq = get_int() * 10;
  if (peek_char() == '.')
    {
    get_char(); // skip '.'
    freq += get_char() - '0';
    }
  return freq;
  }

//----------------------------------------------------------------------------
void inc_dec(UCHAR chr)
  {
  UINT incdec;
  switch (chr)
    {
    case 'i':
      if (++D2A_image[11] == 0)
        if (++D2A_image[12] > 3)
          {
          D2A_image[11] = 0;
          D2A_image[12] = 0;
          }
      write_D2A(11, D2A_image[11]);
      write_D2A(12, D2A_image[12]);
      break;
    case 'I':
      if (++D2A_image[15] == 0)
        if (++D2A_image[16] > 3)
          {
          D2A_image[15] = 0;
          D2A_image[16] = 0;
          }
      write_D2A(15, D2A_image[15]);
      write_D2A(16, D2A_image[16]);
      break;
    case 'd':
      if (--D2A_image[11] == 255)
        if (--D2A_image[12] > 3)
          {
          D2A_image[11] = 255;
          D2A_image[12] = 3;
          }
      write_D2A(11, D2A_image[11]);
      write_D2A(12, D2A_image[12]);
      break;
    case 'D':
      if (--D2A_image[15] == 255)
        if (--D2A_image[16] > 3)
          {
          D2A_image[15] = 255;
          D2A_image[16] = 3;
          }
      write_D2A(15, D2A_image[15]);
      write_D2A(16, D2A_image[16]);
      break;
    case '+':
      incdec = make16(D2A_image[14],D2A_image[13]) & 0x3FF;
      if (++incdec > 0x3FF)
        incdec = 0;
      incdec |= (UINT)(D2A_image[14]  & 0xC0) << 8;
      D2A_image[13] = make8(incdec, 0);
      D2A_image[14] = make8(incdec, 1);
      write_D2A(11, D2A_image[13]);
      write_D2A(12, D2A_image[14]);
      break;
    case '=':
      incdec = make16(D2A_image[18],D2A_image[17]) & 0x3FF;
      if (++incdec > 0x3FF)
        incdec = 0;
      incdec |= (UINT)(D2A_image[18]  & 0xC0) << 8;
      D2A_image[17] = make8(incdec, 0);
      D2A_image[18] = make8(incdec, 1);
      write_D2A(11, D2A_image[17]);
      write_D2A(12, D2A_image[18]);
      break;
    case '-':
      incdec = make16(D2A_image[14],D2A_image[13]) & 0x3FF;
      if (--incdec > 0x3FF)
        incdec = 0x3FF;
      incdec |= (UINT)(D2A_image[14]  & 0xC0) << 8;
      D2A_image[13] = make8(incdec, 0);
      D2A_image[14] = make8(incdec, 1);
      write_D2A(11, D2A_image[13]);
      write_D2A(12, D2A_image[14]);
      break;
    case '_':
      incdec = make16(D2A_image[18],D2A_image[17]) & 0x3FF;
      if (--incdec > 0x3FF)
        incdec = 0x3FF;
      incdec |= (UINT)(D2A_image[18]  & 0xC0) << 8;
      D2A_image[17] = make8(incdec, 0);
      D2A_image[18] = make8(incdec, 1);
      write_D2A(11, D2A_image[17]);
      write_D2A(12, D2A_image[18]);
      break;
    case '>':
      if (setup.phase_offset < 255)
        setup.phase_offset++;
      update_FPGA(1, setup.phase_offset);
      break;
    case '<':
      if (setup.phase_offset)
        setup.phase_offset--;
      update_FPGA(1, setup.phase_offset);
      break;
    }
  }

//----------------------------------------------------------------------------
void list_help1(void)
  {
  COM1_send_str("\r\n");
  COM1_send_str("$AI <channel><cr>  \tRequest analog channel value (10 bits)\r\n");
  COM1_send_str("$AT <level><cr>  \tSet attenuator to <level>\r\n");
  COM1_send_str("$CF <freq><cr>  \tChange frequency (2185.0 - 2300.0 in 0.1 incs)\r\n");
  COM1_send_str("$DI<cr>  \tRequest digital inputs\r\n");
  COM1_send_str("$GD <addr><cr>  \tGet D2A register contents\r\n");
  COM1_send_str("$GF <addr><cr>  \tGet FPGA register contents\r\n");
  COM1_send_str("$OT <output><cr>  \tSet digital outputs to HEX value\r\n");
  COM1_send_str("$RD<cr>  \tReset D2A\r\n");
  COM1_send_str("$SD <addr> <data><cr>  \tSet D2A register <addr> to <data>\r\n");
  COM1_send_str("$SF <addr> <data><cr>  \tSet FPGA register <addr> to <data>\r\n");
  COM1_send_str("\r\n");
  }

//----------------------------------------------------------------------------
bit set_power_level(void)
  {
  UINT idx;
  idx = get_int();
  if (idx <= 40 && idx >= 20)
    {
    setup.power_level = idx - 20;
    power_level = (setup.power_in[setup.power_level]); // * 33) / 50;
    return 1;
    }
  return 0;
  }


//----------------------------------------------------------------------------
bit set_low_power_level(void)
  {
  UINT idx;
  idx = get_int();
  if (idx <= 40 && idx >= 20)
    {
    setup.power_low_level = idx - 20;
    low_power_level = (setup.power_in[setup.power_low_level]); // * 33) / 50;
    return 1;
    }
  return 0;
  }


//----------------------------------------------------------------------------
// command format:
//   $<cmd> [<number>[,<number>]]<cr>
// where:
//    <cmd>       a two letter operation specifier
//    <number>    value to be used in operation
//    <cr>        0x0D character ending command string
//
UCHAR process_dollar_commands(void)
  {
  UCHAR chr, idx, device, addr, data, buf[40];
  ULONG freq, bitrate;
  UINT  value;
  chr = 2;
  comm_ptr = 0;
  switch (toupper(get_char()))
    {
    case 'H':
      list_help1();
      return 0;
    case 'A':
      switch (toupper(get_char()))
        {
        case 'T':
          idx = get_int();

          // write to attenuator
          break;
        case 'I':
          idx = get_int();
          if (idx && idx < 4)
            {
            set_adc_channel(idx-1);
            delay_us(30);
            value = read_adc();
            sprintf(buf, "$AR %lu\r", value);
            COM1_send_str(buf);
            }
          break;
        }
      break;
    case 'C':
      if (chr = toupper(get_char()) == 'F')
        {
        freq = get_frequency();
        PLL_compute_freq_parameters(freq);
        PLL_update();
        }
      else if (chr == 'P')
        {
        idx = get_int();
        if (idx < 2)
          {
          setup.clock_polarity = idx & 1;
          sprintf(buf, "$CP %u\r", idx);
          COM1_send_str(buf);
          }
        }
      break;
    case 'D':
      if (toupper(get_char()) == 'I')
        {
        idx = input_c(); // change to REAL input ports
        sprintf(buf, "$DR %02X\r", idx);
        COM1_send_str(buf);
        }
      break;
    case 'O':
      if (toupper(get_char()) == 'T')
        {
        value = get_hex();
        // output bits
        }
      break;
    case 'R':
      if (toupper(get_char()) == 'D')
        {
        output_high(D2A_RESET);
        delay_ms(100);
        output_low(D2A_RESET);
        }
      break;
    case 'B':             // bit rate
      if (toupper(get_char()) == 'R')
        {
        bitrate = str_to_long();
        set_bitrate(bitrate);
        }
      break;
    case 'G':
      device = get_char();
      addr = get_hex();
      switch (toupper(device))
        {
        case 'F':
          chr = get_FPGA_register(addr, &data);
          sprintf(buf, " \r\n$SF %02X %02X\r", addr, chr);
          COM1_send_str(buf);
          break;
        case 'D':
          data = read_D2A(addr);
          sprintf(buf, " \r\n$SD %02X %02X\r", addr, data);
          COM1_send_str(buf);
          break;
        }
      break;
    case 'F': // fill tables
      skip_spc();
      idx = get_char(); // get table designator
      addr = get_int(); // get table index
      value = get_int(); // get value to put into table
      switch (toupper(idx))
        {
        case 'N': // negative voltage
          if (addr < 3)
            {
            setup.negative_voltage[addr] = value;
            }
          break;
        case 'P': // positive voltage
          if (addr < 21)
            {
            setup.power_in[addr] = value;
            }
          break;
        }
      break;
    case 'S':
      device = get_char();
      addr = get_hex();
      data = get_hex();
      switch (toupper(device))
        {
        case 'F':
          buf[0] = addr;
          buf[1] = data;
          FPGA_image[addr] = data;
          send_FPGA_command(2, buf);
          break;
        case 'D':
          D2A_image[addr] = data;
          write_D2A(addr, data);
          break;
        case 'V':
          allow_write = 2975;
          write_setup();
          break;
        }
      break;
    case 'T':
      if (toupper(get_char()) == 'T')
        if (toupper(get_char()) == 'C')
          if (toupper(get_char()) == 'C')
            if (toupper(get_char()) == 'P')
              ttccp = 1;
      break;
    case '1': // year
      setup.year = get_int();
      break;
    case '2': // week
      setup.week = get_int();
      break;
    case '3': // unit ID
      setup.unit_ID = get_int();
      break;
    default:
      return 0;
    }
  return 0;
  }

//----------------------------------------------------------------------------
#separate
void get_new_bitrate(void)
  {
  ULONG bitrate, sub;
            bitrate = get_int();//* 100;
            get_char();
            sub = get_int();

            if (peek_char() == '.')
              {
              get_char();
              sub = get_int();
              bitrate += sub;
              }

            setup.bitrate = bitrate * 100 + sub;
		//	setup.bitrate1= setup.bitrate;
            FPGA_set_bitrate();

  }

//----------------------------------------------------------------------------
void list_help(void)
  {
  COM1_send_str("\r\n\n");
  COM1_send_str("DS <data soure><cr>  \tSet data sourse (0-1)\r\n");
  COM1_send_str("DP <data polarity><cr>  \tSet data polarity (0-1)\r\n");
  COM1_send_str("DE <setup SOQPSK><cr>  \tSet setup SOQPSK (0-1)\r\n");
  COM1_send_str("RP <power higth><cr>  \tSet power higth (0-1)\r\n");
  COM1_send_str("RF <power comand><cr>  \tSet power comand (0-1)\r\n");
  COM1_send_str("RA <randomizer><cr>  \tset with/without randomizer (0-1)\r\n");
  COM1_send_str("FR <frequency><cr>  \tSet frequency (2200.0-2400.0)\r\n");
  COM1_send_str("MO <mode><cr>  \tSet mode (0-3)\r\n");
  COM1_send_str("IC <bitrate><cr>  \tSet birtate (1.00-30.00DBps)\r\n");
  COM1_send_str("ID <internal pattern><cr>  \tSet internal pattern (0-3)\r\n");
  COM1_send_str("VP <power level><cr>  \tSet power level (20-40)\r\n");
  COM1_send_str("VL <power high><cr>  \tSet high power level (20-40)\r\n");
  COM1_send_str("VM <negative power level><cr>  \tSet negative power level\r\n");
  COM1_send_str("VC <posetive power level><cr>  \tSet posetive power level\r\n");
  COM1_send_str("CS <clock phase><cr>  \tSet clock phase (0-1)\r\n");
  COM1_send_str("SV <save all><cr>  \tSave parameters\r");
  COM1_send_str("\r\n");
  }

//----------------------------------------------------------------------------
#separate
void process_ttccp_commands(void)
  {
  UCHAR ret = 0, chr, buf[40], query = 0, c1, c2, revstat[12], addr;
  ULONG freq, bitrate, sub;
  float temp;
  UINT  val, revp, rp;
  chr = 2;
  comm_ptr = 0;
    if (peek_char() == ':') // addressed message?
    {
    get_char(); // skip ':'
    addr = get_int();
    if (get_char() != ':')
      break;
    if (setup.unit_id != addr)
      goto aaa;
    }
    break;
  c1 = toupper(get_char());
  c2 = toupper(get_char());
  skip_spc();

  if (peek_char() == 13) // is this a query?
    query = 1; // YES
  switch (c1)
    {
    case 'L': // login or logout
      switch (c2)
        {
        case 'I':               // login
          val = get_int();
          if (val == 17592)
            ttccp_login = 1;
			debug_mode = 1;
          break;
        case 'O':               // logout
          ttccp_login = 0;
          break;
        }
      break;
    case '$':
      if (!ttccp_login) break;
      if (c2 == 'R') // switch to $ commands ONLY after ttccp login
        {
        val = get_int();
          if (val != 17591)
            return;
        ttccp = 0;
        COM1_send_str("\r\n\n*");
        }
      break;

  /*  case ':':
       if(c2 == setup.unit_id+48)
        if(toupper(get_char()) == ':')
          comm_ptr = 2;
        break;
*/
      case 'H':
      if (!ttccp_login) break;
      COM1_send_str("\r\t HELP LIST \r");
      list_help();
    break;

    case 'F':
      if (!ttccp_login) break;
      switch (c2)
        {
        case 'R': // set frequency
          if(c2 == 'R')
            {
            if (query)
              {
              sprintf(buf, "FR %lu\r", setup.frequency);
              COM1_send_str(buf);
              }
              else
              {
                freq = get_frequency();
                setup.frequency = freq;
                PLL_compute_freq_parameters(freq);
                PLL_update();
				delay_ms(50);
				PLL_update();
                ret = 1;
              }
            }
            else
              COM1_send_str("\r\nFAULT\r\n");
          break;
        }
      break;

    case 'M':
      if (!ttccp_login) break;
      if (c2 == 'O')  // mode - Addr0 bit 0-3
          {
            if(query)
            {
            sprintf(buf, "MO %u\r", setup.mode);
            COM1_send_str(buf);
            }
          val = get_int();
          if (val <= 3)
            {
            setup.mode = val;
            FPGA_set_reg0();
            ret = 1;
            }
          else
            {
            COM1_send_str("\r\nFAIL\r\n");
            ret = 0;
            break;
            }
          }
          else
              COM1_send_str("\r\nFAIL\r\n");
      break;

    case 'D':
      if (!ttccp_login) break;
      switch (c2)
        {
       // case 'B':  // debug mode
       //   debug_mode = 1;
       //   break;
        case 'S':   // Addr 6 bit 1   setup.data_source
          if (query)
            {
            sprintf(buf, "DS %u\r", setup.data_source);
            COM1_send_str(buf);
            }
          else
            {
            val = get_int();
            if (val < 2)
              {
              setup.data_source = val;
              FPGA_set_reg6();
              }
            else
              {
			  COM1_send_str("\r\nFAIL\r\n");
              sprintf(ttccp_error_message, "ERR DS %u\r", setup.data_source);
              ret = 0;
              break;
              }
            }
          ret = 1;
          break;

        case 'P':   // Addr 0 bit 5   setup.data_polarity
          if (query)
            {
            sprintf(buf, "DP %u\r", setup.data_polarity);
            COM1_send_str(buf);
            }
          else
            {
            val = get_int();
            if (val < 2)
              {
              setup.data_polarity = val;
              FPGA_set_reg0();
              }
            else
              {
			  COM1_send_str("\r\nFAIL\r\n");
              sprintf(ttccp_error_message, "ERR DP %u\r", setup.data_polarity);
              ret = 0;
              break;
              }
            }
          ret = 1;
          break;

        case 'E':   // Addr 0 bit 7   setup.SOQPSK
          if (query)
            {
            sprintf(buf,"DE %u\r", setup.SOQPSK);
            COM1_send_str(buf);
            }
          else
            {
            val = get_int();
            if (val < 2)
              {
              setup.SOQPSK = val;
              FPGA_set_reg0();
              }
            else
              {
			  COM1_send_str("\r\nFAIL\r\n");
              sprintf(ttccp_error_message, "ERR DE %u\r", setup.SOQPSK);
              ret = 0;
              break;
              }
            }
          ret = 1;
          break;
        }
      break;

    case 'R':
      if (!ttccp_login) break;
      switch (c2)
        {
        case 'P':  // HI or LO power - discrete output + DAC   setup.power_high
          if (query)
            {
            sprintf(buf, "RP %u\r", setup.power_high);
            COM1_send_str(buf);
            }
          else
            {
            val = get_int();
            if (val < 2)
              {
	          if(setup.rc == 1)
	            {
	            if(val == 0)
	            {
	            setup.rp =1;
	            }
	          else

	          setup.rp = 0;
	          }
	          if(val == 1)
	          {
              rp_command = setup.rp = 0;
              delay_ms(50);
              update_all();
              }
              else
               {
              rp_command = setup.rp = 1;
              delay_ms(50);
              update_all();
              }
              }
            else
              {
			  COM1_send_str("\r\nFAIL\r\n");
              sprintf(ttccp_error_message, "ERR RP %u\r", rp_command);
              ret = 0;
              break;
              }
            }
          ret = 1;
          break;

        case 'F': // discrete output - power amp on/off       setup.power_amp
          if (query)
            {
            sprintf(buf, "RF %u\r", pwr_command);
            COM1_send_str(buf);
            }
          else
            {
            val = get_int();
            if (val == 0)
              {
			  if(setup.cot || setup.rc)
				{
                pwr_command = 0;
                setup.pwr = pwr_command;
                delay_ms(60);
			 	update_all();
			 	ret = 1;
                }
				else if(setup.cot == 0 || setup.rc)
				  {
                  pwr_command = 0;
                setup.pwr = pwr_command;
                delay_ms(60);
			 	update_all();
                  }
				}
			else
				{
				if (val == 1)
				  {
				  if(setup.cot)
				   {
				   pwr_command = 1;
				   setup.pwr = pwr_command;
				   power_output();
                   delay_ms(50);
				   ret = 1;
                   update_all();
				   }
					else if(setup.cot == 0)
				  {
                  pwr_command = 1;
                  setup.pwr = pwr_command;
                  power_output();
				  delay_ms(50);
				  ret = 1;
                  update_all();
                  }
				}
            else
              {
			  COM1_send_str("\r\nFAIL\r\n");
              sprintf(ttccp_error_message, "ERR RF %u\r", pwr_command);
              ret = 0;
              break;
              }
			}
            }
          ret = 1;
          break;

         case 'C':
         	if (query)
            {
            sprintf(buf, "RC %lu\r", setup.rc);
            COM1_send_str(buf);
            }
          else
            {
          val = get_int();
          if(val < 2)
          	{
	          	if(val == 0)
	          	{
	              setup.rc = 0;
	              delay_ms(50);
	              update_all();
	            }
	            if(val == 1)
	              {
	              setup.rc = 1;
	              delay_ms(50);
	              update_all();
	              }
           }
          else
            COM1_send_str("\r\nFAULT\r\n");
            }
          break;

          case 'B':
            if (query)
            {
            sprintf(buf, "RB %lu\r", setup.cot);
            COM1_send_str(buf);
            }
          else
            {
          val = get_int();
          if(val < 2)
          	{
	          if(val)
	          	{
              setup.cot = val;
              if(pwr_command == 0)
              {
              pwr_command == 1;
              delay_ms(50);
              update_all();
              }
              else
              	pwr_command == 0;
               delay_ms(50);
              update_all();
            }
            setup.cot = val;
              delay_ms(70);
              update_all();
           }
          else
            COM1_send_str("\r\nFAULT\r\n");
            }
          break;

        case 'A': // Addr 0 bit 6     setup.randomizer
          if (query)
            {
            sprintf(buf, "RA %u\r", setup.randomizer);
            COM1_send_str(buf);
            }
          else
            {
            val = get_int();
            if (val < 2)
              {
              setup.randomizer = val;
              FPGA_set_reg0();
              ret = 1;
              }
            else
              {
			  COM1_send_str("\r\nFAIL\r\n");
              sprintf(ttccp_error_message, "ERR RA %u\r", setup.randomizer);
              ret = 0;
              break;
              }
            }
          ret = 1;
          break;

        case 'L':    // recall
          read_setup();
          update_all();
          ret = 1;
          break;
        case 'E':   // reset
          reset_cpu();
          break;
        }
      break;

    case 'W':            // query
      if (!ttccp_login) break;
      if (c2 == 'A')
        {
        //xxxx
        ret = 1;
        }
      break;

    case 'S':
      if (!ttccp_login) break;
      switch (c2)
        {
        case 'P': // power down - discrete outputs
          ret = 1;
          break;
        case 'V':
          allow_write = 2975;
          write_setup();
          ret = 1;
          break;
        }
      break;

    case 'I':
      if (!ttccp_login) break;
      switch (c2)
        {
        case 'D':     // Addr 6 bits 2-5     setup.internal_pattern
          if (query)
            {
            sprintf(buf, "ID %u\r", setup.internal_pattern);
            COM1_send_str(buf);
            }
          else
            {
            val = get_int();
            if (val < 4)
              {
              setup.internal_pattern = val;
              FPGA_set_reg6();
              }
            else
              {
			  COM1_send_str("\r\nFAIL\r\n");
              sprintf(ttccp_error_message, "ERR ID %u\r", setup.internal_pattern);
              ret = 0;
              break;
              }
            }
          ret = 1;
          break;

        case 'C':    // Addr 2 - 5 bit rate
          if (query)
            {
            sprintf(buf, "IC %lu\r", setup.bitrate);
            COM1_send_str(buf);
            }
          else
            {
            get_new_bitrate();
            }
          ret = 1;
          break;
        }
      break;

    case 'T':
      if (!ttccp_login) break;
      if (c2 == 'E')
        {
        goto get_temp;
        }
      break;

    case 'V':
      if (!ttccp_login) break;
      switch (c2)
        {
        case 'E':  // return version
		if(c2 =='E')
		{
          sprintf(buf, "VE %s ID=%02lu DT=%02lu%02u\r", VERSION, setup.unit_ID, setup.year, setup.week);
          COM1_send_str(buf);
          ret = 1;
		}
		else
			COM1_send_str("\r\nFAIL\r\n");
          break;

        case 'L':  // set low power level
		if(c2 == 'L')
		{

          set_low_power_level();
          ret = 1;
		}
		else
		COM1_send_str("\r\nFAIL\r\n");
          break;

        case 'P':  // power level control like in Generic TX  $P
          if (query)
            {
            sprintf(buf, "VP %lu\r", setup.power_level + 20);
            COM1_send_str(buf);
            }
          else
            set_power_level();
            ret = 1;
          break;

        case 'M': // manual power level
          if (query)
            {
            sprintf(buf, "VM %lu\r", manual_negative);
            COM1_send_str(buf);
            }
          else
            {
            manual_negative = get_int();
            set_AD5312(DAC_NEG_VOLT, val);
            }
          break;
        case 'C': // manual power level
          if (query)
            {
            sprintf(buf, "VC %lu\r", manual_pos);
            COM1_send_str(buf);
            }
          else
            {
            val = get_int();
            manual_pos = val;
            set_AD5312(DAC_POS_VOLT, val);
            }
          break;
		}
      break;

    case 'C':
      if (!ttccp_login) break;
      if (c2 == 'S')  // Addr 6 bit 0    setup.clock_source
        {
          if (query)
            {
            sprintf(buf, "CS %u\r", setup.clock_source);
            COM1_send_str(buf);
            }
          else
            {
            val = get_int();
            if (val < 2)
              {
              setup.clock_source = val;
              FPGA_set_reg6();
              }
            else
              {
			  COM1_send_str("\r\nFAIL\r\n");
              sprintf(ttccp_error_message, "ERR CS %u\r", setup.clock_source);
              ret = 0;
              break;
              }
            }

        ret = 1;
        }
      else if (c2 == 'P')  // Addr 6 bit 0    setup.clock_source
        {
          if (query)
            {
            sprintf(buf, "CP %u\r", setup.clock_polarity);
            COM1_send_str(buf);
            }
          else
            {
            val = get_int();
            if (val < 2)
              {
              setup.clock_polarity = val;
              FPGA_set_reg0();
              }
            else
              {
              COM1_send_str("\r\nFAIL\r\n");
              sprintf(ttccp_error_message, "ERR CP %u\r", setup.clock_polarity);
              ret = 0;
              break;
              }
            }

        ret = 1;
        }
      break;

   case 'G':
      if (!ttccp_login) break;
      switch (c2)
        {
        case 'P':
          set_adc_channel(A2D_POWER); // read temperature
          delay_us(50);
          val = read_adc();
          sprintf(ttccp_error_message, "\nGP %lu\r\n", val);
          ret = 0;
          break;
        case 'T':
get_temp:
          set_adc_channel(A2D_TEMP); // read temperature
          delay_us(50);
          val = read_adc();
          temp = (float)val / 1024.0 * 3.3;
          temp -= 0.75;
          temp *= 100;
          temp += 25.0;
          if(setup.pwr)
            {
            sprintf(ttccp_error_message, "\rTEMP=%6.2fdeg\r\nOK\n", temp);
            ret = 0;
            }
            else
            {
            temp = 0;
            COM1_send_str("\r\n\nNO TEMP-RF OFF \r\n");
            ret = 0;
            }
          break;

        case 'R':
                set_adc_channel(A2D_PREV); // select forward power input
                delay_us(20);
                revp = read_adc();
                }
              break;
      break;

      case 'Q': //status
      if (!ttccp_login) break;

      COM1_send_str("\r\n\nOK Request Status \r\n\n");
      COM1_send_str(VERSION);
      sprintf(buf, "\r\nID=%lu DT=%02lu%02u\r",
              setup.unit_ID, setup.year, setup.week);
      COM1_send_str(buf);

                set_adc_channel(A2D_PREV); // select forward power input
                delay_us(20);
                revp = read_adc();

          if (revp <= 580)
          strcpy(revstat, "GOOD");
          else
          strcpy(revstat, "BAD");

          if(setup.rp)
            rp=0;
            else
              rp=1;


      sprintf(buf, "\r\n\nFREQ=%lu, REV=%s, FFWR=%lu, IC=%lu.%luMbps, MO=%u, CS=%u, RF=%lu\r"
              setup.frequency, revstat, setup.power_level+20, setup.bitrate/100, setup.bitrate%100, setup.mode, setup.clock_source, setup.pwr);
      COM1_send_str(buf);

      sprintf(buf, "\r\n\nDE=%u, RA=%u, DP=%u, RP=%lu, DS=%u, ID=%u, VL=%lu, RB=%lu, RC=%lu, CP=%u\r"
                setup.SOQPSK, setup.randomizer, setup.data_polarity, rp, setup.data_source,
                                        setup.internal_pattern, setup.power_low_level+20, setup.cot, setup.rc,
                                        setup.clock_polarity);
                                        COM1_send_str(buf);

      goto get_temp;
      break;
      default:
         COM1_send_str("\r\nFAIL\r\n");
    }
aaa:
  return;
  }
//----------------------------------------------------------------------------
#separate
void ttccp_handler(void)
  {
  UINT chr, ret;

  switch (comm_state)
    {
    case COMM_INIT:
      comm_ridx = 0;
      comm_state = COMM_WAIT_CR;
      comm_timeout = 0;
      COM1_send_str("\r>");
      break;
    case COMM_WAIT_CR:
      if (COM1_rcnt)
        {
        comm_timeout = 0;
        chr = COM1_get_chr();
        comm_buf[comm_ridx++] = chr;
        if (comm_ridx > 70)
          {
          comm_state = 0;
          break;
          }
        if (chr == 13 || chr == ';')
          {
          if (chr == ';')
            {
            comm_buf[comm_ridx-1] = 13;
            comm_ridx = 0;
            }
          else
            COM1_init();
          process_ttccp_commands();
          if (debug_mode)
            COM1_send_str("\r\nOK\n");
          if (ret == 1)
            {
            COM1_send_str("\n\r");
            }
          else
            COM1_send_str(ttccp_error_message);
          }
        }

      if (comm_state > COMM_WAIT_DLR)
        if (TMR_100MS_COMM_TO)
          {
          TMR_100MS_COMM_TO = 0;
          if (++comm_timeout > 10000) // time out after 10 seconds from last char
            comm_state = 0;
          }
      break;
    case COMM_DELAY:
      break;
    }
  }

//----------------------------------------------------------------------------
#separate
void dollar_handler(void)
  {
  UINT chr, ret;

  switch (comm_state)
    {
    case COMM_INIT:
      comm_ridx = 0;
      comm_state++;
      break;
    case COMM_WAIT_DLR:
#ignore_warnings 201
      if (COM1_rcnt)
        if ((chr = COM1_get_chr()) == '$')
          {
          comm_state++;
          comm_timeout = 0;
          }
        else
          inc_dec(chr);
      break;
    case COMM_WAIT_CR:
      if (COM1_rcnt)
        {
        comm_timeout = 0;
        chr = COM1_get_chr();
        comm_buf[comm_ridx++] = chr;
        if (comm_ridx > 70)
          {
          comm_state = 0;
          break;
          }
        if (chr == 13)
          {
          ret = process_dollar_commands();
          if (ret == 1)
            {
//            store_setup();
//            update_all();
            }
          if (ret != 255)
            COM1_send_str("\r\nOK\r\n*");
          COM1_init();
          }
        else if (chr == 27)
          {
          COM1_send_str("\r\n\nBREAK\r\n");
          comm_state = 0;
          }
        }

      if (comm_state > COMM_WAIT_DLR)
        if (TMR_100MS_COMM_TO)
          {
          TMR_100MS_COMM_TO = 0;
          if (++comm_timeout > 10000) // time out after 10 seconds from last char
            comm_state = 0;
          }
      break;
    case COMM_DELAY:
      break;
    }
  }


//----------------------------------------------------------------------------
#separate
void comm_handler(void)
  {
  UINT chr;

  if (OERR)
    {
    OERR = 0;
    CREN = 0;
    delay_us(5);
    CREN = 1;
    }
  if (FERR)
    {
    FERR = 0;
    chr = RCREG1;
    }
  if (ttccp)
    ttccp_handler();
  else
    dollar_handler();
  }

