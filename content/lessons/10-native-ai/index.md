# Build Your Own LLM from Scratch — The Umicom Native AI Course

**Bits to Banking · Umicom Foundation · Course proposal, 20 October 2026**  
**Author and project originator:** Sammy Hegab  
**Implementation language:** C23, with Assembly where justified  
**Source of truth:** Umicom Framework  
**Application laboratory:** Umicom LLM, followed by Umicom Studio IDE

## Why this course exists

This course teaches how a neural language model is constructed, trained and operated. We will **initialise the model's parameters ourselves**, implement its forward and backward calculations in native code, train it on a controlled dataset, and inspect how its predictions change. We are not using a pretrained model as a substitute for understanding training.

The educational objective and product objective are connected but distinct:

- **Educational:** understand tokens, tensors, gradients, attention, optimisation, evaluation and model cooperation, with calculations readers can reproduce.
- **Engineering:** extend the existing Umicom Framework with reusable native training, inference, evaluation and model-management facilities.
- **Application:** expose the reusable facilities through the existing Umicom LLM product, then Umicom Studio IDE.

A small model that learns observable patterns is a success for the first stages even if it is not capable of answering difficult engineering questions. Domain experts come later, once the general model and training procedure are reliable.

## Repository responsibilities

| Repository | Owner of the content | Examples |
|---|---|---|
| `umicom-foundation/Bits2Banking` | Teaching text, exercises, diagrams, assessment and references | `content/lessons/10-native-ai/` |
| `umicom-foundation/umicom-framework` | Reusable C23 neural, training, inference, model and policy services | Framework public C ABI, implementation, CTest tests |
| `umicom-foundation/umicom-llm` | Experimental training application, run configurations, dataset manifests, expert definitions and evaluation records | Model laboratory, expert profiles |
| `umicom-foundation/umicom-llm-module` | Existing thin LLM application/workbench integration, where applicable | Model selection, training progress, comparisons |
| `umicom-foundation/umicom-studio-ide-module` | IDE-specific UI wiring only | Source-aware assistant view and diagnostics |

**No new repository is required initially.** A model catalogue inside Umicom LLM can distinguish the base model and each expert. Large binary checkpoints should not be committed as ordinary Git objects. We can publish selected model artifacts separately once their size, distribution requirements, licences, hashes and release strategy are established.

The names and paths proposed for *new* Framework training modules must be reconciled with the live source tree before implementation. Never replace an existing public API merely to fit a lesson.

## Course map: 24 lessons in five parts

### Part I — What a language model learns

| Lesson | Subject | Evidence of learning |
|---|---|---|
| **01** | From source text to learned predictions | Explain training versus inference; compute a sample next-token loss; inspect our starting code. |
| **02** | Training data, ownership and evaluation splits | Prepare a small licensed corpus and a held-out evaluation set; record provenance. |
| **03** | Tokens, vocabulary and text encoding | Demonstrate byte and subword tokenisation; define reproducible vocabulary IDs. |
| **04** | Probabilities, logits, softmax and cross-entropy | Compute the probability of a target token and its loss by hand. |

### Part II — Native mathematics in Umicom Framework

| Lesson | Subject | Evidence of learning |
|---|---|---|
| **05** | Tensor shapes, strides, lifetimes and ownership | Compile a tested C23 tensor abstraction with bounds and shape validation. |
| **06** | Vectors, matrices, normalisation and activation functions | Verify matrix multiplication and numeric stability against independent expected values. |
| **07** | Gradients and backpropagation | Compare analytical gradients against central finite differences. |
| **08** | Optimisers and numerical robustness | Implement and test SGD and AdamW, including safe rejection of invalid settings. |

### Part III — Build a transformer

| Lesson | Subject | Evidence of learning |
|---|---|---|
| **09** | Token and positional embeddings | Convert bounded token sequences to vectors with validated indices. |
| **10** | Causal self-attention | Demonstrate masking: the prediction must not see future tokens. |
| **11** | Multi-head attention | Show independent heads and correct concatenation/projection. |
| **12** | Feed-forward networks, normalisation and residual paths | Build a complete, shape-checked transformer block. |
| **13** | Transformer logits, loss and backward pass | Produce valid next-token probabilities and gradients. |
| **14** | Dataset streaming, batching and training loops | Process a corpus in batches while preserving reproducibility and bounded memory. |
| **15** | Checkpoints and recovery | Resume training with matching model/optimizer/RNG state and detect corrupt checkpoints. |

### Part IV — Train, inspect and improve our own model

