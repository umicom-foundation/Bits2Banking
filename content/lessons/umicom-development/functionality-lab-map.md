# Framework functionality: a learning and lab map

Umicom Framework supplies reusable engines. Applications connect those engines to commands, windows and domain workflows. This map helps you find a service, understand its contract and practise using it without creating a competing implementation inside an application.

Start with one row. Finish its small exercise before combining it with another service. A source-reading lesson and a runnable lab teach different skills; the table distinguishes them. This is a curated route, not a claim that every Framework function already has a complete tutorial.

## Setup recap

For reading, use the Bits2Banking website or these Markdown pages and a Framework source checkout. For C exercises, install a C23 compiler, CMake and Ninja using [the terminal guide](../learning-c/terminal-lab.md). Installed-SDK labs require a compatible Framework package; [SDK setup](06-use-an-installed-sdk.md) explains the paths. Kernel and training labs state their separate requirements. You can follow the text without an account or private production data.

## 1. Build a small, understandable foundation

| Functionality | Read and practise | Code to inspect |
|---|---|---|
| C values, lengths and capacities | [Length/capacity exercise](../learning-c/19-length-capacity-and-terminators.md) | `labs/native/framework-hash/main.c` in Bits2Banking |
| Calling an installed Framework library | [Complete SDK consumer lab](37-use-a-framework-function-in-a-lab.md) | `include/umicom/base/sha256.h` |
| Incremental state and failure handling | [State and refusal lab](38-incremental-functions-and-failure-contracts.md) | `UmiSha256Init`, `Update`, `Final`, `Hex`, `Buffer` |
| A small C service and optional GTK4 window | [Activity counter lab](sdk-practical-lab.md) | `labs/native/framework-activity` in Bits2Banking |
| Defining a shared feature before editing | [Feature map exercise](36-map-a-shared-feature-before-changing-it.md) | The activity contract, implementation and tests |

The activity counter is a teaching consumer. SHA-256 remains a Framework service. A teaching example does not become the production owner merely because it demonstrates an API.

## 2. Follow application services into real workflows

| Functionality | Available lesson or lab | Practice objective |
|---|---|---|
| Service registration | [Register shared services](11-register-shared-services.md) | Find the owner, registration and caller |
| Service inspection | [Inspect application services](12-inspect-application-services.md) | Explain missing versus registered services |
| Background work | [Close background work](10-close-background-work.md) | Trace cancellation and lifetime |
| Waiting and deadlines | [Event deadline lab](event-deadline-lab.md) | Follow work without an endless wait |
| Protocol boundaries | [Follow message boundaries](22-follow-protocol-message-boundaries.md) | Separate complete messages from fragments |
| Tool connections | [Validate a connection](25-validate-a-tool-connection.md) | Identify configuration and failure paths |
| Offline learning | [Build a reader](13-build-an-offline-learning-reader.md) | Follow a lesson from catalogue to view |
| Learning progress | [Revision-bound checkpoints](16-keep-revision-bound-checkpoints.md) | Keep progress attached to its source |
| Worker persistence | [Store checkpoints on a worker](18-store-checkpoints-on-a-worker.md) | Identify who owns the pending write |
| Text search | [Find text with shared services](24-find-text-with-shared-services.md) | Trace query, result and selection |
| Commands and help | [Connect commands to guides](15-connect-commands-to-guides.md) | Link a command to useful instructions |
| Layout and document drafts | [Check layout and draft retention](34-check-layout-and-draft-retention.md) | Define what must survive a layout change |
| Market calendars | [Read calendar data](35-read-calendar-data-without-inventing-values.md) | Distinguish missing values from zero |

Most entries in this second table are source-reading exercises. Follow their own commands only where they provide a runnable lab. A diagram or a wired button is not evidence that a whole application workflow passed.

## 3. Extend into models and ledgers

| Functionality | Practical route | Framework contract |
|---|---|---|
| Byte tokenisation | [Round-trip lab](../10-native-ai/byte-tokenizer-contract-lab.md) | `UmiAiByteEncode`, `UmiAiByteDecode` |
| Training/evaluation split | [Sequence partition lab](../10-native-ai/sequence-split-contract-lab.md) | `UmiAiTrainingSplitSequences` |
| First model training | [First training experiment](../10-native-ai/first-training-run.md) | Existing native LLM learning project |
| Digest-linked records | [Hash-chain lab](../14-blockchain-ledgers/building-blockchain-from-scratch/04-link-records-with-framework-hashes.md) | Framework SHA-256; consumer-defined record format |

Keep these specialist routes separate from the initial C sequence. Each begins with a setup recap and links back to concepts needed for its exercise.

## 4. Turn an uncovered function into a lesson

For a function without a lab, use this order:

1. Locate its public header and implementation. Record the parameter units and permitted null values.
2. Describe ownership, valid call order, successful output and failure behaviour in plain language.
3. Find existing callers and tests. Reuse the engine rather than copying its implementation.
4. Create one small valid example, one boundary example and one refused request. Predict the results first.
5. Add an extension exercise, recovery instructions and links back to the course. Keep a Markdown and HTML edition together.

Dedicated beginner labs for document open/save/close, Kanban card lifecycle, media generation jobs and persistent financial operations remain follow-on topics. Their current source and tests must be inspected before describing supported end-to-end behaviour. Study the existing reading routes now; do not substitute invented APIs for a missing example.

Return to [Learning Umicom Framework](index.md) or begin the [SDK function lab](37-use-a-framework-function-in-a-lab.md).

## Follow a service across layers

Use these source studies after the introductory practical labs. Each identifies the code to open, traces one responsibility and supplies a worked check.

- [Trace an event to a shared Framework rule](39-trace-an-event-to-a-framework-rule.md)
- [Own state for the lifetime of a window](../06-umicom/learning-gtk4/03-own-state-for-a-window.md)
- [Reject an invalid port before starting a server](../05-engineering/building-a-web-server-in-c/08-reject-an-invalid-port-before-launch.md)
- [Follow a discount factor and its failure paths](../07-practical-domains/financial-instruments-pricing/04-follow-a-discount-factor-and-its-failures.md)
- [Lab: trace a stable job queue](../12-distributed-learning/priority-queue-reading-lab.md)
- [Lab: measure a model without changing its checkpoint](../10-native-ai/checkpoint-observation-lab.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](85-check-real-ai-client-boundaries.md) · [Next lesson](learning-module-files-and-identities.md)
