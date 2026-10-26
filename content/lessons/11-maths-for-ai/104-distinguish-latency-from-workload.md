# Mathematics for AI — Unit 104: Distinguish Latency From Workload

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Introductory mathematics with practical native C23 AI examples.

## 1. Begin with ordinary numbers

A smaller number of stored rows does not guarantee a faster program. Consider an illustrative full-context run taking 6.0 milliseconds and a cache candidate taking 7.2 milliseconds. Despite calculating fewer rows, the second program takes `7.2/6.0=1.2` times as long, which is 20% slower. Benchmarking requires matched builds, models, prompts and repeated trials.

The word **tensor** means a structured collection of numbers. In this subject, **layer** identifies one Transformer block, **token** identifies one position in a sequence, and **channel** identifies one numerical feature of that token. `FP32` means a four-byte floating-point value. These definitions let you read a cache diagram without pretending that every number describes an entire language model.

## 2. Translate the mathematics into engineering

Write the quantities on paper first, attach a unit to every count, and check the operation against the native Framework contract. A number described as **float elements** is not interchangeable with a number described as **bytes**; a count of **token-layer rows** is not a count of **seconds**. The Framework's K/V store and conditional prefix planner expose different measurements for this reason.

Where an example contains a digest, remember that an SHA-256 content hash detects changed bytes but is not a signature. Where it contains synthetic tokens or numbers, those are teaching fixtures, not customer or training records.

## 3. Exercise

**Question:** Can a 28% token-layer-row reduction justify a claim of 28% lower response latency?

<details>
<summary>Show the worked answer</summary>

No. Row work and elapsed time are different measurements. Only measured end-to-end timings support a latency claim.

</details>

## 4. Continue

Read [the browser version of this unit](../../courses/maths-for-ai/lessons/104-distinguish-latency-from-workload.html) and [the K/V mathematics learning path](kv-cache-mathematics.md). For the native connection, study [LLM Lesson 185](../10-native-ai/185-own-k-v-rows-for-each-transformer-layer.md) and [LLM Lesson 194](../10-native-ai/194-measure-stored-token-layer-work.md).

*Sammy Hegab · Umicom Foundation · Service to Many Leads to Greatness.*
