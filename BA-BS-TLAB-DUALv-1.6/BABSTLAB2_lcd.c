/*
#define MLCD_E      PIN_A9
#define MLCD_RS     PIN_A10
#define TLCD_E      PIN_F13
#define TLCD_RS     PIN_F12
#define LCD_CLOCK   PIN_D1
#define LCD_DATA    PIN_D11
#define LCD_LATCH   PIN_D10
#define LCD_RESET   PIN_A14
*/
//============ LCD modes ========================================-
#define LCDM_ON_NO_CURSOR    4
#define LCDM_ON_WITH_CURSOR  7



#define TLCD_CHARACTERS 20
#define TLCD_LINES 4

#define MLCD_CHARACTERS 16
#define MLCD_LINES 2


UCHAR TLCD_Cursor, TLCD_x, TLCD_y;
UCHAR MLCD_Cursor, MLCD_x, MLCD_y;
UCHAR TLCD_image[TLCD_LINES][TLCD_CHARACTERS];
UCHAR MLCD_image[MLCD_LINES][MLCD_CHARACTERS];

#separate
void TLCD_Position(UCHAR x, UCHAR y);


//==================================================================-
void LCD_output(UCHAR datab)
  {
  UINT idx;
  output_LOW(LCD_LATCH);
  output_low(LCD_CLOCK);
  output_low(LCD_RESET);
  delay_cycles(15);
  output_high(LCD_RESET);
  delay_cycles(15);
  for (idx = 8; idx; idx--)
    {
    if (datab & 0x80)
      output_high(LCD_DATA);
    else
      output_low(LCD_DATA);
    delay_cycles(12);
    output_high(LCD_CLOCK);
    delay_cycles(15);
    output_low(LCD_CLOCK);
    datab <<= 1;
    }
  delay_cycles(15);
  output_high(LCD_LATCH);
  delay_cycles(15);
  output_LOW(LCD_LATCH);
  }

//==================================================================-
#separate
void write_TLCD1(UCHAR datab, UINT data_ctl)
  {
  if (data_ctl != 0)
    output_high(TLCD_RS);
  else
    output_low(TLCD_RS);
  LCD_output(datab);
  delay_us(15);
  output_high(TLCD_E);
  delay_us(10);
  output_low(TLCD_E);
  delay_us(50);
  }

#separate
void write_TLCD(UCHAR datab, UINT data_ctl)
  {
//  write_TLCD1((datab >> 4) & 15, data_ctl);
//  write_TLCD1(datab & 15, data_ctl);
  write_TLCD1(datab, data_ctl);
  delay_us(60);
  }

//==================================================================-
#separate
void TLCD_mode(UCHAR mode)
  {
  UCHAR mask;
  mask = 8 | mode;
  write_TLCD(mask, 0); // display clear
  delay_ms(3);
  }

//==================================================================-
#separate
void TLCD_shift(UCHAR RTlf)
  {
  UCHAR wrd;
  wrd = 0x10;
  if (RTlf)
    wrd |= 4;
  write_TLCD(wrd,0); // display clear
  delay_us(50);
  }

//==================================================================-
#separate
void TLCD_init(void)
  {
  output_low(TLCD_RS);
  output_low(TLCD_E);
  delay_ms(20);
  memset(TLCD_image, ' ', sizeof(TLCD_image));

/* // 4 bit interface
  LCD_output(0);
  delay_ms(50);
  write_TLCD1(3,0);
  delay_us(200);
  write_TLCD1(3,0);
  delay_us(200);
  write_TLCD1(3,0);
  delay_us(200);
  write_TLCD1(2,0);
  delay_us(200);
  write_TLCD(0x28,0);
  write_TLCD(0x10,0);
  write_TLCD(0x0f,0);
  write_TLCD(0x06,0);
*/

// 8 bit interface
  LCD_output(0);
  delay_ms(50);
  write_TLCD(0x30,0);
  delay_us(200);
  write_TLCD(0x30,0);
  delay_us(200);
  write_TLCD(0x30,0);
  delay_us(200);
  write_TLCD(0x38,0);
  write_TLCD(0x10,0);
  write_TLCD(0x0c,0);
  write_TLCD(0x06,0);

  TLCD_mode(0x0C);
  }

