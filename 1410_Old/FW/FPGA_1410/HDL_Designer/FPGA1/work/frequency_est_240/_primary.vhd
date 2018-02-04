library verilog;
use verilog.vl_types.all;
entity frequency_est_240 is
    port(
        rst             : in     vl_logic;
        clk             : in     vl_logic;
        transition      : in     vl_logic;
        transition_i    : in     vl_logic;
        transition_data : in     vl_logic;
        activity        : in     vl_logic;
        clock_activity  : in     vl_logic;
        lock_err        : in     vl_logic;
        outside_freq_range: in     vl_logic;
        lock            : in     vl_logic;
        slow_clock      : in     vl_logic;
        CLK_SRC         : in     vl_logic;
        quotient        : out    vl_logic_vector(31 downto 0);
        state           : out    vl_logic_vector(4 downto 0);
        data_trans_cnt  : out    vl_logic_vector(8 downto 0);
        timer           : out    vl_logic_vector(20 downto 0);
        timer_d         : out    vl_logic_vector(20 downto 0);
        timer_not_of    : out    vl_logic
    );
end frequency_est_240;
