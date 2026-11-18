<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/dense-kv-cache-geometry.md

PURPOSE:
Calculate dense key and value cache geometry

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Calculate dense key and value cache geometry

[Course contents](../../../courses/llm-from-scratch/index.html)
A language model processes tokens, which are pieces of text chosen by its tokenizer. During generation, many transformer implementations keep key and value arrays from earlier tokens. This KV cache avoids recomputing some earlier work. More retained tokens usually require more cache memory. Model weights and the cache are different resources.


## 1. Name every dimension

A layer is one repeated processing stage in the model. A head is a group used by the attention computation. Each key or value head contains a fixed number of numeric elements per token. An element width is the number of bytes used to store one number. Sequence capacity counts how many independent sequences this allocation supports. These values must come from the actual backend's cache layout, not from guessing the model name.

~~~text
key bytes per token = sequences * layers * key_heads * key_dimensions * key_element_bytes
value bytes per token = sequences * layers * value_heads * value_dimensions * value_element_bytes
cache bytes = tokens * (key bytes per token + value bytes per token)
~~~


## 2. Work a small example by hand

Take two sequences, three layers, two key heads, two value heads, four dimensions per head and two bytes per element. Key storage is 2 × 3 × 2 × 4 × 2 = 96 bytes per token. Values need another 96. Ten tokens therefore need 1,920 bytes of dense payload. Small numbers make the arithmetic easy to check independently.


## 3. Use Framework's checked service

~~~c
UmiModelDenseKvShape shape = {10, 2, 3, 2, 2, 4, 4, 2, 2};
UmiModelKvFootprint footprint;
UmiStatus status = UmiModelDenseKvCacheBytes(&shape, &footprint);
/* On UMI_STATUS_OK, total_bytes is 1920 for this supplied geometry. */
~~~

Include umicom/local_models/memory_plan.h and link the SDK's Umicom::local_models target. The service checks each multiplication and addition before publishing output. Without those checks, a very large product could wrap around to a small integer and make an impossible allocation appear affordable.


## 4. State the supported layout

This API models dense arrays with element widths of one, two, four or eight bytes. It is not a universal model-memory estimator. Quantized packed caches, sliding windows, paged allocation, recurrent state and hybrid architectures can use different layouts. A valid calculation for the wrong layout is still a wrong estimate for the selected backend.


## 5. Keep other costs separate

Weights may be mapped from a file, copied, converted or split between devices. Temporary workspace is used while loading or computing. The runtime and allocator also consume memory. None of these are included in the dense KV formula. Add them through a separate declared memory assessment, and mark unknown components as unknown.

Exercise: one sequence, 32 layers, eight key heads, eight value heads, 128 dimensions and two-byte elements require 131,072 bytes per token. Multiply by 4,096 tokens to obtain 536,870,912 bytes, or 512 MiB. MiB means 1,048,576 bytes; it is not the decimal MB unit of 1,000,000 bytes.


[Previous lesson](retrieval-installed-qualification.md)

[Next lesson](plan-context-from-a-cache-budget.md)
