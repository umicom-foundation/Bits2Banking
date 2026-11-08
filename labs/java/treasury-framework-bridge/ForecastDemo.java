/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: ForecastDemo.java
 *
 * PURPOSE:
 *   Demonstrate Java consumption of the native Framework treasury calculator.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import java.nio.file.Paths;
public final class ForecastDemo {
    public static void main(String[] args) throws Exception {
        if (args.length != 1) throw new IllegalArgumentException("Supply the absolute treasury-forecast path");
        long net = NativeForecast.net(Paths.get(args[0]), 125000, 140000);
        if (net != -15000) throw new AssertionError("Unexpected funding gap");
        System.out.println(net);
    }
}
