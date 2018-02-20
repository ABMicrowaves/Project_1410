
UCHAR status_scr;
/*
       UINT  bitrate;
       UCHAR loop_bw;
       UCHAR input_enc;
       UCHAR random_length;
       UCHAR input_polarity;
       UCHAR output_clock_phase;
       UCHAR filter_select;
       UCHAR symbol_timing;
       UCHAR descrambler;
       UCHAR impedance;
       UCHAR if_bandwidth;
       UINT  frequency;
 */

//=============================================================================
UINT get_integer(void)
  {
  UINT v = 0;
  UCHAR chr;
  while (1)
    {
    chr = get_button();
    if (isdigit(chr))
      {
      v = v * 10 + (chr - '0');
      TLCD_DspChar(chr);
      }
    else if (chr == 'E')
      return v;
    else if (chr == 'X')
      return 65535;
    }
  }

//=============================================================================
UINT get_bounded_integer(UINT value, UINT lower, UINT higher, UCHAR *name, UCHAR x, UCHAR y)
  {
  UINT nx, v;
  TLCD_clearSCR();
  TLCD_position(0,0);
  TLCD_DspStr("channel ");
  TLCD_DspChar(selected_channel + '1');
  TLCD_position(x, y);
  TLCD_DspStr(name);
  nx = TLCD_x;
  while (1)
    {
    TLCD_position(nx, y);
    TLCD_DspInt(value);
    TLCD_position(nx, y);
    v = get_integer();
    if (v >= lower && v <= higher)
      return v;
    else if (v == 65535)
      return value;
    }
  }


// get_bounded_integer(setup[selected_channel].symbol_timing,     0,1, "symbol tim   ", 1, 3);
// get_bounded_integer(setup[selected_channel].descrambler,       0,1, "descrambler  ", 1, 3);

//=============================================================================
void update_all(void)
  {
  UINT idx;
  for (idx = 1; idx <= 2; idx++)
    {
    set_synchronizer_params(idx, setup[idx-1].bitrate);
    }
  if (!setup[0].input_select)
    output_high(BS1_IN_SEL);
  else
    output_low(BS1_IN_SEL);
  if (!setup[1].input_select)
    output_high(BS2_IN_SEL);
  else
    output_low(BS2_IN_SEL);

  if (!setup[0].impedance)      // inverted on 12.7.2012
    output_high(BS1_IMPEDANCE);
  else
    output_low(BS1_IMPEDANCE);
  if (!setup[1].impedance)      // inverted on 12.7.2012
    output_high(BS2_IMPEDANCE);
  else
    output_low(BS2_IMPEDANCE);
  }
//=============================================================================
UINT get_input_enc(UINT enc, UCHAR *name, UCHAR x, UCHAR y)
  {
  UINT nx, v;
  UCHAR button;
  UCHAR nw[12][20] = { 
  "NRZL       ",
  "NRZM       ",
  "NRZS       ",
  "BI-PHASE   ",
  "BI-PHASE M ",
  "BI-PHASE S " };

  v = enc;
  TLCD_clearSCR();
  TLCD_position(1,0);
  if (selected_channel == 0)
    TLCD_DspStr("BIT SYNC 1");
  else
    TLCD_DspStr("BIT SYNC 2");
  TLCD_position(1,1);
  TLCD_DspStr(name);
  nx = TLCD_x;
  while (1)
    {
    TLCD_position(1, 2);
    TLCD_DspStr(&nw[enc][0]);
    button = get_button();
    if (button == 'B')
     {
       if (++enc >= 6)
        enc = 0;
      }
    else if (button == 'C')
      {
      if(--enc > 6)
      enc = 5;
      }
    else if (button == 'E')
      return enc;
    else if (button == 'X')
      return v;
    }
      store_setup();
      update_all();
  }
