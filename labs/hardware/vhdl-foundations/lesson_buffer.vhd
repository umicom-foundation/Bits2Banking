-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/lesson_buffer.vhd
--
-- PURPOSE:
--   Keep one data word stable until a ready/valid transfer accepts it.
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
entity lesson_buffer is
    port (clk, reset : in std_logic;
          input_valid : in std_logic; input_ready : out std_logic;
          input_word : in std_logic_vector(7 downto 0);
          output_valid : out std_logic; output_ready : in std_logic;
          output_word : out std_logic_vector(7 downto 0));
end entity;
architecture rtl of lesson_buffer is
    signal full : std_logic;
    signal can_accept : std_logic;
    signal held_word : std_logic_vector(7 downto 0);
begin
    -- Reset suppresses advertised transfers; state clears at the clock edge.
    can_accept <= (not full or output_ready) and not reset;
    input_ready <= can_accept;
    output_valid <= full and not reset;
    output_word <= held_word;
    process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                full <= '0';
                held_word <= (others => '0');
            elsif can_accept = '1' then
                full <= input_valid;
                if input_valid = '1' then
                    held_word <= input_word;
                end if;
            end if;
        end if;
    end process;
end architecture;

