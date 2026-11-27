<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/21-verify-a-java-and-c23-file-contract.md

PURPOSE:
  Teach verify a Java and C23 file contract with a small runnable example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

# Verify a Java and C23 file contract

A Java report and a native C23 tool can agree on the same small file. The agreement is a contract that each program can check. It specifies the bytes accepted, the output and the result of invalid input.

Complete the previous lesson before trying this one. Use the same JDK and a writable practice folder.

## Try it

1. Save the two programs and the `usage-rows.txt` fixture together. The fixture uses the ASCII digits 12, 8 and 3, each followed by an LF line break.
2. Compile Java and C23 separately. Run both on the same file and compare the entire output line.
3. Make another fixture with a letter on one line. Both programs should report `Invalid usage data` on their error stream and return failure.
4. Try a copy missing its final LF. Then try a file with more than 64 bytes. Verify both programs reject those cases. Keep the original test fixture unchanged for your next run.

## Example files

### UsageSummary.java

[Open UsageSummary.java](../../../labs/java-path/UsageSummary.java)

~~~java
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class UsageSummary {
    static int summarize(Path file) throws IOException {
        byte[] bytes;
        // Read one byte past the teaching limit so a full prefix cannot pass.
        try (var input = Files.newInputStream(file)) {
            bytes = input.readNBytes(65);
        }
        if (bytes.length == 0 || bytes.length > 64) {
            throw new IllegalArgumentException("Invalid usage data");
        }
        int total = 0;
        int value = 0;
        int digits = 0;
        // Define the portable file format with ASCII bytes and LF line breaks.
        for (byte current : bytes) {
            if (current >= '0' && current <= '9' && digits < 2) {
                value = value * 10 + current - '0';
                digits++;
            } else if (current == '\n' && digits != 0) {
                total += value;
                value = 0;
                digits = 0;
            } else {
                throw new IllegalArgumentException("Invalid usage data");
            }
        }
        if (digits != 0) {
            throw new IllegalArgumentException("Invalid usage data");
        }
        return total;
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: provide one input file");
            System.exit(2);
        }
        try {
            System.out.println("Total: " + summarize(Path.of(args[0])));
        } catch (IllegalArgumentException error) {
            System.err.println("Invalid usage data");
            System.exit(1);
        } catch (IOException error) {
            System.err.println("Could not read usage data");
            System.exit(1);
        }
    }
}
~~~

### usage_summary.c

[Open usage_summary.c](../../../labs/java-path/usage_summary.c)

~~~c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("Usage: provide one input file\n", stderr);
        return 2;
    }
    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        fputs("Could not read usage data\n", stderr);
        return EXIT_FAILURE;
    }

    /* Read one byte past the format limit and close before parsing. */
    unsigned char bytes[65];
    size_t length = fread(bytes, 1, sizeof bytes, input);
    int failed = ferror(input);
    if (fclose(input) == EOF || failed) {
        fputs("Could not read usage data\n", stderr);
        return EXIT_FAILURE;
    }
    if (!length || length > 64) {
        fputs("Invalid usage data\n", stderr);
        return EXIT_FAILURE;
    }

    /* Each LF commits one integer. A final partial line is invalid. */
    int total = 0, value = 0, digits = 0;
    for (size_t index = 0; index < length; ++index) {
        unsigned char current = bytes[index];
        if (current >= '0' && current <= '9' && digits < 2) {
            value = value * 10 + current - '0';
            ++digits;
        } else if (current == '\n' && digits != 0) {
            total += value;
            value = 0;
            digits = 0;
        } else {
            fputs("Invalid usage data\n", stderr);
            return EXIT_FAILURE;
        }
    }
    if (digits != 0) {
        fputs("Invalid usage data\n", stderr);
        return EXIT_FAILURE;
    }
    printf("Total: %d\n", total);
    return EXIT_SUCCESS;
}
~~~

### usage-rows.txt

[Open usage-rows.txt](../../../labs/java-path/usage-rows.txt)

~~~text
12
8
3
~~~

## Run it

~~~text
javac --release 21 UsageSummary.java
gcc -std=c23 -Wall -Wextra -Wpedantic usage_summary.c -o usage-summary
java -cp . UsageSummary usage-rows.txt
./usage-summary usage-rows.txt
~~~

The program output to check is shown below.

~~~text
Total: 23
Total: 23
~~~

## Read the result

The programs accept 1–64 bytes with one or two decimal digits per line and an LF after every line. They read one extra byte to detect excess data, then add a number only after its LF arrives. Pseudocode is `read at most 65 bytes → verify size → for each line verify digits and LF → add the verified value → print total`. On Windows you can compile the C output with `-o usage-summary.exe` and run `.\usage-summary.exe usage-rows.txt` in PowerShell. Bytes, status and output are the shared interface. A native Umicom client could implement this kind of adapter at an explicitly documented file boundary.

## Practise

Create a valid fixture that totals 20 in three lines. Check Java and C against the same expected output. Save the invalid cases separately and include both the expected error text and exit status in your checks.

## Fix a problem

Save or download the supplied LF fixture unchanged. If copied text has CRLF line endings, use the editor’s LF line-ending setting for this specific format. Check `gcc --version` if the compiler does not recognise `-std=c23`.

## Reference

- [Java byte stream API](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/io/InputStream.html)
- [Earlier checked translation exercise](10-check-a-c-java-translation.md)

[Previous · Package a report as a module](20-package-a-report-as-a-module.md) · [Next · Records and a journal](01-records-and-a-journal.md)
