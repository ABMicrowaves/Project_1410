module serial_IFC  (
	clk,
	rst,
	CSB,
	SCLK,
	SDI,
	SDO,
	PLL_lock,
	REV,
	FB_R,
	
	mode,  		  // 0000 = FM/PCM, 0001 = SOQPSK,  0100 = carrier only
	phase_offset, // used for adjacent sideband suppression in IQ modulator
	bit_rate,  	  // requried when data clock is not present
	CLK_POL,		  // set clock polarity
	DAT_POL, 	  // set data polarity
	RAND,			  // enable randomization
	addr_vld,
	word_cnt,
	num_bytes,
	addr, 
	addr_d,
	bit_cnt,
	bit_cnt_wr,
	addr_wr_en,
	data_wr_en, 
	data_wr_en_d, 
	rx_data, 
	rd_nwr,
	SDO_r,
	CLK_SRC, DAT_SRC, DAT_PAT, Diff_en, shift, addr_incr_en, addr_incr
	);
	
input clk;
input rst;
input CSB;
input SCLK;
input SDI;
inout SDO;	
input PLL_lock;
input [4:0] REV;
input [31:0] FB_R;

output [3:0] mode;
output [7:0] phase_offset;
output [31:0] bit_rate;
output CLK_POL;
output RAND;
output addr_vld;
output [1:0] num_bytes;
output [5:0] word_cnt;
output [6:0] addr_d;
output [6:0]  addr;
output rd_nwr;
output [2:0] bit_cnt, bit_cnt_wr;
output addr_wr_en, data_wr_en, data_wr_en_d;
output [7:0] rx_data;
output SDO_r;
output CLK_SRC, DAT_SRC, DAT_POL;
output [3:0] DAT_PAT;
output Diff_en;
output [7:0] shift;
output addr_incr_en, addr_incr;



wire rst;
reg CSB_d, CSB_dd,CSB_ddd, SCLK_d, SCLK_dd, SCLK_ddd;
reg [7:0] shift;
reg [2:0] bit_cnt, bit_cnt_wr;
reg [5:0] word_cnt;
reg [6:0] addr_d;
reg [6:0] addr;
reg rd_nwr;
reg [1:0] num_bytes;
reg [3:0] mode;
reg [7:0] phase_offset;
reg [31:0] bit_rate;
reg CLK_POL;
reg RAND;
reg addr_vld;
reg  SDO_r;	
reg [7:0] rx_data;
reg addr_wr_en, data_wr_en, addr_wr_en_d, data_wr_en_d, addr_incr, addr_incr_en, start_incr;
reg restart;
reg serial_tx_en;
reg [31:0] FB_R_r;
reg CLK_SRC, DAT_SRC, DAT_POL;
reg [3:0] DAT_PAT;
reg [7:0] clk_count;
reg rst_b;
reg Diff_en;

always @(posedge clk)
	begin
	clk_count<=(clk_count!=8'hfe)?(clk_count+8'd1):clk_count;
	rst_b<=rst;//(clk_count==8'hfd);
	end
	


