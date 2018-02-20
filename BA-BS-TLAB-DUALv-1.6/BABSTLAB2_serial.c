enum {
  COMM_INIT = 0,
  COMM_WAIT_DLR,
  COMM_WAIT_CR,
  COMM_DELAY
} COMM_STATES;


UCHAR FPGA_image[32],D2A_image[20];

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
  output_high(MAINEN);
  delay_us(100);
  pos = 0;
  while (*str)
    {
    x = *str++;
    if (x != '\t')
      {
      U1TXREG = (UINT)x & 255;
      U2TXREG = (UINT)x & 255;
      pos++;
      delay_us(300);
      x = U1RXREG;
      }
    else
      {
      tab_stop = 32;
      if (pos >= tab_stop)
        tab_stop = pos + 2;
      while (pos < tab_stop)
        {
        U1TXREG = (UINT)' ';
        U2TXREG = (UINT)' ';
        pos++;
        delay_us(300);
        x = U1RXREG;
        }
      }
    }
  delay_us(100);
  output_low(MAINEN);
  x = U1RXREG;
  enable_interrupts(int_RDA);
  }

//-----------------------------------------------------------------------------
void COM1_init(void)
  {
  COM1_rxi = COM1_rxo = COM1_rcnt = 0;
  comm_state = COMM_INIT;
  enable_interrupts(int_RDA);
  enable_interrupts(int_RDA2);
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
void send_two_lines(void)
  {
  COM1_send_str("\r\n\n");
  }
//----------------------------------------------------------------------------
void enc_tbl(void)
  {
  COM1_send_str("\r\n");
  COM1_send_str("ENCODING TABLE\r\n");
  COM1_send_str("0-NRZL\r\n");
  COM1_send_str("1-NRZM\r\n");
  COM1_send_str("2-NRZS\r\n");
  COM1_send_str("3-BI-PHASE\r\n");
  COM1_send_str("4-BI-PHASE M\r\n");
  COM1_send_str("5-BI-PHASE S\r\n");
  COM1_send_str("\r\n");
  }
//----------------------------------------------------------------------------
void list_help(void)
  {
  COM1_send_str("\r\n");
  COM1_send_str("$S <synchronizer><cr> \tSet synchronizer channel 1 or 2\r\n");
  COM1_send_str("$BR <bitrate><cr> \tSet video data rate in 10Kbps increments\r\n");
  COM1_send_str("$CP <clockphase><cr> \tSet clock output phase (0,90,180,270)\r\n");
  COM1_send_str("$DP <datapolarity><cr> \tSet data polarity (0-INVERTED, 1-NORMAL)\r\n");
  COM1_send_str("$DF <filter><cr> \tSelect filter (0..1)\r\n");
  COM1_send_str("$DE <encoding><cr> \tSet input encoding (0..5)\r\n");
  COM1_send_str("$IM <impedance><cr> \tSet impedance low/high (H->HI,L->LO)\r\n");
  COM1_send_str("$IN <input select><cr> \tSet input select  (1..2)\r\n");
  COM1_send_str("$L <loop bw><cr> \tloop bandwidth (0.1<-to->2.0)\r\n");
  COM1_send_str("$R <random><cr> \tSelect with/without randomizer and-" 
"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   -mode (0->OFF,9,11,15)\r\n");
  COM1_send_str("$Q<cr> \tRequest status\r\n");
  COM1_send_str("\r\n");
  COM1_send_str("                 ENCODING TABLE\r\n");
  COM1_send_str("                    0-NRZL\r\n");
  COM1_send_str("                    1-NRZM\r\n");
  COM1_send_str("                    2-NRZS\r\n");
  COM1_send_str("                    3-BI-PHASE\r\n");
  COM1_send_str("                    4-BI-PHASE M\r\n");
  COM1_send_str("                    5-BI-PHASE S\r\n");
  COM1_send_str("\r\n");
  }

//----------------------------------------------------------------------------
// command format:
//   $<cmd> [<number>[,<number>]]<cr>
// where:
//    <cmd>       a two letter operation specifier
//    <number>    value to be used in operation
//    <cr>        0x0D character ending command string
//

const CHAR enc_name[][20] = {
"NRZL", "NRZM", "NRZS"};

const CHAR enc_name1[][20] = {
 "BI-PHASE  ", "BI-PHASE M  ", "BI-PHASE S  "};

UCHAR process_setup(void)
  {
  UCHAR chr, val, imp[12]={'\0'}, buf[64],q,s;
  CHAR enc[20]={'\0'};
  float lb;
//  ULONG freq, bitrate;
  UINT  idx, ran, frac, cp, value, lop, loop, loop1, v[4];
  chr = 2;
  comm_ptr = 0;
  switch (toupper(get_char()))
    {
    case 'H': 
   case '?':
      list_help();
     COM1_send_str("\r\n$OK Request status \r\n");
      return 0;

/*   case 'A':
     enc_tbl();
     COM1_send_str("\r\n$OK ENCODING TABLE \r\n");
     return 0;
*/
    case 'S':
      value = get_int();
      if (value && value < 3)
        {
      if(value==1)
         {
           selected_channel = value - 1;
           set_selected_channel_led();
         COM1_send_str("\r\n$OK S 1 \r\n");
         }
         else
            {
              selected_channel = value - 1;
              set_selected_channel_led();
            COM1_send_str("\r\n$OK S 2 \r\n");
            }
        }
      else
         COM1_send_str("\r\n$FAULT\r\n");
      break;

    case 'B':
      if (toupper(get_char()) == 'R')
          value = get_int() *100;
         if(value<=30*100)
            {
            if(value>23*100)
               {
               setup[selected_channel].output_clock_phase = 0;  
            setup[selected_channel].filter_select = 1; 
               store_setup();
               update_all();
                  }        
               if (get_char() == '.')
                      frac = get_int() ;
                     if(frac<=99)
                        {
                            setup[selected_channel].bitrate = value + frac;
                            store_setup();
                            update_all();
                            sprintf(buf, "\r\n\r\$OK BR %lu.%lu\r\n", value/100 , frac);
                            COM1_send_str(buf);
                            }
                        else
                           COM1_send_str("\r\n$FAULT\r\n");
                            }
                        else
                           COM1_send_str("\r\n$FAULT\r\n");
      break;

    case 'D':
       skip_spc();
        switch (toupper(get_char()))
        {
         case 'P':
           value = get_int();
           if (value < 2)
            {
         if(value)
            {
               setup[selected_channel].input_polarity = value;
               store_setup();
               update_all();
            COM1_send_str("\r\n$OK DP NORMAL\r\n");
               }
            else
               {
                  setup[selected_channel].input_polarity = value;
                  store_setup();
                  update_all();
               COM1_send_str("\r\n$OK DP INVERTED\r\n");
                  }
            }
         else
            COM1_send_str("\r\n$FAULT\r\n");
      break;

         case 'F':
           value = get_int();
           if (value >=0 && value < 2 )
           {
         if(value==0)
            {
              setup[selected_channel].filter_select = value;
              store_setup();
              update_all();
            COM1_send_str("\r\n$OK DF 0\r\n");
              }
            else
               {
                 setup[selected_channel].filter_select = value;
                 store_setup();
                 update_all();
               COM1_send_str("\r\n$OK DF 1\r\n");
                 }
         }
         else
            COM1_send_str("\r\n$FAULT\r\n");
          break;

       case 'E':
         value = get_int();
         if (value < 6)
          {
          setup[selected_channel].input_enc = value;
          store_setup();
          update_all();
          }
         else
            COM1_send_str("\r\n$FAULT\r\n");
        break;
      }
      break;

    case 'C':
      if (toupper(get_char()) == 'P')
        {
           value = get_int();
           if (value == 0 || value ==90 || value == 180 || value == 270)
             {
         if(value==0)
         {
             setup[selected_channel].output_clock_phase = 3;
             store_setup();
             update_all();
         COM1_send_str("\r\n$OK CP 0\r\n");
             }
         else if(value==90)
            {
                setup[selected_channel].output_clock_phase = 0;
                store_setup();
                update_all();
              COM1_send_str("\r\n$OK CP 90\r\n");
                }
            else if(value==180)
               {
                   setup[selected_channel].output_clock_phase = 1;
                   store_setup();
                   update_all();
               COM1_send_str("\r\n$OK CP 180\r\n");
                   }
               if(value==270)
                  {
                      setup[selected_channel].output_clock_phase = 2;
                      store_setup();
                      update_all();
                  COM1_send_str("\r\n$OK CP 270\r\n");
                      }
         }
           else
              COM1_send_str("\r\n$FAULT\r\n");
          }
      break;

    case 'R':
      value = get_int();
      if (value == 0 || value == 9 ||value == 11 ||value == 15)
        {
      if(value==0)
         {
           setup[selected_channel].random_length = value;
           store_setup();
           update_all();
         COM1_send_str("\r\n$OK R OFF\r\n");
           }
         else if(value==9)
            {
              setup[selected_channel].random_length = 1;
              store_setup();
              update_all();
            COM1_send_str("\r\n$OK R 9\r\n");
              }
            else if(value==11)
               {
                 setup[selected_channel].random_length = 2;
                 store_setup();
                 update_all();
               COM1_send_str("\r\n$OK R 11\r\n");
                 }
               else if(value==15)
                  {
                    setup[selected_channel].random_length = 3;
                    store_setup();
                    update_all();
                  COM1_send_str("\r\n$OK R 15\r\n");
                    }
         }
      else
         COM1_send_str("\r\n$FAULT\r\n");
      break;

    case 'I':
        switch (toupper(get_char()))
     {
     case 'M':
     skip_spc();
      val = get_char();
     if(val == 'H' || val == 'h')
      {
      q = 1;
        setup[selected_channel].impedance = 1;
        store_setup();
        update_all();
      COM1_send_str("\r\n$OK IM HI\r\n");
      }
      else if(val == 'L' || val == 'l')
            {
         s = 0;
              setup[selected_channel].impedance = 0;
              store_setup();
              update_all();
            COM1_send_str("\r\n$OK IM LO\r\n");
            }
      else
         COM1_send_str("\r\n$FAULT\r\n");
      break;

    case 'N':
      value = get_int();
      if (value && value < 3)
        {
      if(value==1)
        {
          setup[selected_channel].input_select = value - 1;
          store_setup();
          update_all();
        COM1_send_str("\r\n$OK IN 1 \r\n");
          }
        else
         {
         setup[selected_channel].input_select = value - 1;
            store_setup();
            update_all();
          COM1_send_str("\r\n$OK IN 2 \r\n");
         }
      }
      else
         COM1_send_str("\r\n$FAULT\r\n");
      break;
    }
   break;

    case 'L':
      lb = get_int();
      if (lb <= 2)
        {
   //   case '.':
      if (toupper(get_char()) == '.')
      lop = get_int();
      if(lb == 0)
      {
      if(lop==1)
         {
           setup[selected_channel].loop_bw = 12;
           store_setup();
           update_all();
         COM1_send_str("\r\n$OK L 0.1 \r\n");
           }
            if (lop == 2)
              {
              setup[selected_channel].loop_bw = 13;
                store_setup();
                 update_all();
            COM1_send_str("\r\n$OK L 0.2 \r\n");
              }
               if (lop == 3)
                 {
                 setup[selected_channel].loop_bw = 14;
                 store_setup();
                 update_all();
               COM1_send_str("\r\n$OK L 0.3 \r\n");
                 }
                  if (lop == 4)
                       {
                    setup[selected_channel].loop_bw = 15;
                    store_setup();
                    update_all();
                  COM1_send_str("\r\n$OK L 0.4 \r\n");
                    }
                     if (lop == 5)
                       {
                          setup[selected_channel].loop_bw = 16;
                        store_setup();
                        update_all();
                     COM1_send_str("\r\n$OK L 0.5 \r\n");
                        }
                      if (lop == 6)
                           {
                           setup[selected_channel].loop_bw = 17;
                            store_setup();
                               update_all();
                        COM1_send_str("\r\n$OK L 0.6 \r\n");
                           }
                           if (lop == 7)
                             {
                             setup[selected_channel].loop_bw = 18;
                             store_setup();
                             update_all();
                           COM1_send_str("\r\n$OK L 0.7 \r\n");
                             }
                              if (lop == 8)
                                {
                                setup[selected_channel].loop_bw = 19;
                                store_setup();
                                update_all();
                              COM1_send_str("\r\n$OK L 0.8 \r\n");
                                }
                                 if (lop == 9)
                                   {
                                   setup[selected_channel].loop_bw = 20;
                                   store_setup();
                                   update_all();
                                 COM1_send_str("\r\n$OK L 0.9 \r\n");
                                   }
                                 }                           
                                    if (lb == 1)
                                 {
                                 if(lop == 0)
                                      {
                                      setup[selected_channel].loop_bw = 21;
                                      store_setup();
                                      update_all();
                                    COM1_send_str("\r\n$OK L 1.0 \r\n");
                                      }
                                       if (lop == 1)
                                         {
                                         setup[selected_channel].loop_bw = 22;
                                         store_setup();
                                         update_all();
                                       COM1_send_str("\r\n$OK L 1.1 \r\n");
                                         }
                                          if (lop == 2)
                                            {
                                            setup[selected_channel].loop_bw = 23;
                                            store_setup();
                                            update_all();
                                          COM1_send_str("\r\n$OK L 1.2 \r\n");
                                            }
                                            if (lop == 3)
                                               {
                                               setup[selected_channel].loop_bw = 24;
                                               store_setup();
                                               update_all();
                                             COM1_send_str("\r\n$OK L 1.3 \r\n");
                                               }
                                                if (lop == 4)
                                                  {
                                                  setup[selected_channel].loop_bw = 25;      
                                                  store_setup();
                                                  update_all();
                                                COM1_send_str("\r\n$OK L 1.4 \r\n");
                                                  }
                                                   if (lop == 5)
                                                     {
                                                     setup[selected_channel].loop_bw = 26;
                                                     store_setup();
                                                     update_all();
                                                   COM1_send_str("\r\n$OK L 1.5 \r\n");
                                                     }
                                                      if (lop == 6)
                                                        {
                                                        setup[selected_channel].loop_bw = 27;
                                                        store_setup();
                                                        update_all();
                                                      COM1_send_str("\r\n$OK L 1.6 \r\n");
                                                        }
                                                         if (lop == 7)
                                                           {
                                                           setup[selected_channel].loop_bw = 28;
                                                           store_setup();
                                                           update_all();
                                                         COM1_send_str("\r\n$OK L 1.7 \r\n");
                                                           }
                                                            if (lop == 8)
                                                              {
                                                              setup[selected_channel].loop_bw = 29;
                                                              store_setup();
                                                              update_all();
                                                            COM1_send_str("\r\n$OK L 1.8 \r\n");
                                                              }
                                                               if (lop == 9)
                                                                 {
                                                                 setup[selected_channel].loop_bw = 30;
                                                                 store_setup();
                                                                 update_all();
                                                               COM1_send_str("\r\n$OK L 1.9 \r\n");
                                                                 }
                                                               }                              
                                                                  if (lb == 2)
                                                                    {
                                                                  if(lop == 0)
                                                                  {
                                                                    setup[selected_channel].loop_bw = 31;
                                                                    store_setup();
                                                                    update_all();
                                                                  COM1_send_str("\r\n$OK L 2.0 \r\n");
                                                                    }   
                                                                  else
                                                                     COM1_send_str("\r\n$FAULT\r\n");
                                                                                    }                           


      }
      else
         COM1_send_str("\r\n$FAULT\r\n");
      break;

    case 'Q':
      COM1_send_str("\r\n$OK Request Status \r\n");
      send_two_lines();
      COM1_send_str(VERSION);
      sprintf(buf, "\r\nID=%u DC=%02u%02u\r\n", unit_id.id=01, unit_id.year=12, unit_id.week=48);
      COM1_send_str(buf);
      for (idx = 0; idx < 2; idx++)
        {
        sprintf(buf, "\r\n\r\nSynchronizer %u\r\n", idx+1);
        COM1_send_str(buf);
      if(setup[idx].impedance)
      {
      imp="HI     ";      
      }
      else
         {
         imp="LO     ";
         }
        sprintf(buf, "\r\nIN=%u, IMP=%ls\r\n",
                setup[idx].input_select+1, imp);
        COM1_send_str(buf);
      if(setup[idx].input_enc ==0)
         {
         enc=enc_name[0];
         }
         else if(setup[idx].input_enc ==1)
            {
            enc=enc_name[1];
            }
            else if(setup[idx].input_enc ==2)
               {
               enc=enc_name[2];
               }
               else if(setup[idx].input_enc ==3)
                  {
                  enc=enc_name1[0];
                  }
                  else if(setup[idx].input_enc ==4)
                     {
                     enc=enc_name1[1];
                     }
                     else
                        {
                        enc=enc_name1[2];
                        }
      if(setup[idx].random_length==0)
         {
         ran = 0;
         }
         else if(setup[idx].random_length==1)
            {
            ran = 9;
            }
            else if(setup[idx].random_length==2)
               {
               ran = 11;
               }
               else
                  {
                  ran = 15;
                  }
      if(setup[idx].loop_bw <13)
        {
      loop=0;
      loop1=1;   
          }
        else if(setup[idx].loop_bw ==13)
            {
         loop=0;
         loop1=2;
              }
           else if(setup[idx].loop_bw ==14)
              {
            loop=0;
            loop1=3;
                }
            else if(setup[idx].loop_bw ==15)
                 {
               loop=0;
               loop1=4;
                   }
               else if(setup[idx].loop_bw ==16)
                    {
                  loop=0;
                  loop1=5;
                      }
                  else if(setup[idx].loop_bw ==17)
                       {
                     loop=0;
                     loop1=6;
                         }
                     else if(setup[idx].loop_bw ==18)
                          {
                        loop=0;
                        loop1=7;
                            }
                        else if(setup[idx].loop_bw ==19)
                            {
                           loop=0;
                           loop1=8;
                               }
                           else if(setup[idx].loop_bw ==20)
                                {
                              loop=0;
                              loop1=9;
                                  }
                              else if(setup[idx].loop_bw ==21)
                                   {
                                 loop=1;
                                 loop1=0;
                                     }
                                 else if(setup[idx].loop_bw ==22)
                                      {
                                    loop=1;
                                    loop1=1;
                                       }
                                     else if(setup[idx].loop_bw ==23)
                                         {
                                       loop=1;
                                       loop1=2;
                                           }
                                        else if(setup[idx].loop_bw ==24)
                                             {
                                          loop=1;
                                          loop1=3;
                                               }
                                           else if(setup[idx].loop_bw ==25)
                                                {
                                             loop=1;
                                             loop1=4;
                                                }      
                                                else if(setup[idx].loop_bw ==26)
                                                   {
                                                loop=1;
                                                loop1=5;
                                                     }      
                                                   else if(setup[idx].loop_bw ==27)
                                                      {
                                                   loop=1;
                                                   loop1=6;
                                                       }      
                                                      else if(setup[idx].loop_bw ==28)
                                                         {
                                                      loop=1;
                                                      loop1=7;
                                                           }      
                                                         else if(setup[idx].loop_bw ==29)
                                                            {
                                                         loop=1;
                                                         loop1=8;
                                                              }      
                                                            else if(setup[idx].loop_bw ==30)
                                                               {
                                                            loop=1;
                                                            loop1=9;
                                                                 }      
                                                               else 
                                                                  {
                                                               loop=2;
                                                               loop1=0;
                                                                    }
        sprintf(buf, "BR=%u.%uMbps, L=%u.%u, ENC=%ls, RL=%u\r\n",
                setup[idx].bitrate/100, setup[idx].bitrate%100, loop ,loop1, enc, ran);
        COM1_send_str(buf);
      if(setup[idx].output_clock_phase==1)
         {
         cp=180;
         }
         else if(setup[idx].output_clock_phase==2)
            {
            cp=270;
            }
            else if(setup[idx].output_clock_phase==3)
               {
               cp=0;
               }
               else
                  {
                  cp=90;
                  }
        sprintf(buf, "IDP=%u, CP=%u, DFL=%u\r\n",
                setup[idx].input_polarity, cp , setup[idx].filter_select);
        COM1_send_str(buf);
        sprintf(buf, "\r\nSignal=%u, Lock=%u\r\n",
                (FPGA_bits[idx] & 0x80) != 0, (FPGA_bits[idx] & 0x40) != 0);
        COM1_send_str(buf);
        }
      break;
    case 'X':
       v[0] = get_int();
       v[1] = get_int();
       v[2] = get_int();
       v[3] = get_int();
       if (v[0] == 17951)
        {
        unit_id.id = 1;//v[1];
        unit_id.year = 12;//v[2];
        unit_id.week = 48;//v[3];
        store_setup();
        }
      break;
    default:
      COM1_send_str("\r\n$FAULT\r\n");
      return 0;
    }
  return 0;
  }

//----------------------------------------------------------------------------
void clear_com_errors(void)
  {
  UCHAR chr;
  if (U1STA.OERR)
    {
    U1STA.OERR = 0;
    }
   if (U1STA.FERR)
    {
    U1STA.FERR = 0;
    chr = U1RXREG;
    }

  if (U2STA.OERR)
    {
    U2STA.OERR = 0;
    }
   if (U2STA.FERR)
    {
    U2STA.FERR = 0;
    chr = U2RXREG;
    }
  }

//----------------------------------------------------------------------------
#separate
void comm_handler(void)
  {
  UINT chr, ret, buf[10];

  clear_com_errors();
  switch (comm_state)
    {
    case COMM_INIT:
      comm_ridx = 0;
      comm_state++;
      break;
    case COMM_WAIT_DLR:
#ignore_warnings 201 
    if (COM1_rcnt)
      {
      chr = COM1_get_chr();
      if (chr)
          if (chr == '$')
             {
             comm_state++;
             comm_timeout = 0;
             }   
           else
              COM1_send_str("\r\n$FAULT\r\n");
      }
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
          ret = process_setup();
          if (ret == 1)
            {
//            store_setup();
//            update_all();
            }
          if (ret != 255)
            COM1_send_str("\r\nOK\r\n");
          sprintf(buf, "S%u> ", selected_channel+1);
          COM1_send_str(buf);
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
          if (++comm_timeout > 5000) // time out after 10 seconds from last char
            comm_state = 0;
          }
      break;
    case COMM_DELAY:
      break;
    }
  }