//=============================================================================
UINT get_impedance(UINT imp, UCHAR *name, UCHAR x, UCHAR y)
  {
  UINT nx, v;
  UCHAR button;
  UCHAR nw[2][4] = { "LO ", "HI "};
  v = imp;
  TLCD_clearSCR();
  TLCD_position(1,0);
  if (selected_channel == 0)
    TLCD_DspStr("BIT SYNC 1");
  else
    TLCD_DspStr("BIT SYNC 2");
  TLCD_position(1,1);
  TLCD_DspStr(name);
  nx = TLCD_x;
  while (1)
    {
    TLCD_position(1, 2);
    TLCD_DspStr(&nw[imp][0]);
    button = get_button();
    if (button == 'B')
      imp ^= 1;
    else if (button == 'C')
      imp ^= 1;
    else if (button == 'E')
      return imp;
    else if (button == 'X')
      return v;
    }
      store_setup();
      update_all();
  }
//=============================================================================
UINT get_random_length(UINT rand, UCHAR *name, UCHAR x, UCHAR y)
  {
  UINT nx, v;
  UCHAR button;
  UCHAR nw[12][12] = { "OFF  ", "9   ", "11   ", "15   "};
  v = rand;
  TLCD_clearSCR();
  TLCD_position(1,0);
  if (selected_channel == 0)
    TLCD_DspStr("BIT SYNC 1");
  else
    TLCD_DspStr("BIT SYNC 2");
  TLCD_position(1,1);
  TLCD_DspStr(name);
  nx = TLCD_x;
  while (1)
    {
    TLCD_position(1, 2);

    TLCD_DspStr(&nw[rand][0]);
    button = get_button();
    if (button == 'C')
     {
       if (++rand >= 4)
        rand = 0;
      }
    else if (button == 'B')
      {
      if(--rand > 4)
      rand = 3;
      }
    else if (button == 'E')
      return rand;
    else if (button == 'X')
      return v;
    }
      store_setup();
      update_all();
  }
//=============================================================================
UINT get_output_clock_phase(UINT cp, UCHAR *name, UCHAR x, UCHAR y)
  {
  UINT nx, v;
  UCHAR button;
  UCHAR nw[6][12] = { "90      ","180       ", "270       ", "OFF       "};
  v = cp;
  TLCD_clearSCR();
  TLCD_position(1,0);
  if (selected_channel == 0)
    TLCD_DspStr("BIT SYNC 1");
  else
    TLCD_DspStr("BIT SYNC 2");
  TLCD_position(1,1);
  TLCD_DspStr(name);
  nx = TLCD_x;
  while (1)
    {
    TLCD_position(1, 2);
    TLCD_DspStr(&nw[cp][0]);
    button = get_button();
    if (button == 'C')
     {
       if (++cp >= 4)
        cp = 0;
      }
    else if (button == 'B')
      {
      if(--cp > 4)
      cp = 3;
      }
    else if (button == 'E')
      return cp;
    else if (button == 'X')
      return v;
    }
      store_setup();
      update_all();
  }
//=============================================================================
UINT get_loop_bw(UINT loop, UCHAR *name, UCHAR x, UCHAR y)
  {
  UINT nx, v;
  UCHAR button;
  UCHAR nw[32][20] = {"0 = 0.1%        ","1 = 0.1%        ","2 = 0.1%        ","3 = 0.1%        ","4 = 0.1%        ","5 = 0.1%         ","6 = 0.1%        ",
                      "7 = 0.1%        ","8 = 0.1%        ","9 = 0.1%        ","10 = 0.1%       ","11 = 0.1%       ","12 = 0.1%        ","13 = 0.2%       ",
                      "14 = 0.3%       ","15 = 0.4%       ","16 = 0.5%       ","17 = 0.6%       ","18 = 0.7%       ","19 = 0.8%        ","20 = 0.9%       ",
                      "21 = 1.0%       ","22 = 1.1%       ","23 = 1.2%       ","24 = 1.3%       ","25 = 1.4%       ","26 = 1.5%        ","27 = 1.6%       ",
                      "28 = 1.7%       ","29 = 1.8%       ","30 = 1.9%       ","31 = 2.0%       "};
  v = loop;
  TLCD_clearSCR();
  TLCD_position(1,0);
  if (selected_channel == 0)
    TLCD_DspStr("BIT SYNC 1");
  else
    TLCD_DspStr("BIT SYNC 2");
  TLCD_position(1,1);
  TLCD_DspStr(name);
  nx = TLCD_x;
  while (1)
    {
    TLCD_position(1, 2);
    TLCD_DspStr(&nw[loop][0]);
    button = get_button();
    if (button == 'C')
     {
       if (++loop >= 32)
        loop = 0;
      }
      else if(button == 'B')
        {
          if (--loop > 32)
        loop = 31;
         }
    else if (button == 'E')
      return loop;
    else if (button == 'X')
      return v;
    }
      store_setup();
      update_all();
  }
