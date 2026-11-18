<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/07-tokenization-templates-and-masks.md

PURPOSE:
Understand tokens, chat templates and loss masks

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Understand tokens, chat templates and loss masks

[Course contents](index.md)
A tokenizer converts text into integer identifiers. A token may be a word, part of a word, punctuation or encoded bytes. The same text can produce different identifiers under different tokenizers. A model’s embedding table expects its compatible tokenizer, vocabulary and special-token rules.

A chat template is a model-specific formatting rule that marks roles and turn boundaries before tokenization. A messages array is not yet the exact tensor the model sees. Adding a generic “User:” prefix to every model can produce the wrong format. Use the chosen tokenizer’s documented template and inspect its rendered text and identifiers.

1. Record model revision, tokenizer revision and chat-template identity alongside the dataset.
2. Format one short conversation, then inspect it before tokenization. Check role order and end-of-turn markers.
3. Tokenize it with the exact tokenizer. Count tokens rather than guessing from character count.
4. Choose a maximum sequence length and an explicit policy for examples that exceed it. Review truncation so an answer or closing marker is not silently removed.
5. Inspect loss masks and padding masks in a tiny batch before starting training.

A padding mask identifies positions added only to make batch shapes compatible. A loss mask identifies positions that contribute to the objective. Some supervised training learns only assistant responses; some learns all selected tokens. These are trainer settings and template capabilities, not properties guaranteed by JSONL. A shifted next-token target must align prediction positions with the intended labels.

~~~text
Illustrative positions, not real tokenizer IDs:
position       0       1       2       3       4
role         user    user   assistant assistant padding
loss used?     no      no      yes      yes      no
~~~


## Check

A text file with one thousand characters does not necessarily contain one thousand tokens. A padded batch with eight slots does not necessarily contain eight meaningful target tokens. If every loss position is masked, a training loop can run without learning the desired behavior. Check these quantities explicitly.


## Further reading

- [TRL supervised fine-tuning documentation](https://huggingface.co/docs/trl/sft_trainer)

## Continue learning

[Previous: Run a native Framework dataset-partition lab](06-run-the-framework-group-lab.md) · [Course contents](index.md) · [Next: Plan batches, epochs and memory before training](08-batches-epochs-and-memory.md)
