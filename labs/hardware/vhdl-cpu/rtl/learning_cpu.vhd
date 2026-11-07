-- -----------------------------------------------------------------------------
-- Bits2Banking / Umicom Framework
-- File: rtl/learning_cpu.vhd
--
-- PURPOSE:
--   Model an eight-bit accumulator and a sixteen-address teaching instruction set.
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

entity learning_cpu is
  port (clock, reset, enable : in std_logic;
        instruction : in std_logic_vector(7 downto 0);
        address : out unsigned(3 downto 0);
        accumulator : out unsigned(7 downto 0);
        halted, fault : out std_logic);
end entity;

architecture rtl of learning_cpu is
  signal pc : unsigned(3 downto 0) := (others => '0');
  signal acc : unsigned(7 downto 0) := (others => '0');
  signal stopped, invalid : std_logic := '0';
begin
  address <= pc;
  accumulator <= acc;
  halted <= stopped;
  fault <= invalid;
  -- One enabled edge executes one instruction. Reset has priority over a halt.
  process(clock)
    variable operand : unsigned(7 downto 0);
  begin
    if rising_edge(clock) then
      if reset = '1' then
        pc <= (others => '0'); acc <= (others => '0');
        stopped <= '0'; invalid <= '0';
      elsif enable = '1' and stopped = '0' then
        operand := resize(unsigned(instruction(3 downto 0)), acc'length);
        -- Fixed-width unsigned operations deliberately wrap modulo 256.
        case instruction(7 downto 4) is
          when x"0" => pc <= pc + 1;
          when x"1" => acc <= operand; pc <= pc + 1;
          when x"2" => acc <= acc + operand; pc <= pc + 1;
          when x"3" => acc <= acc - operand; pc <= pc + 1;
          when x"4" => pc <= unsigned(instruction(3 downto 0));
          when x"5" =>
            if acc = 0 then pc <= unsigned(instruction(3 downto 0));
            else pc <= pc + 1; end if;
          when x"F" => stopped <= '1';
          when others => stopped <= '1'; invalid <= '1';
        end case;
      end if;
    end if;
  end process;
end architecture;
