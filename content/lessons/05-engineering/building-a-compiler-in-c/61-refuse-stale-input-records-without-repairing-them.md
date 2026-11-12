<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/61-refuse-stale-input-records-without-repairing-them.md

PURPOSE:
Refuse stale input records without repairing them

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Refuse stale input records without repairing them

A checker should report a mismatch without overwriting the evidence that made the mismatch visible. Otherwise “verify” can quietly become “accept whatever is present.” The Umicom C input checker keeps those operations separate.

## Trace the two paths

Capture runs during standalone configuration. Verification reads the stored object, takes a current observation, and compares canonical bytes. It has no file-writing branch. Missing, malformed or changed evidence is a failure, not permission to capture a replacement.

Read tests/check_input_identity.cmake. Each case creates a new synthetic directory beneath the test build directory. A fake compiler file supplies bytes to hash; the test never executes it. This lets the suite exercise tool changes without damaging the installed compiler.

## Run the mutation cases

After configuring your Umicom C checkout:

~~~powershell
ctest --test-dir build/windows-ucrt64-debug -R '^umicom.c.input-identity.' --output-on-failure --no-tests=error
~~~

The source case changes 1 to 2 without changing the source file length. The renamed-source case retains the contents but changes the path. Both must fail the nested verifier. The outer regression passes only when that refusal is observed and the receipt remains byte-for-byte unchanged.

## Predict the boundary

The prose-outside-scope case writes ordinary documentation. The binary-outside-scope case creates an executable-shaped file in the output directory. Both are expected to leave this configuration-input check successful. Those results demonstrate its declared limits. In particular, a successful input check does not authorize running an unverified executable.

## Perform a controlled stale check

1. Work in an experimental checkout with your changes already preserved.

2. Configure once and keep a copy of the generated record.

3. Add a comment to an example under examples.

4. Run only the existing-record check:

~~~powershell
ctest --test-dir build/windows-ucrt64-debug -R '^umicom.c.inputs-current$' --output-on-failure --no-tests=error
~~~

5. Expect a mismatch. Review the edit, then explicitly reconfigure, rebuild and rerun tests. Do not modify a stored checksum by hand.

The build convenience target can trigger CMake regeneration before it calls the verifier. Use the CTest command for a stale-record investigation because it does not request a build or configure step.

## Explain the result

A passing regression can contain an intentionally failing child command. Read which layer reported success. If the nested checker crashes or times out instead of issuing a diagnostic refusal, the regression must fail. Keep both the result code and diagnostic output; an arbitrary nonzero status alone is weak evidence.

[Course contents](index.md) · [Previous lesson](60-record-configuration-inputs-with-honest-limits.md) · [Next lesson](62-keep-template-looking-text-as-data.md)
