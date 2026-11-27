/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/first-package/src/training/readings/Reading.java
 *
 * PURPOSE:
 *   Store the site and units for a small reading report.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

package training.readings;

// The report and its data type share a package so they can grow together.
public record Reading(String site, int units) {}
