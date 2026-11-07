-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/tb_lesson_counter.vhd
--
-- PURPOSE:
--   Check two counter widths, synchronous reset, holds and saturation.
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

entity tb_lesson_counter is end entity;
architecture checks of tb_lesson_counter is
    signal clk : std_logic := '0';
    signal reset : std_logic := '1';
    signal enable : std_logic := '0';
    signal wide_count : unsigned(2 downto 0);
    signal narrow_count : unsigned(0 downto 0);
    signal wide_full, narrow_full : std_logic;
begin
    clk <= not clk after 5 ns;
    wide : entity work.lesson_counter generic map(width => 3)
        port map(clk, reset, enable, wide_count, wide_full);
    narrow : entity work.lesson_counter generic map(width => 1)
        port map(clk, reset, enable, narrow_count, narrow_full);
    process
        procedure edge is
        begin
            wait until rising_edge(clk);
            wait for 1 ns;
        end procedure;
    begin
        edge;
        assert wide_count = 0 and narrow_count = 0 report "reset count" severity failure;
        assert wide_full = '0' and narrow_full = '0' report "reset full" severity failure;
        reset <= '0';
        enable <= '1';
        for expected in 1 to 7 loop
            edge;
            assert wide_count = expected report "enabled count" severity failure;
            assert narrow_count = 1 and narrow_full = '1'
                report "one-bit saturation" severity failure;
        end loop;
        assert wide_full = '1' report "wide full" severity failure;
        edge;
        assert wide_count = 7 report "must not wrap at full" severity failure;

        reset <= '1';
        -- No edge has happened yet; synchronous reset must retain the old
        -- count during this interval and take effect at the next edge.
        wait for 1 ns;
        assert wide_count = 7 report "reset changed without clock edge" severity failure;
        edge;
        assert wide_count = 0 report "reset wins over enable" severity failure;
        reset <= '0';
        enable <= '0';
        edge;
        assert wide_count = 0 report "disabled hold" severity failure;
        enable <= '1';
        edge;
        assert wide_count = 1 report "restart count" severity failure;
        enable <= '0';
        edge;
        assert wide_count = 1 report "nonzero hold" severity failure;
        report "Counter checks passed" severity note;
        stop;
        wait;
    end process;
end architecture;

