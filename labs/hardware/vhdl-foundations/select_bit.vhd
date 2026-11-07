-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/select_bit.vhd
--
-- PURPOSE:
--   Describe an explicit two-input selector, including unknown selection.
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
entity select_bit is
    port (a, b, choose_b : in std_logic; result_bit : out std_logic);
end entity;
architecture rtl of select_bit is
begin
    with choose_b select
        result_bit <= a when '0',
                      b when '1',
                      'X' when others;
end architecture;

