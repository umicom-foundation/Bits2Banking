# Mathematics for AI — Unit 122: Distinguish byte tokens from UTF-8 characters

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Familiarity with simple arithmetic is enough.

## What will you learn?

The elementary Umicom byte vocabulary reserves four IDs; ordinary byte values 0..255 map to token IDs 4..259. Unicode text is encoded as a sequence of bytes, so one visual character can require several token IDs.

## A fully worked example

ASCII A has byte value 65 and therefore token ID 69. The UTF-8 character £ is represented by the two bytes C2 A3 (hex), or decimal [194,163]. Their byte-token IDs are [198,167]. Neither token alone is the whole character.

**Helpful symbols:** `×` means multiplication, `÷` means division, `[rows, columns]` states a tensor shape, and a token row is one position in a text sequence. Each byte count and score is specific to the example, not a measured production model.

## Practise the calculation

**Question:** How many byte-token IDs represent UTF-8 £, and can one streamed byte safely be treated as a complete character?

<details>
<summary>Show the worked answer</summary>

Two token IDs are needed. One byte may be an incomplete sequence; use Framework UTF-8 stream validation before display.

</details>

## Connect the idea to native C23

The native byte tokenizer and UTF-8 stream are existing Framework services and must not be reimplemented in course pages or applications.

The actual mathematical implementation remains in Umicom Framework. The connected [native Transformer learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html) applies this principle to a bounded real-model experiment.

## Continue learning

[Previous unit](121-separate-projection-work-from-attention-work.md) · [Next unit](123-count-full-window-rollovers-correctly.md) · [Complete mathematics route](../../courses/maths-for-ai/incremental-attention-mathematics.html)

*Service to Many Leads to Greatness.*
