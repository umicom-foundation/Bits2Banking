/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ReportCounts.java
 *
 * PURPOSE:
 *   Update two shared report counts together and copy them into a snapshot.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

public final class ReportCounts {
    private static final int PAGES_PER_REPORT = 2;

    record Snapshot(int reports, int pages) {
    }

    private int reports;
    private int pages;

    synchronized void recordReport() {
        // The same object lock protects both changes in one operation.
        reports++;
        pages += PAGES_PER_REPORT;
    }

    synchronized Snapshot snapshot() {
        // Copy both values while the owner holds the lock used by writers.
        return new Snapshot(reports, pages);
    }

    private static void recordReports(ReportCounts owner, int count) {
        for (int index = 0; index < count; index++) {
            owner.recordReport();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        ReportCounts owner = new ReportCounts();
        Snapshot opening = owner.snapshot();

        Thread first = new Thread(() -> recordReports(owner, 2));
        Thread second = new Thread(() -> recordReports(owner, 3));
        first.start();
        second.start();

        Snapshot sample = owner.snapshot();
        System.out.println("Sample consistent = " + (sample.pages() == sample.reports() * PAGES_PER_REPORT));

        first.join();
        second.join();

        Snapshot result = owner.snapshot();
        System.out.println("Final reports = " + result.reports() + ", pages = " + result.pages());
        System.out.println("Opening snapshot still shows " + opening.reports() + " reports and "
                + opening.pages() + " pages.");
    }
}
