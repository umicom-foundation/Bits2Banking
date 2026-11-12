![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Study retrieval ownership with the installed Framework SDK

This C23 client uses real Umicom AI services for chunks, embeddings, lexical ranking, vector stores, hybrid composition and optional reranking. Seven scenarios check their observations before printing them. The vectors are hand-written examples; no model is trained and no network request is made.

## Prepare the matching installation

1. Qualify and install the corresponding Framework source through the owner workflow.
2. Confirm that the installed AI component exports the chunk, embedding, store and retrieval validators used in main.c.
3. Use one installation for both headers and libraries. Adjust the prefix below if your installation differs.
4. Run each command separately and stop on errors.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-retrieval-ownership"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
ctest --test-dir build --output-on-failure
.\build\btb-framework-retrieval-ownership.exe rerank
~~~

These commands have not been executed for this authored lab. The expected result is seven passing CTest cases. Each compares the complete output, exit zero and an empty error stream.

## Follow the scenarios

| Argument | Expected observation | Contract |
| --- | --- | --- |
| chunk | Borrowed strings survive; overflow leaves the old record | Staged construction and byte offsets |
| geometry | Scores 1, 0 and -1; invalid input leaves the embedding | Finite vector admission |
| lexical | Repeated match first; malformed late chunk refuses output | Whole-input preflight |
| store | Oversized count refuses both add and search | Owner extent admission |
| top | Indices 0, 3, 1 | Stable descending top matches |
| hybrid | One combined score of 1; overflowing blend refused | Finite merged scores |
| rerank | Two calls before refusal; old output survives | Callback publication and side effects |

The rerank scenario expects:

~~~text
Late callback refusal: 2 calls, output retained
Finite reranking: scores -1, -2
Local retrieval only; no model training or network request.
~~~

A successful scenario can include a deliberately refused operation. The successful observation is that the error and preservation contract matched the prediction.

## Read the owner boundaries

Large fixed records use static fixture storage because this program runs one scenario serially. A concurrent application needs its own established lifetime and synchronization policy.

The chunk and embedding constructors capture borrowed input before replacing the destination. The store validates every active row before publishing output. Search indices refer to the current store; copy a record when it must outlive that observation.

Reranker callbacks receive temporary borrowed chunks. Do not retain their addresses, cast away const or mutate the result owner. A callback counter remains changed after a later refusal. Candidate publication protects the result array; it cannot undo arbitrary external callback effects.

## Check branding and integration

The installed application-branding helper stages the approved SVG resources and embeds the approved Windows ICO through RC. NO_RUNTIME_DEPLOYMENT avoids requesting GTK deployment for a console example. Inspect the actual staged resources and visible icon during owner qualification; static identity checks do not establish rendered appearance.

The paired lessons use the canonical learning stylesheet and its Segoe UI and Cascadia Code fallback families. Continue with [the retrieval module](../../../content/courses/llm-from-scratch/lessons/retrieval-and-model-training.html).

## Troubleshoot without hiding evidence

- Missing component: verify that CMAKE_PREFIX_PATH selects a complete matching Framework installation.
- Missing symbol: compare installed headers and libraries with the source revision containing the new validators.
- Runtime loader failure: inspect the linked installation and runtime dependency search path before changing the client.
- Observation mismatch: retain the scenario name, diagnostic, toolchain and exact revision. Do not replace the check with unconditional success.
- All scenarios pass: report those actual local contracts. Model quality, provider networking, concurrent UI lifetimes and training remain separate qualification work.

Read the public Framework guides ai-vector-admission.md and ai-retrieval-publication.md for the service-level regression targets.
