UCHAR out_buffer[80];

#define MAX_KEYS_IN_BUFFER 32
UCHAR keypad[MAX_KEYS_IN_BUFFER];
UINT kpxi = 0, kpxo = 0, kpxc = 0;

//==============================================================
void put_keypad(UINT key)
  {
  keypad[kpxi] = key;
  if (++kpxi >= MAX_KEYS_IN_BUFFER)
    kpxi = 0;
  if (kpxc >= MAX_KEYS_IN_BUFFER)
    kpxo = kpxi;
  else
    kpxc++;
  }

//==============================================================
bit button_pressed(void)
  {
  restart_wdt();
  comm_handler();
  slave_session();
  return kpxc != 0;
  }

//==============================================================
void init_buttons(void)
  {
  kpxi = 0;
  kpxo = 0;
  kpxc = 0;
  }  

//==============================================================
UCHAR get_button(void)
  {
  UCHAR btn;
  UINT refresh = 0;
  while (!button_pressed())
    if (!++refresh)
      set_signal_lock_leds();

  btn = keypad[kpxo];
  kpxc--;
  if (++kpxo >= MAX_KEYS_IN_BUFFER)
    kpxo = 0;
  return btn;
  }

//==============================================================
void OUT_string(UCHAR *str)
  {
  strcat(out_buffer, str);
  }

//==============================================================
void OUT_char(UCHAR chr)
  {
  UCHAR buf[4];
  buf[0] = chr;
  buf[1] = 0;
  strcat(out_buffer, buf);
  }

//==============================================================
void OUT_space(void)
  {
  OUT_char(' ');
  }

//==============================================================
void OUT_integer(UINT value, UCHAR format)
  {
  UCHAR buf[11];
  switch (format)
    {
    case 'U':
      sprintf(buf, "%lu", value);
      break;
    case 'S':
      sprintf(buf, "%ld", value);
      break;
    case 'F':
      sprintf(buf, "%7.2w", value);
      break;
    }
  strcat(out_buffer, buf);
  }

//==============================================================
void OUT_init(void)
  {
  out_buffer[0] = 0;
  }


