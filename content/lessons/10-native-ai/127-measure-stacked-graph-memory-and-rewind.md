# Measure stacked training-graph memory and rewind

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

## Parameter bytes are not the whole memory budget

Adding Transformer layers increases both parameters and intermediate activations. During a training pass, the Framework tape may retain projected Q/K/V values, attention probabilities, layer-normalisation work, residuals and gradient buffers. Merely multiplying parameter count by four bytes understates actual training-memory requirements.

The native stack exposes `UmiAiTrainingStackedDecoderMemoryInspect`, delegating to the canonical tape's memory-accounting service. The report describes tape-owned allocations—not Windows Task Manager RSS, graphics memory, allocator metadata or temporary operator scratch space.

## What a healthy repeated experiment looks like

Take an inspection immediately after creating the model. Repeat a forward evaluation, selected-loss evaluation and a training step. After each operation the graph must be rolled back to its retained leaf prefix. The expected *current* tensor count and tracked current bytes return to the baseline; *peak* bytes preserve the highest observed allocation.

```c
UmiAiTrainingTapeMemory before = {0}, after = {0};
UmiStatus status = UmiAiTrainingStackedDecoderMemoryInspect(model, &before);
/* Execute one approved training step and check its result. */
status = UmiAiTrainingStackedDecoderMemoryInspect(model, &after);
```

Always check each status before reading the report. A stable tracked allocation does not prove all memory is safe: repeat under sanitizers and investigate application-owned buffers separately.

## Why the bound is conservative

The model uses the existing educational tape, which limits tensor elements and computational-graph nodes. A proposed 40-layer architecture cannot be admitted merely because a spreadsheet estimates affordable parameter memory. Production scaling requires different allocation, activation, optimizer and accelerator strategies.

## Practice

Initial current storage is 7,000 bytes. A forward reaches 11,000, then rewind returns it to 7,000. What should the current and peak readings show?

<details><summary>Worked answer</summary>

Current should return to approximately the original tracked 7,000 bytes if graph lifetime is correct. Peak remains at least 11,000 bytes because it records a historical high-water mark. It is not a live allocation count.

</details>

---

[Native stacked Transformer reading path](stacked-transformer-learning-path.md) · [Mathematics for AI](../11-maths-for-ai/stacked-transformer-mathematics.md)
