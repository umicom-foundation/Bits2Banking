# Lesson 78 — Encode and Verify Position Sidecars

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Source of truth:** Umicom Framework

## Learning objectives

Explain how a portable binary file differs from a C structure in memory, examine a native checkpoint-compatibility sidecar and verify that its exact bytes match the expected model and inference context.

## 1. Why a sidecar is separate

A trained model checkpoint is an established binary contract. Adding fields inside an existing checkpoint without a versioned migration could invalidate older readers or cause different implementations to interpret the same file differently.

The Framework instead defines a separate **128-byte** positional-compatibility record. A *sidecar* is companion metadata stored outside the trained weight file. It declares permitted use of an existing checkpoint; it does not change a parameter or upgrade the model.

## 2. Fixed bytes, fixed meanings

A C23 structure can contain padding and machine-dependent integer widths, so writing its raw memory to disk would not establish a portable format. The sidecar uses fixed-width unsigned little-endian values at declared offsets:

| Byte range | Purpose |
|---|---|
| 0–7 | Eight-byte format magic (`UMIPOS01`) |
| 8–23 | Format version, positional encoding, context mode, rollover rule |
| 24–43 | Five decoder-shape dimensions |
| 44–47 | Encoded checkpoint size |
| 48–63 | Initial seed and completed optimisation steps |
| 64–95 | SHA-256 digest of the checkpoint bytes |
| 96–127 | SHA-256 digest of sidecar bytes 0–95 |

An unknown revision or nonconforming length must be refused; a reader must not guess. The sidecar digest detects content modifications but does **not** authenticate a sender or sign the record.

## 3. Encode, decode and verify

```c
#include "umicom/ai/training/position_contract.h"

UmiAiTrainingPositionContract record = {0};
UmiAiTrainingPositionContract parsed = {0};
uint8_t bytes[UMI_AI_POSITION_CONTRACT_RECORD_BYTES] = {0};
size_t written = 0U;

UmiStatus status = UmiAiTrainingPositionContractBuild(
    model, UMI_AI_POSITION_CONTEXT_GROWING_UNPADDED, &record);
if (status == UMI_STATUS_OK)
    status = UmiAiTrainingPositionContractEncode(
        &record, bytes, sizeof(bytes), &written);
if (status == UMI_STATUS_OK)
    status = UmiAiTrainingPositionContractDecode(bytes, written, &parsed);
if (status == UMI_STATUS_OK)
    status = UmiAiTrainingPositionContractVerify(
        model, &parsed, UMI_AI_POSITION_CONTEXT_GROWING_UNPADDED);
```

These operations work with caller-owned buffers; they do not select files, contact an external service, or execute generated code. The actual model must already have passed separate source-trust checks.

## 4. Evidence is layered

**Content integrity** asks whether the bytes changed. **Authenticity** asks whether a trusted party approved the bytes. **Numerical parity** asks whether two calculation paths agree. **Performance** asks how long they took under observed conditions. No one check can replace the other three.

An Umicom Studio integration should record model/checkpoint identity and requested context separately, then attach benchmark evidence. The Framework's typed APIs perform validation; graphical applications display outcomes and request permitted operations.

## 5. Negative tests

A useful regression covers record lengths of 127 and 129 bytes, corrupted digests, unsupported positional strategies, altered model weights and mismatched requested contexts. Each rejection must preserve the caller's original result structure or encoded output buffer.

## Practice and answers

1. Why not simply cast raw sidecar bytes to a C structure? **Padding, host endianness and type widths need not match the portable format.**
2. If a user changes a byte and recomputes the unsigned digest, is the sidecar authenticated? **No**; a hash is not a signature.
3. Can valid metadata turn learned absolute-position weights into an already trained RoPE model? **No**; the numerical architecture would change.

[Illustrated HTML lesson](../../courses/llm-from-scratch/lessons/78-write-and-verify-position-sidecars.html) · [Lesson 77: Model and policy identity](77-bind-positions-to-checkpoint-identity.md)
