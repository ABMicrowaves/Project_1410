module data_transition_pll_240 (
	clk,   // fixed rate clock which is 240 MHz
	clk_120, // 120 MHz fixed rate clock
	rst,	// reset is active high
	data,	// NRZ input
	clock,	//  data clock which may or may not be present
	frequency_set,  // frequency set is  needed if the clock is not present
					// (bit rate/ clock rate)* 2^32
	test_en,	
	CLK_SRC,	
	DAT_SRC,
	
	sym_phase_of, // bit clock which is true one clock cycle for each bit time
	NCO	,		// 32 bit phase accumulator which is locked to bit rate
	steady_state, 
	
	
	state, 
	frequency,
	dividend, 
	divisor,
	quotient,
	freq_correction, 
	result_A, 
	result_B, 
	phase_err,
	scaled_phase,
	outside_freq_range,
	bit_cnt,  
	timer, 
	timer_d, 

	transition,
	transition_d, 
	transition_i,
	activity_count, 
	activity, 
	clock_d, 
	data_d, 
	IIR,
	quotient_1, 
	testa,
	data_trans_cnt,
	data_dd,
	timer_not_of,
	lock,
	abs_phase_err
	//sample_clk, phase_err, scaled_phase
	);
	
input clk;
input clk_120;
input rst;
input data;
input clock;
input [31:0] frequency_set;
input test_en;
input CLK_SRC;
input DAT_SRC;


output sym_phase_of;
output [31:0] NCO;
output steady_state;



output [23:0] activity_count;
output activity;

output [21:0] dividend, divisor;
output [31:0] quotient,quotient_1, freq_correction,result_A, result_B, scaled_phase;
output [4:0] state;
output [31:0] frequency;
output transition_d, transition_i,transition, clock_d;
output [15:0] IIR;
output outside_freq_range;
output [7:0] phase_err;
output [8:0] bit_cnt;
output [20:0] timer, timer_d;
output testa, data_d, data_dd;
output [8:0] data_trans_cnt;
output timer_not_of;
output lock;
output [7:0] abs_phase_err;



reg clock_d, clock_dd, data_d, data_dd;
wire transition, transition_i;
wire [4:0] state;
wire [20:0] timer, timer_d;
reg timer_of;
reg [8:0] bit_cnt; 
wire [8:0] data_trans_cnt;
reg [5:0] divide_cnt;
reg divide_cnt_32;
reg [21:0] dividend, divisor;
wire [31:0] quotient, quotient_1;
reg decision;
reg [31:0] frequency;
wire [31:0] NCO;
wire [31:0] freq_correction;
reg [7:0] phase_err;
wire [31:0] scaled_phase;
reg [31:0]  freq_delta, freq_delta_1;
wire [31:0] freq_accum;
reg transition_d, transition_dd, transition_ddd, transition_dddd, transition_ddddd,
       transition_dddddd, transition_ddddddd, transition_dddddddd, transition_ddddddddd;
reg [15:0] test_NCO;
wire clock_t;
wire [15:0] test_freq;
wire [7:0] round;
reg [9:0] bit_cnt1;
reg [7:0] abs_phase_err;
reg [15:0] IIR;
wire sample_clk;
wire sym_phase_of;
reg  sym_phase_of_d;
wire [15:0] upper_limit, lower_limit;
reg outside_freq_range;
wire steady_state;
reg [7:0] NCO_cnt;
reg [8:0] bit_cnt_tst, bit_total;
wire [8:0] bit_cnt_err;
reg [8:0] bit_cnt_err_mag;
wire lock_err;
wire [31:0] result_B ;
wire [31:0] result_A ;
reg [23:0] activity_count;
reg activity, activity_test;
wire transition_data;
wire CLK_SRC, DAT_SRC;
reg lock;
reg transition_i_d;
reg transition_data_d , transition_data_dd, transition_data_ddd, transition_data_dddd, transition_data_ddddd;
wire testa;
reg transition_1 , transition_2 , transition_2_d , initial_1 ;
reg [15:0]  IIR_temp;
reg clock_activity, clock_activity_test;




