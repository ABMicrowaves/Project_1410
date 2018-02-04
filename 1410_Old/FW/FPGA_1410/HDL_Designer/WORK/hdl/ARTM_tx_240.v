module ARTM_tx_240 (
	inclk0,  	  // crystal reference oscillator
	data_in,  	  //  data to be modulated 
	data_clock,   // synchronous with data transitions
	mode,  		  // 000 = FM/PCM, 001 = SOQPSK, 100 = carrier only
	phase_offset, // used for adjacent sideband suppression in IQ modulator
	bit_rate,  	  // requried when data clock is not present
	rst_n,        //  active low reset input 
	rst_in,		  //  simulation only
	PB_nBB,       //  passband or not baseband  (passband enabled for Altera eval board)
	CLK_POL,		  // set clock polarity
	RAND,			  // enable randomizer
	CLK_SRC,      // select  clock source  1 = internal clock  0= external clock
	DAT_SRC,		  //  select data source  1 equalz internal data 0 = external data
	DAT_POL,		  //  select data polarity
	internal_data,
	Diff_en,
	
	clk,
	rst,
	DAC_clk ,
	DAC_clk_n,
	
	sine,cosine,  // baseband output needed for IQ modulator
	bit_clock,    //  approximately a square wave
	FB_RATE,		  // reported bit rate
	
	tx_sig, 	     // this is used if signal is passband (one DAC in Paff Eval board)
	scram_data,
	sym_phase_of  ,
	
	
	
	steady_state,
	bit_0_a_ddd, bit_0_b_ddd, pll_state, three_cnt_a, odd_ev, bit_0, bit_1, sym_phase, 
	true_random, phase_modulation, transition_d , transition_i, data_d, clock_d, 
	outside_freq_range, IIR, clk_120, roll_total_ddd, phase_test,
	phase_0, phase_1, phase_2, phase_3,phase_4, phase_5, phase_6, phase_7, lookup_rslt_4, SOQPSK_lookup_4, 
	sym_count_dd, sym_phase_of_d, sym_phase_of_dd,
	ph_roll_0, ph_roll_1, ph_roll_2, ph_roll_3, ph_roll_4, ph_roll_5, ph_roll_6, ph_roll_7,
	phase_total_d1, phase_total_d2, flip_ddd, phase_fm_0, phase_fm_1, fm_phase_of, fm_phase_lu_0,
	alpha_fm_0_dd, phase_fm_rr, phase_fm_r, FM_lookup_addr_0, FM_lookup_addr_1, 
	quotient, quotient_1,
	testa, 
	phase_err,
	data_trans_cnt
	);
	
input inclk0;
input data_in;
input data_clock;
input [3:0] mode;  			// 0000 = FM/PCM, 0001 = SOQPSK,  0011= test
input [7:0] phase_offset;   // used for adjacent sideband suppression in IQ modulator
input [31:0] bit_rate;
input rst_n, rst_in;
input PB_nBB;
input CLK_POL;
input RAND;
input CLK_SRC;
input DAT_SRC;
input DAT_POL;
input internal_data;
input Diff_en;



output [31:0] FB_RATE;
output [13:0] sine,cosine;
output [13:0] tx_sig;   // for test mode only
output bit_clock ;
output DAC_clk, DAC_clk_n;

output clk;
output rst;
output scram_data;
output sym_phase_of;


output clk_120;
output steady_state;
output bit_0_a_ddd, bit_0_b_ddd;
output [4:0] pll_state;
output [1:0] three_cnt_a;
output odd_ev;
output bit_0, bit_1;
output [31:0] sym_phase; 
output true_random;
output [13:0] phase_modulation, roll_total_ddd, phase_test;
output  transition_d, transition_i, data_d, clock_d;
output outside_freq_range;
output [15:0] IIR;
output [13:0] phase_0, phase_1, phase_2, phase_3,phase_4, phase_5, phase_6, phase_7, 
        lookup_rslt_4, SOQPSK_lookup_4;
output [2:0] sym_count_dd;
output sym_phase_of_d, sym_phase_of_dd;
output [13:0] ph_roll_0, ph_roll_1, ph_roll_2, ph_roll_3, ph_roll_4, ph_roll_5, ph_roll_6, ph_roll_7;
output [13:0] phase_fm_rr, phase_fm_r;
output [14:0] phase_total_d1, phase_total_d2;
output flip_ddd, alpha_fm_0_dd;
output [13:0] phase_fm_0, phase_fm_1, fm_phase_of, fm_phase_lu_0;
output [10:0] FM_lookup_addr_0, FM_lookup_addr_1;
output [31:0] quotient, quotient_1;
output testa;
output [8:0] data_trans_cnt;
output [7:0] phase_err;



