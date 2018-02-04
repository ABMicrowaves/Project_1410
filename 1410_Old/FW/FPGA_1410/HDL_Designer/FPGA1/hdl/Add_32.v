module Add_32 (
	clk,
	rst,
	In_A,
	In_B,
	Rslt
	);
	
input [31:0] 	In_A, In_B;
input  clk, rst;
output [31:0] Rslt;

reg [31:0] Rslt;
reg [16:0] temp_1;
reg [15:0] temp_2, temp_3;

always @ (posedge clk)
	if (rst==1'd1)
		begin
		temp_1<=17'd0;
		temp_2<=16'd0;
		temp_3<=16'd0;
		Rslt<=32'd0;
		end
	else
		begin
		temp_1<={1'd0,In_A[15:0]}+{1'd0,In_B[15:0]};
		temp_2<=In_A[31:16];
		temp_3<=In_B[31:16];
		Rslt[15:0]<=temp_1[15:0];
		Rslt[31:16]<= temp_2+temp_3+ {15'd0, temp_1[16]};
		end
	
	

endmodule