//******************************************************************************************
//		phase accumulator which is locked to bit rate
//******************************************************************************************

always @(posedge clk)
	if (rst==1'd1)
		begin
		NCO_cnt<=8'd0;
		end
	else
		begin
		NCO_cnt<=(sym_phase_of_d==1'd1)?(NCO_cnt+8'd1):NCO_cnt;
		end

NCO_32 osc(
	.clk (clk),
	.rst (rst),
	.In_A (frequency),

	.Rslt (NCO),
	.sym_phase_of (sym_phase_of)
	);
		
//******************************************************************************************
//******************************************************************************************
//******************************************************************************************		
		

// Verify that the number of bit clock transitions is approximately the same as the number
// of cycles of the NCO		
always @(posedge clk)
	if (initial_1==1'd1)
		begin
		bit_cnt_tst<=9'd0;
		bit_total<=9'd0;
		bit_cnt_err_mag<=9'd0;
		end
	else if ((sym_phase_of_d==1'd1)&&(NCO_cnt==8'hff))	// at every 256 NCO periods
		begin
		bit_cnt_tst<=9'd0;
		bit_total<=bit_cnt_tst;
		end
	else if (transition_1==1'd1)	      // at every clock transition
		begin 
		bit_cnt_tst<=(bit_cnt_tst!=9'd511)?(bit_cnt_tst+9'd1):bit_cnt_tst;
		bit_cnt_err_mag<=(bit_cnt_err[8]==1'd0)?bit_cnt_err:(-bit_cnt_err);
		end
		
assign bit_cnt_err= bit_total-9'd255;	
assign lock_err= (bit_cnt_err_mag>9'd20);  
		
//******************************************************************************************
//******************************************************************************************
//******************************************************************************************	

// this signal is a one for one clock cycle for each bit time
 //assign sym_phase_of= ({1'd0,frequency}+{1'd0,NCO})>33'h0ffffffff;

always @ (posedge clk)
	sym_phase_of_d<=sym_phase_of;

// sample the phase accumulator to establish the phase error		
always @(posedge clk)
	if (rst==1'd1)		
		phase_err<=8'd0;
	else if (transition_d==1'd1)
		phase_err<=(NCO[31:24]==8'd128)?8'd127:-NCO[31:24];	



// scale the discriminator so that the second order phase locked loop maintains the 
// same characteristics over the entire frequency range (normalized to bit rate).		
mult_24_8 SCALER	(
	.clock (clk),
	.dataa (phase_err),  //8 bits
	.datab (frequency),  // 32 bits
	.result ({scaled_phase, round})  // 32 bits
	);		


// set the frequency of the bit rate tracking depending on whether the clock is present or not
always @(posedge clk)
	if (rst==1'd1)
		begin
		frequency <= 32'd0;
		end
	else if ((transition_ddddd==1'd1)|(CLK_SRC==1'd1))
		begin 
		frequency <=	(((CLK_SRC==1'd1)&(DAT_SRC==1'd1))|(state<=5'd4))?	frequency_set:	 
					 		((DAT_SRC==1'd0)&	(state>=5'd10))?  	result_A:  // tracking data transitions
							(((CLK_SRC==1'd0)&(DAT_SRC==1'd0))|(state<=5'd4))?	result_B :// tracking clock transitions
								frequency_set;		
		end

Add_32 add_a(
		.clk (clk),
		.rst ((rst==1'd1)|(state==5'd0)),
		.In_A (frequency_set),
		.In_B (freq_correction),
		.Rslt (result_A)
		);		
		
Add_32 add_b(
		.clk (clk),
		.rst ((rst==1'd1)|(state==5'd0)),
		.In_A (quotient),
		.In_B (freq_correction),
		.Rslt (result_B)
		);			

// generate pipeline delays as needed
always @ (posedge clk)
	if (rst==1'd1)
		begin
		clock_d <= 1'd0;
		clock_dd <= 1'd0;
		data_d <= 1'd0;
		data_dd <= 1'd0;
		initial_1 <= 1'd1;
		transition_1 <= 1'd0;
		transition_2 <= 1'd0;
		transition_2_d <= 1'd0;
		transition_d <= 1'd0;
		transition_dd <= 1'd0;
		transition_ddd <= 1'd0;
		transition_dddd <= 1'd0;
		transition_ddddd <= 1'd0;
		transition_dddddd <= 1'd0; 
		transition_ddddddd <= 1'd0; 
		transition_dddddddd <= 1'd0; 
		transition_ddddddddd <= 1'd0;
		transition_i_d <= 1'd0;
		transition_data_d <= 1'd0;
		transition_data_dd <= 1'd0;
		transition_data_ddd<= 1'd0; 
		transition_data_dddd<= 1'd0;
		transition_data_ddddd<= 1'd0;
		end
	else
		begin
		clock_d  <= clock;
		clock_dd <= clock_d;
		data_d   <= data;
		data_dd  <= data_d;
		initial_1 <= (state==5'd0)|(state==5'd1)|(state==5'd2);
		transition_1 <= ((clock_d==1'd1)&&(clock_dd==1'd0));
		transition_2 <= ((transition_d==1'd1)&&(state>5'd4));
		transition_2_d <= transition_2;
		transition_d <= transition;
		transition_dd <= transition_d;
		transition_ddd <= transition_dd;
		transition_dddd <= transition_ddd;
		transition_ddddd <= transition_dddd;
		transition_dddddd <= transition_ddddd; 
		transition_ddddddd <= transition_dddddd; 
		transition_dddddddd <= transition_ddddddd; 
		transition_ddddddddd <= transition_dddddddd;
		transition_i_d <= transition_i;
		transition_data_d <= transition_data;
		transition_data_dd <= transition_data_d;
		transition_data_ddd<= transition_data_dd; 
		transition_data_dddd<= transition_data_ddd;
		transition_data_ddddd<= transition_data_dddd;
		end


// input to phase tracking loop - active high for one clock cycle
assign transition = ((CLK_SRC==1'd1)&(DAT_SRC==1'd0))?	
									(((data_d==1'd1)&(data_dd==1'd0))|((data_d==1'd0)&(data_dd==1'd1))):
									(((clock_d==1'd1)&(clock_dd==1'd0)));
									
assign transition_data=(((data_d==1'd1)&&(data_dd==1'd0))|((data_d==1'd0)&&(data_dd==1'd1)));

// used only during initialization									
assign transition_i = (((clock_d==1'd1)&&(clock_dd==1'd0))) || (transition_data==1'd1);									



//*********************************************************
//*********************************************************
always @ (posedge clk)
	if (rst==1'd1)
		activity_count<=24'd0;
	else
		activity_count<=activity_count+24'd1;

always @ (posedge clk)
	if ((rst==1'd1)|(activity_count==24'hffffff))
	   activity_test<=1'd0;
	else if (transition_i==1'd1)
		activity_test<=1'd1;
		
always @ (posedge clk)
	if ((rst==1'd1)|(activity_count==24'hffffff))
	   clock_activity_test<=1'd0;
	else if ((clock_d==1'd1)&&(clock_dd==1'd0))
		clock_activity_test<=1'd1;
		
		
always @ (posedge clk)
	if (rst==1'd1)
	   activity<=1'd1;
	else if (activity_count==24'hffffff)	
		activity<=activity_test;
		
always @ (posedge clk)
	if (rst==1'd1)
	   clock_activity<=1'd1;
	else if (activity_count==24'hffffff)	
		clock_activity<=clock_activity_test;
			
		
		
		
		
		
		
		
		
//*********************************************************
//*********************************************************




//*************************************************************************************************************
//*************************************************************************************************************
// 			       State Machine which controls PLL loop acquisition
//*************************************************************************************************************
//*************************************************************************************************************


frequency_est_240 freq_est2(
	.rst (rst),
	.clk (clk_120),
	.transition (transition|transition_d),
	.transition_i (transition_i|transition_i_d),
	.transition_data ( transition_data_d | transition_data_dd ),
	.activity (activity),
	.clock_activity (clock_activity),
	.lock_err (lock_err), 
	.lock (lock),
	.outside_freq_range (outside_freq_range),
	.slow_clock (1'd1),
	.CLK_SRC (CLK_SRC),

	.quotient (quotient),
	.state (state),
	.data_trans_cnt (data_trans_cnt),
	.timer (timer), 
	.timer_d (timer_d),
	.timer_not_of (timer_not_of)
	);

//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************

	
	
always @ (posedge clk)	
	if (rst==1'd1)
		begin
		lock<=1'd0;
		end
	else
		begin
		lock<=(IIR[15:8]>8'd35);
		end
	


always @ (posedge clk)
	if (rst==1'd1)
		freq_delta<=32'd0;
	else
		case(state)
		(5'd7):	freq_delta<=({{10{scaled_phase[31]}}, scaled_phase[31:10]});
		(5'd8):	freq_delta<=({{14{scaled_phase[31]}}, scaled_phase[31:14]});
		(5'd11):	freq_delta<=({{10{scaled_phase[31]}}, scaled_phase[31:10]});
		(5'd12):	freq_delta<=({{14{scaled_phase[31]}}, scaled_phase[31:14]});
		default	freq_delta<=32'd0;
		endcase

ACCUM_32 accum(
	.clk (clk),
	.rst (rst),
	.en (transition_dddddddd),
	.state (state),
	.In_A (freq_delta),
	.Rslt (freq_accum)
	);
	
always @ (posedge clk)
	if (rst==1'd1)
		freq_delta_1<=32'd0;
	else 
		case(state)  // for frequency accumulation
		(5'd7):	freq_delta_1<=({{4{scaled_phase[31]}}, scaled_phase[31:4]});
		(5'd8):	freq_delta_1<=({{6{scaled_phase[31]}}, scaled_phase[31:6]});
		(5'd11):	freq_delta_1<=({{6{scaled_phase[31]}}, scaled_phase[31:6]});
		(5'd12):	freq_delta_1<=({{7{scaled_phase[31]}}, scaled_phase[31:7]});
		default	freq_delta_1<=32'd0;
		endcase	
	
Add_32 add_c(
		.clk (clk),
		.rst (rst),
		.In_A (freq_delta_1),
		.In_B (freq_accum),
		.Rslt (freq_correction)
		);			
	
	
	

assign steady_state = (state==5'd12)|(state==5'd8)|(activity==1'd0)|(CLK_SRC==1'd1);

//*******************************************************************************************
//						Lock Detect
//			reset the state machine if loss of lock is detected
//			or if the frequency goes beyond acceptable limits.
//*******************************************************************************************

always @ (posedge clk)
	if (rst==1'd1)
		abs_phase_err<=8'd0;
	else 
		abs_phase_err<=(phase_err[7]==1'd0)?phase_err:-phase_err;
		
assign testa= 	lock_err;//abs_phase_err>8'd20;	
		

always @ (posedge clk)
	if (rst==1'd1)
		begin
		IIR<=16'd0;
		IIR_temp<=16'd0;
		end
	else if (transition_2==1'd1)	
		IIR_temp<={8'd0,abs_phase_err}- {  8'd0 ,  IIR[15:8]   };
		
	else if (transition_2_d==1'd1)
		IIR<=IIR + IIR_temp;
		
always @ (posedge clk)
	if (rst==1'd1)		
		outside_freq_range<=1'd0;		
	else
		outside_freq_range<= ((frequency[31:16]> upper_limit)||(frequency[31:16]< lower_limit)); //***********************************
		
		
assign upper_limit=16'h4000;
assign lower_limit=16'd10;		

//*******************************************************************************************
//*******************************************************************************************

endmodule