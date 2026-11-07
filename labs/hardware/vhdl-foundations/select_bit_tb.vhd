-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/select_bit_tb.vhd
--
-- PURPOSE:
--   Check every binary selector input and an unknown control.
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
use std.env.all;
entity select_bit_tb is end entity;
architecture checks of select_bit_tb is
    signal a, b, choose_b, result_bit : std_logic := '0';
begin
    dut : entity work.select_bit port map (a, b, choose_b, result_bit);
    stimulus : process
        type bits is array (0 to 1) of std_logic;
        constant values : bits := ('0', '1');
    begin
        for ai in 0 to 1 loop
            for bi in 0 to 1 loop
                a <= values(ai); b <= values(bi);
                choose_b <= '0'; wait for 1 ns;
                assert result_bit = values(ai) report "A selection failed" severity failure;
                choose_b <= '1'; wait for 1 ns;
                assert result_bit = values(bi) report "B selection failed" severity failure;
            end loop;
        end loop;
        choose_b <= 'X'; wait for 1 ns;
        assert result_bit = 'X' report "Unknown control was concealed" severity failure;
        report "selector checks passed" severity note;
        finish;
        wait;
    end process;
end architecture;

