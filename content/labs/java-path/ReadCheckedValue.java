/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: content/labs/java-path/ReadCheckedValue.java
 *
 * PURPOSE:
 *   Report an expected input error returned by a task before advertising success.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;

public class ReadCheckedValue {
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        System.exit(run(args));
    }

    private static int run(String[] args) throws InterruptedException, ExecutionException {
        if (args.length != 1) {
            System.err.println("Give one reading.");
            return 2;
        }

        // Finish and close the executor before publishing the command's exit code.
        try (var worker = Executors.newVirtualThreadPerTaskExecutor()) {
            var reading = worker.submit(() -> Integer.parseInt(args[0]));
            try {
                System.out.println("Reading: " + reading.get());
                return 0;
            } catch (ExecutionException failure) {
                // Give an actionable message for the input error this task expects.
                if (failure.getCause() instanceof NumberFormatException) {
                    System.err.println("Enter a whole number that fits in a Java int.");
                    return 1;
                }
                throw failure;
            }
        }
    }
}
