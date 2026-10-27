# Mathematics Video — KV Capacity and Grouped-Query Calculation

**Bits to Banking · Umicom Foundation**  
**Author and narrator:** Sammy Hegab  
**Companion reading:** Mathematics Units 167, 168, 171 and 172.

## Narration

The K/V cache contains two kinds of projections: keys and values. Every retained position contributes a row at each Transformer layer. Memory depends on the number of layers, token positions, K/V heads, channels per head and bytes per scalar. Multiplying those dimensions gives a payload estimate.

Begin with a tiny educational example: two layers, six positions, eight key/value channels, and four bytes per FP32 scalar. There are two arrays, K and V, so the payload is two times two times six times eight times four. The result is 768 bytes. It is not the total memory consumed by the application; model weights, tensor nodes and allocator metadata still occupy space.

Now increase the model. Suppose twelve layers, 2,048 positions, 64 channels per head, and two bytes per scalar. Standard multi-head attention with sixteen K/V heads requires 96 MiB for the K and V payload. Grouped-query attention with four K/V heads uses 24 MiB under those same assumptions. The payload becomes one quarter because sixteen divided by four is four.

Cache quantity is not cache validity. A full window using learned absolute positions cannot discard its oldest token and reuse the old projections unchanged. Every remaining token receives a new position embedding, changing calculations across the model. A full reconstruction may therefore consume more arithmetic than a single incremental append.

Finally consider sharing an immutable prefix across requests. A cache block with two borrowers keeps a reference count of two. When one borrower finishes, the count becomes one; the other may still use the block. When the last reference is gone, the owner can reclaim the block, provided its lifetime rules allow it.

## Visual storyboard

| Frame | Picture | Equation |
|---|---|---|
| 1 | K and V blocks arranged by layers and time | 2 × L × T × channels × bytes |
| 2 | Small FP32 box | 768 bytes |
| 3 | 16 MHA heads compared with 4 GQA heads | 96 MiB vs 24 MiB |
| 4 | Evicted token and shifted absolute positions | Previously cached rows are stale |
| 5 | Two requests holding one immutable prefix | Reference count 2 → 1 → 0 |

## Exercise

For four layers, ten positions and sixteen FP32 channels, calculate the combined K/V payload. Answer: 2 × 4 × 10 × 16 × 4 = 5,120 bytes.

*Service to Many Leads to Greatness.*
