# Unit 69 — Count UTF-8 bytes separately from displayed characters

**Mathematics for AI · Umicom Foundation**  
**Author:** Sammy Hegab

## Work from a small example

The ASCII letter `A` uses one UTF-8 byte (`41` in hexadecimal). The euro symbol `€` uses three (`E2 82 AC`). An emoji such as `💡` uses four (`F0 9F 92 A1`). The text `A€💡` therefore occupies `1+3+4=8` UTF-8 bytes but contains three Unicode scalar values.

## Why the calculation matters

The current reversible Framework byte tokeniser maps each raw byte into one ordinary token ID. Thus this particular text requires eight ordinary byte tokens, before any optional BOS or EOS tokens are added. Other tokenisers may use different token counts.

The demonstration is about byte lengths and numerical capacity. It does not authorise rendering generated HTML, executing returned commands or importing unreviewed text for training.

## Practice

**Question:** How many ordinary byte tokens represent `A€` with the current byte tokeniser?

<details><summary>Reveal the worked solution</summary>

`A` is one byte and `€` is three; the total is four byte tokens.

</details>

## Continue

Read [native LLM lesson 157](../10-native-ai/157-stream-generated-utf8-with-native-c23.md) and the earlier [byte tokenizer course](../10-native-ai/03-tokens-vocabulary-and-encoding.md).
