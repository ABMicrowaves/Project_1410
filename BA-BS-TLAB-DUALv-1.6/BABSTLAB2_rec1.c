
ULONG PLL1_A, PLL1_B;


//==================================================================================
//--------- ADF4113 handling functions -------------------------
/*
Device Programming After Initial Power-Up
Initialization Latch Method
• Apply VDD.
• Program the initialization latch (11 in two LSBs of input word).
  Make sure that the F1 bit is programmed to 0.
• Do a function latch load (10 in two LSBs of the control word),
  making sure that the F1 bit is programmed to a 0.
• Do an R load (00 in two LSBs).
• Do an N (A, B) load (01 in two LSBs).
When the initialization latch is loaded, the following occurs:
• The function latch contents are loaded.
• An internal pulse resets the R, N (A, B), and timeout counters to
  load-state conditions and also three-states the charge pump.
  Note that the prescaler band gap reference and the oscillator input
  buffer are unaffected by the internal reset pulse,
  allowing close phase alignment when counting resumes.
• Latching the first N (A, B) counter data after the initialization word
  activates the same internal reset pulse.
  Successive N (A, B) loads will not trigger the internal reset pulse,
  unless there is another initialization.
*/

void PLL1_send_bits(UCHAR data)
  {
  UCHAR count;
  for (count = 8; count ; count--)
    {
    if (bit_test(data, count-1))
      output_high(PLL1_DAT);
    else
      output_low(PLL1_DAT);
    delay_us(100);
    output_high(PLL1_CLK);
    delay_us(100);
    output_low(PLL1_CLK);

    delay_us(250);
    }
  output_low(PLL1_DAT);
  output_low(PLL1_CLK);
  }

void PLL1_send_word(ULONG prog)
  {
  restart_wdt();
  disable_interrupts(GLOBAL);
  PLL1_send_bits(make8(prog, 2));               // send LSB
  PLL1_send_bits(make8(prog, 1));               // send middle byte
  PLL1_send_bits(make8(prog, 0));               // send MSB
  delay_us(40);
  output_high(PLL1_LAT);                 // latch 24 bits into register
  delay_us(5);
  output_low(PLL1_LAT);                 // latch 24 bits into register
  enable_interrupts(GLOBAL);
  restart_wdt();
  }

#separate
void PLL1_update(void)
  {
  ULONG prog;
  prog = (PLL1_B << 8) + (PLL1_A << 2) + LATCH_NCOUNT; // N counter latch
  restart_wdt();
  PLL1_send_word(prog);
  }

#separate
void PLL1_initialize(void)
  {
  ULONG prog;
  prog = INIT_DIV|INIT_MUX_LOCK|INIT_PHASE_POS|INIT_CHARGE|INIT_FASTLOCK|INIT_TIMER|INIT_CURRENT1|INIT_CURRENT2;         // Initialization latch
  PLL1_send_word(prog|LATCH_INIT);
  delay_ms(250);
  prog = FREQ_R * 4 + LATCH_REF;    // Reference counter latch
  PLL1_send_word(prog);
  delay_ms(250);
  PLL1_update(); // N counter latch
  }

#separate
void PLL1_reset(UCHAR PLLx)
  {
  output_low(PLL1_DAT);
  output_low(PLL1_CLK);
  delay_us(1000);
  PLL1_initialize();
  }

//--------- frequency computation functions --------------------
#separate
void PLL1_compute_freq_parameters(UINT Frequest)
  {
  ULONG Fvco, D;
  restart_wdt();
  Fvco = (ULONG)FREQ_STEP * (ULONG)Frequest;
  Fvco += FREQ_BASE;
  Fvco -= FREQ_IF;
  restart_wdt();
  D = Fvco / FREQ_STEP;
  restart_wdt();
  PLL1_B = D / FREQ_P_MULT;
  PLL1_A = D - (PLL1_B * FREQ_P_MULT);
  }


//==================================================================================
// output is 0.5mV per increment
void DA11_update(UINT level)
  {
  UCHAR count;
  UINT mask;
  TRISE = 0;
  output_low(DA11_CLK);
  for (mask = 0x800, count = 12; count; count--, mask >>= 1)
    {
    if (level & mask)
      output_high(DA11_DAT);
    else
      output_low(DA11_DAT);
    output_high(DA11_CLK);
    delay_us(2);
    if (count == 1)
      {
      output_low(DA11_LAT);
      delay_us(2);
      }
    output_low(DA11_CLK);
    delay_us(2);
    }
  output_high(DA11_LAT);
  }

void DA12_update(UCHAR channel, UINT level)
  {
  UCHAR count;
  level <<= 2; // adjust data
  if (channel)
    level |= 0x8000;
  output_low(DA12_SYN);
  for (count = 0; count < 16; count++)
    {
    output_high(DA12_CLK);
    if (level & 0x8000)
      output_high(DA12_DAT);
    else
      output_low(DA12_DAT);
    delay_us(2);
    output_low(DA12_CLK);
    level <<= 1;
    }
  output_high(DA12_SYN);
  delay_us(2);
  output_low(DA12_LAT);
  delay_us(2);
  output_high(DA12_LAT);
  }


