-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/tb_pulse_counter.vhd
-- 
-- PURPOSE:
--   Check composition latency, held input, pending-pulse reset and saturation.
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
use ieee.numeric_std.all;
use std.env.all;

entity tb_pulse_counter is end entity;
architecture checks of tb_pulse_counter is
    signal clk : std_logic := '0';
    signal reset : std_logic := '1';
    signal sampled_input : std_logic := '0';
    signal detected, full : std_logic;
    signal count : unsigned(1 downto 0);
begin
    clk <= not clk after 5 ns;
    dut : entity work.pulse_counter generic map(width => 2)
        port map(clk, reset, sampled_input, detected, count, full);
    process
        procedure step(value : std_logic; expected_count : natural;
                       expected_pulse : std_logic) is
        begin
            sampled_input <= value;
            wait until rising_edge(clk);
            wait for 1 ns;
            assert count = expected_count report "composed count" severity failure;
            assert detected = expected_pulse report "composed pulse" severity failure;
            if expected_count = 3 then
                assert full = '1' report "full at capacity" severity failure;
            else
                assert full = '0' report "full before capacity" severity failure;
            end if;
        end procedure;
    begin
        step('0', 0, '0');
        reset <= '0';
        step('1', 0, '1');
        step('1', 1, '0');
        step('1', 1, '0');
        step('0', 1, '0');
        step('1', 1, '1');
        step('0', 2, '0');
        step('1', 2, '1');
        step('0', 3, '0');
        step('1', 3, '1');
        step('0', 3, '0');
        reset <= '1';
        step('0', 0, '0');
        reset <= '0';
        step('1', 0, '1');
        -- Reset deliberately discards the pending event instead of allowing
        -- the previous pulse to increment the freshly reset count.
        reset <= '1';
        step('1', 0, '0');
        reset <= '0';
        step('1', 0, '1');
        step('1', 1, '0');
        report "Pulse counter checks passed" severity note;
        stop;
        wait;
    end process;
end architecture;

