library verilog;
use verilog.vl_types.all;
entity mult_24_8 is
    port(
        clock           : in     vl_logic;
        dataa           : in     vl_logic_vector(7 downto 0);
        datab           : in     vl_logic_vector(31 downto 0);
        result          : out    vl_logic_vector(39 downto 0)
    );
end mult_24_8;
