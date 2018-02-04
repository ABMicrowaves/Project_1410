`timescale 1 ps / 1 ps
module multiplier_14_12 (
	clock,
	dataa,
	datab,
	result);

	input	  clock;
	input	[13:0]  dataa;
	input	[11:0]  datab;
	output	[25:0]  result;

	wire [25:0] sub_wire0;
	wire [25:0] result = sub_wire0[25:0];

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
		lpm_mult_component.lpm_pipeline = 2,
		lpm_mult_component.lpm_representation = "SIGNED",
		lpm_mult_component.lpm_type = "LPM_MULT",
		lpm_mult_component.lpm_widtha = 14,
		lpm_mult_component.lpm_widthb = 12,
		lpm_mult_component.lpm_widthp = 26;


endmodule
