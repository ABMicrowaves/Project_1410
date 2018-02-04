library verilog;
use verilog.vl_types.all;
entity frequency_translate_cyclone_2 is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        real_in         : in     vl_logic_vector(13 downto 0);
        imag_in         : in     vl_logic_vector(13 downto 0);
        frequency_mod   : in     vl_logic_vector(13 downto 0);
        frequency       : in     vl_logic_vector(31 downto 0);
        frequency_en    : in     vl_logic;
        real_rslt       : out    vl_logic_vector(13 downto 0);
        sine            : out    vl_logic_vector(13 downto 0);
        cosine          : out    vl_logic_vector(13 downto 0)
    );
end frequency_translate_cyclone_2;
