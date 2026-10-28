# Native Federated Authentication Laboratory

**Bits2Banking · Umicom Foundation · Sammy Hegab · MIT**

## Aim

Trace how a **valid UMFW frame** becomes an **HMAC-authenticated UMFA frame** while the existing Umicom Framework continues to own SHA-256, job admission, weighted aggregation and message contracts. The learner writes no independent cryptographic primitives and does not use a scripting runtime.

## Steps

1. Read LLM Lessons 425–432 and Mathematics Units 269–272.
2. Build the native laboratory with the checked-out Framework root supplied as `UMICOM_FRAMEWORK_SOURCE` through CMake. The library and all its dependencies are brought in through Framework's own CMake modules.
3. Observe successful round-trip and the byte count for one scalar: 184 + 4 + 32 + 20 + 32 = **272 bytes**.
4. Flip one byte in the authenticated payload. The HMAC verification must reject before changing `observed`.
5. Compare with the Framework tests for wrong keys, epoch changes, long HMAC keys, malformed inner checksums and local ticket replay.
6. Record which assurances are NOT present: no transport encryption, key-service enrolment, source-rights approval, multi-host network execution, durable retry state or true model-quality evaluation.

The embedded key is **synthetic and deliberately unsuitable for deployment**. Use a proper secret-management provider for real work. Existing third-party research scripts may be retained as alternatives, but this implementation is native C23.

## Further reading

- [RFC 4231 test vectors](https://www.rfc-editor.org/rfc/rfc4231.html)
- [HMAC standard RFC 2104](https://www.rfc-editor.org/rfc/rfc2104.html)
- [FedAvg](https://proceedings.mlr.press/v54/mcmahan17a.html)