wire  [31:0] FB_RATE;
wire  CLK_POL;	 // Clock Polarity
wire  RAND;     // Randomization On/Off
wire  [31:0] sym_phase_p;   
reg   [31:0] sym_phase;   
reg   [2:0] sym_count, sym_count_d, sym_count_dd, sym_count_ddd;
reg   sym_phase_of;
wire  sym_phase_of_p;
reg [13:0] lookup_rslt_0, lookup_rslt_1, lookup_rslt_2, lookup_rslt_3;
reg [13:0] lookup_rslt_4, lookup_rslt_5, lookup_rslt_6, lookup_rslt_7;
wire [13:0] SOQPSK_lookup_0, SOQPSK_lookup_1, SOQPSK_lookup_2, SOQPSK_lookup_3;
wire [13:0] SOQPSK_lookup_4, SOQPSK_lookup_5, SOQPSK_lookup_6, SOQPSK_lookup_7;
wire [11:0] lookup_addr_0, lookup_addr_1, lookup_addr_2, lookup_addr_3;
wire [11:0] lookup_addr_4, lookup_addr_5, lookup_addr_6, lookup_addr_7;
wire [10:0] FM_lookup_addr_0, FM_lookup_addr_1;
wire [13:0] fm_phase_lu_0, fm_phase_lu_1;
reg [13:0] phase_fm_0, phase_fm_1, phase_fm_1_d, phase_fm_r, phase_fm_rr, fm_phase_of, fm_phase_of_d;
wire [12:0] phase_fm;
wire [25:0] product;
reg sym_phase_of_d, sym_phase_of_dd, sym_phase_of_ddd, sym_phase_of_dddd, sym_phase_of_ddddd;
wire bit_clock;
reg I_0, I_1, I_2, Q_0, Q_1, Q_2;
reg bit_0, bit_1;
reg [1:0] alpha, alpha_0, alpha_1, alpha_2, alpha_3,alpha_4, alpha_5, alpha_6, alpha_7;
reg [1:0] alpha_d, alpha_0_d, alpha_1_d, alpha_2_d, alpha_3_d,alpha_4_d, alpha_5_d, alpha_6_d, alpha_7_d;
reg alpha_fm_0, alpha_fm_1, alpha_fm_0_d, alpha_fm_1_d, alpha_fm_0_dd, alpha_fm_1_dd, alpha_fm_0_ddd, alpha_fm_1_ddd;
wire tag1, tag2, tag3, tag4;
reg flip, flip_d, flip_dd, flip_ddd;
reg [13:0] phase_0, phase_1, phase_2, phase_3,phase_4, phase_5, phase_6, phase_7;
reg [13:0] ph_roll_0, ph_roll_1, ph_roll_2, ph_roll_3, ph_roll_4, ph_roll_5, ph_roll_6, ph_roll_7,
		roll_total_1,roll_total_2,
		roll_total_d, roll_total_dd, roll_total_ddd, phase_total_d; 
		
		
reg [14:0] phase_total_1, phase_total_2, phase_total_3, phase_total_4, phase_total_d1, 
		phase_total_d2, phase_testx; 
wire [13:0] phase_test;		
wire [13:0] constant;	
reg [13:0] tx_sig;	
wire one;
wire [31:0] car_freq;
wire [13:0] sine_O, cosine_O, sine, cosine;
wire [31:0] bit_rate;
wire [13:0] tx_sig_p;
wire locked;
wire clk_x;
reg rst;
wire clk;
wire scram_data;
reg [3:0] bit_cnt;
wire [13:0] phase_modulation;
wire clk1, clk1_n;
reg odd_ev, odd_ev_d, odd_ev_dd, odd_ev_ddd, odd_ev_dddd, odd_ev_ddddd;
reg bit_0_a, bit_0_b, bit_1_a, bit_1_b, bit_2_a, bit_2_b;
reg bit_0_a_d, bit_0_a_dd, bit_0_a_ddd, bit_0_b_d, bit_0_b_dd, bit_0_b_ddd;
reg bit_1_a_d, bit_1_a_dd, bit_1_a_ddd, bit_1_b_d, bit_1_b_dd, bit_1_b_ddd;
reg bit_2_a_d, bit_2_a_dd, bit_2_a_ddd, bit_2_b_d, bit_2_b_dd, bit_2_b_ddd;
wire steady_state;
reg [13:0] cosine_O_d, cosine_O_dd, cosine_O_ddd, sine_O_d, sine_O_dd, sine_O_ddd;
wire [14:0] cosine_O_ddd_x;
wire PB_nBB;
wire data_clock_sel; 
reg true_random;
reg data_in_d;
wire [4:0] pll_state;

wire test_en;
wire simulation;
wire CLK_SRC, DAT_SRC, DAT_POL, internal_data;
wire clk_120;
reg [9:0] sym_phase_ms10_d;
wire [31:0] quotient, quotient_1;
reg [31:0] bit_rate_r;
reg bit_rate_rs;
reg rst_d, rst_dd, rst_ddd;
reg [2:0] select_0, select_1, select_2 , select_3, select_4, select_5, select_6, select_7;
wire outside_freq_range;
wire [8:0] data_trans_cnt;
wire [7:0] phase_err;
reg phase_31_d;
reg data_samp;


//assign bit_rate=32'h2000000;

always @ (posedge clk)
	begin
	rst_d<= rst;
	rst_dd<= rst_d;
	rst_ddd<=rst_dd;
	end





