-- -----------------------------------------------------------------------------
-- Bits2Banking / Umicom Framework
-- File: rtl/learning_system.vhd
--
-- PURPOSE:
--   Connect the teaching CPU to its program memory while exposing observable state.
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

entity learning_system is
  port (clock, reset, enable : in std_logic;
        address : out unsigned(3 downto 0);
        accumulator : out unsigned(7 downto 0);
        instruction : out std_logic_vector(7 downto 0);
        halted, fault : out std_logic);
end entity;

architecture structural of learning_system is
  signal pc : unsigned(3 downto 0);
  signal word : std_logic_vector(7 downto 0);
begin
  -- The CPU owns execution state; the ROM only selects the current word.
  address <= pc;
  instruction <= word;
  memory : entity work.learning_program
    port map (address => pc, instruction => word);
  cpu : entity work.learning_cpu
    port map (clock => clock, reset => reset, enable => enable,
              instruction => word, address => pc, accumulator => accumulator,
              halted => halted, fault => fault);
end architecture;
