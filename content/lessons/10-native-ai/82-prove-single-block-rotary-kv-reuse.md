# Lesson 82 — Prove rotary KV reuse within a bounded attention block

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation owner:** Umicom Framework (C23)

## Learning objectives

Explain how a fixed absolute position differs from a circular-buffer slot, calculate bounded KV-cache work and state precisely which assumptions are necessary before a previously computed key/value row can be retained.

## 1. A circular buffer is a storage strategy

For a context capacity of four, a newly appended token contributes one query, key and value. After four tokens the buffer is full. Adding the fifth evicts the oldest entry, but **does not rename the remaining tokens' original absolute positions**. Each retained key was rotated using its original position.

The existing `UmiAiTrainingRotaryWindow` component holds single-head, single-block, already-projected Q/K/V rows. It calculates masked causal attention over the retained rows and reports actual insertions and evictions. It does not train the Transformer or generate a complete language-model response.

```c
#include "umicom/ai/training/rotary_window.h"

const UmiAiTrainingRotaryWindowConfig config = {
    {4U, 4U, 10000.0}, 4U
};
UmiAiTrainingRotaryWindow *window = NULL;
UmiStatus status = UmiAiTrainingRotaryWindowCreate(&config, &window);
if (status == UMI_STATUS_OK) {
    const float query[4] = {0.5F, 0.1F, 0.2F, 0.3F};
    const float key[4] = {0.1F, 0.2F, 0.4F, 0.0F};
    const float value[4] = {1.0F, 0.5F, -0.2F, 1.0F};
    float context[4] = {0};
    status = UmiAiTrainingRotaryWindowAppend(
        window, query, key, value, 4U, context, 4U);
    UmiAiTrainingRotaryWindowDestroy(window);
}
```

The operation is failure-atomic: rejected input does not advance the buffer or partially overwrite its output.

## 2. Calculate the work

With **12 append operations** and a **four-token window**, independent full-window projection recomputation requires:

`1 + 2 + 3 + 4 + 8 × 4 = 42` projected token rows.

A reusable first-block ring computes one new projection per append, for **12 rows** total. Thus it avoids `42 − 12 = 30` projection rows, or approximately **71.4%** of this *particular* count. Attention still evaluates scores across the retained keys; fewer projection rows does not establish proportionately lower latency.

After all twelve successful appends, the Framework counters should indicate **12 computed rows**, **8 evictions**, **4 retained rows** and **0 full-window rebuilds** in this qualified single-block experiment.

## 3. The important limit

This reuse is correct only when the supplied Q/K/V projections of retained tokens do not depend on earlier context that was evicted. First-block projections of fixed embeddings can satisfy that condition. Upper-layer hidden states in a deeper Transformer may already encode context outside the new window, so replacing that earlier context may change their values.

No result here allows us to load an existing learned-absolute checkpoint as a rotary model or claim full-decoder parity without separate tests.

## 4. Exercise

Increase the window capacity to **eight** for twelve appends. The full recomputation count is `1+2+3+4+5+6+7+8 + 4×8 = 36+32 = 68`. The ring still computes twelve new rows, avoiding **56** projected rows. Explain what happens to attention-score work and memory as the window capacity increases.

**Takeaway:** cache reuse must be proven for the precise computation and model history it preserves.

[Illustrated lesson](../../courses/llm-from-scratch/lessons/82-prove-single-block-rotary-kv-reuse.html) · [Previous](81-introduce-rotary-position-mathematics.md)
