# Mathematics for AI — Unit 38: Binary Layouts and Safe Capacity

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Why byte counts are part of correct mathematics

A training model may be mathematically correct but still fail if its binary record uses the wrong number of bytes. Native C23 distinguishes counts of elements from counts of bytes. An array of 50 `float` values on an IEEE-754 binary32 machine occupies `50×4 = 200` value bytes, excluding any metadata.

A portable snapshot needs a specified encoding. Its header uses explicit integer widths, the payload uses stable per-projection encodings and its trailer contains a 32-byte SHA-256. It never writes uninitialised C structure padding.

## Calculate a combined checkpoint size

Suppose a simplified record contains a 112-byte header, two child payloads of 200 and 120 bytes, and a 32-byte digest. Each child also has a four-byte length field. The complete record needs:

`total = 112 + (4+200) + (4+120) + 32 = 472 bytes`.

A destination array of 471 bytes is too small. A correct encoder returns a capacity error **without altering the array**; a caller should first ask the Framework's size service for the exact requirement.

## Why overflow checks happen before multiplication

A shape with `rows` and `columns` requires `rows×columns` elements. In native unsigned arithmetic, multiplication can wrap when the result exceeds `SIZE_MAX`. A safe check can first confirm `rows <= SIZE_MAX / columns` for a nonzero `columns`. Only then is it safe to calculate the product and compare it with the Framework's separate tensor element limit.

A second check is needed when multiplying element count by bytes per element. Avoid silently assuming `size_t` has the same width on all supported platforms.

## Do not confuse integer and floating-point rules

Token IDs, file lengths, cryptographic digests and cursor indices require exact comparisons. Floating-point training losses usually require specified numerical tolerances across different implementations. A SHA-256 hash should **never** be compared using a floating-point tolerance: either its exact byte sequence matches or it does not.

## Practise

1. A 32-byte digest has how many bits? `32×8 = 256`. 2. A buffer holds 300 bytes and the encoded file needs 304. What should the encoder do? Reject without mutation. 3. A 9×9 FP32 matrix needs how many value bytes? `81×4 = 324`.

The production code for capacity validation and format checks belongs in Umicom Framework. The mathematical examples here are deliberately small and inspectable.

**Continue:** [portable snapshot lesson](../10-native-ai/96-build-portable-snapshot-records.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
