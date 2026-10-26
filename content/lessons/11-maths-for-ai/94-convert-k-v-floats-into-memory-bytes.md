# Mathematics for AI — Unit 94: Convert K/V Floats into Memory Bytes

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Introductory mathematics with practical native C23 AI examples.

## 1. Begin with ordinary numbers

FP32 has four bytes per value. The raw K/V capacity for L layers, C context tokens and D channels is `2*L*C*D*4` bytes. For L=6, C=16 and D=16 this equals 12,288 bytes, or 12 KiB because one KiB is 1,024 bytes. These numbers exclude model weights, activations, allocator metadata and alignment.

The word **tensor** means a structured collection of numbers. In this subject, **layer** identifies one Transformer block, **token** identifies one position in a sequence, and **channel** identifies one numerical feature of that token. `FP32` means a four-byte floating-point value. These definitions let you read a cache diagram without pretending that every number describes an entire language model.

## 2. Translate the mathematics into engineering

Write the quantities on paper first, attach a unit to every count, and check the operation against the native Framework contract. A number described as **float elements** is not interchangeable with a number described as **bytes**; a count of **token-layer rows** is not a count of **seconds**. The Framework's K/V store and conditional prefix planner expose different measurements for this reason.

Where an example contains a digest, remember that an SHA-256 content hash detects changed bytes but is not a signature. Where it contains synthetic tokens or numbers, those are teaching fixtures, not customer or training records.

## 3. Exercise

**Question:** How many raw bytes for four layers, eight tokens and 16 channels?

<details>
<summary>Show the worked answer</summary>

2 * 4 * 8 * 16 * 4 = 4,096 bytes, exactly 4 KiB.

</details>

## 4. Continue

Read [the browser version of this unit](../../courses/maths-for-ai/lessons/94-convert-k-v-floats-into-memory-bytes.html) and [the K/V mathematics learning path](kv-cache-mathematics.md). For the native connection, study [LLM Lesson 185](../10-native-ai/185-own-k-v-rows-for-each-transformer-layer.md) and [LLM Lesson 194](../10-native-ai/194-measure-stored-token-layer-work.md).

*Sammy Hegab · Umicom Foundation · Service to Many Leads to Greatness.*
