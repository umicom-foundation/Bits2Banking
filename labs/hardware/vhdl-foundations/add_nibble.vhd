-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/add_nibble.vhd
--
-- PURPOSE:
--   Retain the carry bit when adding two four-bit unsigned values.
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
entity add_nibble is
    port (a, b : in unsigned(3 downto 0); total : out unsigned(4 downto 0));
end entity;
architecture rtl of add_nibble is
begin
    -- Extend before addition: a wider destination alone does not widen operands.
    total <= resize(a, total'length) + resize(b, total'length);
end architecture;

