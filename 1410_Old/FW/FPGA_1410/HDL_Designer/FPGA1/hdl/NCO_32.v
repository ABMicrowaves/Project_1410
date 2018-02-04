module NCO_32 (
	clk,
	rst,
	In_A,

	Rslt, Rslt_p, temp_1,temp_2,
	sym_phase_of
	);
	
input [31:0] 	In_A;
input  clk, rst;
output [31:0] Rslt;
output [32:0] Rslt_p;
output [16:0] temp_1,temp_2;
output sym_phase_of;

reg [32:0] Rslt_pp, Rslt_p;
reg [16:0] temp_1;
reg [16:0] temp_2;
reg Rslt_p_32_d;
wire sym_phase_of;

always @ (posedge clk)
	if (rst==1'd1)
		begin
		temp_1<=17'd0;
		temp_2<=17'd0;
		Rslt_p<=32'd0;
		Rslt_pp<=32'd0;
		Rslt_p_32_d<=1'd0;
		end
	else
		begin
		temp_1<={1'd0,In_A[15:0]}  + {1'd0,temp_1[15:0]};
		temp_2<={1'd0,In_A[31:16]} + {1'd0,temp_2[15:0]};
		
		Rslt_p[15:0]<=temp_1[15:0];
		Rslt_p[32:16]<= temp_2 +{16'd0, temp_1[16]};
		Rslt_p_32_d<=Rslt_p[32];
		Rslt_pp<=Rslt_p;
		end

	assign sym_phase_of=Rslt_p[32]&(Rslt_p_32_d==1'd0);	
	assign Rslt= Rslt_pp[31:0];
	

endmodule