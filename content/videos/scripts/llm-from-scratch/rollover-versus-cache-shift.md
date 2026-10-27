# Absolute positions and invalidation — video narration and storyboard

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Opening · 0:00–0:30

Explain the question: how can we estimate a Transformer cache without allocating one? Establish that every scalar count needs a declared shape and numeric representation.

## Visual demonstration · 0:30–2:30

Explain why learned absolute positions force cache reconstruction at a full context boundary.

On screen, draw the product `2 × layers × tokens × KV heads × head width × bytes per scalar`. Explain every factor and show a second configuration that changes only one variable.

## Native engineering · 2:30–4:00

Introduce the Framework's overflow-safe capacity planner and its status/result contract. Show which assumptions it validates and which properties belong to the decoder and actual allocator instead.

## Closing exercise · 4:00–4:30

Ask viewers to compute the payload for a doubled context and decide whether it necessarily changes end-to-end latency. State the answer: memory scales with context in this model; time must be measured independently.

*Service to Many Leads to Greatness.*
