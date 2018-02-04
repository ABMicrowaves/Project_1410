
//  Top Level module for BA Microwave Transmitter

//  Cresated by Mike Paff 					Delivered on April 6, 2012


module Clock_240_tx (
	inclk0,  //10 MHz reference
	
	// SPI from PIC for configuring registers.
	// --------------------------------------
	SPI_clk, // serial interface clock
	SPI_DI,	 // serial interface data in
	SPI_DO,  // serial interface data out
	SPI_CS,	 // serial interface active low select

	Bit_clock,  // external data clock in
	Bit_data,	  // external data in

	I,		//  inphase output
	Q,		// quadrature output
	
	TP3,
	TP4,
	TP5,
	TP6,
	
	LED1,  // LED driver 1
	LED2,		// LED driver 2
	LED3,		// LED driver 3
	LED4,		// LED driver 4
	
	DAC_clk_p,  // 240 MHz clock to DAC  positive
	DAC_clk_m,  // 240 MHz clock to DAC  negative

	test 
	);
	
	
input inclk0;
input SPI_clk;
input SPI_DI;
inout SPI_DO;
input SPI_CS;

input Bit_clock;
input Bit_data;


output [13:0] I,Q;
output 	TP3, TP4, TP5, TP6;
output DAC_clk_p, DAC_clk_m;
output  LED1, LED2, LED3, LED4;

output test;


wire [31:0] FB_RATE;
wire [31:0] bit_rate;
reg [13:0] I,Q; // @@@@@@@@@ Haim @@@@@@ There are I and Q also outputs, and here they are internal registers ?
wire [13:0] I_p , Q_p ;
wire [3:0] mode;
wire clk;
wire rst, rst_n;
wire [7:0] phase_offset;
wire CLK_POL;
wire RAND;
wire DAC_clk_p, DAC_clk_m, DAC_clk, DAC_clk_n; // @@@@@@ Haim @@@@ DAC_clk_p and DAC_clk_m are also outputs
wire [4:0] REV;
wire steady_state;
wire test_clk;
wire Bit_data, Bit_clock ; // @@@@@@@ Haim @@@@ those are also inputs
wire 	TP3, TP4, TP5, TP6;
wire CLK_SRC, DAT_SRC, DAT_POL;
wire [3:0] DAT_PAT;
wire internal_data;
wire [31:0] sym_phase;
wire sym_phase_of_d;

wire [6:0] addr_d, addr;
wire [4:0] pll_state;
wire transition_i, clock_d, data_d;
wire SDO_r;
wire true_random;
wire [13:0]  phase_modulation, roll_total_ddd, phase_test;
wire [16:0] shift_tst;
wire [15:0] IIR;
wire outside_freq_range;
wire clk_120;
wire [2:0] sym_count_dd;
wire [13:0] ph_roll_0, ph_roll_1, ph_roll_2, ph_roll_3, ph_roll_4, ph_roll_5, ph_roll_6, ph_roll_7;
wire [31:0] quotient, quotient_1;
wire LED1, LED2, LED3, LED4;
reg [27:0] timer;
wire test;
reg [14:0] shift;
wire testa;
wire Diff_en;
wire [8:0] data_trans_cnt;

