# Lesson 02 — Training Data, Provenance and Evaluation Splits

**Bits to Banking · Build Your Own LLM from Scratch**  
**Sammy Hegab · Umicom Foundation**  
**Level:** introductory · **Implementation status:** curriculum and dataset-design exercise; no corpus ingestion is claimed in Batch 01.

## Why we begin with data

A model does not know what a C function, Calypso trade or Umicom module means when its weights are first initialised. Training exposes the model to examples and changes its numerical parameters so that useful token sequences receive higher probabilities. The training data therefore determines much of what the model can learn. A mathematically correct trainer cannot compensate for unsuitable or improperly licensed material.

Suppose we want an assistant that understands `UmiAiTrainingTapeCreate`. We could provide the public header, the tested implementation, a short explanation of the ownership rule and several examples of valid and invalid calls. These sources contain complementary evidence: the header states the contract, the implementation shows the mechanism, and tests establish verified behaviour. We should not fill a dataset solely with repetitive copies of a function declaration and expect useful reasoning to emerge.

## Dataset, example, corpus and token

A **corpus** is a curated collection of source material, such as Umicom's owned C23 code, reference manuals, documentation and approved technical prose. An **example** is the precise unit presented to the training loop: perhaps a contiguous segment of tokens with its next-token targets. The **tokeniser** maps the source text into numbered tokens (Lesson 03). A **batch** groups several examples for one parameter update. An **epoch** normally means one pass through the selected training examples. In our small local experiments, we will sometimes iterate repeatedly over a fixed miniature corpus to make the mathematics visible; that is not a substitute for diverse training material.

Consider the deliberately restricted corpus:

```text
umicom framework trains
umicom framework trains
```

With the educational vocabulary `umicom=0`, `framework=1`, `trains=2`, the input-target pairs become:

| Input | Expected next token |
|---|---|
| `umicom` | `framework` |
| `framework` | `trains` |
| `trains` | `umicom` (the next line is treated as a continuation in this exercise) |

The native demonstration in `framework/learning/native-llm/train_bigram.c` learns these three transitions. We can inspect its parameters because the vocabulary has only three entries. It **cannot** generalise to arbitrary C code or answer questions about Calypso.

## Preserve where training material came from

The source inventory should record the repository, original file path, revision, applicable licence, owner, content classification and any approved transformations. A manifest also needs an exact content checksum and the training run that consumed the material. This prevents a model trained on an earlier, superseded API from being mistaken for a model trained on today's contracts.

For Umicom, an initial policy is straightforward. Include original material authored or licensed for appropriate training by Umicom, and individually review third-party dependencies, external documentation and inherited repositories. Do not assume that a repository clone makes every file suitable for model training. A Calypso specialist must not ingest proprietary SDK code, client records or confidential configuration without appropriate authorisation. Secret tokens, account credentials and personal information must be excluded before indexing and training.

## Why training and evaluation must be separated

If the model repeatedly sees every question and its answer during training, it can memorise them. A very low *training loss* would then reveal little about its ability to handle unfamiliar questions. Divide data into **training**, **validation** and **held-out test** sets. Training updates weights; validation helps choose configurations; the held-out test is consulted for an independent final evaluation. For a toy demonstration, showing training loss alone is acceptable provided we explicitly label the result as a training exercise.

For a software repository, random line-by-line splitting is often misleading. Two copies of the same function, or a test and its implementation, can leak information across splits. Prefer grouping by repository, module, file family, commit epoch or problem family, depending on what the experiment intends to measure. Deduplicate examples and record the grouping strategy. No single split proves every kind of generalisation.

## A practical preparation exercise

Use PowerShell to inspect files without modifying them:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
Get-ChildItem '.\framework\include\umicom\ai' -File | Select-Object Name
Get-ChildItem '.\framework\tests' -Directory | Select-Object -First 12 Name
```

Then create a review table **outside any model's training directory** with columns: `Source path`, `Revision`, `Owner`, `Licence`, `Purpose`, `Allowed for training?`, and `Why?`. Select five Framework-owned files and document why they would—or would not—belong in an introductory dataset. The purpose is to practise data governance, not to claim that this batch already implements ingestion or permission enforcement.

## Review questions

1. Why is a corpus different from a model checkpoint?
2. What is the danger of putting modified copies of a function into both training and evaluation sets?
3. Why do public source files and licensed third-party SDKs require different dataset decisions?
4. What does a reduction in training loss demonstrate, and what does it not demonstrate?

**Next:** [Lesson 03 — Tokens and vocabulary](03-tokens-vocabulary-and-encoding.md).
