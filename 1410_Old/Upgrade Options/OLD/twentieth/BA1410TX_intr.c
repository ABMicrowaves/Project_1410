
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
   if (++TMR_SendStatus >= setup.Block_per_second && StartStatusFlag == 1 && setup.UART_Status == 1&& (stay_on == 1 || stay_on == 0)) // VERSION 3.3 17.1.2016
    {
    TMR_SendStatus = 0;
    SendStatusFlag = 1;
    TX_Counter++; //VERSION 3.3 21.3.2016 cunt the number of time block is sent
    //if (StartStatusFlag == 1 && setup.UART_Status == 1)
    if (!ttccp_login)
      {
      	COM1_send_block(24);
      }
    }
  if (++TMR_1mS_Cnt >= 10)
    {
    TMR_1mS_Cnt = 0;
    ++TMR_SendStatus; //1mSec count for rhe status VERSION 3.3 20.2.2016
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
        if (++TMR_StartStatus >= setup.UART_Time) // VERSION 3.3 17.1.2016
   				 {
   					 TMR_StartStatus = 0;
    				 StartStatusFlag = 1;
    				 //test_status++;
    				 //setup.Block_per_second = convert_power(test_status);
			     }
        }
      }
    }
  }


//--------------------------------------------------------------------------
#int_EXT
void  EXT_isr(void)
    {

    }

//--------------------------------------------------------------------------
#int_EXT1
void  EXT1_isr(void)
  {

  }

//--------------------------------------------------------------
#int_RDA
void  RDA_isr(void)
  {
  int8 x;
  x = RCREG1;
  COM1_rbuf[COM1_rxi] = x;
  if (++COM1_rxi >= COM1_RX_LEN)
    COM1_rxi = 0;
  if (COM1_rcnt < COM1_RX_LEN)
    COM1_rcnt++;
  }
  
#int_TBE // VERSION 3.3 17.1.2016
void TBE_isr(void)
  {
	  output_high(RS485_EN);
	  status_tx_index = 0;
	  while (tx_block_len--)
	  {
		  output_high(RS485_EN);
		 	TXREG1 = status_buffer[status_tx_index++];
		 	delay_us(500); 
		 	output_low(RS485_EN);
		}
		
		disable_interrupts(int_TBE);    
  }


