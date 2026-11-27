/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ReportTaskDeadline.java
 *
 * PURPOSE:
 *   Observe a wait deadline, request cancellation, and verify worker acknowledgement.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public final class ReportTaskDeadline {
    public static void main(String[] args) throws Exception {
        CountDownLatch started = new CountDownLatch(1);
        CountDownLatch reportReady = new CountDownLatch(1);
        CountDownLatch acknowledged = new CountDownLatch(1);

        try (var executor = Executors.newVirtualThreadPerTaskExecutor()) {
            // The closed gate makes this example exercise a deadline every time.
            Future<String> waiting = executor.submit(() -> {
                started.countDown();
                try {
                    reportReady.await();
                    return "report ready";
                } catch (InterruptedException interruption) {
                    // Tell the caller the worker has actually received the request.
                    Thread.currentThread().interrupt();
                    acknowledged.countDown();
                    throw interruption;
                }
            });

            try {
                if (!started.await(5, TimeUnit.SECONDS)) {
                    throw new IllegalStateException("No worker start reported");
                }

                try {
                    waiting.get(200, TimeUnit.MILLISECONDS);
                    throw new IllegalStateException("The closed report gate returned early");
                } catch (TimeoutException timeout) {
                    System.out.println("Timed out waiting for report");
                }

                // Request interruption separately from the caller's wait deadline.
                if (!waiting.cancel(true) || !acknowledged.await(5, TimeUnit.SECONDS)) {
                    throw new IllegalStateException("No worker acknowledgement");
                }
                System.out.println("Worker acknowledged interruption");

                Future<String> normal = executor.submit(() -> "report ready");
                System.out.println("Normal work returned " + normal.get(5, TimeUnit.SECONDS));
            } finally {
                // Release the gate on an early failure so closing the executor can finish.
                reportReady.countDown();
            }
        }
    }
}
