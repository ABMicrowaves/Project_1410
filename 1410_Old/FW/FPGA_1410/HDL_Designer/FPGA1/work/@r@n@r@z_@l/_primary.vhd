library verilog;
use verilog.vl_types.all;
entity RNRZ_L is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        data_in         : in     vl_logic;
        data_clk        : in     vl_logic;
        mode_15_n11     : in     vl_logic;
        TX_nRX          : in     vl_logic;
        BER_test        : in     vl_logic;
        data_out        : out    vl_logic
    );
end RNRZ_L;
