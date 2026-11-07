-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/buffer_pipeline_reset_tb.vhd
--
-- PURPOSE:
--   Verify reset discards both queued words and suppresses transfers until a new sequence starts.
--
-- AUTHOR AND ORGANISATION:
-- Sammy Hegab
-- Umicom Foundation
--
-- LICENCE:
-- MIT
-- -----------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use std.env.all;
entity buffer_pipeline_reset_tb is end entity;
architecture checks of buffer_pipeline_reset_tb is
    signal clk : std_logic := '0';
    signal reset : std_logic := '1';
    signal iv, ir, ov, ready : std_logic := '0';
    signal iw, ow : std_logic_vector(7 downto 0) := (others => '0');
begin
    clk <= not clk after 5 ns;
    dut : entity work.buffer_pipeline port map(clk, reset, iv, ir, iw, ov, ready, ow);
    process
        procedure edge is
        begin wait until rising_edge(clk); wait for 1 ns; end procedure;
    begin
        edge; reset <= '0'; iv <= '1'; iw <= x"11";
        edge; iw <= x"22";
        edge; iv <= '0';
        assert ov = '1' and ow = x"11" and ir = '0'
            report "expected two held words" severity failure;
        reset <= '1'; ready <= '1';
        wait for 1 ns;
        assert ov = '0' and ir = '0' report "reset advertised transfer" severity failure;
        edge; reset <= '0'; ready <= '0';
        wait for 1 ns;
        assert ov = '0' and ir = '1' report "reset did not clear both stages" severity failure;
        iv <= '1'; iw <= x"33";
        edge; iv <= '0';
        edge;
        assert ov = '1' and ow = x"33" report "old word survived reset" severity failure;
        ready <= '1'; edge;
        assert ov = '0' report "unexpected trailing word" severity failure;
        report "Pipeline reset checks passed" severity note;
        finish;
        wait;
    end process;
end architecture;
