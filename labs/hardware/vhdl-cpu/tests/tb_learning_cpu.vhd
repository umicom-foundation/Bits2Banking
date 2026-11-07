-- -----------------------------------------------------------------------------
-- Bits2Banking / Umicom Framework
-- File: tests/tb_learning_cpu.vhd
--
-- PURPOSE:
--   Check instruction execution, pause, halt, reset, invalid opcode and wraparound.
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

entity tb_learning_cpu is end entity;
architecture test of tb_learning_cpu is
  signal clock : std_logic := '0';
  signal reset : std_logic := '1';
  signal enable : std_logic := '0';
  signal instruction : std_logic_vector(7 downto 0) := x"00";
  signal address : unsigned(3 downto 0);
  signal accumulator : unsigned(7 downto 0);
  signal halted, fault : std_logic;
begin
  clock <= not clock after 5 ns;
  dut: entity work.learning_cpu port map(clock, reset, enable, instruction,
                                        address, accumulator, halted, fault);
  process
    procedure step(value : std_logic_vector(7 downto 0)) is
    begin
      instruction <= value;
      wait until rising_edge(clock); wait for 1 ns;
    end procedure;
  begin
    step(x"00");
    assert accumulator = 0 and address = 0 and halted = '0' severity failure;
    reset <= '0'; enable <= '1';
    step(x"13"); -- LOAD 3
    assert accumulator = 3 and address = 1 severity failure;
    enable <= '0'; step(x"2F");
    assert accumulator = 3 and address = 1 report "pause changed state" severity failure;
    enable <= '1'; step(x"31");
    assert accumulator = 2 severity failure;
    step(x"58");
    assert address = 3 report "nonzero branch was taken" severity failure;
    step(x"32"); step(x"58");
    assert accumulator = 0 and address = 8 report "zero branch failed" severity failure;
    step(x"31");
    assert accumulator = 255 report "subtraction wrap failed" severity failure;
    step(x"22");
    assert accumulator = 1 report "addition wrap failed" severity failure;
    step(x"4F"); step(x"00");
    assert address = 0 report "address wrap failed" severity failure;
    step(x"F0"); step(x"19");
    assert halted = '1' and accumulator = 1 and address = 0 severity failure;
    reset <= '1'; step(x"00"); reset <= '0';
    assert halted = '0' and fault = '0' and accumulator = 0 severity failure;
    step(x"60");
    assert halted = '1' and fault = '1' and address = 0 severity failure;
    report "CPU checks passed";
    finish;
    wait;
  end process;
  -- A stalled stimulus must fail instead of silently reaching a stop time.
  process begin wait for 2 us; assert false report "CPU test exceeded its deadline" severity failure; end process;
end architecture;
