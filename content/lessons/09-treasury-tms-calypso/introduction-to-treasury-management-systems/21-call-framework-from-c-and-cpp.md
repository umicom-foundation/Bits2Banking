# Call the Framework treasury contract from C and C++

## Read the boundary

C is the primary implementation language of Umicom Framework. Its public cash-forecast header has a C linkage guard so a C++ consumer can call the same functions. C++ is used here to demonstrate integration, not to replace the service.

Open forecast.c and forecast_cpp.cpp in the [native laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/treasury-framework-bridge). The C program accepts two decimal command arguments. Its parser accepts ASCII digits only and checks overflow before multiplying by ten. The C++ program supplies a fixed, explained fixture.

## Follow one request

For arguments 125000 and 140000, parsing produces two nonnegative int64 values. Framework initialization validates its record, and the existing net operation returns -15000. stdout contains one decimal line; diagnostics go to stderr. Exit status zero means that this invocation completed, not that a financial operation settled.

For 9223372036854775808, the parser must refuse before conversion because the value exceeds INT64_MAX. For -1, the sign violates this input contract even though a net result may be negative.

## Build and inspect

Follow the lab README's installed-SDK commands. CMake finds UmicomFramework with the finance component and links Umicom::finance. Do not compile copied Framework .c files into a parallel local engine. If the package is missing, fix the installation path; if linking fails, compare compiler, architecture and runtime.

The authored CTest contract checks valid limits and malformed input through the executable. It has not been run for this delivery.

## Exercise and answer

Why can net be negative while inflow and outflow must be nonnegative? Answer: each input represents a gross magnitude. The difference expresses direction. Allowing negative outflow would introduce a second sign convention and could reverse its meaning.

## Recovery

If a test prints the expected number but exits nonzero, preserve both facts. Output does not erase an error. If the C++ build fails while C succeeds, inspect the compiler/linkage boundary before altering treasury logic. An installed-consumer failure can reveal packaging or ABI problems unrelated to the financial formula.

[Course contents](index.md)