always @ (posedge clk)
	if (rst==1'd1)
		timer<=28'd0;
	else
		timer<=timer+28'd1;

assign rst_n= (shift!=16'hfffe);
assign REV=5'd1;
assign TP5=rst;
assign TP4=rst;
assign TP3=rst;

assign LED1=timer[27];
assign LED2=timer[27];
assign LED3=timer[27];
assign LED4=timer[27];


assign test=internal_data;


always @ (posedge clk)
	if (rst==1'd1)
	begin
			I<=14'd0;
			Q<=14'd0;
		end
	else 
		begin
			I<={I_p};
			Q<={Q_p};
		end



	
ARTM_tx_240  transmitter(
	.inclk0  (inclk0),  	  // crystal reference oscillator
	.data_in  (Bit_data),  	  //  data to be modulated 
	.data_clock  (Bit_clock),   // synchronous with data transitions
	.mode  (mode),  		  // 000 = FM/PCM, 001 = SOQPSK, 010 = CPM, 100 = carrier only
	.phase_offset  (phase_offset), // used for adjacent sideband suppression in IQ modulator
	.bit_rate  (bit_rate),  	  // requried when data clock is not present
	.rst_n  (rst_n),      //   active low reset input 
	.PB_nBB  (1'd0),      //   passband or not baseband  (passband enabled for Altera eval board)
	.CLK_POL  (CLK_POL),	 //   set clock polarity
	.DAT_POL (DAT_POL),
	.RAND  (RAND),			 //   enable randomizer
	.CLK_SRC (CLK_SRC),   //  0 selects external clock, 1 selects internal clock
	.DAT_SRC (DAT_SRC),   //  0 selects external data, 1 selects internal data
	.internal_data (internal_data),
	.Diff_en (Diff_en),
	
	
	.clk  (clk),
	.rst (rst),
	.DAC_clk   (DAC_clk_p),
	.DAC_clk_n (DAC_clk_m),
	.clk_120 (clk_120),
	.sine  (Q_p),
	.cosine  (I_p),  		// baseband output needed for IQ modulator
	.bit_clock  (TP6),   //  approximately a square wave
	.FB_RATE  (FB_RATE),	// reported bit rate	
	.steady_state (steady_state),
	.pll_state (pll_state),
	.transition_i (transition_i),
	.data_d (data_d), 
	.clock_d (clock_d),
	.true_random (true_random),
	.outside_freq_range (outside_freq_range),
	.sym_phase (sym_phase),
	.phase_modulation (phase_modulation),
	.IIR (IIR),
	.roll_total_ddd (roll_total_ddd),
	.phase_test (phase_test),
	.phase_0 (phase_0), 
	.phase_1 (phase_1), 
	.phase_2 (phase_2), 
	.phase_3 (phase_3),
	.phase_4 (phase_4), 
	.phase_5 (phase_5), 
	.phase_6 (phase_6), 
	.phase_7 (phase_7),
	.ph_roll_0 (ph_roll_0), 
	.ph_roll_1 (ph_roll_1), 
	.ph_roll_2 (ph_roll_2), 
	.ph_roll_3 (ph_roll_3), 
	.ph_roll_4 (ph_roll_4), 
	.ph_roll_5 (ph_roll_5), 
	.ph_roll_6 (ph_roll_6), 
	.ph_roll_7 (ph_roll_7),
	.phase_fm_rr (phase_fm_rr),
	.phase_fm_r (phase_fm_r),
	.lookup_rslt_4 (lookup_rslt_4),
	.SOQPSK_lookup_4 (SOQPSK_lookup_4),
	.sym_count_dd (sym_count_dd),
	.sym_phase_of_d (sym_phase_of_d),
	.sym_phase_of_dd (sym_phase_of_dd),
	.phase_total_d1 (phase_total_d1), 
	.phase_total_d2 (phase_total_d2),
	.flip_ddd (flip_ddd),
	.phase_fm_0 (phase_fm_0), 
	.phase_fm_1 (phase_fm_1),
	.fm_phase_of (fm_phase_of),
	.fm_phase_lu_0 (fm_phase_lu_0),
	.alpha_fm_0_dd (alpha_fm_0_dd),
	.FM_lookup_addr_0 (FM_lookup_addr_0),
	.FM_lookup_addr_1 (FM_lookup_addr_1),
	.quotient (quotient), 
	.quotient_1 (quotient_1),
	.testa (testa),
	.data_trans_cnt (data_trans_cnt),
	.phase_err (phase_err)
	);
	
Internal_Data_Gen internal(
	.clk (clk_120),
	.rst (rst),
	.data_clock (!sym_phase[31]),
	.DAT_PAT (DAT_PAT),
	.internal_data (internal_data),
	.shift (shift_tst)
	);


always @(posedge clk)
 if (shift==15'd0)
	shift=15'h5aaa;
else if (shift!=15'h1110)
	shift<=(shift!=15'h7fff)?(shift+15'd1):shift;



serial_IFC  SPI(
	.clk (clk_120),
	.rst (rst==1'd1),
	.CSB (SPI_CS),
	.SCLK (SPI_clk),
	.SDI (SPI_DI),
	.SDO (SPI_DO),
	.PLL_lock (steady_state),
	.REV (REV),
	.FB_R ({FB_RATE[31:0]}),
	
	.bit_rate (bit_rate),  	  		// requried when data clock is not present
	.CLK_SRC (CLK_SRC),
	.DAT_SRC (DAT_SRC), 
	.DAT_PAT (DAT_PAT),
	.mode (mode),  		  			// 000 = FM/PCM, 001 = SOQPSK,  110 = test, 100 = carrier only
	.phase_offset (phase_offset), // used for adjacent sideband suppression in IQ modulator
	.CLK_POL (CLK_POL),				// set clock polarity
	.RAND (RAND),
	.addr_d (addr_d),
	.SDO_r (SDO_r),
	.DAT_POL (DAT_POL),
	.Diff_en (Diff_en),
	.addr (addr),
	.bit_cnt_wr (bit_cnt_wr)
	);
	
endmodule	