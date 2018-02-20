
//--------------------------------------------------------------------------
#int_TIMER4
void  TIMER4_isr(void)
  {

  }

//--------------------------------------------------------------------------
#int_TIMER2
void TIMER2_isr(void) // 1mS tick
  {
  TMR_1mS_Flags = 0xFF;
  TMR_1mS_Count++;
  if (++TMR_1mS_Cnt >= 10)
    {
    TMR_1mS_Cnt = 0;
    TMR_10mS_Count++;
    TMR_10mS_Flags = 0xFF;
    if (++TMR_10mS_Cnt >= 10)
      {
      TMR_10mS_Cnt = 0;
      TMR_100mS_Flags = 0xFF;
      if (++TMR_100mS_Cnt >= 10)
        {
        TMR_100mS_Cnt = 0;
        TMR_1sec_Flags = 0xFF;
        }
      }
    }
  }


//--------------------------------------------------------------
#int_RDA
void  RDA_isr(void)
  {
  int8 x;
  x = U1RXREG;
  COM1_rbuf[COM1_rxi] = x;
  if (++COM1_rxi >= COM1_RX_LEN)
    COM1_rxi = 0;
  if (COM1_rcnt < COM1_RX_LEN)
    COM1_rcnt++;
  }

//--------------------------------------------------------------
#int_RDA2
void  RDA2_isr(void)
  {
  int8 x;
  x = U2RXREG;
  COM1_rbuf[COM1_rxi] = x;
  if (++COM1_rxi >= COM1_RX_LEN)
    COM1_rxi = 0;
  if (COM1_rcnt < COM1_RX_LEN)
    COM1_rcnt++;
  }


