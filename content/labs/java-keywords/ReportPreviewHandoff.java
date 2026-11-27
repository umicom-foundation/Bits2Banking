/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-keywords/ReportPreviewHandoff.java
 *
 * PURPOSE:
 *   Publish one immutable report preview from a worker to its reader.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

public final class ReportPreviewHandoff {
    private record Preview(String heading, int rows) {
    }

    private volatile Preview latest;

    private void publishPreview() {
        // Publish the heading and count together through one reference.
        latest = new Preview("Daily readings", 3);
    }

    public static void main(String[] args) throws InterruptedException {
        ReportPreviewHandoff handoff = new ReportPreviewHandoff();
        System.out.println("Before publication " + handoff.latest);

        Thread worker = new Thread(handoff::publishPreview);
        worker.start();

        // Observe the volatile field before waiting for the worker to finish.
        Preview published = handoff.latest;
        for (int attempt = 0; published == null && attempt < 500; attempt++) {
            Thread.sleep(10);
            published = handoff.latest;
        }
        worker.join();

        if (published == null) {
            throw new IllegalStateException("The worker took too long to publish the preview.");
        }
        System.out.println("Published heading " + published.heading());
        System.out.println("Published row count " + published.rows());
    }
}
