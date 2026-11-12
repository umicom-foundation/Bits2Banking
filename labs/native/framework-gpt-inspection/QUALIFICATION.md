<!--
Umicom Bits2Banking
File: labs/native/framework-gpt-inspection/QUALIFICATION.md

PURPOSE:
Record installed image-inspection client evidence without conflating source review with execution.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Qualify the installed image client

The source and scenarios are authored. Fill in this record only after running the relevant operation. An expected result is not a recorded pass.

## Identify the inputs

Record the Framework revision and relevant local changes, SDK producer build, installation prefix, compiler version, architecture, Bits2Banking revision and client build directory. Keep the selected Framework configuration path from configuration output or CMakeCache.txt. Confirm the installed target is Umicom::gpt_image.

## Run separate stages

1. Configure using the commands in README.md. An origin or layout refusal is a failed configuration, not a reason to bypass its guards.
2. Build and retain compiler output, including warnings. Stop if compilation or linking fails.
3. List tests with ctest -N in the client build directory. Eight scenarios should be registered when BUILD_TESTING is enabled.
4. Run CTest with --output-on-failure --no-tests=error and retain its exit status.
5. Run selected scenarios directly if diagnosing a failure, preserving their original output.
6. Keep Framework's own GPT parser and media integration results separate from client results.

| Scenario | Expected contract | Actual result and evidence |
| --- | --- | --- |
| valid-512 | Accepted 512-byte profile | Not executed |
| valid-4096 | Accepted 4096-byte profile | Not executed |
| reservation | Parse refusal, unchanged output | Not executed |
| stride | Parse refusal, unchanged output | Not executed |
| overlap | Parse refusal, unchanged output | Not executed |
| backup | Parse refusal, unchanged output | Not executed |
| read-failure | Callback IO error, unchanged output | Not executed |
| retry | Refusal followed by fresh acceptance | Not executed |

A failed producing build can leave older binaries on disk. Verify which files were used before attributing later output to the edited source. An absent test must be investigated; do not record an empty test selection as success.

## Review identity and limits

Inspect the Windows executable's embedded Umicom icon separately from console behavior. Course SVG/ICO paths and font declarations can be checked statically, while actual browser rendering and installed font availability require their own observations.

These scenarios use synthetic memory only. They establish no physical device safety, optical burn, filesystem integrity, publisher authenticity, system installation or successful boot. A different source adapter, concurrent access model or expanded format profile requires additional qualification. Record skipped coverage separately from successful cases.
