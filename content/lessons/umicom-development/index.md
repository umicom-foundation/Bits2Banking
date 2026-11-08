# Umicom Framework Development

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## First application: one example from source to a window

After Learning C, follow the exercise counter through its Framework interface, build description, console and GTK4 window. The C introduction is a recap, not a replacement for the C course.

1. [Introduction to C programming](01-introduction-to-c.md)
1. [Introduction to Umicom Framework](02-introduction-to-framework.md)
1. [Introduction to CMake](03-introduction-to-cmake.md)
1. [Use an installed Framework SDK](06-use-an-installed-sdk.md)
1. [Umicom Framework Development](04-framework-development.md)
1. [Introduction to GTK4](05-introduction-to-gtk4.md)

## Build, test and investigate a change

Use the same project to learn incremental builds, diagnostics and test commands. Continue with test data and skipped coverage after understanding a normal run.

1. [Build only what changed](07-build-only-what-changed.md)
1. [Read build and test evidence](08-read-build-and-test-evidence.md)
1. [Understand which program a test runs](09-understand-test-commands.md)
1. [Keep test data separate from your work](30-keep-test-data-separate.md)
1. [Understand skipped tests and host coverage](31-understand-skipped-tests-and-host-coverage.md)

## Shared services and application lifetimes

Further source studies after the first application. Follow registration and inspection before asynchronous work, waiting and connection boundaries.

1. [Register shared application services](11-register-shared-services.md)
1. [Inspect application services](12-inspect-application-services.md)
1. [Close background work safely](10-close-background-work.md)
1. [Understand waiting and timeouts](28-understand-waiting-and-timeouts.md)
1. [Follow protocol message boundaries](22-follow-protocol-message-boundaries.md)
1. [Validate a tool connection](25-validate-a-tool-connection.md)

## Project study: an offline learning reader

A separate project after shared services. Start with the reader and safe example copying, then add help, checkpoints, text and images in that order.

1. [Build an offline learning reader](13-build-an-offline-learning-reader.md)
1. [Copy examples without overwriting your work](14-copy-examples-without-overwriting.md)
1. [Connect commands to helpful guides](15-connect-commands-to-guides.md)
1. [Connect keyboard and button help](21-connect-keyboard-and-button-help.md)
1. [Keep learning checkpoints with their source revision](16-keep-revision-bound-checkpoints.md)
1. [Keep reading state consistent](17-keep-reading-state-consistent.md)
1. [Store checkpoints on a worker](18-store-checkpoints-on-a-worker.md)
1. [Remember locations without inheriting trust](19-remember-locations-without-inheriting-trust.md)
1. [Preserve structure when reading code](20-preserve-structure-when-reading-code.md)
1. [Carry image pixels from a worker to a window](23-carry-image-pixels-to-a-window.md)
1. [Find text with shared Framework services](24-find-text-with-shared-services.md)
1. [Search verified learning resources](26-search-verified-learning-resources.md)
1. [Open search results without losing your place](27-open-search-results-without-losing-your-place.md)

## Project study: application workspaces

After GTK4 events and shared services, study projects, panels, keyboard focus and retained work.

1. [Remember projects without deleting their files](29-remember-projects-without-deleting-files.md)
1. [Use Studio, Trader and Media workspaces](32-use-application-workspaces.md)
1. [Navigate panels with the keyboard](33-follow-keyboard-focus.md)
1. [Check layouts without losing your work](34-check-layout-and-draft-retention.md)

## Optional application study: calendar data

A trading-data example after the core development route; it is not a prerequisite for C or GTK4.

1. [Read calendar data without inventing values](35-read-calendar-data-without-inventing-values.md)

## Consolidation: map a shared feature

Trace the same example through its public contract, implementation, consumers and checks.

1. [Map a shared feature before changing it](36-map-a-shared-feature-before-changing-it.md)

## Practical contracts and memory

Apply the preceding ideas to small, source-backed examples. Read the setup recap before each lab.

1. [Use a Framework function in a practical lab](37-use-a-framework-function-in-a-lab.md)
1. [Incremental functions and failure contracts](38-incremental-functions-and-failure-contracts.md)
1. [Trace an event to a shared Framework rule](39-trace-an-event-to-a-framework-rule.md)

## Project: one C model across platforms

Follow the shared model through desktop, browser, mobile and sampled-device inputs. Each adapter has its own build and evidence boundary.

