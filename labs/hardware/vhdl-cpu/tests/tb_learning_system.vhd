-- -----------------------------------------------------------------------------
-- Bits2Banking / Umicom Framework
-- File: tests/tb_learning_system.vhd
--
-- PURPOSE:
--   Check a complete countdown program, pauses, halt stability and restart against an explicit trace.
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

entity tb_learning_system is end entity;

architecture test of tb_learning_system is
  signal clock : std_logic := '0';
  signal reset : std_logic := '1';
  signal enable : std_logic := '1';
  signal address : unsigned(3 downto 0);
  signal accumulator : unsigned(7 downto 0);
  signal instruction : std_logic_vector(7 downto 0);
  signal halted, fault : std_logic;
  signal probe_address : unsigned(3 downto 0) := (others => 'X');
  signal probe_instruction : std_logic_vector(7 downto 0);
  type trace_values is array (natural range <>) of natural;
  constant expected_pc : trace_values := (1, 2, 3, 1, 2, 3, 1, 2, 4, 4);
  constant expected_acc : trace_values := (3, 2, 2, 2, 1, 1, 1, 0, 0, 0);
begin
  clock <= not clock after 5 ns;
  system : entity work.learning_system
    port map (clock, reset, enable, address, accumulator, instruction, halted, fault);
  probe : entity work.learning_program port map (probe_address, probe_instruction);
  process
    procedure edge is
    begin
      wait until rising_edge(clock);
      -- Observe after the CPU and combinational memory have settled.
      wait for 1 ns;
    end procedure;
  begin
    edge;
    assert address = 0 and accumulator = 0 and instruction = x"13" severity failure;
    assert halted = '0' and fault = '0' severity failure;
    assert probe_instruction = x"60" report "unknown ROM address was accepted" severity failure;
    probe_address <= to_unsigned(15, probe_address'length);
    reset <= '0';
    for cycle in expected_pc'range loop
      edge;
      assert to_integer(address) = expected_pc(cycle) report "program counter differs from trace" severity failure;
      assert to_integer(accumulator) = expected_acc(cycle) report "accumulator differs from trace" severity failure;
      assert fault = '0' report "valid program raised a fault" severity failure;
      if cycle = expected_pc'high then
        assert halted = '1' severity failure;
      else
        assert halted = '0' report "program halted early" severity failure;
      end if;
      if cycle = 0 then
        assert probe_instruction = x"60" report "unused ROM address was accepted" severity failure;
        enable <= '0';
        edge;
        assert address = 1 and accumulator = 3 and instruction = x"31" severity failure;
        enable <= '1';
      end if;
    end loop;
    edge;
    assert address = 4 and accumulator = 0 and halted = '1' and fault = '0' severity failure;
    -- Reset must restart even while execution is disabled and the CPU is halted.
    enable <= '0'; reset <= '1'; edge;
    assert address = 0 and accumulator = 0 and halted = '0' and fault = '0' severity failure;
    reset <= '0'; edge;
    assert address = 0 and accumulator = 0 severity failure;
    enable <= '1'; edge;
    assert address = 1 and accumulator = 3 and halted = '0' severity failure;
    report "Stored program checks passed";
    finish;
    wait;
  end process;
  process
  begin
    wait for 2 us;
    assert false report "Stored program test exceeded its deadline" severity failure;
  end process;
end architecture;
