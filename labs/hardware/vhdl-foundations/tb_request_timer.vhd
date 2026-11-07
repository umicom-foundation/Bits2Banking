-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/tb_request_timer.vhd
--
-- PURPOSE:
--   Check request latency, busy-time rejection and reset cancellation.
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
entity tb_request_timer is end entity;
architecture checks of tb_request_timer is
    signal clk : std_logic := '0';
    signal reset : std_logic := '1';
    signal start : std_logic := '0';
    signal busy, done : std_logic;
begin
    clk <= not clk after 5 ns;
    dut : entity work.request_timer
        generic map (CYCLES => 3)
        port map (clk => clk, reset => reset, start => start, busy => busy, done => done);
    stimulus : process
    begin
        wait until rising_edge(clk); wait for 1 ns;
        assert busy = '0' and done = '0' report "Reset state" severity failure;
        reset <= '0'; start <= '1';
        wait until rising_edge(clk); wait for 1 ns;
        assert busy = '1' and done = '0' report "Start acceptance" severity failure;
        start <= '0';
        wait until rising_edge(clk); wait for 1 ns;
        assert busy = '1' and done = '0' report "Early completion at one" severity failure;
        start <= '1';
        wait until rising_edge(clk); wait for 1 ns;
        assert busy = '1' and done = '0' report "Early completion at two" severity failure;
        start <= '0';
        wait until rising_edge(clk); wait for 1 ns;
        assert busy = '0' and done = '1' report "Completion at three" severity failure;
        wait until rising_edge(clk); wait for 1 ns;
        assert busy = '0' and done = '0' report "Done pulse or queued start" severity failure;
        start <= '1';
        wait until rising_edge(clk); wait for 1 ns;
        start <= '0'; reset <= '1';
        wait until rising_edge(clk); wait for 1 ns;
        assert busy = '0' and done = '0' report "Reset must cancel" severity failure;
        reset <= '0';
        for cycle in 1 to 4 loop
            wait until rising_edge(clk); wait for 1 ns;
            assert busy = '0' and done = '0' report "Cancelled work returned" severity failure;
        end loop;
        report "request timer checks passed" severity note;
        finish;
        wait;
    end process;
end architecture;