//==================================================================-
#separate
void TLCD_DspChar(UCHAR chr)
  {
  UCHAR pos;
  if (TLCD_x >= TLCD_CHARACTERS || TLCD_y >= TLCD_LINES)
    return;
  pos = 0x80 + (TLCD_cursor & 0x7F);
  /*
  write_TLCD(pos, 0);
  delay_us(50);
  write_TLCD(chr, 1);
  delay_us(50);
   */
  write_TLCD(pos, 0);
  delay_us(50);
  write_TLCD(chr, 1);
  delay_us(50);
  TLCD_cursor++;
  TLCD_image[TLCD_y][TLCD_x++] = chr; // update LCD image and advance X
  }

//==================================================================-
#separate
bit TLCD_DspStr(UCHAR *str)
  {
  bit newline;
  UCHAR buf[32], chr;
  UINT idx = 0;
  newline = 0;
  strcpy(buf, str);
  while (buf[idx])
    {
    if (buf[idx] == '\n')
      {
      TLCD_Position(0, 1);
      idx++;
      newline = 1;
      }
    else
      {
      chr = buf[idx++];
      TLCD_DspChar(chr);
      }
//    delay_us(100);
    }
  return newline;
  }

//==================================================================-
#separate
void TLCD_clearSCR(void)
  {
  UINT idx;

  TLCD_mode(4);
  /*
  for (idx = 0; idx < 4; idx++)
    {
    TLCD_position(0, idx);
    TLCD_DspStr("                    ");
    }
    */
//  write_TLCD(0x01,0); // display clear
//  delay_us(3000);
  write_TLCD(0x01,0); // display clear
  delay_us(3000);

  TLCD_mode(6);
  TLCD_Cursor = 0;
  TLCD_x = 0;
  TLCD_y = 0;
  memset(TLCD_image, ' ', sizeof(TLCD_image));
  }

//==================================================================-
#separate
void TLCD_Dsp2digits(UCHAR num)
  {
  TLCD_DspChar((num / 10) + '0');
  TLCD_DspChar((num % 10) + '0');
  }

//==================================================================-
#separate
void TLCD_Dsp4digits(UINT num)
  {
  TLCD_Dsp2digits(num / 100);
  TLCD_Dsp2digits(num % 100);
  }

//==================================================================-
#separate
void TLCD_Position(UCHAR x, UCHAR y)
  {
  UCHAR addr;
  y++; // display on lines 2 to 4
  switch (y)
    {
    case 0: addr = 0;    break;// 00
    case 1: addr = 0x40; break;// 40
    case 2: addr = 0x14; break;// 14
    case 3: addr = 0x54; break;// 54
    }

  addr += x;
  TLCD_Cursor = addr;
  write_TLCD(0x80 + (TLCD_cursor & 0x7F), 0);
  TLCD_x = x;
  TLCD_y = y;
  }

//==================================================================-
//#separate
#separate
void TLCD_Home(void)
  {
  TLCD_Position(0,0);
  }

//==================================================================-
#separate
void TLCD_clearEOL(void)
  {
  UCHAR org_Cursor;
  org_Cursor = TLCD_Cursor;
  while (TLCD_Cursor < 20)
    TLCD_DspChar(' ');
  TLCD_Cursor = org_Cursor;
  }


//==================================================================-
#separate
void TLCD_disp_time(UCHAR l, UCHAR r)
  {
  TLCD_Position(10, 1);
  TLCD_Dsp2digits(l);
  TLCD_DspChar(':');
  TLCD_Dsp2digits(r);
  }

//==================================================================-
void TLCD_DspInt(UINT number)
  {
  UCHAR buf[10];
  sprintf(buf, "%lu", number);
  TLCD_DspStr(buf);
  }

//==================================================================-
#separate
void write_MLCD1(UCHAR datab, UINT data_ctl)
  {
  UINT idx, image;
  UCHAR dt = 0;

  if (data_ctl != 0)
    output_high(MLCD_RS);
  else
    output_low(MLCD_RS);
  LCD_output(datab);
  delay_us(15);
  output_high(MLCD_E);
  delay_us(10);
  output_low(MLCD_E);
  delay_us(50);
  }

#separate
void write_MLCD(UCHAR datab, UINT data_ctl)
  {
  write_MLCD1(datab, data_ctl);
  delay_us(60);
  }


//==================================================================-
#separate
void MLCD_mode(UCHAR mode)
  {
  UCHAR mask;
  mask = 8 | mode;
  write_MLCD(mask, 0); // display clear
  delay_ms(3);
  }

