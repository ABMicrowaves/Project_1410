library verilog;
use verilog.vl_types.all;
entity Add_32 is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        In_A            : in     vl_logic_vector(31 downto 0);
        In_B            : in     vl_logic_vector(31 downto 0);
        Rslt            : out    vl_logic_vector(31 downto 0)
    );
end Add_32;
