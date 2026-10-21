# Supplement 15B — Native Corpus Import and Next-Token Windows

**Bits to Banking · Native AI laboratory · Sammy Hegab · Umicom Foundation**

## What a training corpus is

A corpus is the source material used to train or evaluate a language model. For the future Umicom C Expert, a corpus could contain approved C23 source, documented APIs and educational explanations. It must be reviewed for copyright, personal information and confidential code before training. A corpus loader reads bytes; it does not grant permission to train on them.

## The first native data pipeline

Batch 05 introduces `UmiAiCorpusCreate`, `UmiAiCorpusLoadFile`, `UmiAiCorpusLength` and `UmiAiCorpusWindow` in `framework/include/umicom/ai/training/corpus.h`. The implementation belongs to the Framework, and the learning executable only calls those contracts.

The loader copies all file bytes into owned memory. It rejects empty files, missing paths, or files larger than 1 MiB; it also checks for failed reads and detects extra data appended before the read completes. This intentional 1 MiB limit applies to the **educational importer**, not an eventual large-corpus streaming system.

## Construct a next-token example

Given the bytes `C23`, IDs are `71`, `54`, `55` because the ASCII byte values are 67, 50 and 51. A two-position training window at offset zero is:

| Position | Input token | Target token |
|---|---:|---:|
| 0 | 71 (`C`) | 54 (`2`) |
| 1 | 54 (`2`) | 55 (`3`) |

A future decoder will receive the **input** tokens, produce a probability distribution at each position and be scored against the **target** tokens. `UmiAiCorpusWindow` does not train a model by itself: it only prepares aligned pairs. The model, optimiser and existing dataset-splitting services remain separately owned Framework components.

## Try the read-only corpus inspector

After configuring and building the native LLM laboratory, run:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-corpus.exe" `
  ".\framework\learning\native-llm\README.md"
```

It prints the corpus byte count and a short list of first-position token pairs. **No source file is edited.** Run the related tests:

```powershell
ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
  -R "framework.ai.training.(corpus|byte_tokenizer)" --output-on-failure
```

## Train and validation separation

Do not randomly split overlapping windows from one source file into training and validation sets: almost identical material could appear in both sets and make evaluation appear stronger than it is. For meaningful C Expert experiments, reserve entire files, modules, projects or chronological revisions for evaluation before generating examples. Keep the existing Framework dataset-split API as the authority for the configured split policy; this small loader intentionally does not duplicate it.

## Limits and what comes next

The importer is presently an in-memory, one-file laboratory. It does not yet implement a multi-file corpus manifest, licence enforcement, deduplication, streaming, a learned subword vocabulary or an end-to-end decoder trainer. Those are explicit future milestones. Inspect the exact source and tests before claiming other capabilities.

## Exercises

Using an approved local document, compare the byte count with the number of visible characters. Explain why a UTF-8 character may contain multiple bytes. Find a short input/target window manually, then verify the displayed IDs. Finally, propose a train/evaluation split that avoids repeated source fragments.
