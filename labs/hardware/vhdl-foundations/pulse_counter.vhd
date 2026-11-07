-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/pulse_counter.vhd
-- 
-- PURPOSE:
--   Compose the existing sampled pulse detector and saturating counter on one clock.
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

entity pulse_counter is
    generic (width : positive := 4);
    port (clk, reset, sampled_input : in std_logic;
          detected : out std_logic;
          count : out unsigned(width - 1 downto 0);
          full : out std_logic);
end entity;

architecture composed of pulse_counter is
    signal enable_count : std_logic;
begin
    -- The register boundary is intentional: the counter consumes the pulse
    -- that existed before an edge. A newly detected rise is counted on the
    -- following edge. Both components share the same synchronous reset.
    detector : entity work.sampled_pulse
        port map(clk => clk, reset => reset, sampled_input => sampled_input,
                 pulse => enable_count);
    counter : entity work.lesson_counter generic map(width => width)
        port map(clk => clk, reset => reset, enable => enable_count,
                 count => count, full => full);
    detected <= enable_count;
end architecture;

