library verilog;
use verilog.vl_types.all;
entity ACCUM_32 is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        en              : in     vl_logic;
        state           : in     vl_logic_vector(4 downto 0);
        In_A            : in     vl_logic_vector(31 downto 0);
        Rslt            : out    vl_logic_vector(31 downto 0)
    );
end ACCUM_32;
