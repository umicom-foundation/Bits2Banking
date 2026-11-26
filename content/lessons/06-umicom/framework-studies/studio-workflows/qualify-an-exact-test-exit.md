![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom icon](../../../../assets/branding/umicom.ico)

# Test an exact process result

[Previous lesson](trace-a-native-library-link.md) · [Next lesson](compare-a-recorded-artifact-identity.md)

A process returns an exit code when it finishes. A test for a deliberate refusal must distinguish that refusal from an unrelated launch error, timeout or output failure.

An exit code belongs to the process that was actually launched. It does not describe a command that was only planned or an executable a build did not produce. CTest records the result of the wrapper. The wrapper records whether the child met the expectation.

The evidence program reserves 1 for output failure. Its other statuses distinguish agreement, a different valid digest and invalid text. A test that only accepts any nonzero exit would confuse these outcomes. Compare the exact exit result of the child with the expected value.

The wrapper also separates standard output and standard error. The usage case deliberately puts its message on standard error. A message in the wrong stream indicates a different interface even if the numeric exit is correct.

Run the focused filter and read each result before reading the final count. Select one case and explain whether the child succeeded or correctly refused and why the test itself passed. Avoid counting an unlaunched process as a failed assertion.

As an exercise, copy the wrapper to a separate build directory and change the expected code for the different case from 2 to 3. Run only that copied check. It should fail at the comparison. Keep the shipped wrapper available so you can return to the correct expectation.

## Repeat the exercise

```powershell
ctest --test-dir build/studio-evidence --output-on-failure --no-tests=error
ctest --test-dir build/studio-evidence --output-on-failure -R "^bits[.]studio[.]evidence[.](different|malformed|usage)$"
```

The refusal cases pass when the program gives the precise expected status and message. A run that cannot find the executable stops separately. A failure test passes because the expected refusal occurred.

If CTest reports no tests, check the build directory and confirm BUILD_TESTING is enabled. If the executable cannot be launched, build the named target successfully before interpreting test assertions.

[Back to course](../../../../courses/framework-and-finance/studio-workflows/index.html)
