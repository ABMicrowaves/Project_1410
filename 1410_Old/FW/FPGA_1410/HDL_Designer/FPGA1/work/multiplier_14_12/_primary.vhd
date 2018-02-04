library verilog;
use verilog.vl_types.all;
entity multiplier_14_12 is
    port(
        clock           : in     vl_logic;
        dataa           : in     vl_logic_vector(13 downto 0);
        datab           : in     vl_logic_vector(11 downto 0);
        result          : out    vl_logic_vector(25 downto 0)
    );
end multiplier_14_12;
