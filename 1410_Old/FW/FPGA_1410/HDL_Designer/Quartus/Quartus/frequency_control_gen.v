module frequency_control_gen (
	clk,
	rst,
	clock_rate,
	restart,
	NCO,
	state_1, NCO_control, mult_count, bit_rate_shft, bit_rate_shft_rt
	);
	
	input clk;
	input rst;
	input restart;
	input [15:0] clock_rate;   // in units of 1KHz
	output [31:0] NCO;
	output [4:0] state_1;
	output [45:0] NCO_control;
	output [4:0] mult_count;
	output [45:0] bit_rate_shft;
	output [15:0] bit_rate_shft_rt;
	
	
	wire [29:0] one_Khertz;
	reg [4:0] state_1;
	reg [45:0] NCO_control;
	reg [4:0] mult_count;
	reg [45:0] bit_rate_shft;
	reg [15:0] bit_rate_shft_rt;
	
//********************************************************************************************************
//*******************   Convert input in Bits per Second to NCO control word *****************************
//********************************************************************************************************

assign one_Khertz=  30'h1179ec9c;  // (2^46)*(1000/240Mhz)


// Compute NCO_control_s=round((2^46)*(bit_rate/160))
always @ (posedge clk)
	if ((restart==1'd1)|(rst==1'd1))
		begin
		state_1<=5'd0;
		NCO_control<=46'd0;
		mult_count<=5'd0;
		bit_rate_shft<={16'd0,one_Khertz};  //[45:0]
		bit_rate_shft_rt<=clock_rate;
		end
	else
	case(state_1)	
	(5'd0):	begin
			state_1<=5'd1;
			NCO_control<=NCO_control+({46{bit_rate_shft_rt[0]}}& bit_rate_shft);  //  [45:0]
			mult_count<=mult_count+5'd1;
			end
	(5'd1):	begin
			state_1<=(mult_count==5'd16)?5'd2:5'd0;
			bit_rate_shft_rt<={1'd0,bit_rate_shft_rt[15:1]};   //  [24:0]
			bit_rate_shft<={bit_rate_shft[43:0],1'd0};
			end
	(5'd2): state_1<=5'd3;
	(5'd3): state_1<=5'd3;
	endcase		
//

assign NCO= NCO_control[45:14];


	endmodule
	