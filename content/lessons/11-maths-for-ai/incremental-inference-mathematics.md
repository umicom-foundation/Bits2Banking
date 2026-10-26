# Mathematics for native incremental inference — study route

**Sammy Hegab · Umicom Foundation**

The [browser units](../../courses/maths-for-ai/incremental-attention-mathematics.html) cover [Unit 113](113-count-multilayer-qkv-tensor-shapes.md) through [Unit 124](124-compare-release-timings-with-uncertainty.md). Start with tensor shapes, then one-query attention, softmax, row selection, layer normalisation, residuals, numerical tolerances and inference-work accounting.

All examples use small fictional numbers and explicitly describe their units. Use the existing [Mathematics Unit 3](03-vectors-and-dot-products.md) for dot products and [Unit 4](04-matrices-and-shapes.md) for matrix multiplication whenever a step seems unfamiliar. The C23 operators remain Framework-owned; arithmetic written in these manuscripts is for human comprehension and independent qualification.

A practice result is not a measurement from the target Windows machine. Only correctly controlled tests against the actual source and model can support a performance claim.
