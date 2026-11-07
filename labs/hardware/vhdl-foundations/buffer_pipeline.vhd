-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/buffer_pipeline.vhd
--
-- PURPOSE:
--   Compose two existing ready/valid buffers without duplicating their storage rules.
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

entity buffer_pipeline is
    port (clk, reset : in std_logic;
          input_valid : in std_logic; input_ready : out std_logic;
          input_word : in std_logic_vector(7 downto 0);
          output_valid : out std_logic; output_ready : in std_logic;
          output_word : out std_logic_vector(7 downto 0));
end entity;

architecture composition of buffer_pipeline is
    signal middle_valid, middle_ready : std_logic;
    signal middle_word : std_logic_vector(7 downto 0);
begin
    -- The existing buffer owns each storage slot. Connecting ready in the
    -- reverse direction propagates downstream capacity to the producer.
    first_stage : entity work.lesson_buffer
        port map (clk => clk, reset => reset,
                  input_valid => input_valid, input_ready => input_ready,
                  input_word => input_word, output_valid => middle_valid,
                  output_ready => middle_ready, output_word => middle_word);
    second_stage : entity work.lesson_buffer
        port map (clk => clk, reset => reset,
                  input_valid => middle_valid, input_ready => middle_ready,
                  input_word => middle_word, output_valid => output_valid,
                  output_ready => output_ready, output_word => output_word);
end architecture;