always @ (posedge clk)
	if (rst==1'd1)
		begin
		CSB_d<=1'd0;
		CSB_dd<=1'd0;
		CSB_ddd<=1'd0;
		SCLK_d<=1'd0; 
		SCLK_dd<=1'd0;
		SCLK_ddd<=1'd0;
		addr_wr_en_d<=1'd0; 
		data_wr_en_d<=1'd0;
		addr_d<=7'd0;
		start_incr<=1'd0;
		end
	else
		begin
		CSB_d <= CSB;
		CSB_dd <= CSB_d;
		CSB_ddd <= CSB_dd;
		SCLK_d <= SCLK; 
		SCLK_dd <= SCLK_d;
		SCLK_ddd <= SCLK_dd;
		addr_wr_en_d<=addr_wr_en; 
		data_wr_en_d<=data_wr_en;
		addr_d<=addr;
		start_incr<=((bit_cnt_wr==3'd7)&(word_cnt!=6'd0)&(word_cnt!=6'd1));
		end

always @ (posedge clk)
	if ((rst==1'd1)||((CSB_d==1'd0)&&(CSB_dd==1'd1)))
		begin
		shift<=8'd0;
		bit_cnt<=3'd0;
		bit_cnt_wr<=3'd0;
		rd_nwr<=1'd0;
		word_cnt<=6'd0;
		addr_vld<=1'd0;
		num_bytes<=2'd0;
		rx_data<=8'd0;
		addr_wr_en<=1'd0; 
		data_wr_en<=1'd0; 
		end
	else if ((CSB_d==1'd0)&&(CSB_dd==1'd0)&&(SCLK_d==1'd1)&&(SCLK_dd==1'd0))
		begin
		shift<={shift[6:0],SDI};
		bit_cnt<=bit_cnt+3'd1;
		word_cnt<= ((bit_cnt==3'd7)&(word_cnt!=6'd63))?(word_cnt+6'd1):word_cnt;
		addr_wr_en<=((bit_cnt==3'd7)&(word_cnt==6'd0)); 
		data_wr_en<=((bit_cnt==3'd7)&(word_cnt!=6'd0)); 
		addr_vld <=((bit_cnt==3'd7)&(word_cnt==6'd0))?(rd_nwr==(num_bytes[1]^num_bytes[0]^addr[4]^addr[3]^addr[2]^addr[1]^addr[0])):addr_vld;
		end
	else if ((CSB_dd==1'd0)&&(CSB_ddd==1'd0)&&(SCLK_dd==1'd1)&&(SCLK_ddd==1'd0))	
		begin
		rd_nwr <= (addr_wr_en==1'd1)?shift[7]:rd_nwr;
		num_bytes <=(addr_wr_en==1'd1)?shift[6:5]:num_bytes;
		rx_data<=(data_wr_en==1'd1)?shift[7:0]:rx_data;
		addr_wr_en<=1'd0; 
		data_wr_en<=1'd0; 
		end
	else if ((CSB_d==1'd0)&&(CSB_dd==1'd0)&&(SCLK_d==1'd0)&&(SCLK_dd==1'd1))
		begin
		bit_cnt_wr<=bit_cnt_wr+3'd1;
		end	
		
always @ (posedge clk)
	if ((rst==1'd1)||((CSB_d==1'd0)&&(CSB_dd==1'd1)))		
		addr_incr	<=1'd0;	
	else if ((CSB_d==1'd0)&&(CSB_dd==1'd0)&&(SCLK_d==1'd0)&&(SCLK_dd==1'd1))
		addr_incr	<= addr_incr_en;
	else 
		addr_incr	<= 1'd0;
		
		
always @ (posedge clk)
	if ((rst==1'd1)||((CSB_d==1'd0)&&(CSB_dd==1'd1)))		
		addr<=7'd0;
	else if (addr_wr_en==1'd1)
		addr<=shift[6:0];	
	else if (addr_incr==1'd1)			
		addr<= (addr+7'd1);
		
always @ (posedge clk)
	if ((rst==1'd1)||((CSB_d==1'd0)&&(CSB_dd==1'd1)))		
		addr_incr_en<=1'd0;
	else if	(((bit_cnt_wr==3'd7)&(word_cnt!=6'd0)&(word_cnt!=6'd1))&(start_incr==1'd0))
		addr_incr_en<=1'd1;
	else if (addr_incr==1'd1)	
		addr_incr_en<=1'd0;

always @ (posedge clk)
	if (rst==1'd1)
		begin
		mode<=4'd0;
		phase_offset<=8'd0;
		bit_rate<=32'h11000000;
		CLK_POL<=1'd0;
		RAND<=1'd0;
		CLK_SRC<= 1'd1;
		DAT_SRC<= 1'd1;
		DAT_POL<= 1'd0;
		DAT_PAT<= 4'd2;
		Diff_en<= 1'd1;
		end
	else if (data_wr_en_d==1'd1)   	
	case (addr_d)
	(7'd0):	begin
			mode    <= rx_data[3:0];
			CLK_POL <= rx_data[4];
			DAT_POL <= rx_data[5];
			RAND    <= rx_data[6];
			Diff_en <= rx_data[7];
			end
	(7'd1):	phase_offset    <=	rx_data;	
	(7'd2):	bit_rate[7:0]   <=	rx_data;	
	(7'd3):	bit_rate[15:8]  <=	rx_data;	
	(7'd4):	bit_rate[23:16] <=	rx_data;	
	(7'd5):	bit_rate[31:24] <=	{2'd0,rx_data[5:0]};	
	(7'd6):  begin
				CLK_SRC<= rx_data[0];
				DAT_SRC<= rx_data[1];
				DAT_PAT<= rx_data[5:2]; 
				end
					
	
	default 
			begin
			mode <= mode;
			CLK_POL <= CLK_POL;
			DAT_POL  <= DAT_POL;
			RAND <= RAND;
			phase_offset <= phase_offset;
			bit_rate <= bit_rate;
			CLK_SRC  <= CLK_SRC;
			DAT_SRC  <= DAT_SRC;
			DAT_PAT  <= DAT_PAT;
			end 
	endcase	
	
//*************************************************************************	
always @ (posedge clk)
	if (rst==1'd1)
		restart <= 1'd0;
	else	
	   restart <= ((addr_d==7'd40)|(addr_d==7'd41))&(data_wr_en_d==1'd1);

	
//*************************************************************************		
always @ (posedge clk)
	if (rst==1'd1)
		FB_R_r<=32'd0;
	else if ((addr_wr_en_d==1'd1)&(addr==7'd17))
		FB_R_r<=FB_R;
	
always @ (posedge clk)	
	if (rst==1'd1)
		SDO_r<=1'd1;
	else if ((CSB_d==1'd0)&(CSB_dd==1'd0))
	case({addr_d, bit_cnt_wr})	
	({7'd16, 3'd0}):		SDO_r<=1'd0;
	({7'd16, 3'd1}):		SDO_r<=1'd0;
	({7'd16, 3'd2}):		SDO_r<=REV[4];
	({7'd16, 3'd3}):		SDO_r<=REV[3];
	({7'd16, 3'd4}):		SDO_r<=REV[2];
	({7'd16, 3'd5}):    	SDO_r<=REV[1];
	({7'd16, 3'd6}):		SDO_r<=REV[0];
	({7'd16, 3'd7}):		SDO_r<=PLL_lock;
	({7'd17, 3'd0}):		SDO_r<=FB_R_r[7];
	({7'd17, 3'd1}):		SDO_r<=FB_R_r[6];
	({7'd17, 3'd2}):		SDO_r<=FB_R_r[5];
	({7'd17, 3'd3}):		SDO_r<=FB_R_r[4];
	({7'd17, 3'd4}):		SDO_r<=FB_R_r[3];
	({7'd17, 3'd5}):		SDO_r<=FB_R_r[2];
	({7'd17, 3'd6}):		SDO_r<=FB_R_r[1];
	({7'd17, 3'd7}):		SDO_r<=FB_R_r[0];
	({7'd18, 3'd0}):		SDO_r<=FB_R_r[15];
	({7'd18, 3'd1}):		SDO_r<=FB_R_r[14];
	({7'd18, 3'd2}):		SDO_r<=FB_R_r[13];
	({7'd18, 3'd3}):		SDO_r<=FB_R_r[12];
	({7'd18, 3'd4}):		SDO_r<=FB_R_r[11];
	({7'd18, 3'd5}):		SDO_r<=FB_R_r[10];
	({7'd18, 3'd6}):		SDO_r<=FB_R_r[9];
	({7'd18, 3'd7}):		SDO_r<=FB_R_r[8];
	({7'd19, 3'd0}):		SDO_r<=FB_R_r[23];
	({7'd19, 3'd1}):		SDO_r<=FB_R_r[22];
	({7'd19, 3'd2}):		SDO_r<=FB_R_r[21];
	({7'd19, 3'd3}):		SDO_r<=FB_R_r[20];
	({7'd19, 3'd4}):		SDO_r<=FB_R_r[19];
	({7'd19, 3'd5}):		SDO_r<=FB_R_r[18];
	({7'd19, 3'd6}):		SDO_r<=FB_R_r[17];
	({7'd19, 3'd7}):		SDO_r<=FB_R_r[16];
	({7'd20, 3'd0}):		SDO_r<=FB_R_r[31];
	({7'd20, 3'd1}):		SDO_r<=FB_R_r[30];
	({7'd20, 3'd2}):		SDO_r<=FB_R_r[29];
	({7'd20, 3'd3}):		SDO_r<=FB_R_r[28];
	({7'd20, 3'd4}):		SDO_r<=FB_R_r[27];
	({7'd20, 3'd5}):		SDO_r<=FB_R_r[26];
	({7'd20, 3'd6}):		SDO_r<=FB_R_r[25];
	({7'd21, 3'd7}):		SDO_r<=FB_R_r[24];
	({7'd21, 3'd0}):		SDO_r<=1'd0;
	({7'd21, 3'd1}):		SDO_r<=1'd0;
	({7'd21, 3'd2}):		SDO_r<=DAT_PAT[3];
	({7'd21, 3'd3}):		SDO_r<=DAT_PAT[2];
	({7'd21, 3'd4}):		SDO_r<=DAT_PAT[1];
	({7'd21, 3'd5}):		SDO_r<=DAT_PAT[0];
	({7'd21, 3'd6}):		SDO_r<=DAT_SRC;
	({7'd21, 3'd7}):		SDO_r<=CLK_SRC;
	default					SDO_r<=1'd1;
	endcase
	
always @ (posedge clk)
	if (rst==1'd1)
	   serial_tx_en<=1'd0;
	else if (addr_wr_en==1'd1)
	   serial_tx_en<=1'd1;
	else if (CSB==1'd1)
		serial_tx_en<=1'd0;
	
	assign SDO= ((CSB==1'd0)&(serial_tx_en==1'd1)&((addr==7'd16)|(addr==7'd17)|(addr==7'd18)|
				(addr==7'd19)|(addr==7'd20)|(addr==7'd21)))?(SDO_r==1'd1):1'dz;	//

endmodule
