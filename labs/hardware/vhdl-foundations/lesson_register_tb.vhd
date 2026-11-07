-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/lesson_register_tb.vhd
--
-- PURPOSE:
--   Check reset priority, enabled capture and retention between edges.
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
entity lesson_register_tb is end entity;
architecture checks of lesson_register_tb is
    signal clk, reset, enable : std_logic := '0';
    signal input_word, stored_word : std_logic_vector(7 downto 0);
begin
    clk <= not clk after 5 ns;
    dut : entity work.lesson_register port map (clk, reset, enable, input_word, stored_word);
    stimulus : process
    begin
        reset <= '1'; enable <= '1'; input_word <= x"FF";
        wait until rising_edge(clk); wait for 1 ns;
        assert stored_word = x"00" report "Reset must win over enable" severity failure;
        reset <= '0'; input_word <= x"2A";
        wait until rising_edge(clk); wait for 1 ns;
        assert stored_word = x"2A" report "Enabled capture failed" severity failure;
        enable <= '0'; input_word <= x"77";
        wait until rising_edge(clk); wait for 1 ns;
        assert stored_word = x"2A" report "Disabled register changed" severity failure;
        reset <= '1'; wait for 1 ns;
        assert stored_word = x"2A" report "Synchronous reset changed data before edge" severity failure;
        wait until rising_edge(clk); wait for 1 ns;
        assert stored_word = x"00" report "Synchronous reset failed" severity failure;
        report "register checks passed" severity note;
        finish;
        wait;
    end process;
end architecture;

