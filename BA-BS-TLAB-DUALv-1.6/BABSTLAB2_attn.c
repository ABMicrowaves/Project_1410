//--------------------------------------------------------------
#define PE43dat_cal     PIN_B3
#define PE43702clk_cal2 PIN_G8
#define PE43702clk_cal3 PIN_B4
#define PE43702le_cal   PIN_B5

void CAL_attn2(UCHAR onoff, UCHAR level)
  {
  int8 loop;
  level &= 127;
  for (loop = 0; loop < 8; loop++)
    {
    if (level & 1)
      output_high(PE43dat_cal);
    else
      output_low(PE43dat_cal);
    delay_us(2);
    output_high(PE43702clk_cal2);
    delay_us(2);
    output_low(PE43702clk_cal2);
    delay_us(2);
    level >>= 1;
    }
  output_high(PE43702le_cal);
  delay_us(100);
  output_low(PE43702le_cal);
  }

void CAL_attn3(UCHAR onoff, UCHAR level)
  {
  int8 loop;
  level &= 127;
  for (loop = 0; loop < 8; loop++)
    {
    if (level & 1)
      output_high(PE43dat_cal);
    else
      output_low(PE43dat_cal);
    delay_us(2);
    output_high(PE43702clk_cal3);
    delay_us(2);
    output_low(PE43702clk_cal3);
    delay_us(2);
    level >>= 1;
    }
  output_high(PE43702le_cal);
  delay_us(100);
  output_low(PE43702le_cal);
  }