| Lesson | Subject | Evidence of learning |
|---|---|---|
| **16** | First complete training run from random weights | Show independently measured training and evaluation loss with a retained checkpoint. |
| **17** | Sampling and inference | Reload the model and generate controlled text from a prompt. |
| **18** | Evaluation, memorisation and failure analysis | Compare held-out loss, simple task accuracy and repeated-run reproducibility. |
| **19** | Performance, profiling and native acceleration | Establish a C23 baseline before optional Assembly/SIMD/GPU backends. |

### Part V — A cooperating family of specialised models

| Lesson | Subject | Evidence of learning |
|---|---|---|
| **20** | Train the Umicom C Expert | Train on reviewed C23 educational material; measure narrow, verifiable tasks. |
| **21** | Train the Umicom Framework Expert | Teach architecture and conventions; ground current API facts in retrieved source. |
| **22** | Train the Calypso/TMS Expert | Train on authorised educational material; mark version-specific API uncertainty. |
| **23** | Coordinate experts without confusing them with neural MoE | Route tasks, exchange bounded responses, attach evidence and record disagreements. |
| **24** | Embed the experts in Umicom applications | Display model status, citations, evaluations and reviewed proposals in Studio. |

## How each lesson is written

Every lesson will use the same professional learning format:

1. **Purpose and prerequisites** — why this part matters and what the reader should know first.
2. **Conceptual explanation** — define each new term and its role in a real model.
3. **Worked numerical example** — show every important intermediate value.
4. **Native implementation** — complete C23/Assembly source, once that capability is ready for implementation.
5. **Build and test** — complete commands, positive and negative tests, expected output and diagnostic interpretation.
6. **Umicom integration** — show exactly which existing Framework contract is reused or extended.
7. **Review questions and extension work** — check understanding before advancing.
8. **Evidence and limitations** — distinguish demonstrable results from planned functionality.

Lesson 01 introduces the problem and performs a read-only repository audit. Lesson 05 onwards introduces the core tensor implementation once the existing Framework contracts have been assessed. Later labs reuse that implementation rather than creating a second training engine under Bits2Banking.

## Our first model: an experimental baseline, not a coding assistant

An illustrative starting transformer may use **4 decoder blocks, 4 attention heads, a 256-dimensional hidden state, a 4,096-token vocabulary and a 256-token context**. With a tied output embedding and ordinary feed-forward dimensions, the configuration is in the region of **4–5 million parameters**. The exact count depends on the final design and must be generated from the actual model definition, not taken on trust.

Training starts with randomly initialised weights and a fixed random seed. A first experiment should fit on accessible hardware and be small enough to debug. Training duration will depend on the implementation, dataset, CPU/GPU backend and selected batch size; we should measure it rather than promising a particular time.

## Specialised experts: the research plan

We will **train one common Umicom foundation model from scratch**, then continue training separate copies for the C23, Framework and Calypso/TMS domains. This avoids relearning basic language patterns independently for every expert. We can later compare against an expert trained independently from random weights.

Independent models coordinated at the application level are **not** the same as a neural *mixture-of-experts* layer. We will implement the former first; a learned neural router is a later research option.

For every expert, keep the training set separate from evaluation material. A current Framework API should be resolved from authoritative source retrieval rather than trusted solely because the model has seen a historical implementation. Compiler tests, source references and human approval remain outside the model.

## Milestones and acceptance criteria

**Milestone A — Baseline inventory:** confirm existing AI, dataset, retrieval, model-registry and testing facilities; record what is implemented versus proposed. Preserve existing source and public API contracts.

**Milestone B — Native mathematical kernel:** tested tensors, matrix operations, numerical stability and gradient checking in Framework C23.

**Milestone C — First genuine transformer:** a model with trainable parameters, attention, forward/backward propagation, checkpoint persistence and inference; training demonstrably updates weights.

**Milestone D — Specialised models:** repeatable domain experiments with comparable held-out evaluations, dataset provenance and explicit resource budgets.

**Milestone E — Coordinated applications:** a thin Umicom LLM workbench and then Studio integration, with governed access and traceable outputs.

**Start with [Lesson 01: From source text to learned predictions](01-from-source-text-to-learning.md).**

## Existing Umicom material to retain

- *Bits to Banking, Volume 3H — External Connectivity, IBKR Adapter and Local AI Runtime*: local inference and retrieval/provider boundaries.
- *Bits to Banking, Volume 3I — Building a Small Language Model and Native AI Inference Engine*: a transparent word-transition training demonstration and the mathematical preparation for transformers.
- Accepted Framework `ADR-0006-native-local-llm.md`: the C23-first training and inference direction; the production model trainer is not represented as completed.

The new course is a **practical continuation**, not a replacement for either volume.

