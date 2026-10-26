# Video frames, captions and alignment

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

Video training can involve multiple distinct inputs: frame images, scene timing, human-written descriptions, detected speech and audio events. A text-only decoder cannot consume raw pixels as ordinary token IDs.

## Worked example

An extracted caption at 00:12–00:16 identifies a time interval, not necessarily everything visible or audible during that interval. Multimodal models require explicit alignment and separately trained encoders.

## Engineering application

Start by preparing reviewed text derivatives and provenance. Do not label the existing native byte decoder as a multimodal model until image/audio encoders and training integration genuinely exist.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

Can a text-only model infer all visible frame details from subtitles alone?

<details><summary>Reveal the worked answer</summary>

No. Subtitles omit many visual details.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
