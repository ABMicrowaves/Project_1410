module RNRZ_L  (
	clk,
	rst,
	data_in,
	data_clk,
	mode_15_n11,
	TX_nRX,
	BER_test,
	data_out
	
	);
	
input clk;
input rst;
input data_in;
input data_clk;
input mode_15_n11;
input TX_nRX;
input BER_test;	// a one enables BER test mode (assumes all zeros at TX in RNRZ mode)
				// only meaningful in receiver
output data_out;

reg data_clk_d;
wire data_en;
reg [14:0]  shift_reg;
reg data_out;
wire shift_in;
reg [2:0] state;
reg [3:0] zero_cnt;
reg [7:0] top_cnt;
reg [3:0] total_cnt;
wire shift_in_rx;


always @ (posedge clk)
	if (rst==1'd1)
	data_clk_d<=1'd0;
	else
	data_clk_d<=data_clk;


assign data_en = (data_clk==1'd1)&&(data_clk_d==1'd0);

always @ (posedge clk)
	if (rst==1'd1)
	shift_reg<=15'b100011001011101;
	else if (data_en==1'd1)
	shift_reg<={shift_in, shift_reg[14:1]};

assign shift_in=(TX_nRX==1'd1)?((data_in==1'd1)^(shift_reg[0]==1'd1)^(shift_reg[1]==1'd1)):
				shift_in_rx;


assign shift_in_rx =(state==3'd0)?(data_in==1'd1):((shift_reg[0]==1'd1)^(shift_reg[1]==1'd1));

always @ (posedge clk)
	if (rst==1'd1)
		data_out<=1'd0;
	else if (data_en==1'd1)
		data_out<=((data_in==1'd1)^(shift_reg[0]==1'd1)^(shift_reg[1]==1'd1));

always @ (posedge clk)
	if (rst==1'd1)
		zero_cnt<=4'd0;
	else if (data_en==1'd1)
		zero_cnt<=(data_out==1'd1)?4'd0:
			(zero_cnt!=4'd15)?(zero_cnt+4'd1):zero_cnt;
		
		
always @ (posedge clk)
	if (rst==1'd1)
		begin
		state<=3'd0;
		top_cnt<=8'd1;
		total_cnt<=4'd0;
		end
	else
	case (state)	
	(3'd0):  	begin
				state<=((BER_test==1'd1)&(TX_nRX==1'd0)&(zero_cnt==4'd15)&(data_en==1'd1))?3'd1:3'd0;
				top_cnt<=8'd1;
				end
				
	(3'd1):	 	state<=(data_en==1'd1)?3'd1:
					(top_cnt==8'd0)?3'd0:3'd2;
					
	(3'd2):  	begin
				state<=(data_en==1'd0)?3'd2:(total_cnt==4'd15)?3'd2:3'd3;
				total_cnt<=(data_en==1'd0)?total_cnt:(total_cnt+4'd1);
				end
	(3'd3):  	begin	
				state<=3'd1;
				top_cnt<= ((zero_cnt==4'd15)&(top_cnt!=8'd255))? (top_cnt+8'd1):
				(top_cnt!=8'd0)?(top_cnt-8'd1):top_cnt;
				end

	endcase
		
		

endmodule
