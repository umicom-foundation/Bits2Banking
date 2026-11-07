-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/sampled_pulse.vhd
--
-- PURPOSE:
--   Create one pulse when a synchronous input changes from low to high.
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

entity sampled_pulse is
    port (clk, reset, sampled_input : in std_logic;
          pulse : out std_logic);
end entity;

architecture rtl of sampled_pulse is
    signal previous : std_logic;
begin
    process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                previous <= '0';
                pulse <= '0';
            else
                -- Both right-hand values are from before this clock edge.
                -- Unknown inputs are propagated by std_logic operations.
                pulse <= sampled_input and not previous;
                previous <= sampled_input;
            end if;
        end if;
    end process;
end architecture;

