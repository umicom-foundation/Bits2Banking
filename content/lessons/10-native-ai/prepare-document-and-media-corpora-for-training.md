# Prepare Documents, Captions and Media for Responsible Native Training

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Source extraction is not training approval

Umicom AI applications may eventually learn from manuals, authorised source code, public research, captions or other media. These inputs differ in format, copyright, privacy risk, factual reliability and extraction quality. Converting a PDF or recording into text is a *technical transformation*; it is not permission to train a model on that text.

All production logic belongs in **Umicom Framework**. Bits2Banking contains lessons and fictional exercises, not a second PDF converter, speech recogniser or dataset publishing service.

## What is already available in Framework?

The Framework currently exposes reviewed source admission, exact SHA-256 verification, canonical JSONL prompt/completion preparation, duplicate/source-group auditing and the new supervised dataset owner. Creative Workspace also provides a native C23 SRT/WebVTT caption-track parser. The adapter tooling can convert a *validated* caption track into reviewable text.

These components do **not** automatically perform document OCR, speech recognition, video frame understanding, semantic near-duplicate detection or human rights approval. Those capabilities must be added behind reusable Framework contracts and independently tested before real-world ingestion is automated.

## Walk through one synthetic caption source

Suppose a licensed fictional educational clip has two subtitles:

- `00:00–00:03`: “A token is a numerical identifier.”
- `00:03–00:06`: “A Transformer predicts the next token.”

The Framework caption reader validates the actual SRT or WebVTT structure, text and timing. A review workflow then checks speaker attribution, timestamp alignment and whether the transcript accurately reflects the recording. The source asset and the reviewed transcript receive separate SHA-256 identities.

Only after explicit training-use approval may a teaching editor compose a prompt, such as “Define a token”, and a reviewed completion. `ReviewedExampleJsonl` encodes that exact pair. `ReviewedCorpusAudit` keeps derivatives of the same original clip on one side of the train/evaluation split. The native supervised dataset owner turns the authorised JSONL into token windows.

## Protect the source-to-training chain

A useful evidence chain contains original asset identifier, approved licence, source digest, extraction method, reviewed derivative digest, redaction/quality review outcome, training-permission decision, split, canonical example digest and the model-run digest.

**Not all these fields should be stored in the same place.** Model-facing examples need the approved text only; source review evidence can contain restricted metadata and must follow its own access controls. Private material must not be copied into public Git repositories or build logs.

## Why mixing extraction quality with model quality is misleading

If an audio transcription incorrectly changes “fifteen” to “fifty”, fine-tuning can learn the erroneous sentence perfectly. A low training loss would then demonstrate reproduction of the **wrong extracted target**. Quality review needs source comparison before tokenisation, and held-out evaluation should contain independently reviewed answers rather than merely more copies of extraction errors.

## Exercises

1. A subtitle file is syntactically valid but incorrectly transcribes one number. May it be admitted automatically? **No; editorial accuracy still needs review.**
2. Two text derivatives come from one recording. Should they be divided across training and evaluation? **No; preserve source grouping.**
3. Does a published PDF on the internet automatically grant model-training rights? **No.**
4. Where should a new generic document extractor live? **In Umicom Framework, with a reviewed adapter contract and independent tests.**

Continue with [the source-audit lesson](audit-supervised-learning-datasets.md) and [the supervised JSONL pipeline](from-approved-jsonl-to-training-windows.md).