//=============================================================================
UINT get_input_polarity(UINT dp, UCHAR *name, UCHAR x, UCHAR y)
  {
  UINT nx, v;
  UCHAR button;
  UCHAR nw[2][20] = {"INVERTED        ","NORMAL          "};
  v = dp;
  TLCD_clearSCR();
  TLCD_position(1,0);
  if (selected_channel == 0)
    TLCD_DspStr("BIT SYNC 1");
  else
    TLCD_DspStr("BIT SYNC 2");
  TLCD_position(1,1);
  TLCD_DspStr(name);
  nx = TLCD_x;
  while (1)
    {
    TLCD_position(1, 2);
    TLCD_DspStr(&nw[dp][0]);
    button = get_button();
    if (button == 'B')
      dp ^= 1;
    else if (button == 'C')
      dp ^= 1;
    else if (button == 'E')
      return dp;
    else if (button == 'X')
      return v;
    }
      store_setup();
      update_all();
  }
  //=============================================================================
UINT get_filter_select(UINT fl, UCHAR *name, UCHAR x, UCHAR y)
  {
  UINT nx, v;
  UCHAR button;
  UCHAR nw[2][20] = {"OFF           ","ON            "};
  v = fl;
  TLCD_clearSCR();
  TLCD_position(1,0);
  if (selected_channel == 0)
    TLCD_DspStr("BIT SYNC 1");
  else
    TLCD_DspStr("BIT SYNC 2");
  TLCD_position(1,1);
  TLCD_DspStr(name);
  nx = TLCD_x;
  while (1)
    {
    TLCD_position(1, 2);
    TLCD_DspStr(&nw[fl][0]);
    button = get_button();
    if (button == 'B')
      fl ^= 1;
    else if (button == 'C')
      fl ^= 1;
    else if (button == 'E')
      return fl;
    else if (button == 'X')
      return v;
    }
      store_setup();
      update_all();
  }
//=============================================================================
void set_synchronizer(UCHAR channel)
  {
  UCHAR btn;
  UINT v;
  selected_channel = channel;
  set_selected_channel_led();
  CMD_LEDTOP;
  while (1)
    {
    TLCD_ClearSCR();
    TLCD_Position(0, 0);    TLCD_DspStr("1-IN  2-IMP 3-BR    ");
    TLCD_Position(0, 1);    TLCD_DspStr("4-L   5-ENC 6-RL    ");
    TLCD_Position(0, 2);    TLCD_DspStr("7-IDP 8-CP  9-DFL   ");
    btn = get_button();
    switch (btn)
      {
      case '1': v = get_bounded_integer(setup[selected_channel].input_select + 1,  1, 2 ,        "sync input   ", 1, 1); break;
      case '2': v = get_impedance(setup[selected_channel].impedance,                             "impedance    ", 1, 1); break;
      case '3': v = get_bounded_integer(setup[selected_channel].bitrate,             0, 3000,    "bitrate      ", 1, 1); break;
      case '4': v = get_loop_bw(setup[selected_channel].loop_bw,                                 "loop bw      ", 1, 1); break;
      case '5': v = get_input_enc(setup[selected_channel].input_enc,                             "input enc    ", 1, 1); break;
      case '6': v = get_random_length(setup[selected_channel].random_length,                     "rnd length   ", 1, 1); break;
      case '7': v = get_input_polarity(setup[selected_channel].input_polarity,                   "in polarity  ", 1, 1); break;
      case '8': v = get_output_clock_phase(setup[selected_channel].output_clock_phase,           "clock phase  ", 1, 1); break;
      case '9': v = get_filter_select(setup[selected_channel].filter_select,                     "filter       ", 1, 1); break;
      case 'X': return;
      }
    if (v != 65535)
      {
      switch (btn)
        {
        case '1': setup[selected_channel].input_select = v - 1;     break;
        case '2': setup[selected_channel].impedance = v;            break;
        case '3':
           if(v)
            {
            setup[selected_channel].bitrate = v; 
            }
            else 
              break;              
        if(setup[selected_channel].bitrate>2300)
         {
           setup[selected_channel].output_clock_phase = 0;  
         setup[selected_channel].filter_select = 1;
         }                                                          break;
        case '4': setup[selected_channel].loop_bw = v;              break;
        case '5': setup[selected_channel].input_enc = v;            break;
        case '6': setup[selected_channel].random_length = v;        break;
        case '7': setup[selected_channel].input_polarity = v;       break;
        case '8': setup[selected_channel].output_clock_phase = v;   break;
        case '9': setup[selected_channel].filter_select = v;        break;
        }
      store_setup();
      update_all();
      }
    }
  }