## Native training laboratory — mathematical foundations (20 October 2026)

The initial Framework training foundation adds a Framework-owned, bounded CPU training tape with row-major float32 matrices, matrix multiplication, broadcast addition, ReLU, mean-squared-error loss, stable cross-entropy, reverse-mode autodifferentiation, SGD, and six CTest regression checks. The included C23 example trains a **three-token bigram model** from zero weights. It **does not** yet train a transformer or provide attention, checkpoint persistence, a production tokenizer or domain experts.

New course lessons accompanying this implementation:

- [02. Training data and evaluation](02-training-data-and-evaluation.md)
- [03. Tokens, vocabulary and encoding](03-tokens-vocabulary-and-encoding.md)
- [04. Logits, softmax and cross-entropy](04-logits-softmax-and-cross-entropy.md)
- [05. Tensor shapes and ownership](05-tensor-shapes-and-ownership.md)
- [06. Matrix operations and activations](06-matrix-operations-and-activations.md)
- [07. Gradients and backpropagation](07-gradients-and-backpropagation.md)
- [08. Optimisers and first training run](08-optimisers-and-first-training-run.md)

The educational package retains the original [Lesson 01](01-from-source-text-to-learning.md). Every experiment compiles against existing `umicom/base/status.h` in the actual Framework checkout. See the merge instructions for exact PowerShell build and Git commands.

## Native training laboratory — learned embeddings and causal attention

The attention implementation adds seeded C23 parameter initialisation, a bounded logical
`[batch,time,channels]` sequence layout, differentiable embedding lookup with
repeated-token scatter gradients, and trainable single-head scaled dot-product
causal attention. It includes six new registered checks (five focused unit
and gradient tests plus a tiny context-dependent training demonstration).
The original six regression tests are preserved. This is **not** yet a complete transformer.

- [09. Seeded initialisation and token embeddings](09-seeded-initialisation-and-token-embeddings.md)
- [10. Causal self-attention and context-sensitive training](10-causal-self-attention-and-context.md)

The accompanying source is in the existing Framework training tape and
`framework/learning/native-llm/train_attention.c`, not in a second AI engine.
The Framework baseline was documented in the accompanying merge instructions; the
standalone laboratory remains available even when the very large root CMake
file has not yet registered the optional training module.


## Native training laboratory — trainable decoder Transformer Block

The Transformer Block extends the exact same C23 training tape (no parallel maths engine):

- **Two or more attention heads:** configurable channel partitions with
  independently scaled, causal and batch-separated softmax weighting;
  Q/K/V derivatives and alias accumulation are verified numerically.
- **Learned layer normalisation:** per-token channel statistics, trainable
  gamma/beta, epsilon control and independently verified backward gradients.
- **Pre-LN decoder block:** Q/K/V projections, multi-head attention, output
  projection, residual connection, second normalisation, ReLU feed-forward
  expansion/reduction and final residual connection.
- **Tape graph transactions:** checkpoint and rollback prevent failed composed
  operations from leaving partial nodes or publishing an output pointer.
- **Trainable demonstration:** four tokens in two short sequences are used to
  show decreasing cross-entropy. These data are memorisable and are NOT
  held-out evaluation of a language model.

[**Lesson 11 — Multi-Head Causal Attention**](11-multi-head-causal-attention.md)  
[**Lesson 12 — Layer Normalisation, Residual Paths and Transformer Block**](12-layer-normalisation-residuals-and-transformer-block.md)

The cumulative isolated native laboratory contains **21 CTest cases** (the
12 earlier tests, eight new focused tests and one new demonstration test).
The main Framework CMake target is unchanged; the optional root
`CMakeLists.txt` include must be reviewed and added exactly once if you want
these tests inside the complete Umicom Applications preset.

---

## Lessons 13–15 — complete bounded decoder and checkpoints

Our previous 12 lessons remain unchanged. The decoder implementation introduces a **learned
absolute-position table**, a reusable single-block decoder with vocabulary
logits, a deterministic sequence-level train/evaluation partition, a portable
`UMIDEC04` checkpoint and a multi-parameter SGD transaction.

- [Lesson 13 — From a Transformer Block to a Trainable Decoder](13-from-transformer-block-to-decoder.md): token and position embeddings, logits, gradients, whole-model update and causal-sequence validation.
- [Lesson 14 — Train/Evaluation Splits and Learning Discipline](14-held-out-evaluation-and-training-discipline.md): reproducible held-out groups, training/evaluation loss and an honest overfitting example.
- [Lesson 15 — Portable Checkpoints and Exact Resume](15-portable-checkpoints-and-recovery.md): binary format, endian safety, no-clobber file publication and checkpoint restoration.

