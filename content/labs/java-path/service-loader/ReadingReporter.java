/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/service-loader/ReadingReporter.java
 *
 * PURPOSE:
 *   Define the text result provided to the reading report application.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

package learning.readings;

/** The application and its approved provider agree on one output method. */
public interface ReadingReporter {
    String summarize(int total);
}