1. [Plan one C model for several interfaces](40-one-model-several-interfaces.md)
1. [Validate values at a platform boundary](41-signed-values-at-a-platform-boundary.md)
1. [Connect a desktop event to owned state](42-desktop-events-and-state.md)
1. [Call the shared C model from a browser](43-call-c-from-a-browser.md)
1. [Connect mobile screens without copying the rule](44-mobile-bindings-without-duplicated-rules.md)
1. [Model a sampled button for a small device](45-sampled-buttons-on-small-devices.md)
1. [Keep platform builds and evidence separate](46-build-targets-and-platform-evidence.md)
1. [Test both the shared rule and the user journey](47-test-adapters-and-user-journeys.md)

## Project: a microdevice client

Cross-compile the shared C model, sample a button and record the actual device observation.

1. [Share a C model with a microdevice](48-share-a-model-with-a-microdevice.md)
1. [Understand a cross-compiled build](49-understand-a-cross-compiled-build.md)
1. [Read a button as a sampled signal](50-read-a-button-as-a-sampled-signal.md)
1. [Record a device observation](51-record-a-device-observation.md)

## Project: SDK hashing and record identity

Call the installed SDK, count bytes and capacities, then define an ordered serialization and retained chain head.

1. [Use an SDK service without copying it](52-use-an-sdk-service-without-copying-it.md)
1. [Count input bytes and output capacity](53-count-input-bytes-and-output-capacity.md)
1. [Feed a hash in ordered chunks](54-feed-a-hash-in-ordered-chunks.md)
1. [Finish a context once](55-finish-a-context-once.md)
1. [Retain a usable context after rejected input](56-retain-a-usable-context-after-rejected-input.md)
1. [Serialize fields before hashing](57-serialize-fields-before-hashing.md)
1. [Separate hash domains](58-separate-hash-domains.md)
1. [Interpret a retained chain head](59-interpret-a-retained-chain-head.md)

## AI foundations: byte tokens

Use the actual Framework tokenizer to preserve arbitrary bytes and validate complete token sequences.

1. [Introduce byte token identities](60-introduce-byte-token-identities.md)
1. [Preserve zero bytes in input](61-preserve-zero-bytes-in-input.md)
1. [Measure token buffer capacity](62-measure-token-buffer-capacity.md)
1. [Separate special tokens from text](63-separate-special-tokens-from-text.md)
1. [Validate every ID before decoding](64-validate-every-id-before-decoding.md)
1. [Decode with a count, not a terminator](65-decode-with-a-count-not-a-terminator.md)
1. [Round-trip a multibyte character](66-round-trip-a-multibyte-character.md)
1. [Design tokenizer contract cases](67-design-tokenizer-contract-cases.md)

## AI foundations: dataset partitions

Separate training from evaluation, follow seeded shuffling and document its limitations.

