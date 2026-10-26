# Unit 70 — Calculate capacity for streamed Unicode scalars

**Mathematics for AI · Umicom Foundation**  
**Author:** Sammy Hegab

## Work from a small example

A complete UTF-8 Unicode scalar occupies between one and four bytes. An incremental validator can buffer at most three bytes of an incomplete scalar before receiving the fourth. To publish the complete scalar when it finishes, a caller-owned output buffer needs capacity for **four bytes**.

## Why the calculation matters

If a three-byte scalar completes while the caller advertises only two output bytes, a failure-atomic API must refuse the operation without changing the stream or caller output. Applications should use the returned length because `U+0000` can be a valid scalar represented by a zero byte; it is not necessarily a text terminator.

The demonstration is about byte lengths and numerical capacity. It does not authorise rendering generated HTML, executing returned commands or importing unreviewed text for training.

## Practice

**Question:** A caller allocates `uint8_t output[4]` and receives a completed three-byte scalar. How many bytes remain unused?

<details><summary>Reveal the worked solution</summary>

`4−3=1` byte remains unused. The caller must still use the reported output length of three.

</details>

## Continue

Read [native LLM lesson 157](../10-native-ai/157-stream-generated-utf8-with-native-c23.md) and the earlier [byte tokenizer course](../10-native-ai/03-tokens-vocabulary-and-encoding.md).
