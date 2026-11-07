-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/add_nibble_tb.vhd
--
-- PURPOSE:
--   Exhaustively compare all 256 four-bit input pairs with arithmetic.
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
entity add_nibble_tb is end entity;
architecture checks of add_nibble_tb is
    signal a, b : unsigned(3 downto 0) := (others => '0');
    signal total : unsigned(4 downto 0);
begin
    dut : entity work.add_nibble port map (a, b, total);
    stimulus : process
    begin
        for left_value in 0 to 15 loop
            for right_value in 0 to 15 loop
                a <= to_unsigned(left_value, a'length);
                b <= to_unsigned(right_value, b'length);
                wait for 1 ns;
                assert to_integer(total) = left_value + right_value
                    report "sum or carry was lost" severity failure;
            end loop;
        end loop;
        report "adder checks passed" severity note;
        finish;
        wait;
    end process;
end architecture;

