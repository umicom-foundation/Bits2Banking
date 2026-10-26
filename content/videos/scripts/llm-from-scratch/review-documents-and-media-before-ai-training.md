# Video Lesson — Review Documents and Media Before AI Training

**Bits to Banking · Umicom Foundation · Sammy Hegab**

**Format:** Eight-minute educational narration and storyboard. **Audience:** Contributors preparing approved text, subtitle and source-code examples.

## Scene 1 — Source first, model second

**Visual:** Icons for a document, video, audio recording and C source file feeding into a controlled review gate.

**Narration:** “Before building our own native Umicom language model, we need good training material. A file being available does not mean we have permission to train on it. Rights review, personal-data handling, text accuracy and source identity all happen before dataset admission.”

## Scene 2 — Extract, then review

**Visual:** An SRT subtitle track becomes a reviewable transcript. A separate path for PDF and image inputs is labelled ‘format-specific extractor required’.

**Narration:** “The Framework already parses supported subtitle formats and can prepare text from their validated caption tracks. That is not the same as listening to audio and recognising speech. Other document and media formats need suitable reusable extraction providers.”

## Scene 3 — Explain original and derived hashes

**Visual:** One original video with SHA-256 identity branching into two corrected transcripts, each with its own text digest.

**Narration:** “We keep one identity for the original asset and a separate identity for each prepared derivative. If the same video supplies two examples, both must remain in the same source-level training or evaluation partition. Otherwise our test set could contain information already seen during training.”

## Scene 4 — Only selected response tokens learn

**Visual:** A small teacher-forced stream `[BOS] + prompt + answer + [EOS]`. Prompt targets and padding are grey; answer targets and EOS are highlighted.

**Narration:** “The Framework's native byte tokenizer and loss-mask builder identify which targets should teach the assistant. We train on the approved response and its end marker, not on padding or on the prompt itself.”

## Scene 5 — Measure without exaggerating

**Visual:** Training loss and held-out loss shown separately; a quality report marks the accuracy threshold independently.

**Narration:** “Lower training loss alone does not prove a model has learned to answer new questions. We evaluate source-separated held-out examples and compare explicit metrics. Even a passing quality gate is not permission to automate financial transactions.”

## Closing exercises

**Narration:** “Name the three things that must be recorded before a source enters training: its rights and review evidence, exact original and prepared text identities, and a consistent train/evaluation source group. Where should extraction and model logic live? In the shared Umicom Framework, never duplicated inside an educational repository.”

**Storyboard note:** All visual documents, people, captions and model results must be fictional teaching examples with no personal data or third-party material lacking permission.

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
