# Video script — Stream native LLM bytes as valid UTF-8

**Bits to Banking · Umicom Foundation · Sammy Hegab**

**Objective:** Explain the difference between a byte token and a completed Unicode scalar, using real Framework interfaces without executing model output.

## Opening: one token is not always one character

Show three labelled hex bytes, `E2`, `82` and `AC`. Explain that their combination encodes the euro symbol. Draw a timeline with three calls and no visible output until the third byte arrives.

## Scene 1: Stateful native validation

Display the public `UmiUtf8StreamReset`, `UmiUtf8StreamAppend` and `UmiUtf8StreamFinish` names. Explain that the caller owns the fixed-size state and the output buffer. No Python or JavaScript decoder is needed.

## Scene 2: Error behaviour

Show an illegal continuation byte and an insufficient output capacity. Explain failure atomicity: no half-character is displayed and the pending state remains unchanged after rejection. Show a cancelled generation with an incomplete final sequence and explain the `Finish` refusal.

## Scene 3: What Unicode validity does not grant

Show sample output `2 < 5` and teach HTML escaping. A valid Unicode sequence may still be unsafe to interpret as executable markup. Native C23 AI code belongs in Framework and presentation in an authorised Umicom UI adapter.

## Closing exercise

Ask: “Does `A€💡` contain three model byte tokens or eight?” Pause. Reveal: “It contains eight UTF-8 bytes, so eight ordinary byte tokens in the current Framework byte tokenizer.”

**Publishing note:** This is a narration/storyboard manuscript, not a produced audio or video file.
