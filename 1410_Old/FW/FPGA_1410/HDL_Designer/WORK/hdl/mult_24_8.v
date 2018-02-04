`timescale 1 ps / 1 ps
module mult_24_8 (
	clock,
	dataa,
	datab,
	result);

	input	  clock;
	input	[7:0]  dataa;
	input	[31:0]  datab;
	output	[39:0]  result;

	wire [39:0] sub_wire0;
	wire [39:0] result = sub_wire0[39:0];

	lpm_mult	lpm_mult_component (
				.dataa (dataa),
				.datab (datab),
				.clock (clock),
				.result (sub_wire0),
				.aclr (1'b0),
				.clken (1'b1),
				.sum (1'b0));
	defparam
		lpm_mult_component.lpm_hint = "MAXIMIZE_SPEED=5",
		lpm_mult_component.lpm_pipeline = 4,
		lpm_mult_component.lpm_representation = "SIGNED",
		lpm_mult_component.lpm_type = "LPM_MULT",
		lpm_mult_component.lpm_widtha = 8,
		lpm_mult_component.lpm_widthb = 32,
		lpm_mult_component.lpm_widthp = 40;


endmodule