The executable `learning/native-llm/train_decoder.c` is a **thin consumer** of
native Umicom Framework AI services. Model code and checkpoint encoding remain
in Framework. The isolated suite at this stage ran **27 native CTest tests**;
this is not a claim that the large consolidated Umicom Applications suite
has passed. The next step is a proper corpus loader, configurable sequence
length and eventually a multi-block decoder, AdamW and controlled sampling.

**Scientific honesty:** On the small synthetic corpus, training loss decreased
but held-out loss increased. The sample shows how a model can memorise its
training pairs without generalising to unseen combinations. Do not describe
this model as a C23 or Calypso expert until independent benchmarks support it.


## Native byte tokenizer and corpus import

The original complete decoder used small fixed token sequences.
The corpus implementation introduces **read-only corpus ingestion** and a reversible byte-token
baseline, with three additional native CTest checks. This is not yet large-corpus
streaming or an end-to-end model trained from a source file.

- [Supplement 15A — Reversible byte tokenisation](15a-byte-tokenisation-and-corpus-import.md)
- [Supplement 15B — Native corpus import and next-token windows](15b-native-corpus-and-next-token-windows.md)

These supplements prepare the data pipeline for planned Lesson 16 without
renumbering or replacing the existing 24-lesson roadmap.


## Native source-code training (21 October 2026)

The training lesson now connects the existing byte tokenizer, immutable corpus
snapshots and decoder-only Transformer through a reviewed, file-level dataset
manifest. The Framework owns deterministic partition-specific minibatches and
rejects obvious duplicate documents. This is a bounded experiment, **not yet a
competent C23 coding assistant**.

- [Lesson 16 — Train an Umicom Decoder on C23 Source Code](16-source-code-training-with-file-level-evaluation.md)
- [Supplement 16A — Review Training Manifests and Provenance](16a-reviewing-training-manifests-and-provenance.md)

The executable example lives in
`framework/learning/native-llm/train_source.c` and reads the fixture manifest
at `framework/learning/native-llm/fixtures/manifest.txt`. Nothing under the
Bits2Banking repository reimplements Framework training functionality.


## Reproducible experiments, checkpoints and text generation

The native experiment service now provides reproducible run plans, sampled
held-out evaluation, cancellation and exact continuation from an approved
checkpoint. These facilities are Framework-owned; learners can change a
reviewed plan without introducing a secondary training implementation.

- [Supplement 16B — Reproducible native training experiments](16b-reproducible-native-training-experiments.md)
- [Supplement 16C — Resume checkpoints and training evidence](16c-resume-checkpoints-and-training-evidence.md)
- [Lesson 17 — Generate Text with Our Own Native Transformer](17-autoregressive-generation-and-sampling.md)

Lesson 17 adds rolling-context autoregressive inference and reproducible
best-token or top-K sampling. Generated bytes are returned with their lengths
and rendered safely by the small command-line laboratory. Training remains
separate from inference: the model's saved weights and completed optimiser
steps do not change during generation. The present model still lacks sufficient
capacity and training data for reliable programming assistance.


## Evidence-driven decoder evaluation and checkpoint identity

We can now evaluate a previously trained native decoder on deterministic
held-out source samples and tie the measurements to its exact checkpoint,
reviewed source manifest and complete training configuration. This adds
Top-1 and Top-5 next-token accuracy alongside the existing cross-entropy and
perplexity metrics; all maths and provenance services remain Framework-owned.

- [Lesson 18 — Evaluate Our Native Language Model and Preserve its Provenance](18-model-evaluation-and-provenance.md)
- [Supplement 18A — Repeatable Checkpoint Comparisons and Evidence Boundaries](18a-checkpoint-identity-and-repeatable-comparisons.md)

The thin `umicom-native-llm-audit` laboratory loads approved checkpoints but
never writes data or executes generated code. Fingerprints are reproducible
FNV-1a64 accidental-change indicators, **not** security signatures. Results
come from sampled held-out next-token predictions and must not be described
as evidence of general C23 or treasury-system competence.


## Incremental attention inference and key/value caching

The decoder now has a Framework-owned, inspectable **key/value inference
cache**. It reuses previously computed attention projections while a prompt
prefix grows, and checks every cached prediction against the authoritative
decoder. Because our first transformer uses **learned absolute position
embeddings**, a full rolling context must invalidate and reconstruct cached
keys and values when tokens shift to earlier positions. Incorrectly reusing
these rows would change the model's predictions.

- [Lesson 19 — Incremental Native Inference and Key/Value Caching](19-incremental-inference-and-kv-caching.md)

