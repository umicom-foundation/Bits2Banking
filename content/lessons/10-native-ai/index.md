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

## Native training laboratory — Batch 01 (20 October 2026)

The first implementation batch adds a Framework-owned, bounded CPU training tape with row-major float32 matrices, matrix multiplication, broadcast addition, ReLU, mean-squared-error loss, stable cross-entropy, reverse-mode autodifferentiation, SGD, and six CTest regression checks. The included C23 example trains a **three-token bigram model** from zero weights. It **does not** yet train a transformer or provide attention, checkpoint persistence, a production tokenizer or domain experts.

New course lessons accompanying this implementation:

- [02. Training data and evaluation](02-training-data-and-evaluation.md)
- [03. Tokens, vocabulary and encoding](03-tokens-vocabulary-and-encoding.md)
- [04. Logits, softmax and cross-entropy](04-logits-softmax-and-cross-entropy.md)
- [05. Tensor shapes and ownership](05-tensor-shapes-and-ownership.md)
- [06. Matrix operations and activations](06-matrix-operations-and-activations.md)
- [07. Gradients and backpropagation](07-gradients-and-backpropagation.md)
- [08. Optimisers and first training run](08-optimisers-and-first-training-run.md)

The educational package retains the original [Lesson 01](01-from-source-text-to-learning.md). Every experiment compiles against existing `umicom/base/status.h` in the actual Framework checkout. See the batch merge guide for exact PowerShell build and Git commands.

## Native training laboratory — Batch 02: learned embeddings and causal attention

Batch 02 adds seeded C23 parameter initialisation, a bounded logical
`[batch,time,channels]` sequence layout, differentiable embedding lookup with
repeated-token scatter gradients, and trainable single-head scaled dot-product
causal attention. It includes six new registered checks (five focused unit
and gradient tests plus a tiny context-dependent training demonstration).
The six Batch 01 tests are preserved. This is **not** yet a complete transformer.

- [09. Seeded initialisation and token embeddings](09-seeded-initialisation-and-token-embeddings.md)
- [10. Causal self-attention and context-sensitive training](10-causal-self-attention-and-context.md)

The accompanying source is in the existing Framework training tape and
`framework/learning/native-llm/train_attention.c`, not in a second AI engine.
The remote Framework baseline is inspected in the Batch 02 merge guide; the
standalone laboratory remains available even when the very large root CMake
file has not yet registered the optional training module.
