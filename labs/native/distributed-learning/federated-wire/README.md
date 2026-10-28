# Federated-wire laboratory — native C23 consumer

**Bits to Banking · Sammy Hegab · Umicom Foundation · MIT**

## Learning objective

Inspect the difference between an ordinary C structure, a portable binary
message, an authenticated sender and a mathematically useful model update.
The lab calls the real **Umicom Framework** C23 `federated_wire` functions;
there is no duplicate hash, training algorithm, message parser or FedAvg
implementation in Bits2Banking.

### Build the small laboratory

The learning exercise is built using CMake and Ninja against a checked-out
Framework containing `cmake/UmicomAiFederatedWire.cmake`:

```text
cmake -S labs/native/distributed-learning/federated-wire -B build/federated-wire -G Ninja -DUMICOM_FRAMEWORK_SOURCE=<framework-source-path> -DBUILD_TESTING=ON
cmake --build build/federated-wire
ctest --test-dir build/federated-wire --output-on-failure
```

Use the actual path on your machine in place of `<framework-source-path>`.
These are educational build commands; repository publication and Git operations
are unrelated to the laboratory.

## Explore

An assignment contains only metadata and a checksum. The bounded result
contains one finite FP32 value. The correct output is:

```text
C23 lab: assignment 216 bytes, synthetic result 220 bytes, identity and Framework envelope verified
```

Corrupt one byte of a generated frame and verify that `Decode` fails and its
output remains unchanged. Try a zero sample count or an invalid base digest
and explain why the parser refuses the request. Next, explain why a forged
message with a recomputed checksum is still a threat: **SHA-256 is not an
identity signature**.

A passing test proves only structural behaviour and the integrity of this
deterministic exercise; no network authentication, genuine gradient training,
privacy guarantee, blockchain or performance improvement is claimed.