The optional `umicom-native-llm-kv-inspect` command displays retained tokens,
computed projection rows, complete-window rebuild counts and maximum deviation
from the canonical decoder. It reports **work counters**, not speedup claims.
Its implementation is written in C23 and uses the established model parameters;
no second training engine or application-local model is introduced.

## CPU matrix performance and measurable optimisation

The transformer training tape and the incremental key/value cache now share a
single Framework-owned C23 matrix kernel. Learners can compare the original
reference operation with column-tiled multiplication, verify unchanged
training gradients and cached logits, and measure actual process CPU time.

- [Supplement 19A — Make Our Native Model's Mathematics Measurable](19a-native-cpu-matrix-optimisation-and-benchmarking.md)

The benchmark does not assert a guaranteed speedup. The elementary decoder's
model-size and context limits remain unchanged until additional memory and
numerical qualifications are completed.


## Train with AdamW and controlled learning rates

Native training now includes an inspectable AdamW optimiser with transactional
moment/weight updates, and opt-in, absolute-step learning-rate scheduling for
existing direct and accumulated SGD experiments. The original training paths
and model checkpoint format are retained unchanged.

- [Supplement 19H — Build a Native AdamW Optimiser](19h-adamw-and-native-optimisation.md)
- [Supplement 19I — Learning-Rate Schedules and Reproducible Resume](19i-learning-rate-schedules-and-reproducible-resume.md)

The optimizer's first and second moments are not yet serialised. Consequently,
a decoder-only checkpoint cannot be used to continue AdamW exactly. Scheduled
SGD continuation remains reproducible when its **original** training horizon,
reviewed data, seeds and rates are preserved. The educational examples do not
claim that our bounded decoder has become a capable source-code expert.

## Continuing AdamW training across application restarts

The earlier optimiser lesson described a process-local AdamW state. The
Framework now has an additional, explicitly versioned combined checkpoint
for the complete decoder **and** AdamW first/second moments. The established
model-only checkpoint remains unchanged, while the combined checkpoint can
restore the exact optimiser-step count and reproduce subsequent deterministic
updates on identical reviewed training examples.

- [Supplement 19J — Resume AdamW Training with a Portable Native Checkpoint](19j-resume-adamw-with-persistent-native-checkpoints.md)

This new checkpoint is subject to strict size, shape and numerical checks.
Its FNV checksum only detects accidental corruption, not malicious tampering.
The external dataset, initial seed, optimiser hyperparameters and learning-rate
schedule must be independently verified. Windows antivirus blocks must be
investigated rather than bypassed merely to obtain a green CTest result.


## Reproducible AdamW experiments and exact optimiser continuation

The Framework now offers scheduled AdamW experiments with separate owned
model and optimiser handles. A combined checkpoint retains both model weights
and AdamW moment history so interrupted training can continue from the correct
absolute step, provided that the reviewed source corpus, optimiser settings
and original full learning-rate schedule have not changed.

- [Supplement 19K — Reproducible AdamW Training Experiments and Verified Resume](19k-native-adamw-experiments-and-verifiable-resume.md)

These experiments still use a bounded native training batch; existing SGD
gradient accumulation is a separate capability. Exact checkpoint byte parity
does not authenticate a source corpus or claim production-ready language ability.


## Illustrated HTML learning course

The beginner-friendly [Umicom Native AI illustrated course](../../llm-course/index.html)
connects the source-based lessons into a navigable collection of standalone HTML
pages. The course uses the **existing** Umicom Foundation brand SVGs and font
stack, custom explanatory diagrams, glossary, beginner orientation, responsive
reading layout and previous/next navigation. Source Markdown remains here for
editorial review and the native C23 Framework remains the sole implementation
owner. No font binaries or scripting runtimes are redistributed.

- [Supplement 19L — AdamW Effective Batches and Exact Checkpoint Continuation](19l-adamw-effective-batches-and-checkpoint-continuation.md)


## Native benchmark and Umicom LLM product integration

Continue from the source-data and checkpoint lessons to an independently
reviewed, **read-only byte completion** measurement. The canonical C23
Framework owns every score and generation operation; a thin application
console displays the results without compiling or executing generated bytes.

- [Lesson 26 — Build a Native C23 Completion Benchmark](26-build-a-native-completion-benchmark.md)
- [Lesson 27 — Interpret Model Completion Metrics](27-interpret-model-completion-metrics.md)
- [Lesson 28 — Connect the Benchmark to Umicom LLM](28-connect-benchmark-to-umicom-llm.md)

These measurements are a teaching baseline, **not evidence of reliable C23
programming or production financial-system competence**.