//==================================================================-
#separate
void MLCD_Position(UCHAR x, UCHAR y)
  {
  UINT addr;
  switch (y)
    {
    case 0: addr = 0;    break;
    case 1: addr = 0x40; break;
    }

  addr += x;
  MLCD_Cursor = addr;
  write_MLCD(0x80 + (MLCD_cursor & 0x7F), 0);
  MLCD_x = x;
  MLCD_y = y;
//  write_TLCD(0x2C,0); // two lines
  }

//==================================================================-
#separate
void MLCD_shift(UCHAR RTlf)
  {
  UCHAR wrd;
  wrd = 0x10;
  if (RTlf)
    wrd |= 4;
  write_MLCD(wrd,0); // display clear
  delay_us(50);
  }

//==================================================================-
#separate
void MLCD_clearSCR(void)
  {
  write_MLCD(0x01,0); // display clear
  delay_us(3000);
  MLCD_Cursor = 0;
  MLCD_x = 0;
  MLCD_y = 0;
  memset(MLCD_image, ' ', sizeof(MLCD_image));
  }

//==================================================================-
#separate
void MLCD_init(void)
  {
  LCD_output(0);
  delay_ms(50);
  output_low(MLCD_RS);
  output_low(MLCD_E);
  delay_ms(50);
  memset(MLCD_image, ' ', sizeof(MLCD_image));
  delay_us(200);
/* // 4 BIT INTERFACE
  write_MLCD(0x28,0);
  write_MLCD(0x10,0);
  write_MLCD(0x0f,0);
  write_MLCD(0x06,0); */

  LCD_output(0);
  delay_ms(50);
  write_MLCD(0x30,0);
  delay_us(200);
  write_MLCD(0x30,0);
  delay_us(200);
  write_MLCD(0x30,0);
  delay_us(200);
  write_MLCD(0x38,0);
  write_MLCD(0x10,0);
  write_MLCD(0x0c,0);
  write_MLCD(0x06,0);
  }

//==================================================================-
#separate
void MLCD_DspChar(UCHAR chr)
  {
  UCHAR pos;
  if (MLCD_x >= MLCD_CHARACTERS || MLCD_y >= MLCD_LINES)
    return;
  pos = 0x80 + (MLCD_cursor & 0x7F);
  write_MLCD(pos, 0);
  delay_us(100);
  write_MLCD(chr, 1);
  delay_us(100);
/*  write_MLCD(pos, 0);
  delay_us(100);
  write_MLCD(chr, 1);
  delay_us(100);*/
  MLCD_cursor++;
  MLCD_image[MLCD_y][MLCD_x++] = chr; // update LCD image and advance X
  }

//==================================================================-
#separate
bit MLCD_DspStr(UCHAR *str)
  {
  bit newline;
  newline = 0;
  while (*str)
    {
    if (*str == '\n')
      {
      MLCD_Position(0, 1);
      str++;
      newline = 1;
      }
    else
      MLCD_DspChar(*str++);
    }
  return newline;
  }

//==================================================================-
#separate
bit MLCD_DspStr1(UCHAR *str)
  {
  bit newline;
  newline = 0;
  while (*str)
    {
    if (*str == '\n')
      {
      MLCD_Position(0, 0);
      str++;
      newline = 1;
      }
    else
      MLCD_DspChar(*str++);
    }
  return newline;
  }
//==================================================================-
//#separate
#separate
void MLCD_Home(void)
  {
  MLCD_Position(0,0);
  }


//==================================================================-
#separate
void MLCD_clearEOL(void)
  {
  UCHAR org_Cursor;
  org_Cursor = MLCD_Cursor;
  while (MLCD_Cursor < 20)
    MLCD_DspChar(' ');
  MLCD_Cursor = org_Cursor;
  }

//=============================================================================
void display_rssi_columns(UINT left, UINT right)
  {
  UCHAR buf[20];
  UINT idx, v[2], line;
  v[0] = left; v[1] = right;
  for (line = 0; line < 2; line++)
    {
    for (idx = 0; v[line]; idx++, v[line]--)
      buf[idx] = 'x';
    while (idx < 16)
      buf[idx++] = ' ';
    buf[idx] = 0;
    MLCD_position(0, line);
    MLCD_DspStr(buf);
    }
  }