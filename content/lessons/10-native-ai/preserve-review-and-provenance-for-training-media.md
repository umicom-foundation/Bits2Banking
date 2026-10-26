# Preserve Review and Provenance When Preparing Media for Training

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## What does a media-training pipeline actually prepare?

A source asset might be a lesson video, a music recording, a scanned document, a source-code repository or a licensed article. The model trainer in Umicom Framework expects **approved, validated training examples**; it is not a universal binary decoder. Native media or document extraction must remain a separate, explicitly qualified Framework provider.

For a video with an available subtitle track, the existing Creative Workspace caption parser can import supported SRT and WebVTT text under strict constraints. The caption-to-text adaptation prepares human-reviewable UTF-8. A reviewer then checks the words, segment boundaries, language, source rights and personal data before any supervised prompt/completion example is admitted. A subtitle file alone does not prove transcription accuracy or training permission.

## Why two digest levels?

Keep one SHA-256 for the **original media bytes** and another for each **prepared text derivative**. If a video is captioned and later re-captioned, the derivatives change, but they still derive from the same original source. Grouping by original source helps prevent the same video appearing in both training and evaluation.

The existing reviewed-corpus audit detects exact duplicate records and some exact-content cross-partition conflicts. It cannot identify rephrased near-duplicates or infer whether recorded participants consented. Those require additional review, not a relaxed checksum.

## A careful staged workflow

First record where the asset came from and whether its use is permitted. Next use a trusted Framework extractor with bounded memory and explicit format support. Review the extracted text, correct errors, remove disallowed personal details and obtain explicit training-use approval. Format approved prompt/completion pairs through the existing Framework JSONL writer; then build source-separated, loss-masked training windows. Run the corpus integrity audit **before** training begins.

The resulting dataset is not placed in a public Bits2Banking repository merely because it contains educational material. Classroom lessons explain the workflow; private or licensed data must remain in approved storage with its original access rules.

## Review question

A video contains two captions with identical text but different timestamp offsets. May one go to training and the other to evaluation? **No.** Both are derived from the same source asset and could create leakage. The source-level grouping must remain consistent.

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
