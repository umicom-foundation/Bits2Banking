# Lesson 03 — Tokens, Vocabulary and Text Encoding

**Bits to Banking · Build Your Own LLM from Scratch**  
**Sammy Hegab · Umicom Foundation**  
**Level:** introductory · **Implementation status:** a fixed three-token teaching vocabulary; general-purpose tokenisation remains future work.

## Why a language model receives numbers

A CPU cannot multiply the word `framework` by a matrix. It can operate on numbers stored in memory. A **tokeniser** turns text into tokens; a **vocabulary** assigns a stable integer identifier to every token that the model can represent. In a transformer, an embedding table maps each token identifier to a vector of learned numeric values.

A token is not necessarily a complete English word. Depending on the design, it may represent a byte, character, punctuation mark, whole word or frequently occurring word fragment. In C23 source code, syntax characters such as `(`, `*`, `{` and `;` matter. A useful future code model must preserve those distinctions reliably.

## A transparent Umicom example

Consider this tiny training sequence:

```text
umicom framework trains
```

For the first training demonstration, define exactly three token IDs:

| ID | Token |
|---:|---|
| 0 | `umicom` |
| 1 | `framework` |
| 2 | `trains` |

A one-hot representation is a vector with one value of `1` and all other values `0`:

```text
umicom    -> [1, 0, 0]
framework -> [0, 1, 0]
trains    -> [0, 0, 1]
```

The native trainer uses these vectors as the input matrix. Multiplying a one-hot row by a `3 × 3` weight matrix selects the row of weights associated with that input token. Those three numbers are the model's logits for the next token. The target index tells cross-entropy which probability should increase.

This representation is appropriate for a three-token classroom example. A general LLM would use many more tokens and typically learn dense embeddings instead of carrying around enormous one-hot input matrices.

## Byte-level, word-level and subword approaches

**Byte-level tokenisation** starts from raw bytes. It can represent arbitrary UTF-8 content without a special unknown-word token. However, one visible character may occupy several bytes and sequences can become long. A learner must distinguish UTF-8 encoding from character boundaries.

**Word-level tokenisation** can be straightforward for a restricted laboratory. It often performs badly when asked to process symbols, new identifiers or rare words. For example, `UmiAiTrainingTapeCreate` should not become an unrecoverable unknown token because the exact name was absent during vocabulary construction.

**Subword tokenisation** offers a compromise. Common words and fragments receive useful identifiers, while rarer strings can be assembled from smaller pieces. Byte Pair Encoding (BPE) is one family of subword methods. It must be implemented and tested separately from the training tape. Merely using a split-on-spaces routine does not make a BPE tokenizer.

## Stable identifiers are part of the model format

Training connects each embedding row and output probability to a particular token ID. If `framework` is ID 1 during training and ID 2 during inference, the saved parameters no longer mean what the model expects. A model checkpoint must therefore identify its tokeniser and vocabulary unambiguously. Training and inference must use the same mapping or a verified compatible conversion.

Useful validation cases for a future tokenizer include an empty input, malformed UTF-8, long C identifiers, Windows and Linux line endings, literal punctuation, unknown words and round-trip byte preservation. We should not silently change text or discard unsupported bytes while preparing financial-system or source-code datasets.

## Trace the real first laboratory

Open these two files in the merged Framework checkout:

```text
framework/learning/native-llm/train_bigram.c
framework/tests/ai_training/test_training_bigram.c
```

Find the `oneHot` matrix and the `targets` indices. Their values are part of the exercise dataset; the training engine itself knows only matrices and class identifiers. That separation allows a future tokenizer to feed the same mathematical runtime.

Using PowerShell:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
Get-Content '.\framework\learning\native-llm\train_bigram.c' -TotalCount 90
```

On paper, draw the `3 × 3` weight matrix and show which row is selected for each one-hot input. Start with all weights zero. The model has no preference for any next token, so each initial probability is `1/3`.

## Review questions

1. Why do we need a tokeniser when training a model on ordinary source text?
2. What does the vector `[0, 1, 0]` represent in the three-token laboratory?
3. Why might a word-level tokeniser be unsuitable for C identifiers?
4. Why must a checkpoint record vocabulary compatibility?

**Next:** [Lesson 04 — Softmax and cross-entropy](04-logits-softmax-and-cross-entropy.md).
