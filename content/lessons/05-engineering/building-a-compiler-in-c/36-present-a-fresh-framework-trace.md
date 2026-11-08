<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/36-present-a-fresh-framework-trace.md

PURPOSE:
Present a fresh Framework trace

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Present a fresh Framework trace

## Setup recap

Read Framework docs/learning/cvm-preview.md and the new cvm_trace.h header. This is an optional source-composed adapter using an installed Umicom C SDK. Build and install the updated SDK before configuring the separate Framework example; the main Framework SDK does not automatically enable this service.

## Translate ownership into presentation state

The runtime leaves an output result unchanged when execution fails. That is useful for a low-level contract, but a screen must not display an old success as the new answer. Framework owns this presentation decision: after validating storage sizes, it clears the previous success and numeric result, sets the phase to compiling, and resets the trace count.

umi_cvm_preview_traced accepts the existing workspace and result plus a sized UmiCvmPreviewTrace. It compiles through Umicom C, changes the phase to executing, and delegates to umc_execute_trace. It sets complete only after the runtime succeeds. No parser or evaluator is copied into the adapter.

## Read a failed request correctly

A syntax failure leaves phase compiling and trace count zero. An arithmetic or fuel failure leaves phase executing and retains the completed and rejected rows. A valid storage-size mismatch leaves every supplied object unchanged because the adapter has not accepted a new request. These cases need different presentation messages.

The old umi_cvm_preview API still works without trace storage. Both APIs use the same request lifecycle and status translation. Consumers must use status and completed together, and must not read trace entries at or beyond count.

## Exercise

These cases are represented in test_cvm_trace.c. They are adapter checks, not evidence of a Studio debugger panel. A future UI still needs document-revision handling, approved layout integration and its own interaction qualification.

1. Start with a successful four-instruction preview and note result 42.
2. Submit malformed source into the same objects. Predict count zero and completed false.
3. Submit valid source with fuel zero. Predict one attempted step and no completed result.
4. Repeat using a separate workspace, result and trace to check that the first set is unaffected.

## Read the source

[Umicom-Applications/framework/src/toolchain/cvm_preview.c](https://github.com/umicom-foundation/umicom-framework/blob/main/src/toolchain/cvm_preview.c). Read the matching checkout when qualifying your own build.

## Continue learning

[Course contents](index.md) · [Previous: Compare source and bytecode traces](35-compare-source-and-bytecode-traces.md) · [Next: Qualify a freestanding trace](37-qualify-a-freestanding-trace.md)
