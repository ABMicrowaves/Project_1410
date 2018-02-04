module frequency_translate_cyclone_2 (
	clk,
	rst,
	real_in,
	imag_in,
	frequency_mod,
	frequency,
	frequency_en,
	real_rslt,
	sine,
	cosine
	);
	
input clk;
input rst;
input [13:0] real_in;
input [13:0] imag_in;
input [31:0] frequency;
input frequency_en;
input [13:0] frequency_mod;
output [13:0] real_rslt;
output [13:0] sine,cosine;

reg [31:0] phase_accum;
reg [31:0] frequency_r;
reg [13:0] phase_ms_d, phase_ms_dd, phase_ms_ddd, phase_ms_dddd;
reg [13:0] sine, cosine ;

wire[12:0] sin_rom_rslt, cos_rom_rslt;
wire [13:0] real_in;
wire [13:0] imag_in;
wire [15:0] product1,product2;
wire [15:0] product_real_p;
reg [13:0] real_rslt;
reg [13:0] sin_rom_plus, sin_rom_minus, cos_rom_plus, cos_rom_minus;

always @ (posedge clk)
	if (rst==1'd1)
		frequency_r<=32'd0;
	else if (frequency_en==1'd1)
		frequency_r<=frequency;	


always @ (posedge clk)
	if (rst==1'd1)
		begin
		phase_accum<=32'd0;
		phase_ms_d<=14'd0;
		phase_ms_dd<=14'd0;
		phase_ms_ddd<=14'd0;
		phase_ms_dddd<=14'd0;
		end
	else	
		begin
		phase_accum<=phase_accum-frequency_r;
		phase_ms_d<=phase_accum[31:18]+{frequency_mod};
		phase_ms_dd<=phase_ms_d;
		phase_ms_ddd<=phase_ms_dd;
		phase_ms_dddd<=phase_ms_ddd;
		end

COS_ROM_2_cy	cos_rom(
		.address (phase_ms_d[11:0]),
		.clock (clk),
		.q (cos_rom_rslt)  //12:0
		);

SIN_ROM_2_cy	sin_rom(
		.address (phase_ms_d[11:0]),
		.clock (clk),
		.q (sin_rom_rslt)  //    [12:0]
		);
		
always @ (posedge clk)
	if (rst==1'd1)
		begin
			sin_rom_plus<=14'd0;
			sin_rom_minus<=14'd0; 
			cos_rom_plus<=14'd0; 
			cos_rom_minus<=14'd0;	
		end	
	else
		begin
			sin_rom_plus<=  {1'd0, 	sin_rom_rslt};
			sin_rom_minus<=-{1'd0, 	sin_rom_rslt};
			cos_rom_plus<=  {1'd0, 	cos_rom_rslt}; 
			cos_rom_minus<=-{1'd0, 	cos_rom_rslt};
		end	
		
		

always @ (posedge clk)
	if (rst==1'd1)
		begin
		sine<=14'd0;
		cosine<=14'd0;
		end
	else
		case (phase_ms_dddd[13:12])
		2'd0: begin   	sine   <=  sin_rom_plus;
						   cosine <=  cos_rom_plus; end
		2'd1: begin  	sine   <=  cos_rom_plus;
						   cosine <=  sin_rom_minus; end
		2'd2: begin   	sine   <=  sin_rom_minus;
						   cosine <=  cos_rom_minus; end
		2'd3: begin   	sine   <=  cos_rom_minus;
						   cosine <=  sin_rom_plus; end
		endcase			




multiplier_1_st cos_mult(
	.clock (clk),
	.dataa  (cosine), 	//11:0
	.datab  (real_in), 	//13:0
	.result  (product1)  //15:0
	);
	
	
multiplier_1_st sin_mult(
	.clock (clk),
	.dataa  (sine), 		//11:0
	.datab  (imag_in), 	//13:0
	.result  (product2)  //15:0
	);
	
assign product_real_p= {product1[15],product1[15:1]}-{product2[15],product2[15:1]};

always @ (posedge clk)
	 real_rslt<= (product_real_p[13]==product_real_p[14])?product_real_p[13:0]:
	  (product_real_p[15]==1'd0)?14'b01111111111111:14'b10000000000000;





endmodule