/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: NativeForecast.java
 *
 * PURPOSE:
 *   Call a trusted Framework-backed calculator with bounded output and timeout.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.*;

public final class NativeForecast {
    private NativeForecast() { }
    public static long net(Path executable, long inflow, long outflow) throws Exception {
        if (!executable.isAbsolute() || !Files.isRegularFile(executable) || inflow < 0 || outflow < 0)
            throw new IllegalArgumentException("An absolute trusted executable and nonnegative amounts are required");
        // Arguments never pass through a shell. Framework owns the calculation.
        Process process = new ProcessBuilder(executable.toString(), Long.toString(inflow), Long.toString(outflow))
            .redirectError(ProcessBuilder.Redirect.INHERIT).start();
        ExecutorService reader = Executors.newSingleThreadExecutor(runnable -> {
            Thread thread = new Thread(runnable, "forecast-output");
            thread.setDaemon(true);
            return thread;
        });
        Future<String> output = reader.submit(() -> {
            try (InputStream input = process.getInputStream(); ByteArrayOutputStream bytes = new ByteArrayOutputStream()) {
                int ch;
                while ((ch = input.read()) != -1) {
                    if (bytes.size() == 128) throw new IOException("Native output exceeds protocol limit");
                    bytes.write(ch);
                }
                return new String(bytes.toByteArray(), StandardCharsets.US_ASCII);
            }
        });
        try {
            process.getOutputStream().close();
            if (!process.waitFor(10, TimeUnit.SECONDS)) throw new TimeoutException("Native forecast timed out");
            if (process.exitValue() != 0) throw new IOException("Native forecast exit " + process.exitValue());
            String text = output.get(2, TimeUnit.SECONDS);
            if (!text.matches("-?(0|[1-9][0-9]*)\r?\n")) throw new IOException("Invalid native amount response");
            return Long.parseLong(text.trim());
        } catch (InterruptedException interrupted) {
            Thread.currentThread().interrupt();
            throw interrupted;
        } finally {
            if (process.isAlive()) process.destroyForcibly();
            try {
                process.getInputStream().close();
            } finally {
                // Release the reader even if stream cleanup reports an error.
                output.cancel(true);
                reader.shutdownNow();
            }
        }
    }
}
