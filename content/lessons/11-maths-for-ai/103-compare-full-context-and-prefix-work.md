# Mathematics for AI — Unit 103: Compare Full-Context and Prefix Work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Introductory mathematics with practical native C23 AI examples.

## 1. Begin with ordinary numbers

A full-context stacked decoder requests L*C token-layer rows for each of G generated tokens. A hypothetical stable-position cache would perform L*(P+S+C*R) rows. With L=2, C=8, P=3, G=12, appends=11, S=5 and R=6, so full=192 and cache=112. The conditional saving is 80 rows, but this is not a measured speedup.

The word **tensor** means a structured collection of numbers. In this subject, **layer** identifies one Transformer block, **token** identifies one position in a sequence, and **channel** identifies one numerical feature of that token. `FP32` means a four-byte floating-point value. These definitions let you read a cache diagram without pretending that every number describes an entire language model.

## 2. Translate the mathematics into engineering

Write the quantities on paper first, attach a unit to every count, and check the operation against the native Framework contract. A number described as **float elements** is not interchangeable with a number described as **bytes**; a count of **token-layer rows** is not a count of **seconds**. The Framework's K/V store and conditional prefix planner expose different measurements for this reason.

Where an example contains a digest, remember that an SHA-256 content hash detects changed bytes but is not a signature. Where it contains synthetic tokens or numbers, those are teaching fixtures, not customer or training records.

## 3. Exercise

**Question:** Using the example above, what is the avoided fraction?

<details>
<summary>Show the worked answer</summary>

80/192 = 0.416666..., or about 41.7% fewer token-layer rows.

</details>

## 4. Continue

Read [the browser version of this unit](../../courses/maths-for-ai/lessons/103-compare-full-context-and-prefix-work.html) and [the K/V mathematics learning path](kv-cache-mathematics.md). For the native connection, study [LLM Lesson 185](../10-native-ai/185-own-k-v-rows-for-each-transformer-layer.md) and [LLM Lesson 194](../10-native-ai/194-measure-stored-token-layer-work.md).

*Sammy Hegab · Umicom Foundation · Service to Many Leads to Greatness.*
