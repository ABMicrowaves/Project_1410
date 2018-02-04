module frequency_est_240 (
	rst,
	clk,
	transition,
	transition_i,
	transition_data,
	activity,
	clock_activity,
	lock_err,
	outside_freq_range,
	lock,
	slow_clock,
	CLK_SRC,
	quotient,
	state,
	data_trans_cnt,
	timer, 
	timer_d,
	timer_not_of
	);

	
input clk;
input rst;
input transition;
input transition_i;
input transition_data;
input activity;
input clock_activity;
input lock_err;
input lock;
input outside_freq_range;
input slow_clock;
input CLK_SRC;

output [31:0]  quotient;
output [4:0] state;
output [8:0] data_trans_cnt;
output [20:0] timer, timer_d;
output timer_not_of;



reg [4:0] state;
reg [20:0] timer, timer_d;
reg timer_of;
reg [8:0] bit_cnt, data_trans_cnt;
reg [9:0] bit_cnt1;
reg [5:0] divide_cnt;
reg divide_cnt_32;
reg [21:0] dividend, divisor;
reg [31:0] quotient;
reg decision;
reg timer_not_of;

wire slow_clock;

/*  inputs

transition
transition_i
transition_data
activity
lock_err
outside_freq_range
quotient
*/

always @ (posedge clk)
	if (rst==1'd1)
		begin
		state<=5'd0;
		timer<=21'd0;
		timer_d<=21'd0;
		timer_of<=1'd0;
		bit_cnt<=9'd0;
		bit_cnt1<=10'd0;
		data_trans_cnt<=9'd0;
		end
	else
	case(state)
	(5'd0): begin
			timer <=21'd0;
			timer_d <=21'd0;
			timer_of<=1'd0;
			bit_cnt <=9'd0;
			bit_cnt1 <=10'd0;
			data_trans_cnt <=9'd0;
			state <=5'd1;
			dividend <=(slow_clock==1'd0)?22'd256:22'd128;
			divisor <=22'd0;
			divide_cnt <=6'd0;
			quotient <=32'd0;
			
			end
			
	(5'd1): begin
			timer[10:0]<=(timer_not_of==1'd1)?(timer[10:0]+11'd1):timer[10:0];
			timer_d[10:0]<=timer[10:0];
			timer_of<=(timer[10:0]==11'h7ff);
			timer[20:11]<=((timer_not_of==1'd1)&(timer_of==1'd1))?(timer[20:11]+10'd1):timer[20:11];
			//state<=((CLK_SRC==1'd0)&((transition_i==1'd1)||(timer_not_of==1'd1)))?5'd2:5'd1;
			//state<=(((transition_i==1'd1)||(timer_not_of==1'd1)))?5'd2:5'd1;
			state<=(CLK_SRC==1'd1)?5'd10:((transition_i==1'd1)|(timer_not_of==1'd1))?5'd2:5'd1;
			end
			
	(5'd2): begin  // wait 256 bit intervals
			timer[10:0]<=(timer_not_of==1'd1)?(timer[10:0]+11'd1):timer[10:0];
			timer_d[10:0]<=timer[10:0];
			timer_of<=(timer[10:0]==11'h7ff);
			timer[20:11]<=((timer_not_of==1'd1)&(timer_of==1'd1))?(timer[20:11]+10'd1):timer[20:11];
			bit_cnt<=(transition==1'd1)?(bit_cnt+9'd1):bit_cnt;
			data_trans_cnt<=(transition_data==1'd1)?(data_trans_cnt+9'd1):data_trans_cnt;
			state<=((bit_cnt==9'd256)&&(timer[20:11]!=10'h3ff))? 	5'd3 :   // bit clock is active
			(data_trans_cnt==9'd256)?								5'd10:				// bit clock is not active
				(timer_not_of==1'd0)	?5'd0:5'd2;	// wait
			divisor<={1'd0, {timer[20:11],timer_d[10:0]}};
			end
	
	// timer contains the number of clock cycles in 256 bit intervals
	// now calculate the 32 bit frequency for the bit timing NCO		
			
	(5'd3):	begin
			decision<=(divisor<dividend);
			state<=5'd4;
			end
	(5'd4): begin
			dividend<=(decision==1'd1)?(dividend-divisor):dividend;
			quotient<= {quotient[30:0],decision};
			state<=5'd5;
			end
	(5'd5): begin
			dividend<={dividend[20:0],1'd0};
			divide_cnt<=divide_cnt+6'd1;
			state<=(divide_cnt==6'd32)?5'd6:5'd3;
			end
	
			
	//  now phase lock to the received signal to remove uncertainty		
	//  Use second order digital phase locked loop	
	(5'd6): begin
			timer<=21'd0;
			timer_d<=21'd0;
			timer_of<=1'd0;
			state<=5'd7;
			end
				
	(5'd7): begin
			timer[10:0]<=(timer_not_of==1'd1)?(timer[10:0]+11'd1):timer[10:0];
			timer_d[10:0]<=timer[10:0];
			timer_of<=(timer[10:0]==11'h7ff);
			timer[20:11]<=((timer_not_of==1'd1)&(timer_of==1'd1))?(timer[20:11]+10'd1):timer[20:11];
			state<=(((timer[20:11]==10'h3ff))|(CLK_SRC==1'd1))?5'd0:
						 (bit_cnt1==10'd1023)?5'd8:5'd7;
			bit_cnt1<=bit_cnt1+ ((transition==1'd1)?10'd1:10'd0);
			end
			
	// reduce the loop bandwidth 
	// tracking clock transitions
			
	(5'd8): begin
			state<=((outside_freq_range==1'd1)|(lock_err==1'd1)|(clock_activity==1'd0)|(CLK_SRC==1'd1))?5'd0:5'd8;
			timer<=21'd0;
			timer_d<=21'd0;
			timer_of<=1'd0;
			end		
			
	
	// begin tracking data transitions using second order phase locked loop
	(5'd10): begin
			state <=5'd11;
			timer<=21'd0;
			timer_d<=21'd0;
			timer_of<=1'd0;
			end
			
	(5'd11): begin
			timer[10:0]<=(timer_not_of==1'd1)?(timer[10:0]+11'd1):timer[10:0];
			timer_d[10:0]<=timer[10:0];
			timer_of<=(timer[10:0]==11'h7ff);
			timer[20:11]<=((timer_not_of==1'd1)&(timer_of==1'd1))?(timer[20:11]+10'd1):timer[20:11];
			state <=((timer_not_of==1'd0)|(activity==1'd0))?5'd0:  // start over if timeout happens
				(bit_cnt1==10'd200)?5'd12:5'd11;		
			bit_cnt1<=bit_cnt1+ ((transition_data==1'd1)?10'd1:10'd0);
			end
			
	(5'd12): begin
			state<=((lock==1'd1)|(outside_freq_range==1'd1)|(activity==1'd0)|(CLK_SRC==1'd0))?5'd0:5'd12;
			timer<=21'd0;
			timer_d<=21'd0;
			timer_of<=1'd0;
			end
						
	default state<=state;
	endcase	
	
always @ (posedge clk)	
	if ((rst==1'd1)|(state==5'd0))
		begin
		timer_not_of<=1'd1;
		divide_cnt_32<=1'd0;
		end
	else
		begin
		timer_not_of<=(timer[20:11]!=10'h3ff);
		divide_cnt_32<=(divide_cnt==6'd32);
		end
		
endmodule
	