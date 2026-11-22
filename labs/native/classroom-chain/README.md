![Umicom Foundation](../../../content/assets/branding/umicom-wordmark.svg)

# Classroom proof-of-work chain

This native C23 exercise keeps a small synthetic ledger in memory. It writes each block into a canonical 60-byte format and uses the existing Framework SHA-256 source to generate and verify fingerprints. It accepts one transfer and a fixed two-unit reward per block, checks whole histories and compares the work of valid branches. The fixed target accepts a digest beginning with a zero byte, and the maximum history contains 12 blocks.

Read the [written course](../../../content/lessons/14-blockchain-ledgers/classroom-chain/index.md) for an opening-balance trace, a byte worksheet and optional language exercises. The example demonstrates a classroom consensus idea and does not operate as a Bitcoin node, wallet, exchange or transferable currency.

## Build and verify

From the Bits2Banking root, select a C23 compiler and Ninja, then run:

```powershell
$framework = (Resolve-Path '../Umicom-Applications/framework').Path
cmake -S labs/native/classroom-chain -B build/classroom-chain -G Ninja "-DUMICOM_FRAMEWORK_SOURCE:PATH=$framework" -DBUILD_TESTING=ON
cmake --build build/classroom-chain
ctest --test-dir build/classroom-chain --output-on-failure --no-tests=error
```

If your Framework checkout is in a different location, use its absolute path on the configure command. The lab consumes the shared digest source directly, so you do not need to install the Framework SDK for this exercise.

The tests check known proof bytes, value conservation and issuance, argument and budget refusal, tampering, valid fork choice and the demonstration output. To include the Assembly parity fixture, add `-DCLASSROOM_ENABLE_X86_64_ASM=ON` while configuring with a compatible x86-64 GNU-style toolchain. The separate `check_target.d` lesson uses the C static library with a matching Linux D toolchain. See the [language boundary exercise](../../../content/lessons/14-blockchain-ledgers/classroom-chain/03-connect-assembly-d-and-gtk4.md).

The accepted demonstration branch finishes with three blocks, A = 9, B = 5, C = 4 and 18 total classroom units. An altered proof preserves the previous accepted state. The default lab does not need any network services or personal data.

[SVG icon](../../../content/assets/branding/umicom-icon.svg) · [Windows icon](../../../content/assets/branding/umicom.ico)
