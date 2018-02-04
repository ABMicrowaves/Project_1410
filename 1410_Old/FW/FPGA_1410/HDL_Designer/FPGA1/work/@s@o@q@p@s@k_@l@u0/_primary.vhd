library verilog;
use verilog.vl_types.all;
entity SOQPSK_LU0 is
    port(
        address         : in     vl_logic_vector(8 downto 0);
        clock           : in     vl_logic;
        q               : out    vl_logic_vector(13 downto 0)
    );
end SOQPSK_LU0;