1. [Separate training and evaluation examples](68-separate-training-and-evaluation-examples.md)
1. [Shuffle identities without copying corpus](69-shuffle-identities-without-copying-corpus.md)
1. [Follow a bounded shuffle step](70-follow-a-bounded-shuffle-step.md)
1. [Record the seed and data identity](71-record-the-seed-and-data-identity.md)
1. [Check the dataset-split boundary](72-check-the-dataset-split-boundary.md)
1. [Publish a complete split](73-publish-a-complete-split.md)
1. [Understand a sampler's limits](74-understand-a-samplers-limits.md)
1. [Review a split before training](75-review-a-split-before-training.md)

## AI foundations: gradient measurement

Measure one global norm across arrays and derive a shared clipping scale without altering inputs.

1. [Measure a gradient vector](76-measure-a-gradient-vector.md)
1. [Measure several parameter arrays together](77-measure-several-parameter-arrays-together.md)
1. [Derive a common clipping scale](78-derive-a-common-clipping-scale.md)
1. [Leave small gradients unchanged](79-leave-small-gradients-unchanged.md)
1. [Reject nonfinite gradient input](80-reject-nonfinite-gradient-input.md)
1. [Avoid overflow while measuring](81-avoid-overflow-while-measuring.md)
1. [Publish a gradient report together](82-publish-a-gradient-report-atomically.md)
1. [Write a gradient-measurement lab record](83-write-a-gradient-measurement-lab-record.md)

## Project: a Framework AI client

Compile two original Framework services with a small consumer and exercise their failure contracts.

1. [Build the Framework AI contract lab](84-build-the-framework-ai-contract-lab.md)
1. [Check real AI client boundaries](85-check-real-ai-client-boundaries.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

# Umicom Framework Development

Follow First application, then Build, test and investigate a change. Continue with one source-study project at a time.

[Beginner sequence](../../start/learning-sequence.md) · [Browser course](../../courses/umicom-development/index.html)

## First application: one example from source to a window

After Learning C, follow the exercise counter through its Framework interface, build description, console and GTK4 window. The C introduction is a recap, not a replacement for the C course.

1. [Introduction to C programming](01-introduction-to-c.md)
2. [Introduction to Umicom Framework](02-introduction-to-framework.md)
3. [Introduction to CMake](03-introduction-to-cmake.md)
4. [Use an installed Framework SDK](06-use-an-installed-sdk.md)
5. [Umicom Framework Development](04-framework-development.md)
6. [Introduction to GTK4](05-introduction-to-gtk4.md)

## Build, test and investigate a change

Use the same project to learn incremental builds, diagnostics and test commands. Continue with test data and skipped coverage after understanding a normal run.

1. [Build only what changed](07-build-only-what-changed.md)
2. [Read build and test evidence](08-read-build-and-test-evidence.md)
3. [Understand which program a test runs](09-understand-test-commands.md)
4. [Keep test data separate from your work](30-keep-test-data-separate.md)
5. [Understand skipped tests and host coverage](31-understand-skipped-tests-and-host-coverage.md)

## Shared services and application lifetimes

Further source studies after the first application. Follow registration and inspection before asynchronous work, waiting and connection boundaries.

1. [Register shared application services](11-register-shared-services.md)
2. [Inspect application services](12-inspect-application-services.md)
3. [Close background work safely](10-close-background-work.md)
4. [Understand waiting and timeouts](28-understand-waiting-and-timeouts.md)
5. [Follow protocol message boundaries](22-follow-protocol-message-boundaries.md)
6. [Validate a tool connection](25-validate-a-tool-connection.md)

## Project study: an offline learning reader

A separate project after shared services. Start with the reader and safe example copying, then add help, checkpoints, text and images in that order.

1. [Build an offline learning reader](13-build-an-offline-learning-reader.md)
2. [Copy examples without overwriting your work](14-copy-examples-without-overwriting.md)
3. [Connect commands to helpful guides](15-connect-commands-to-guides.md)
4. [Connect keyboard and button help](21-connect-keyboard-and-button-help.md)
5. [Keep learning checkpoints with their source revision](16-keep-revision-bound-checkpoints.md)
6. [Keep reading state consistent](17-keep-reading-state-consistent.md)
7. [Store checkpoints on a worker](18-store-checkpoints-on-a-worker.md)
8. [Remember locations without inheriting trust](19-remember-locations-without-inheriting-trust.md)
9. [Preserve structure when reading code](20-preserve-structure-when-reading-code.md)
10. [Carry image pixels from a worker to a window](23-carry-image-pixels-to-a-window.md)
11. [Find text with shared Framework services](24-find-text-with-shared-services.md)
12. [Search verified learning resources](26-search-verified-learning-resources.md)
13. [Open search results without losing your place](27-open-search-results-without-losing-your-place.md)

## Project study: application workspaces

After GTK4 events and shared services, study projects, panels, keyboard focus and retained work.

1. [Remember projects without deleting their files](29-remember-projects-without-deleting-files.md)
2. [Use Studio, Trader and Media workspaces](32-use-application-workspaces.md)
3. [Navigate panels with the keyboard](33-follow-keyboard-focus.md)
4. [Check layouts without losing your work](34-check-layout-and-draft-retention.md)

## Optional application study: calendar data

A trading-data example after the core development route; it is not a prerequisite for C or GTK4.

1. [Read calendar data without inventing values](35-read-calendar-data-without-inventing-values.md)

## Practise with the source

The [Framework project walkthrough](../../umicom/development-path.md) maps each file to its role and explains how to change, build and check the example.


## Consolidation: map a shared feature

After the earlier modules, trace the same example through its contract, implementation, consumers and checks.

1. [Map a shared feature before changing it](36-map-a-shared-feature-before-changing-it.md)


## Course outline: later topics

New shared services, documentation, SDK consumers and application integration.

[Choose another subject](../../start/course-series.md).

## Step-by-step practical labs

Each lab includes a setup recap, commands, expected results and a repair exercise. Work in a practice folder.

- [Build and check the Framework activity example](sdk-practical-lab.md)
- [Investigate an event-loop timeout](event-deadline-lab.md)

## Practical labs: read, change and check

Follow these after the introductory lessons. Each lab includes its own setup recap and explains the expected result.

- [Use a Framework function in a practical lab](37-use-a-framework-function-in-a-lab.md)
- [Incremental functions and failure contracts](38-incremental-functions-and-failure-contracts.md)
- [Framework functionality: a learning and lab map](functionality-lab-map.md)

## Continue with a practical source study

A button becomes useful when its event reaches a rule and the result reaches the screen. This lab makes that path visible using the existing activity window. It is a small teaching example of the separation used by Umicom applications.

- [Trace an event to a shared Framework rule](39-trace-an-event-to-a-framework-rule.md)



## Continue with practical labs

1. [Plan one C model for several interfaces](40-one-model-several-interfaces.md)
1. [Validate values at a platform boundary](41-signed-values-at-a-platform-boundary.md)
1. [Connect a desktop event to owned state](42-desktop-events-and-state.md)
1. [Call the shared C model from a browser](43-call-c-from-a-browser.md)
1. [Connect mobile screens without copying the rule](44-mobile-bindings-without-duplicated-rules.md)
1. [Model a sampled button for a small device](45-sampled-buttons-on-small-devices.md)
1. [Keep platform builds and evidence separate](46-build-targets-and-platform-evidence.md)
1. [Test both the shared rule and the user journey](47-test-adapters-and-user-journeys.md)


- [Share a C model with a microdevice](48-share-a-model-with-a-microdevice.md)

- [Understand a cross-compiled build](49-understand-a-cross-compiled-build.md)

- [Read a button as a sampled signal](50-read-a-button-as-a-sampled-signal.md)

- [Record a device observation](51-record-a-device-observation.md)

- [Use an SDK service without copying it](52-use-an-sdk-service-without-copying-it.md)

- [Count input bytes and output capacity](53-count-input-bytes-and-output-capacity.md)

- [Feed a hash in ordered chunks](54-feed-a-hash-in-ordered-chunks.md)

- [Finish a context once](55-finish-a-context-once.md)

- [Retain a usable context after rejected input](56-retain-a-usable-context-after-rejected-input.md)

- [Serialize fields before hashing](57-serialize-fields-before-hashing.md)

- [Separate hash domains](58-separate-hash-domains.md)

- [Interpret a retained chain head](59-interpret-a-retained-chain-head.md)

- [Introduce byte token identities](60-introduce-byte-token-identities.md)

- [Preserve zero bytes in input](61-preserve-zero-bytes-in-input.md)

- [Measure token buffer capacity](62-measure-token-buffer-capacity.md)

- [Separate special tokens from text](63-separate-special-tokens-from-text.md)

- [Validate every ID before decoding](64-validate-every-id-before-decoding.md)

- [Decode with a count, not a terminator](65-decode-with-a-count-not-a-terminator.md)

- [Round-trip a multibyte character](66-round-trip-a-multibyte-character.md)

- [Design tokenizer contract cases](67-design-tokenizer-contract-cases.md)

- [Separate training and evaluation examples](68-separate-training-and-evaluation-examples.md)

- [Shuffle identities without copying corpus](69-shuffle-identities-without-copying-corpus.md)

- [Follow a bounded shuffle step](70-follow-a-bounded-shuffle-step.md)

- [Record the seed and data identity](71-record-the-seed-and-data-identity.md)

- [Check the dataset-split boundary](72-check-the-dataset-split-boundary.md)

- [Publish a complete split](73-publish-a-complete-split.md)

- [Understand a sampler's limits](74-understand-a-samplers-limits.md)

- [Review a split before training](75-review-a-split-before-training.md)

- [Measure a gradient vector](76-measure-a-gradient-vector.md)

- [Measure several parameter arrays together](77-measure-several-parameter-arrays-together.md)

- [Derive a common clipping scale](78-derive-a-common-clipping-scale.md)

- [Leave small gradients unchanged](79-leave-small-gradients-unchanged.md)

- [Reject nonfinite gradient input](80-reject-nonfinite-gradient-input.md)

- [Avoid overflow while measuring](81-avoid-overflow-while-measuring.md)

- [Publish a gradient report together](82-publish-a-gradient-report-atomically.md)

- [Write a gradient-measurement lab record](83-write-a-gradient-measurement-lab-record.md)

- [Build the Framework AI contract lab](84-build-the-framework-ai-contract-lab.md)

- [Check real AI client boundaries](85-check-real-ai-client-boundaries.md)

</details>

## Observe files and qualify evidence

- [Distinguish file bytes from version responses](evidence-bytes-and-version-strings.md)
- [Validate a complete file selection before reading](evidence-selection-before-reading.md)
- [Own an observation independently of its inputs](evidence-observation-ownership.md)
- [Bound one file and the complete request](evidence-file-and-total-budgets.md)
- [Write complete JSON values into bounded buffers](evidence-complete-json-values.md)
- [Preserve earlier evidence when saving a report](evidence-exclusive-report-files.md)
- [Compare selected bytes before and after a run](evidence-before-after-comparison.md)
- [Separate selected libraries from loaded runtime identity](evidence-runtime-and-patch-identity.md)

## Restart an owned program

- [Choose the operation you actually own](restart-own-the-right-operation.md)
- [Separate a stop request from completion](restart-request-is-not-completion.md)
- [Retain the old result before a new run](restart-retain-the-old-result.md)
- [Recheck project authority after waiting](restart-renew-project-authority.md)
- [Keep Stop effective across thread boundaries](restart-preserve-cross-thread-stop.md)
- [Preserve separate transcripts for each run](restart-retain-separate-transcripts.md)
- [Connect a menu action to normal refresh](restart-connect-menu-and-refresh.md)
- [Qualify restart at each ownership boundary](restart-qualify-each-layer.md)

## Execute a reviewed development lifecycle

- [Admit the whole request before work starts](workflow-admit-the-whole-request.md)
- [Map descriptive stages to real actions](workflow-plan-stages-and-real-actions.md)
- [Check every host capability before execution](workflow-check-every-host-capability.md)
- [Keep borrowed request data alive](workflow-borrowed-inputs-and-lifetime.md)
- [Report attempted and completed actions separately](workflow-attempted-and-completed-evidence.md)
- [Separate previews from optional audit policy](workflow-preview-and-optional-audits.md)
- [Forward only options with defined meaning](workflow-adapters-and-option-scope.md)
- [Qualify a workflow through distinct layers](workflow-qualify-the-integration-layers.md)

## Deployment state and evidence

Rehearse the actual Framework plan and controller, including bounded admission, content-specific approval, cancellation, rollback and revision limits.

- [Separate a deployment model from real operations](deployment-models-and-real-providers.md)
- [Admit bounded deployment values before reading them](deployment-bounded-public-values.md)
- [Publish a complete replacement plan](deployment-publish-a-complete-plan.md)
- [Keep approval attached to the reviewed content](deployment-approval-follows-content.md)
- [Give one deployment step the execution slot](deployment-one-running-step.md)
- [Preserve cancellation when the running step returns](deployment-stop-and-completion-evidence.md)
- [Report rollback progress without erasing failure](deployment-rollback-and-phase-progress.md)
- [Qualify revision limits and deployment layers](deployment-revisions-and-layered-qualification.md)

## Task admission and ownership

Build safe task descriptors, publish owned values and distinguish local validation from graph and execution evidence.

- [Validate task storage before task meaning](task-descriptor-storage-before-meaning.md)
- [Change a command and directory together](task-command-and-directory-transaction.md)
- [Publish task values into an owning registry](task-registry-owning-public-values.md)
- [Treat revisions as identities that cannot wrap](task-revision-refusal-and-reset.md)
- [Separate local task validity from dependency validity](task-descriptors-and-dependency-graphs.md)
- [Qualify task behavior at source and SDK boundaries](task-source-sdk-and-runtime-evidence.md)

## Dependency graph transactions

Preserve running workflows during rejected replacements, model dependency policy and qualify graph observations independently of process execution.

- [Keep a running graph when replacement is invalid](task-graph-rejected-replacement.md)
- [Compute readiness across chains and diamonds](task-graph-readiness-and-diamonds.md)
- [Distinguish blocked work from permitted continuation](task-graph-failure-and-skip-policy.md)
- [Retry a failed task without erasing its attempt budget](task-graph-retry-and-attempts.md)
- [Cancel waiting work while preserving running-process ownership](task-graph-cancellation-and-process-ownership.md)
- [Verify graph transactions across public and private boundaries](task-graph-transactions-and-regression-evidence.md)

## Task operation ownership

Select dependency-closed plans, bound traversal memory and coordinate parallel lifecycle changes through one shared owner.

- [Select a task and its complete dependency closure](orchestration-select-a-dependency-closure.md)
- [Bound dependency traversal without recursive task copies](orchestration-explicit-depth-first-frames.md)
- [Keep accepted plans separate from editable source tasks](orchestration-owned-plans-and-source-edits.md)
- [Admit parallel work through one owning orchestrator](orchestration-parallel-slots-and-outcomes.md)
- [Distinguish stopping, retrying and finishing an operation](orchestration-stop-retry-and-finish.md)
- [Qualify orchestration across owner and child boundaries](orchestration-layered-regression-evidence.md)
