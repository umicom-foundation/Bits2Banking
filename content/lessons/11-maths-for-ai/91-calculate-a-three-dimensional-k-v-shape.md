# Mathematics for AI — Unit 91: Calculate a Three-Dimensional K/V Shape

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Introductory mathematics with practical native C23 AI examples.

## 1. Begin with ordinary numbers

For a tensor with L layers, T tokens and D channels, one K tensor contains `L*T*D` floats. V doubles the count. With L=3, T=4 and D=4, each has 48 floats. Both together have 96 floats, or 384 bytes in FP32. This is the same simple multiplication rule used in an ordinary table, just with one more dimension.

The word **tensor** means a structured collection of numbers. In this subject, **layer** identifies one Transformer block, **token** identifies one position in a sequence, and **channel** identifies one numerical feature of that token. `FP32` means a four-byte floating-point value. These definitions let you read a cache diagram without pretending that every number describes an entire language model.

## 2. Translate the mathematics into engineering

Write the quantities on paper first, attach a unit to every count, and check the operation against the native Framework contract. A number described as **float elements** is not interchangeable with a number described as **bytes**; a count of **token-layer rows** is not a count of **seconds**. The Framework's K/V store and conditional prefix planner expose different measurements for this reason.

Where an example contains a digest, remember that an SHA-256 content hash detects changed bytes but is not a signature. Where it contains synthetic tokens or numbers, those are teaching fixtures, not customer or training records.

## 3. Exercise

**Question:** If L=2, T=5 and D=8, how many raw FP32 bytes hold both K and V?

<details>
<summary>Show the worked answer</summary>

2 * 2 * 5 * 8 * 4 = 320 bytes.

</details>

## 4. Continue

Read [the browser version of this unit](../../courses/maths-for-ai/lessons/91-calculate-a-three-dimensional-k-v-shape.html) and [the K/V mathematics learning path](kv-cache-mathematics.md). For the native connection, study [LLM Lesson 185](../10-native-ai/185-own-k-v-rows-for-each-transformer-layer.md) and [LLM Lesson 194](../10-native-ai/194-measure-stored-token-layer-work.md).

*Sammy Hegab · Umicom Foundation · Service to Many Leads to Greatness.*
