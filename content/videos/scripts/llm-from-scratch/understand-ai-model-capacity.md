# Understanding LLM memory before choosing hardware

**Bits to Banking · Educational video script**  
**Author:** Sammy Hegab · Umicom Foundation

## Opening — the question

Today we will answer one practical question with small numbers and reproducible reasoning, before asking a computer to do anything for us.

## Visual storyboard

Visualise one model on a workbench: parameter values, K/V cache, activations, gradients and optimiser state are separate labelled stacks.

## Narration: first principles

An AI model uses numerical parameters. During training, it also needs inputs, targets and temporary memory for computing gradients. Training text must be approved for that specific use. A checksum can verify that bytes match, but it cannot grant permission or prove an organisation approved publication.

## Demonstration sequence

1. Draw a tiny two-row table and count its numerical values.
2. Add a separate storage box for each state that the workflow requires.
3. Explain which operations are performed by Umicom Framework C23 services.
4. Highlight the difference between a validated numerical calculation and a deployed, authorised model.
5. Present a worked exercise and show the arithmetic slowly.

## Closing

Repeat the example with your own synthetic values and write down the shape, source permissions, expected answer, memory bounds and tests. A useful claim must describe precisely what was actually measured.
