-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/lesson_register.vhd
--
-- PURPOSE:
--   Describe an enabled eight-bit register with synchronous reset.
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
entity lesson_register is
    port (clk, reset, enable : in std_logic;
          input_word : in std_logic_vector(7 downto 0);
          stored_word : out std_logic_vector(7 downto 0));
end entity;
architecture rtl of lesson_register is
begin
    process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                stored_word <= (others => '0');
            elsif enable = '1' then
                stored_word <= input_word;
            end if;
        end if;
    end process;
end architecture;

