library verilog;
use verilog.vl_types.all;
entity FM is
    port(
        address         : in     vl_logic_vector(10 downto 0);
        clock           : in     vl_logic;
        q               : out    vl_logic_vector(13 downto 0)
    );
end FM;
