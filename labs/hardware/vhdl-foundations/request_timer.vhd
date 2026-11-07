-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/request_timer.vhd
--
-- PURPOSE:
--   Complete one sampled request after a configurable number of clock edges.
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
entity request_timer is
    generic (CYCLES : positive := 3);
    port (clk, reset, start : in std_logic;
          busy, done : out std_logic);
end entity;
architecture rtl of request_timer is
    signal remaining : natural range 0 to CYCLES;
    signal active : std_logic;
begin
    busy <= active;
    process(clk)
    begin
        if rising_edge(clk) then
            -- Reset cancels the request. The caller supplies a start pulse
            -- only while idle; pulses during active work are not queued.
            if reset = '1' then
                remaining <= 0;
                active <= '0';
                done <= '0';
            else
                done <= '0';
                if active = '1' then
                    if remaining = 1 then
                        remaining <= 0;
                        active <= '0';
                        done <= '1';
                    else
                        remaining <= remaining - 1;
                    end if;
                elsif start = '1' then
                    remaining <= CYCLES;
                    active <= '1';
                end if;
            end if;
        end if;
    end process;
end architecture;
