library verilog;
use verilog.vl_types.all;
entity SIN_ROM_2_cy is
    port(
        address         : in     vl_logic_vector(11 downto 0);
        clock           : in     vl_logic;
        q               : out    vl_logic_vector(12 downto 0)
    );
end SIN_ROM_2_cy;