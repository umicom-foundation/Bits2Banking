-- -----------------------------------------------------------------------------
-- Bits2Banking / Umicom Framework
-- File: rtl/learning_program.vhd
--
-- PURPOSE:
--   Provide a small read-only instruction program with explicit invalid addresses.
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

entity learning_program is
  port (address : in unsigned(3 downto 0);
        instruction : out std_logic_vector(7 downto 0));
end entity;

architecture rtl of learning_program is
  type program_words is array (0 to 15) of std_logic_vector(7 downto 0);
  -- Load three, subtract one, branch to HALT at zero, otherwise repeat.
  -- Unused addresses deliberately decode as an invalid CPU operation.
  constant program : program_words := (
    0 => x"13", 1 => x"31", 2 => x"54", 3 => x"41", 4 => x"F0",
    others => x"60");
begin
  process(all)
  begin
    -- Do not convert an unresolved simulation address into an array index.
    if is_x(std_logic_vector(address)) then
      instruction <= x"60";
    else
      instruction <= program(to_integer(address));
    end if;
  end process;
end architecture;