always @ (posedge clk)
	if(rst_n==1'd0)
		begin
		bit_rate_r<=32'd0;
		bit_rate_rs<=1'd0;
		end
	else	
		begin
		bit_rate_r<=bit_rate;
		bit_rate_rs<=(bit_rate_r!=bit_rate);
		end

//***************************************************************************************
//			Lock to the input data clock or data
//***************************************************************************************
assign data_clock_sel=(CLK_POL==1'd0)?data_clock:!data_clock;

data_transition_pll_240  detect_bit_rate(
	.clk (clk),
	.clk_120 (clk_120),
	.rst (rst|rst_d|rst_dd),
	.data (data_in),
	.clock (data_clock_sel),
	.frequency_set (bit_rate),
	.test_en (1'd0), //
	.CLK_SRC (CLK_SRC),
	.DAT_SRC (DAT_SRC),
	
	.sym_phase_of (sym_phase_of_p), 
	.NCO (sym_phase_p),
	.steady_state (steady_state),
	.frequency (FB_RATE),
	.state (pll_state),
	.transition_d (transition_d),
	.transition_i (transition_i),
	.clock_d (clock_d), 
	.data_d (data_d),
	.outside_freq_range (outside_freq_range),
	.IIR (IIR),
	.quotient (quotient),
	.quotient_1 (quotient_1),
	.testa (testa),
	.data_trans_cnt (data_trans_cnt),
	.phase_err (phase_err)
	);
	

always @ (posedge clk)
		if (rst==1'd1)
			begin
			sym_phase_of<=1'd0;
			sym_phase<=32'd0;
			end
		else
			begin
			sym_phase_of<=sym_phase_of_p;
			sym_phase<=sym_phase_p;
			end
	
	
	
	
	
//**************************************************************************************
//**************************************************************************************


assign car_freq  =  (PB_nBB==1'd1)?32'd1879048192 : 32'd0;  // 70MHz  - should be set to zero if baseband is needed.

always @ (posedge clk)
	tx_sig<={!tx_sig_p[13],tx_sig_p[12:0]};
	
	
assign simulation =1'd0;	
always @ (posedge clk)
	//rst <= (simulation ==1'd1)?((rst_n==1'd0)|(bit_rate_rs==1'd1)):(rst_n==1'd0);
	rst <=(rst_n==1'd0);


RNRZ_L scrambler (
	.clk (clk),
	.rst (rst),
	.data_in  (data_d),//(data_in), //
	.data_clk (sym_phase[31]),//(bit_clock),  //
	.mode_15_n11 (1'd1),
	.TX_nRX (1'd1),
	.BER_test (1'd0),
	.data_out (scram_data)
	);
	
always @ (posedge clk)
	if(rst==1'd1)
		phase_31_d<=1'd0;
	else
		phase_31_d<=sym_phase[31];

always @ (posedge clk)
	if(rst==1'd1)
		data_samp<=1'd0;
	else if ((sym_phase[31]==1'd1)&(phase_31_d==1'd0))
		data_samp<=data_d;

always @ (scram_data or RAND or data_in_d or DAT_SRC or DAT_POL or internal_data)
	case( {DAT_SRC, DAT_POL, RAND} )
	(3'd0):	true_random=data_samp;
	(3'd1):  true_random=scram_data;
	(3'd2):	true_random=!data_samp;
	(3'd3):  true_random=!scram_data;
	(3'd4):  true_random=internal_data;
	(3'd5):  true_random=internal_data;
	(3'd6):  true_random=!internal_data;
	(3'd7):  true_random=!internal_data;
	endcase






always @ (posedge clk)
	if (rst==1'd1)
		begin
		bit_cnt<=4'd2;
		flip<=1'd0;
		end
	else if (sym_phase_of==1'd1)
		begin
		bit_cnt<=bit_cnt+4'd1;
		flip<=!flip;
		end

assign DAC_clk=clk1;
assign DAC_clk_n=clk1_n;

PLL_10_240 phase_locked_loop (
	.inclk0 (inclk0),
	.c0 (clk),
	.c1 (clk1),
	.c2 (clk1_n),
	.c3 (clk_120),
	.locked (locked)
	);
	
	
// generate pipeline delay signals
always @ (posedge clk)
	if (rst==1'd1)
		begin
		sym_count<=3'd0;
		sym_count_d<=3'd0; 
		sym_count_dd<=3'd0;
		sym_count_ddd<=3'd0;
		sym_phase_of_d<=1'd0;
		sym_phase_of_dd<=1'd0;
		sym_phase_of_ddd<=1'd0;
		sym_phase_of_dddd<=1'd0;
		sym_phase_of_ddddd<=1'd0;
		flip_d<=1'd0;
		flip_dd<=1'd0;
		flip_ddd<=1'd0;
		data_in_d<=1'd0;
		sym_phase_ms10_d<=10'd0;
		end
	else
		begin	
		sym_count<= sym_count+((sym_phase_of==1'd1)? 3'd1:3'd0);
		sym_count_d<=sym_count; 
		sym_count_dd<=sym_count_d;
		sym_count_ddd<=sym_count_dd;
		sym_phase_of_d<=sym_phase_of;
		sym_phase_of_dd<=sym_phase_of_d;
		sym_phase_of_ddd<=sym_phase_of_dd;	
		sym_phase_of_dddd<=sym_phase_of_ddd;
		sym_phase_of_ddddd<=sym_phase_of_dddd;		
		flip_d<=flip;
		flip_dd<=flip_d;
		flip_ddd<=flip_dd;	
		data_in_d<=data_in;	
		sym_phase_ms10_d<=sym_phase[31:22];
		end


//************************************************************************************************
//								FM/PCM modulator
//************************************************************************************************



assign FM_lookup_addr_0 = {sym_count_d[0],sym_phase_ms10_d} ;
assign FM_lookup_addr_1 = {!sym_count_d[0],sym_phase_ms10_d} ;


FM  FM_PCM_phase_0 (
	.address (FM_lookup_addr_0),  //12 bits
	.clock (clk),
	.q (fm_phase_lu_0)  // 14 bits
	);

FM  FM_PCM_phase_1 (
	.address (FM_lookup_addr_1),  //12 bits
	.clock (clk),
	.q (fm_phase_lu_1)  // 14 bits
	);

always @ (posedge clk)
	if (rst==1'd1)
		begin
		alpha_fm_0<=1'd0; 
		alpha_fm_1<=1'd0; 
		end
	else if (sym_phase_of==1'd1)
		begin
		alpha_fm_0<=(flip==1'd1)?bit_0:alpha_fm_0; 
		alpha_fm_1<=(flip==1'd0)?bit_0:alpha_fm_1;
		end

always @ (posedge clk)
	if (rst==1'd1)
		begin
		alpha_fm_0_d<=1'd0; 
		alpha_fm_0_dd<=1'd0; 
		alpha_fm_0_ddd<=1'd0; 
		alpha_fm_1_d<=1'd0;  
		alpha_fm_1_dd<=1'd0; 
		alpha_fm_1_ddd<=1'd0; 
		end
	else	
		begin
		alpha_fm_0_d<=alpha_fm_0; 
		alpha_fm_0_dd<=alpha_fm_0_d; 
		alpha_fm_0_ddd<=alpha_fm_0_dd; 
		alpha_fm_1_d<=alpha_fm_1;  
		alpha_fm_1_dd<=alpha_fm_1_d; 
		alpha_fm_1_ddd<=alpha_fm_1_dd; 
		end

always @ (posedge clk)
	if (rst==1'd1)
		begin
		phase_fm_0<=14'd0;
		phase_fm_1<=14'd0;
		end
	else	
		begin
		phase_fm_0<=(alpha_fm_0_ddd==1'd1)?fm_phase_lu_0:(-fm_phase_lu_0);
		phase_fm_1<=(alpha_fm_1_ddd==1'd1)?fm_phase_lu_1:(-fm_phase_lu_1);
		end
		
	
always @ (posedge clk)
	if (rst==1'd1)		
		fm_phase_of	<=14'd0;
	else if ((sym_phase_of_ddd==1'd1)&&(flip_ddd==1'd1))	
		fm_phase_of	<=fm_phase_of+((phase_fm_0[13]==1'd0)?14'h1666:14'h299a);
	else if ((sym_phase_of_ddd==1'd1)&&(flip_ddd==1'd0))	
		fm_phase_of	<=fm_phase_of+((phase_fm_1[13]==1'd0)?14'h1666:14'h299a);
	

always @ (posedge clk)
	if (rst==1'd1)
      begin	
		fm_phase_of_d <=14'd0;
		phase_fm_r   <= 14'd0;
		phase_fm_rr  <= 14'd0;
		phase_fm_1_d <= 14'd0;
		end
	else
		begin
		fm_phase_of_d <=fm_phase_of;
		phase_fm_r   <= phase_fm_0 + fm_phase_of_d;
		phase_fm_1_d <= phase_fm_1;
		phase_fm_rr  <= phase_fm_r + phase_fm_1_d;
		end


// phase modulation for PCM/FM modulation		
assign phase_fm= phase_fm_rr[13:1];		




//************************************************************************************************
//							SOQPSK modulator
//************************************************************************************************

assign bit_clock=sym_phase[31];



always @ (posedge clk)
	if (rst==1'd1)
		begin
		bit_0<=1'd1;
		bit_1<=1'd1;
		end
	else if (sym_phase_of==1'd1)	
		begin
		bit_0<=true_random;
		bit_1<=bit_0;
		end



//**********************************************************************************
//									Precoder
//**********************************************************************************

always @ (posedge clk)
	if (rst==1'd1)
		begin
		I_1<=1'd1;
		Q_1<=1'd1;
		I_2<=1'd1;
		Q_2<=1'd1;
		end
	else if (sym_phase_of==1'd1)	
		begin
		I_1<=I_0;
		Q_1<=Q_0;
		I_2<=I_1;
		Q_2<=Q_1;
		end


always @ (posedge clk)
	if (rst==1'd1)
		begin
		I_0<=1'd0;
		Q_0<=1'd0;
		end
	else if (sym_phase_of==1'd1)
	case (flip)	
	1'b0:  	begin
				I_0<=(Diff_en==1'd1)?(bit_0^(!Q_0)):bit_0;
			   end
	1'b1:  	begin
				Q_0<=(Diff_en==1'd1)?(bit_0^(I_0)):bit_0;
			   end
	endcase																								


assign tag1= Q_0==Q_2;
assign tag2= Q_0^I_1;
assign tag3= I_0==I_2;
assign tag4= I_0^Q_1;




always @ (posedge clk)
	if (rst==1'd1)
		begin
		alpha<=2'd0;
		end
	else if (sym_phase_of==1'd1)
	casex ({flip, tag1, tag2, tag3, tag4})
		(5'b000xx): alpha<=2'd1 ;
		(5'b001xx): alpha<=2'd3 ;
		(5'b1xx01): alpha<=2'd1 ;
		(5'b1xx00): alpha<=2'd3 ;
		default  alpha<=2'd0 ;
	endcase
 
 
 
//******************************************************************
//*****  generate 8 overlapping phase modulation waveforms  ********
//******************************************************************


		
always @ (posedge clk)
	if (rst==1'd1)
		alpha_0<=2'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count==3'd0))
		alpha_0<=alpha;
		
always @ (posedge clk)
	if (rst==1'd1)
		alpha_1<=2'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count==3'd1))
		alpha_1<=alpha;
		
always @ (posedge clk)
	if (rst==1'd1)
		alpha_2<=2'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count==3'd2))
		alpha_2<=alpha;
		
always @ (posedge clk)
	if (rst==1'd1)
		alpha_3<=2'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count==3'd3))
		alpha_3<=alpha;			
		
always @ (posedge clk)
	if (rst==1'd1)
		alpha_4<=2'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count==3'd4))
		alpha_4<=alpha;
		
always @ (posedge clk)
	if (rst==1'd1)
		alpha_5<=2'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count==3'd5))
		alpha_5<=alpha;
		
always @ (posedge clk)
	if (rst==1'd1)
		alpha_6<=2'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count==3'd6))
		alpha_6<=alpha;
		
always @ (posedge clk)
	if (rst==1'd1)
		alpha_7<=2'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count==3'd7))
		alpha_7<=alpha;			

always @ (posedge clk)
if (rst==1'd1)
	begin
	alpha_d<=2'd0; 
	alpha_0_d<=2'd0;  
	alpha_1_d<=2'd0;  
	alpha_2_d<=2'd0;  
	alpha_3_d<=2'd0; 
	alpha_4_d<=2'd0;  
	alpha_5_d<=2'd0;  
	alpha_6_d<=2'd0;  
	alpha_7_d<=2'd0; 
	end
else
	begin
	alpha_d<=alpha; 
	alpha_0_d<=alpha_0;  
	alpha_1_d<=alpha_1;  
	alpha_2_d<=alpha_2;  
	alpha_3_d<=alpha_3; 
	alpha_4_d<=alpha_4;  
	alpha_5_d<=alpha_5;  
	alpha_6_d<=alpha_6;  
	alpha_7_d<=alpha_7; 
	end


		

//***************************************************************************************
//***************************************************************************************
//***************************************************************************************

SOQPSK_LU0 soqpsk_lu0(
	.address (sym_phase[31:23]),   //[8:0]
	.clock (clk),
	.q  (SOQPSK_lookup_0) //		[13:0]
	);
	
SOQPSK_LU1 soqpsk_lu1(
	.address (sym_phase[31:23]),   //[8:0]
	.clock (clk),
	.q  (SOQPSK_lookup_1) //		[13:0]
	);
	
SOQPSK_LU2 soqpsk_lu2(
	.address (sym_phase[31:23]),   //[8:0]
	.clock (clk),
	.q  (SOQPSK_lookup_2) //		[13:0]
	);	
	
SOQPSK_LU3 soqpsk_lu3(
	.address (sym_phase[31:23]),   //[8:0]
	.clock (clk),
	.q  (SOQPSK_lookup_3) //		[13:0]
	);	
	
SOQPSK_LU4 soqpsk_lu4(
	.address (sym_phase[31:23]),   //[8:0]
	.clock (clk),
	.q  (SOQPSK_lookup_4) //		[13:0]
	);			
	
SOQPSK_LU5 soqpsk_lu5(
	.address (sym_phase[31:23]),   //[8:0]
	.clock (clk),
	.q  (SOQPSK_lookup_5) //		[13:0]
	);		
	
SOQPSK_LU6 soqpsk_lu6(
	.address (sym_phase[31:23]),   //[8:0]
	.clock (clk),
	.q  (SOQPSK_lookup_6) //		[13:0]
	);	
	
SOQPSK_LU7 soqpsk_lu7(
	.address (sym_phase[31:23]),   //[8:0]
	.clock (clk),
	.q  (SOQPSK_lookup_7) //		[13:0]
	);			
	
//***************************************************************************************
//***************************************************************************************
//***************************************************************************************
always @ (posedge clk)
	if (rst==1'd1)
		begin
		select_0<=3'd0; 
		select_1<=3'd0; 
		select_2<=3'd0; 
		select_3<=3'd0;  
		select_4<=3'd0; 
		select_5<=3'd0;  
		select_6<=3'd0;  
		select_7<=3'd0; 
		end
	else
		begin
		select_0<=sym_count_d; 
		select_1<=sym_count_d-3'd1; 
		select_2<=sym_count_d-3'd2; 
		select_3<=sym_count_d-3'd3;  
		select_4<=sym_count_d-3'd4; 
		select_5<=sym_count_d-3'd5; 
		select_6<=sym_count_d-3'd6;   
		select_7<=sym_count_d-3'd7; 
		end



always @ (posedge clk)
	if (rst==1'd1)
		lookup_rslt_0<=14'd0;
	else
		case (select_0) //(sym_count_dd)
		(3'd0):	lookup_rslt_0<=SOQPSK_lookup_0;
		(3'd1):	lookup_rslt_0<=SOQPSK_lookup_1;
		(3'd2):	lookup_rslt_0<=SOQPSK_lookup_2;
		(3'd3):	lookup_rslt_0<=SOQPSK_lookup_3;
		(3'd4):	lookup_rslt_0<=SOQPSK_lookup_4;
		(3'd5):	lookup_rslt_0<=SOQPSK_lookup_5;
		(3'd6):	lookup_rslt_0<=SOQPSK_lookup_6;
		(3'd7):	lookup_rslt_0<=SOQPSK_lookup_7;
		endcase

always @ (posedge clk)
	if (rst==1'd1)
		lookup_rslt_1<=14'd0;
	else
		case (select_1) //(sym_count_dd-3'd1)
		(3'd0):	lookup_rslt_1<=SOQPSK_lookup_0;
		(3'd1):	lookup_rslt_1<=SOQPSK_lookup_1;
		(3'd2):	lookup_rslt_1<=SOQPSK_lookup_2;
		(3'd3):	lookup_rslt_1<=SOQPSK_lookup_3;
		(3'd4):	lookup_rslt_1<=SOQPSK_lookup_4;
		(3'd5):	lookup_rslt_1<=SOQPSK_lookup_5;
		(3'd6):	lookup_rslt_1<=SOQPSK_lookup_6;
		(3'd7):	lookup_rslt_1<=SOQPSK_lookup_7;
		endcase

always @ (posedge clk)
	if (rst==1'd1)
		lookup_rslt_2<=14'd0;
	else
		case (select_2) //(sym_count_dd-3'd2)
		(3'd0):	lookup_rslt_2<=SOQPSK_lookup_0;
		(3'd1):	lookup_rslt_2<=SOQPSK_lookup_1;
		(3'd2):	lookup_rslt_2<=SOQPSK_lookup_2;
		(3'd3):	lookup_rslt_2<=SOQPSK_lookup_3;
		(3'd4):	lookup_rslt_2<=SOQPSK_lookup_4;
		(3'd5):	lookup_rslt_2<=SOQPSK_lookup_5;
		(3'd6):	lookup_rslt_2<=SOQPSK_lookup_6;
		(3'd7):	lookup_rslt_2<=SOQPSK_lookup_7;
		endcase

always @ (posedge clk)
	if (rst==1'd1)
		lookup_rslt_3<=14'd0;
	else
		case (select_3) //(sym_count_dd-3'd3)
		(3'd0):	lookup_rslt_3<=SOQPSK_lookup_0;
		(3'd1):	lookup_rslt_3<=SOQPSK_lookup_1;
		(3'd2):	lookup_rslt_3<=SOQPSK_lookup_2;
		(3'd3):	lookup_rslt_3<=SOQPSK_lookup_3;
		(3'd4):	lookup_rslt_3<=SOQPSK_lookup_4;
		(3'd5):	lookup_rslt_3<=SOQPSK_lookup_5;
		(3'd6):	lookup_rslt_3<=SOQPSK_lookup_6;
		(3'd7):	lookup_rslt_3<=SOQPSK_lookup_7;
		endcase

always @ (posedge clk)
	if (rst==1'd1)
		lookup_rslt_4<=14'd0;
	else
		case (select_4) //(sym_count_dd-3'd4)
		(3'd0):	lookup_rslt_4<=SOQPSK_lookup_0;
		(3'd1):	lookup_rslt_4<=SOQPSK_lookup_1;
		(3'd2):	lookup_rslt_4<=SOQPSK_lookup_2;
		(3'd3):	lookup_rslt_4<=SOQPSK_lookup_3;
		(3'd4):	lookup_rslt_4<=SOQPSK_lookup_4;
		(3'd5):	lookup_rslt_4<=SOQPSK_lookup_5;
		(3'd6):	lookup_rslt_4<=SOQPSK_lookup_6;
		(3'd7):	lookup_rslt_4<=SOQPSK_lookup_7;
		endcase

always @ (posedge clk)
	if (rst==1'd1)
		lookup_rslt_5<=14'd0;
	else
		case (select_5) //(sym_count_dd-3'd5)
		(3'd0):	lookup_rslt_5<=SOQPSK_lookup_0;
		(3'd1):	lookup_rslt_5<=SOQPSK_lookup_1;
		(3'd2):	lookup_rslt_5<=SOQPSK_lookup_2;
		(3'd3):	lookup_rslt_5<=SOQPSK_lookup_3;
		(3'd4):	lookup_rslt_5<=SOQPSK_lookup_4;
		(3'd5):	lookup_rslt_5<=SOQPSK_lookup_5;
		(3'd6):	lookup_rslt_5<=SOQPSK_lookup_6;
		(3'd7):	lookup_rslt_5<=SOQPSK_lookup_7;
		endcase
	
always @ (posedge clk)
	if (rst==1'd1)
		lookup_rslt_6<=14'd0;
	else
		case (select_6) //(sym_count_dd-3'd6)
		(3'd0):	lookup_rslt_6<=SOQPSK_lookup_0;
		(3'd1):	lookup_rslt_6<=SOQPSK_lookup_1;
		(3'd2):	lookup_rslt_6<=SOQPSK_lookup_2;
		(3'd3):	lookup_rslt_6<=SOQPSK_lookup_3;
		(3'd4):	lookup_rslt_6<=SOQPSK_lookup_4;
		(3'd5):	lookup_rslt_6<=SOQPSK_lookup_5;
		(3'd6):	lookup_rslt_6<=SOQPSK_lookup_6;
		(3'd7):	lookup_rslt_6<=SOQPSK_lookup_7;
		endcase	
	
always @ (posedge clk)
	if (rst==1'd1)
		lookup_rslt_7<=14'd0;
	else
		case (select_7) //(sym_count_dd-3'd7)
		(3'd0):	lookup_rslt_7<=SOQPSK_lookup_0;
		(3'd1):	lookup_rslt_7<=SOQPSK_lookup_1;
		(3'd2):	lookup_rslt_7<=SOQPSK_lookup_2;
		(3'd3):	lookup_rslt_7<=SOQPSK_lookup_3;
		(3'd4):	lookup_rslt_7<=SOQPSK_lookup_4;
		(3'd5):	lookup_rslt_7<=SOQPSK_lookup_5;
		(3'd6):	lookup_rslt_7<=SOQPSK_lookup_6;
		(3'd7):	lookup_rslt_7<=SOQPSK_lookup_7;
		endcase	

//***************************************************************************************
//***************************************************************************************
//***************************************************************************************
always @ (posedge clk)
	if (rst==1'd1)
		begin
		phase_0<=14'd0;
		phase_1<=14'd0;
		phase_2<=14'd0;
		phase_3<=14'd0;
		phase_4<=14'd0;
		phase_5<=14'd0;
		phase_6<=14'd0;
		phase_7<=14'd0;
		end
	else 
begin
		case (alpha_0_d)
			2'd0: phase_0<=  14'd0;
			2'd1: phase_0<=  lookup_rslt_0;
			2'd2: phase_0<= -lookup_rslt_0;
			2'd3: phase_0<= -lookup_rslt_0;
		endcase
		case (alpha_1_d)
			2'd0: phase_1<=   14'd0;
			2'd1: phase_1<=  lookup_rslt_1;
			2'd2: phase_1<= -lookup_rslt_1;
			2'd3: phase_1<= -lookup_rslt_1;
		endcase
		case (alpha_2_d)
			2'd0: phase_2<=  14'd0;
			2'd1: phase_2<=  lookup_rslt_2;
			2'd2: phase_2<= -lookup_rslt_2;
			2'd3: phase_2<= -lookup_rslt_2;
		endcase
		case (alpha_3_d)
			2'd0: phase_3<=  14'd0;
			2'd1: phase_3<=  lookup_rslt_3;
			2'd2: phase_3<= -lookup_rslt_3;
			2'd3: phase_3<= -lookup_rslt_3;
		endcase
		case (alpha_4_d)
			2'd0: phase_4<=  14'd0;
			2'd1: phase_4<=  lookup_rslt_4;
			2'd2: phase_4<= -lookup_rslt_4;
			2'd3: phase_4<= -lookup_rslt_4;
		endcase
		case (alpha_5_d)
			2'd0: phase_5<=  14'd0;
			2'd1: phase_5<=  lookup_rslt_5;
			2'd2: phase_5<= -lookup_rslt_5;
			2'd3: phase_5<= -lookup_rslt_5;
		endcase
		case (alpha_6_d)
			2'd0: phase_6<=  14'd0;
			2'd1: phase_6<=  lookup_rslt_6;
			2'd2: phase_6<= -lookup_rslt_6;
			2'd3: phase_6<= -lookup_rslt_6;
		endcase
		case (alpha_7_d)
			2'd0: phase_7<=  14'd0;
			2'd1: phase_7<=  lookup_rslt_7;
			2'd2: phase_7<= -lookup_rslt_7;
			2'd3: phase_7<= -lookup_rslt_7;
		endcase
end
// At the end of each phase transition time, the total phase contribution needs to
// identified and saved before the next waveform can begin.  The total phase is kept 
// modulo 2pi


always @ (posedge clk)
	if (rst==1'd1)
		ph_roll_0<=14'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count_dd==3'd7))	
		ph_roll_0<=ph_roll_0+((phase_0[13]==1'd1)?14'h3000:
							  (phase_0[12:9]!=4'd0)?14'h1000:14'h0000);
		
always @ (posedge clk)
	if (rst==1'd1)
		ph_roll_1<=14'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count_dd==3'd0))	
		ph_roll_1<=ph_roll_1+((phase_1[13]==1'd1)?14'h3000:
							  (phase_1[12:9]!=4'd0)?14'h1000:14'h0000);
		
always @ (posedge clk)
	if (rst==1'd1)
		ph_roll_2<=14'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count_dd==3'd1))	
		ph_roll_2<=ph_roll_2+((phase_2[13]==1'd1)?14'h3000:
							  (phase_2[12:9]!=4'd0)?14'h1000:14'h0000);
		
always @ (posedge clk)
	if (rst==1'd1)
		ph_roll_3<=14'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count_dd==3'd2))	
		ph_roll_3<=ph_roll_3+((phase_3[13]==1'd1)?14'h3000:
							  (phase_3[12:9]!=4'd0)?14'h1000:14'h0000);
		
always @ (posedge clk)
	if (rst==1'd1)
		ph_roll_4<=14'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count_dd==3'd3))	
		ph_roll_4<=ph_roll_4+((phase_4[13]==1'd1)?14'h3000:
							  (phase_4[12:9]!=4'd0)?14'h1000:14'h0000);
		
always @ (posedge clk)
	if (rst==1'd1)
		ph_roll_5<=14'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count_dd==3'd4))	
		ph_roll_5<=ph_roll_5+((phase_5[13]==1'd1)?14'h3000:
							  (phase_5[12:9]!=4'd0)?14'h1000:14'h0000);
		
always @ (posedge clk)
	if (rst==1'd1)
		ph_roll_6<=14'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count_dd==3'd5))	
		ph_roll_6<=ph_roll_6+((phase_6[13]==1'd1)?14'h3000:
							  (phase_6[12:9]!=4'd0)?14'h1000:14'h0000);
		
always @ (posedge clk)
	if (rst==1'd1)
		ph_roll_7<=14'd0;
	else if ((sym_phase_of_dd==1'd1)&(sym_count_dd==3'd6))	
		ph_roll_7<=ph_roll_7+((phase_7[13]==1'd1)?14'h3000:
							  (phase_7[12:9]!=4'd0)?14'h1000:14'h0000);					
		
always @ (posedge clk)
	if (rst==1'd1)
		begin	
		
		roll_total_1<=14'd0;
		roll_total_2<=14'd0;
		roll_total_d<=14'd0;
		roll_total_dd<=14'd0;
		roll_total_ddd<=14'd0;
		phase_testx <= 15'd0;
		
		phase_total_1<=15'd0; 
		phase_total_2<=15'd0; 
		phase_total_3<=15'd0; 
		phase_total_4<=15'd0; 
		phase_total_d<=14'd0; 
		phase_total_d1<=15'd0; 
		phase_total_d2<=15'd0;
		
		end
	else	
		begin		
		roll_total_1 <= ph_roll_0 + ph_roll_1 + ph_roll_2 + ph_roll_3;
		roll_total_2 <= ph_roll_4 + ph_roll_5 + ph_roll_6 + ph_roll_7;
		roll_total_d <= roll_total_1 + roll_total_2;
		roll_total_dd <= roll_total_d;
		roll_total_ddd <= roll_total_dd;
		
		phase_total_1 <= {1'd0, phase_0} + {1'd0, phase_1}; 
		phase_total_2 <= {1'd0, phase_2} + {1'd0, phase_3};
		phase_total_3 <= {1'd0, phase_4} + {1'd0, phase_5} ; 
		phase_total_4 <= {1'd0, phase_6} + {1'd0, phase_7} ;
		
		phase_total_d1<={1'd0,phase_total_1[13:0]}+ {1'd0, phase_total_2[13:0]};
		phase_total_d2<={1'd0,phase_total_3[13:0]}+ {1'd0, phase_total_4[13:0]};
		
		phase_total_d <= roll_total_ddd + phase_total_d1[13:0] + phase_total_d2[13:0];
		phase_testx <= phase_total_1 + phase_total_2 + phase_total_3 + phase_total_4;
		end
assign phase_test=phase_testx[13:0];
// phase_total_d is the phase modulation signal for SOQPSK mode


//******************************************************************************
//						phase modulation
//******************************************************************************

assign constant=14'd5500;
assign one=1'd1;


assign phase_modulation= (mode==4'd0)? {phase_fm,1'd0}:
						 (mode==4'd1)? phase_total_d://SOQPSK
						 (mode==4'd2)? 14'd0: 
						 (mode==4'd3)? sym_phase[31:18]:
						 14'd0			;


frequency_translate_cyclone_2  produce_carrier(
	.clk (clk),
	.rst  (rst),
	.real_in  (constant),
	.imag_in  (constant),
	.frequency_mod  (phase_modulation),
	.frequency  (car_freq),
	.frequency_en  (one),
	.real_rslt  (tx_sig_p),
	.sine  (sine_O),   //13:0
	.cosine  (cosine_O)  //13:0
	);
	
//***************************************************
//***************************************************
assign sine   = sine_O_ddd;
assign cosine = cosine_O_ddd;


always @ (posedge clk)
	if (rst==1'd1)
		begin
		cosine_O_d  <=14'd0;
		cosine_O_dd <=14'd0;
		cosine_O_ddd<=14'd0;
		sine_O_d    <=14'd0;
		sine_O_dd   <=14'd0;
		sine_O_ddd  <=14'd0;
		end
	else
		begin
		cosine_O_d<=cosine_O;
		cosine_O_dd<=cosine_O_d;
		cosine_O_ddd<=(cosine_O_ddd_x[14]==cosine_O_ddd_x[13])? cosine_O_ddd_x[13:0]  :
						(cosine_O_ddd_x[14]==1'd0)?14'h1fff  :14'h2000  ;
						
		sine_O_d<=sine_O;
		sine_O_dd<=sine_O_d;
		sine_O_ddd<=sine_O_dd;
		end

//  correct for phase imabalance in the I-Q modulator
	multiplier_14_12 scale(
		.clock (clk),
		.dataa (sine_O),   //14 bits
		.datab ({ {1{phase_offset[7]}} ,  phase_offset, 3'd0 }),							// 12 bits
		.result (product)							// 26 bits
		);

assign cosine_O_ddd_x= {cosine_O_dd[13],cosine_O_dd}+{product[25],product[25:12]};						
		
endmodule
