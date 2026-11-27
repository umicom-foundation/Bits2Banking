/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ReadingResult.java
 *
 * PURPOSE:
 *   Run the referenced Learning Java exercise.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

public class ReadingResult {
    sealed interface Result permits Accepted, Rejected {}
    record Accepted(int units) implements Result {}
    record Rejected(String reason) implements Result {}

    static Result classify(int units) {
        return units >= 0 ? new Accepted(units) : new Rejected("negative reading");
    }

    static String show(Result result) {
        // Java checks both permitted result types are handled by the switch.
        return switch (result) {
            case Accepted accepted -> "Accepted: " + accepted.units();
            case Rejected rejected -> "Rejected: " + rejected.reason();
        };
    }

    public static void main(String[] args) {
        System.out.println(show(classify(4)));
        System.out.println(show(classify(-1)));
    }
}
