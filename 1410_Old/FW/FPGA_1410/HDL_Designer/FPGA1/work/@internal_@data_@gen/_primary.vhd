library verilog;
use verilog.vl_types.all;
entity Internal_Data_Gen is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        data_clock      : in     vl_logic;
        DAT_PAT         : in     vl_logic_vector(3 downto 0);
        internal_data   : out    vl_logic;
        shift           : out    vl_logic_vector(16 downto 0)
    );
end Internal_Data_Gen;
