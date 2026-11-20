<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/03-design-a-small-control-message.md

PURPOSE:
Build and inspect a C23 exercise for bounded messages between execution domains.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Design a small control message

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

Two execution environments may have different address spaces, compilers and CPU architectures. A pointer belongs to the address space that created it. Send defined bytes and identifiers across the boundary. A receiver can then validate the fields before trusting the request. **Byte order** specifies which part of a multibyte number appears first.

## Read the exercise frame

| Offset | Width in bytes | Meaning | Example value |
| --- | --- | --- | --- |
| 0 | 1 | Protocol revision | 1 |
| 1 | 2 | Instance generation, high byte first | 7 |
| 3 | 2 | Request identifier, high byte first | 42 |
| 5 | 1 | Payload length | 3 |
| 6 | 3 | Three numbers for the sample | 7, 11, 24 |

The decoder verifies the header, revision, exact length, current generation and request identity before copying data. In this example it accepts at most eight payload bytes. It leaves the previous result intact after a refusal. The current generation is a value the host has already associated with the peer. The lab uses a local byte array in place of a transport.

## Run the C23 lab

1. Open a terminal at the root of the Bits2Banking checkout. Confirm that CMake, Ninja and a C23 compiler are available on its `PATH`.
2. Configure and build the exercise in its own build folder. Run each command separately and stop on an error.

```powershell
cmake -S content/labs/native/multikernel-message -B build/multikernel-message -G Ninja -DBUILD_TESTING=ON
cmake --build build/multikernel-message
ctest --test-dir build/multikernel-message --output-on-failure --no-tests=error
```

3. Expect seven passed tests. The complete frame produces sum 42. The stale generation, unknown revision, missing request and each length violation have a separate checked outcome.
4. Open `main.c`. Predict what would happen if the test changed the first byte after decoding. Run `multikernel.message.complete` with `ctest -V -R 'multikernel\.message\.complete' --test-dir build/multikernel-message`. The copy still produces sum 42 even after the input changes.

If CMake cannot find a suitable compiler, put its tools on `PATH` or choose it with `-DCMAKE_C_COMPILER=<path>`. Reconfigure into a new folder after changing compilers. If a length case fails, compare the field with the bytes actually supplied before looking at the payload.

For production source reading, compare the structure of this exercise with the existing bounded Framework envelope. It has its own field definitions and stream boundary rules. [Framework envelope format](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/INTEGRATION_ENVELOPE_WIRE_FORMAT.md) · [Original C23 lab](../../../labs/native/multikernel-message/main.c)
