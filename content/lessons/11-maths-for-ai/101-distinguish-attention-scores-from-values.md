# Mathematics for AI — Unit 101: Distinguish Attention Scores From Values

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Introductory mathematics with practical native C23 AI examples.

## 1. Begin with ordinary numbers

For query q=[1,2] and key k=[3,4], the dot product is `1*3 + 2*4 = 11`. A head of width two scales this by `sqrt(2)`, producing approximately 7.778. This score controls attention weighting. The separate value vector, such as `[5,6]`, is mixed after softmax; it is not the key.

The word **tensor** means a structured collection of numbers. In this subject, **layer** identifies one Transformer block, **token** identifies one position in a sequence, and **channel** identifies one numerical feature of that token. `FP32` means a four-byte floating-point value. These definitions let you read a cache diagram without pretending that every number describes an entire language model.

## 2. Translate the mathematics into engineering

Write the quantities on paper first, attach a unit to every count, and check the operation against the native Framework contract. A number described as **float elements** is not interchangeable with a number described as **bytes**; a count of **token-layer rows** is not a count of **seconds**. The Framework's K/V store and conditional prefix planner expose different measurements for this reason.

Where an example contains a digest, remember that an SHA-256 content hash detects changed bytes but is not a signature. Where it contains synthetic tokens or numbers, those are teaching fixtures, not customer or training records.

## 3. Exercise

**Question:** For q=[2,1] and k=[1,3], what is the unscaled dot product?

<details>
<summary>Show the worked answer</summary>

2*1 + 1*3 = 5.

</details>

## 4. Continue

Read [the browser version of this unit](../../courses/maths-for-ai/lessons/101-distinguish-attention-scores-from-values.html) and [the K/V mathematics learning path](kv-cache-mathematics.md). For the native connection, study [LLM Lesson 185](../10-native-ai/185-own-k-v-rows-for-each-transformer-layer.md) and [LLM Lesson 194](../10-native-ai/194-measure-stored-token-layer-work.md).

*Sammy Hegab · Umicom Foundation · Service to Many Leads to Greatness.*
