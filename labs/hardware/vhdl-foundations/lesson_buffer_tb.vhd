-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/lesson_buffer_tb.vhd
--
-- PURPOSE:
--   Check waiting, simultaneous replacement, draining and reset of a buffer.
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
entity lesson_buffer_tb is end entity;
architecture checks of lesson_buffer_tb is
    signal clk, reset, input_valid, input_ready, output_valid, output_ready : std_logic := '0';
    signal input_word, output_word : std_logic_vector(7 downto 0) := (others => '0');
begin
    clk <= not clk after 5 ns;
    dut : entity work.lesson_buffer port map
        (clk, reset, input_valid, input_ready, input_word, output_valid, output_ready, output_word);
    stimulus : process
    begin
        reset <= '1';
        wait until rising_edge(clk); wait for 1 ns;
        assert output_valid = '0' and input_ready = '0' report "Reset transfer" severity failure;
        reset <= '0'; input_valid <= '1'; input_word <= x"2A";
        wait until rising_edge(clk); wait for 1 ns;
        assert output_valid = '1' and output_word = x"2A" report "Capture failed" severity failure;
        input_word <= x"77";
        wait until rising_edge(clk); wait for 1 ns;
        assert input_ready = '0' and output_word = x"2A" report "Stalled word changed" severity failure;
        output_ready <= '1';
        wait until rising_edge(clk); wait for 1 ns;
        assert output_valid = '1' and output_word = x"77" report "Replacement failed" severity failure;
        input_valid <= '0';
        wait until rising_edge(clk); wait for 1 ns;
        assert output_valid = '0' report "Draining failed" severity failure;
        input_valid <= '1'; input_word <= x"55"; output_ready <= '0';
        wait until rising_edge(clk); wait for 1 ns;
        reset <= '1';
        wait until rising_edge(clk); wait for 1 ns;
        assert output_valid = '0' and output_word = x"00" report "Reset retained pending data" severity failure;
        report "buffer checks passed" severity note;
        finish;
        wait;
    end process;
end architecture;