//=============================================================================
void set_signal_lock_leds(void)
  {
  UCHAR status[2];
  status[0] = get_register_from_FPGA1(7);
  FPGA_bits[0] = status[0];
  status[1] = get_register_from_FPGA2(7);
  FPGA_bits[1] = status[1];
  if (status[0] & 0x80)
    {
    output_high(GLED1);    output_low(RLED1);
    }
  else
    {
    output_low(GLED1);     output_high(RLED1);
    }
  if (status[0] & 0x40)
    {
    output_high(GLED2);    output_low(RLED2);
    }
  else
    {
    output_low(GLED2);     output_high(RLED2);
    }

  if (status[1] & 0x80)
    {
    output_high(GLED3);    output_low(RLED3);
    }
  else
    {
    output_low(GLED3);     output_high(RLED3);
    }
  if (status[1] & 0x40)
    {
    output_high(GLED4);    output_low(RLED4);
    }
  else
    {
    output_low(GLED4);     output_high(RLED4);
    }
  }

//=============================================================================
void display_status_screen(void)
  {
  UCHAR buf[22];
  TLCD_clearSCR();
  TLCD_position(0,0);
  TLCD_DspStr(VERSION);
  TLCD_position(0,1);
  sprintf(buf, "Bit Sync %u ", selected_channel+1);
  TLCD_DspStr(buf);
  set_signal_lock_leds();
  }

//=============================================================================
void user_interface(void)
  {
  UCHAR btn, buf[10];
  UINT refresh;
  status_scr = 0;
  TLCD_mode(4);
  display_status_screen();
  delay_ms(2000);
  sprintf(buf, "S%u> ", selected_channel+1);
  COM1_send_str(buf);
  init_buttons();
#ignore_warnings 203
  while (1)
    {
    if (TMR_1sec_DISP_STAT)
      {
      TMR_1sec_DISP_STAT = 0;
      output_toggle(LED2);
      if (++refresh > 1)
        {
        refresh = 0;
        display_status_screen();
        }
      }
    if (button_pressed())
      {
      btn = get_button();
      if (btn == 'E')
        {
        TLCD_ClearSCR();
        TLCD_Position(0, 0);    TLCD_DspStr("Select channel");
        TLCD_Position(0, 1);    TLCD_DspStr("  1-BIT SYNC 1    ");
        TLCD_Position(0, 2);    TLCD_DspStr("  2-BIT SYNC 2    ");
        btn = get_button();
        if (btn != 'X')
          {
          if (btn == '1' || btn == '2')
            set_synchronizer(btn - '1');
            set_selected_channel_led();
          if (btn == 'A' || btn == 'B')
            set_synchronizer(btn - 'A');
            set_selected_channel_led();
          }
        }
      else if (btn == '5')
        if (++status_scr > 2)
          status_scr = 0;
      display_status_screen();
      }
    }
  }
