#define MAX_BUTTONS    8
#define BTN_PACE     200

//-----------------------------------------------------------------------------
UCHAR prev_button = 255;
UCHAR const button_trans[] = { 'A', 'B', 'C',' ',  '1', '4', '7','X',  '2', '5', '8','0',  '3', '6', '9','E'};
UCHAR const lbtton_trans[] = { '4', '1', 'X','7',  'C', ' ', 'A','B',  '6', '3', 'E','9',  '5', '2', '0','L'};
UCHAR btnix, btnox, btnc, buttons[MAX_BUTTONS], scan_pace;
UINT  debounce_buttons = 0;
UCHAR pace_button = BTN_PACE;

//-----------------------------------------------------------------------------
void add_button(UINT btn)
  {
  UCHAR button;
  if (btn & 0x80)
    button = lbtton_trans[btn & 0x1F];
  else
    button = button_trans[btn];
  buttons[btnix] = button;
  if (++btnix >= MAX_BUTTONS)
    btnix = 0;
  if (btnc < MAX_BUTTONS)
    btnc++;
  else
    btnox = btnix;
  }

//-----------------------------------------------------------------------------
UCHAR get_button(void)
  {
  UCHAR btn;
  btn = buttons[btnox];
  if (++btnox >= MAX_BUTTONS)
    btnox = 0;
  if (btnc)
    btnc--;
  return btn;
  }

//-----------------------------------------------------------------------------
UCHAR peek_button(void)
  {
  return buttons[btnox];
  }

//-----------------------------------------------------------------------------
void scan_buttons(void)
  {
  UCHAR abc, mask, row, col, idx, btn, mtx[4];
  UINT cols[4];
  if (!TMR_1MS_KEYPAD)
    return;
  TMR_1MS_KEYPAD = 0;
  scan_pace ^= 1;
  if (!scan_pace)
    return;
  btn = 0;
  output_a(0);
  set_tris_a(0xFF);
  output_a(0);
  for (mask = 0xFE, row = 0; row < 4; row++, mask = (mask << 1) | 1)
    {
    if (row == 1)
      {
      TRISA = 0xF0;
      delay_us(10);
      output_a(0xFD);
      }
    else
      output_a(0);
    TRISA = mask;
    delay_us(200);
    col = input_a();
    cols[row] = col;
//    if (row == 1)
//      mtx[row] = (col & 15) | 2;
//    else
      mtx[row] = col >> 4;
    if (mtx[row] != 0x0F)
      btn++;
    }

  if (btn != 1)
    {
    abc = 0;
    if (cols[0] == 0xF6 && cols[3] == 0xF6)
      mtx[0] = 0xE;
    else if (cols[0] == 0xFA && cols[2] == 0xFA)
      mtx[0] = 0xD;
    else if (cols[0] == 0xFC && cols[1] == 0xFC)
      mtx[0] = 0xB;
    if (mtx[0] != 0xF)
      goto scan_mtx;
    prev_button = 255;
    debounce_buttons = BTN_PACE - 30;
    pace_button = BTN_PACE;
    }
  else
    {
scan_mtx:
    for (row = 0; row < 4; row++)
      for (col = 0, mask = 1; col < 4; col++, mask <<= 1)
        if (!(mtx[row] & mask))
          {
          btn = (row << 2) | col;
          if (btn != prev_button)
            {
            debounce_buttons = BTN_PACE - 30;
            pace_button = BTN_PACE;
            prev_button = btn;
            }
          else
            {
            debounce_buttons++;
            if (debounce_buttons && (debounce_buttons % pace_button) == 0) // 50 ms debounce
              {
              add_button(btn);
              if (pace_button > 50)
                pace_button -= 5;
              }
            else if (debounce_buttons == 700) // 50 ms debounce
              add_button(btn | 0x80);
            else if (debounce_buttons > 1000)
              debounce_buttons = 0;
            }
          return;
          }

    }
  idx++;
  idx--;
  }

//-----------------------------------------------------------------------------
#separate
bit button_pressed(void)
  {
//  comm_handler();
  scan_buttons();
  return btnc != 0;
  }

//-----------------------------------------------------------------------------
UCHAR wait_button(UCHAR seconds)
  {
  UCHAR t100;
  TMR_100MS_USER_TO = 0;
  for (t100 = 0; seconds;)
    {
    if (button_pressed())
      return get_button();
    if (TMR_100MS_USER_TO)
      {
      TMR_100MS_USER_TO = 0;
      if (++t100 >= 10)
        {
        t100 = 0;
        seconds--;
        }
      if (blink_led)
        if ((t100 % 5) == 0)
          if (blink_led == 1)
            output_toggle(LED_T);
          else
            output_toggle(LED_B);
      }
    }
  return 'X';
  }

//-----------------------------------------------------------------------------
void init_buttons(void)
  {
  btnix = 0;
  btnox = 0;
  btnc = 0;
  scan_pace = 0;
  output_a(0);
  set_tris_a(0xFF);
  }
