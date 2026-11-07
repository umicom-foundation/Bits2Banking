-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/word_parity.vhd
--
-- PURPOSE:
--   Reduce an eight-bit word to an odd-parity indication.
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
entity word_parity is
    port (word_in : in std_logic_vector(7 downto 0);
          odd : out std_logic);
end entity;
architecture rtl of word_parity is
begin
    process(all)
        variable folded : std_logic;
    begin
        folded := '0';
        for bit_index in word_in'range loop
            folded := folded xor word_in(bit_index);
        end loop;
        odd <= folded;
    end process;
end architecture;
