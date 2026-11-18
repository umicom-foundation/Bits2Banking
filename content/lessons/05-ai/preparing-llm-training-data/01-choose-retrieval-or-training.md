<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/01-choose-retrieval-or-training.md

PURPOSE:
Choose retrieval, fine-tuning or training from scratch

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Choose retrieval, fine-tuning or training from scratch

[Course contents](index.md)
A language model predicts tokens: pieces of encoded text. Its parameters, often called weights, are numbers learned during training. Inference uses those numbers to produce an answer. Training changes them. A document on disk, a prompt and a model checkpoint are different artifacts. This course starts with that distinction before asking you to run a trainer.

Suppose you want an assistant to answer questions about an Umicom SDK guide. You can supply a relevant excerpt in the prompt. Retrieval-augmented generation, or RAG, searches a collection for excerpts and adds them to the prompt. It usually does not change the language model’s weights. Fine-tuning starts with existing weights and updates some or all of them using examples. Training from scratch starts without a pretrained model and requires a much larger engineering and data effort.

1. Write one desired behavior, such as “answer with a source citation from the SDK guide.”
2. Write whether the underlying facts change often. Changing reference facts are often a retrieval problem.
3. Write whether you need a consistent response format or behavior demonstrated by examples. That can motivate supervised fine-tuning, after testing prompting and retrieval.
4. Choose a small evaluation set before changing anything: questions, expected properties and allowed sources. Keep it separate from training examples.

A vector is a list of numbers. An embedding model maps text to such a list so similar items can be searched. A vector database stores vectors plus identifiers and metadata. It is an index for retrieval, not a universal format that an LLM trainer requires. You do not have to turn every document into a dictionary or key-value pair to train. The training objective and loader decide the required record schema.


## Check

Copying a PDF into a model folder does not train a model. Creating embeddings does not by itself fine-tune the generation model. A good first project is a tiny inspected dataset and a reproducible evaluation; no expensive training is required to understand the formats.


## Choose by objective

| Goal | Typical data | Changes LLM weights? |
| --- | --- | --- |
| Answer with current documents | Document chunks, identifiers, search index | Usually no: RAG |
| Learn a response style or task | Reviewed input/output or chat examples | Yes: fine-tuning |
| Continue general text learning | Clean text sequences and tokenizer | Yes: continued pretraining |
| Create a base model | Large curated corpus, architecture, optimizer | Yes: training from scratch |

## Continue learning

[Course contents](index.md) · [Next: Turn documents into reviewed text without losing provenance](02-turn-documents-into-reviewed-text.md)
