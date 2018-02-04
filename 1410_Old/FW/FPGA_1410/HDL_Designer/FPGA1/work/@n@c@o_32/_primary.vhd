library verilog;
use verilog.vl_types.all;
entity NCO_32 is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        In_A            : in     vl_logic_vector(31 downto 0);
        Rslt            : out    vl_logic_vector(31 downto 0);
        Rslt_p          : out    vl_logic_vector(32 downto 0);
        temp_1          : out    vl_logic_vector(16 downto 0);
        temp_2          : out    vl_logic_vector(16 downto 0);
        sym_phase_of    : out    vl_logic
    );
end NCO_32;
