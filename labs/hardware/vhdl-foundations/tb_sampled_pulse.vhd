-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/tb_sampled_pulse.vhd
--
-- PURPOSE:
--   Check low-to-high pulses, held inputs and reset priority.
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

entity tb_sampled_pulse is end entity;
architecture checks of tb_sampled_pulse is
    signal clk : std_logic := '0';
    signal reset : std_logic := '1';
    signal sampled_input : std_logic := '0';
    signal pulse : std_logic;
begin
    clk <= not clk after 5 ns;
    dut : entity work.sampled_pulse port map(clk, reset, sampled_input, pulse);
    process
        procedure step(value : std_logic; expected : std_logic) is
        begin
            sampled_input <= value;
            wait until rising_edge(clk);
            wait for 1 ns;
            assert pulse = expected report "unexpected pulse" severity failure;
        end procedure;
    begin
        step('1', '0'); -- reset wins even when the input is high
        reset <= '0';
        step('0', '0');
        step('1', '1');
        step('1', '0');
        step('1', '0');
        step('0', '0');
        step('1', '1');
        reset <= '1';
        step('1', '0');
        reset <= '0';
        step('1', '1'); -- reset history was low
        step('1', '0');
        step('X', 'X');
        report "Sampled pulse checks passed" severity note;
        stop;
        wait;
    end process;
end architecture;

