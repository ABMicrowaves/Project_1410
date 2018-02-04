library verilog;
use verilog.vl_types.all;
entity Clock_240_tx is
    port(
        inclk0          : in     vl_logic;
        SPI_clk         : in     vl_logic;
        SPI_DI          : in     vl_logic;
        SPI_DO          : inout  vl_logic;
        SPI_CS          : in     vl_logic;
        Bit_clock       : in     vl_logic;
        Bit_data        : in     vl_logic;
        I               : out    vl_logic_vector(13 downto 0);
        Q               : out    vl_logic_vector(13 downto 0);
        TP3             : out    vl_logic;
        TP4             : out    vl_logic;
        TP5             : out    vl_logic;
        TP6             : out    vl_logic;
        LED1            : out    vl_logic;
        LED2            : out    vl_logic;
        LED3            : out    vl_logic;
        LED4            : out    vl_logic;
        DAC_clk_p       : out    vl_logic;
        DAC_clk_m       : out    vl_logic;
        test            : out    vl_logic
    );
end Clock_240_tx;
