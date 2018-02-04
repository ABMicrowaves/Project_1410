module Internal_Data_Gen (
	clk,
	rst,
	data_clock, // selected clock
	DAT_PAT,  //  select an internal data pattern
	internal_data,  
	shift// test signal
	);
	
	
input clk;
input rst;
input data_clock;
input[3:0] DAT_PAT;

output internal_data;
output [16:0] shift;
	
	
	reg data_clock_d, internal_data;
	reg [16:0] shift;
	
	always @ (posedge clk)
		if (rst==1'd1)
			begin
			data_clock_d<=1'd0;
			end
		else	
			begin
			data_clock_d<=data_clock;
			end
			
	always @ (posedge clk)
		if ((rst==1'd1)|(shift==17'd0))
			begin
			shift<= {1'd1,16'haa00};
			internal_data<=1'd0;
			end
		else if ((data_clock==1'd1)&(data_clock_d==1'd0))	
		case (DAT_PAT)
		(4'd0):	internal_data<=1'd0;
		(4'd1):	internal_data<=1'd1;
		(4'd2):	begin
					internal_data<=shift[16];
					shift<={(shift[2]^shift[3]), shift[16:3], 2'd0};
					end
		(4'd3):	begin
					internal_data<=shift[16];
					shift<={(shift[0]^shift[3]), shift[16:1]};
					end
					
		default	begin
					internal_data<=shift[16];
					shift<={(shift[2]^shift[3]), shift[16:3],2'd0};
					end
		endcase
	
endmodule
