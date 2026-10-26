# Lesson 101 — Review Documents, Captions and Code Before LLM Training

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Learning objectives

Draw a source-to-dataset pipeline that respects permissions, original asset identity, train/evaluation separation and privacy. Learn why text extraction and model training must remain different stages.

## 1. Original assets are not yet training data

A PDF, DOCX document, source-code file, audio recording, video or image contains material in its original format. A training system cannot responsibly treat every byte as an approved text example. It first needs an appropriate **Framework-owned extractor or provider adapter**, a record of the asset's origin and licence, and an explicit human review of the prepared derivative.

For videos with trusted subtitles, the existing Framework Creative Workspace can parse supported SRT and WebVTT subsets into validated caption tracks. The existing native caption-to-text service can prepare reviewable text from such a track. This is not speech recognition; footage without approved transcripts needs a separately qualified extraction provider.

For PDF, DOCX and image data, use an already available Framework document/media component where supported and add native C23 provider boundaries when a required format is missing. Never silently assume all binary or scanned documents can be decoded by the current teaching dataset loader.

## 2. Record both hashes

The **original asset SHA-256** identifies the reviewed input bytes. The **prepared derivative SHA-256** identifies the exact reviewed UTF-8 text bytes. If a video is captioned twice or one document is split into multiple examples, both derivatives should retain the same original asset identity.

The Framework's reviewed-source admission and `ReviewedCorpusAudit` make those identities available for a source-level train/evaluation separation. A paraphrased duplicate or nearly identical recording still requires a separate near-duplicate review; exact hashes cannot detect semantic duplication.

## 3. Keep model-facing text separate from provenance

A reviewed prompt/completion JSONL row contains just the approved training prompt and response. Its evidence record separately holds hashes, source grouping, partition and reviewed span positions. This design reduces the risk that a model learns filenames, personal identifiers or editorial metadata merely because those values were packaged alongside the text.

It does **not** provide automatic personal-data redaction, licence discovery or proof of the right to train. Those decisions must be separately established before import. Restricted or private assets must never be admitted into a public example repository to make demonstration output convenient.

## 4. Move from an approved row to a training window

The Framework byte tokenizer represents raw bytes as token IDs offset by four, reserving IDs for PAD, BOS, EOS and UNK. The supervised-window component builds `[BOS]+prompt+completion+[EOS]`, creates next-token targets and masks prompt/padding targets. Only assistant-response bytes and EOS contribute to the selected-token cross-entropy.

**No document extraction logic belongs in Bits2Banking.** Educational pages can explain the workflow, while the actual C23 operations remain reusable Framework services.

## Practice

A video produces two corrected subtitle documents. Should its transcripts automatically go to different evaluation partitions? **No.** Both share the original video identity and must retain the same source-level partition to reduce leakage.

Continue with [quality gates](102-qualify-model-results-before-promotion.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
