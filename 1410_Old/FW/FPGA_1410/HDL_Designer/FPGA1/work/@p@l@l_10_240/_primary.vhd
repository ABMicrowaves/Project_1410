library verilog;
use verilog.vl_types.all;
entity PLL_10_240 is
    port(
        inclk0          : in     vl_logic;
        c0              : out    vl_logic;
        c1              : out    vl_logic;
        c2              : out    vl_logic;
        c3              : out    vl_logic;
        locked          : out    vl_logic
    );
end PLL_10_240;
