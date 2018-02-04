module ACCUM_32 (
	clk,
	rst,
	en,
	state,
	In_A,

	Rslt
	);
	
input [31:0] 	In_A;
input  clk, rst, en;
input [4:0] state;
output [31:0] Rslt;


reg [31:0] Rslt;
reg [16:0] temp_1;
reg [15:0] temp_2;
reg en_d;
reg state_0;


always @ (posedge clk)
	if (rst==1'd1)
		begin
		en_d<=1'd0;
		state_0<=1'd0;
		end
	else
		begin
		en_d<=en;
		state_0<=(state==5'd0);
		end


always @ (posedge clk)
	if ((rst==1'd1)|(state_0==1'd1))
		begin
		temp_1<=17'd0;
		temp_2<=16'd0;
		Rslt<=32'd0;
		end
	else if (en==1'd1)
		begin
		temp_1<={1'd0,In_A[15:0]}+{1'd0,temp_1[15:0]};
		temp_2<=In_A[31:16];
		end
		
	else if (en_d==1'd1)	
		begin
		Rslt[15:0]<=temp_1[15:0];
		Rslt[31:16]<= temp_2+Rslt[31:16]+ {15'd0, temp_1[16]};
		end
		
	

endmodule