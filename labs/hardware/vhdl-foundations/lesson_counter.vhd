-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/lesson_counter.vhd
--
-- PURPOSE:
--   Count enabled clock edges with an explicit width and saturation contract.
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

entity lesson_counter is
    generic (width : positive := 4);
    port (clk, reset, enable : in std_logic;
          count : out unsigned(width - 1 downto 0);
          full : out std_logic);
end entity;

architecture rtl of lesson_counter is
    signal held_count : unsigned(width - 1 downto 0);
    constant maximum : unsigned(width - 1 downto 0) := (others => '1');
begin
    count <= held_count;
    -- Compare bit patterns before reset without asking numeric_std to
    -- interpret an uninitialized word as a number. The count is usable
    -- only after the documented reset edge.
    full <= '1' when std_logic_vector(held_count) = std_logic_vector(maximum) else '0';
    process(clk)
    begin
        if rising_edge(clk) then
            -- Reset is synchronous: the output becomes known at an active
            -- edge with reset asserted. Saturation preserves a full count
            -- instead of wrapping it into an apparently empty counter.
            if reset = '1' then
                held_count <= (others => '0');
            elsif enable = '1' and held_count /= maximum then
                held_count <= held_count + 1;
            end if;
        end if;
    end process;
end architecture;

