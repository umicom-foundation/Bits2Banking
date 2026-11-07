-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/tb_word_parity.vhd
--
-- PURPOSE:
--   Check all binary byte patterns and propagation of an unknown input.
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
entity tb_word_parity is end entity;
architecture checks of tb_word_parity is
    signal word_in : std_logic_vector(7 downto 0) := (others => '0');
    signal odd : std_logic;
begin
    dut : entity work.word_parity port map (word_in => word_in, odd => odd);
    stimulus : process
        variable remaining, ones : natural;
    begin
        for value in 0 to 255 loop
            word_in <= std_logic_vector(to_unsigned(value, 8));
            remaining := value;
            ones := 0;
            for bit_index in 0 to 7 loop
                ones := ones + (remaining mod 2);
                remaining := remaining / 2;
            end loop;
            wait for 1 ns;
            if ones mod 2 = 0 then
                assert odd = '0' report "Expected even parity" severity failure;
            else
                assert odd = '1' report "Expected odd parity" severity failure;
            end if;
        end loop;
        word_in <= "0000000X";
        wait for 1 ns;
        assert odd = 'X' report "Unknown input was hidden" severity failure;
        report "word parity checks passed" severity note;
        finish;
        wait;
    end process;
end architecture;
