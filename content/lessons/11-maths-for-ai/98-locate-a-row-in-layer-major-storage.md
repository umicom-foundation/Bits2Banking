# Mathematics for AI — Unit 98: Locate a Row in Layer-Major Storage

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Introductory mathematics with practical native C23 AI examples.

## 1. Begin with ordinary numbers

In a fixed layout `[layer][context][channel]`, the flat starting offset in floats is `(layer*C + token)*D`. With C=4 and D=4, layer 2 and token 3 begin at `(2*4+3)*4 = 44`. The analogous V row begins after the entire K allocation of L*C*D floats.

The word **tensor** means a structured collection of numbers. In this subject, **layer** identifies one Transformer block, **token** identifies one position in a sequence, and **channel** identifies one numerical feature of that token. `FP32` means a four-byte floating-point value. These definitions let you read a cache diagram without pretending that every number describes an entire language model.

## 2. Translate the mathematics into engineering

Write the quantities on paper first, attach a unit to every count, and check the operation against the native Framework contract. A number described as **float elements** is not interchangeable with a number described as **bytes**; a count of **token-layer rows** is not a count of **seconds**. The Framework's K/V store and conditional prefix planner expose different measurements for this reason.

Where an example contains a digest, remember that an SHA-256 content hash detects changed bytes but is not a signature. Where it contains synthetic tokens or numbers, those are teaching fixtures, not customer or training records.

## 3. Exercise

**Question:** For C=8, D=4, find the offset for layer 1, token 5.

<details>
<summary>Show the worked answer</summary>

(1*8+5)*4 = 52 floats from the beginning of its K or V region.

</details>

## 4. Continue

Read [the browser version of this unit](../../courses/maths-for-ai/lessons/98-locate-a-row-in-layer-major-storage.html) and [the K/V mathematics learning path](kv-cache-mathematics.md). For the native connection, study [LLM Lesson 185](../10-native-ai/185-own-k-v-rows-for-each-transformer-layer.md) and [LLM Lesson 194](../10-native-ai/194-measure-stored-token-layer-work.md).

*Sammy Hegab · Umicom Foundation · Service to Many Leads to Greatness.*
