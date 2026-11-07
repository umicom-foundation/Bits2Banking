-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/hardware/vhdl-foundations/buffer_pipeline_tb.vhd
--
-- PURPOSE:
--   Check ordered transfers, backpressure and bounded occupancy with an independent scoreboard.
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

entity buffer_pipeline_tb is end entity;
architecture checks of buffer_pipeline_tb is
    signal clk : std_logic := '0';
    signal reset : std_logic := '1';
    signal input_valid, input_ready, output_valid, output_ready : std_logic := '0';
    signal input_word, output_word : std_logic_vector(7 downto 0) := (others => '0');
begin
    clk <= not clk after 5 ns;
    dut : entity work.buffer_pipeline
        port map (clk, reset, input_valid, input_ready, input_word,
                  output_valid, output_ready, output_word);
    process
        type words is array (0 to 63) of natural range 0 to 255;
        variable expected : words := (others => 0);
        variable sent, received : natural := 0;
        variable accept_input, accept_output, stalled : boolean;
        variable observed : std_logic_vector(7 downto 0);
    begin
        wait until rising_edge(clk); wait for 1 ns;
        assert output_valid = '0' report "reset did not empty pipeline" severity failure;
        reset <= '0';
        for cycle in 0 to 199 loop
            wait until falling_edge(clk);
            if sent < 64 then
                input_valid <= '1';
                input_word <= std_logic_vector(to_unsigned(sent, 8));
            else
                input_valid <= '0';
            end if;
            if cycle mod 5 < 3 then output_ready <= '1';
            else output_ready <= '0'; end if;
            -- Snapshot the handshake before the active edge. A value
            -- observed after the edge can belong to the next transfer.
            wait for 1 ns;
            accept_input := input_valid = '1' and input_ready = '1';
            accept_output := output_valid = '1' and output_ready = '1';
            stalled := output_valid = '1' and output_ready = '0';
            observed := output_word;
            if accept_output then
                assert received < sent report "output without accepted input" severity failure;
                assert to_integer(unsigned(observed)) = expected(received)
                    report "lost, duplicated or reordered word" severity failure;
                received := received + 1;
            end if;
            if accept_input then
                expected(sent) := sent;
                sent := sent + 1;
            end if;
            assert sent >= received and sent - received <= 2
                report "pipeline occupancy exceeded storage" severity failure;
            wait until rising_edge(clk); wait for 1 ns;
            if stalled then
                assert output_valid = '1' and output_word = observed
                    report "stalled output changed" severity failure;
            end if;
            exit when received = 64;
        end loop;
        assert sent = 64 and received = 64 report "pipeline did not drain within budget" severity failure;
        assert output_valid = '0' report "extra output after drain" severity failure;
        report "Pipeline scoreboard checks passed" severity note;
        finish;
        wait;
    end process;
end architecture;
