<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/retrieval-hybrid-weights.md

PURPOSE:
Combine lexical and vector evidence with finite weights

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Combine lexical and vector evidence with finite weights

## Two signals can identify the same chunk

Hybrid retrieval combines lexical matches with vector matches. The reference implementation normalizes lexical scores relative to the strongest lexical candidate, weights both signals and merges entries with the same chunk ID. One chunk can therefore receive contributions from two routes while remaining one candidate. This is a scoring policy, not proof that the candidate answers a question.


In Hybrid, the laboratory uses one chunk that matches the query text and has the same vector direction. Default weights are one half for each route. The normalized lexical contribution and vector contribution each add one half, so the expected combined score is one. Read the actual candidate count as well as the score to verify merging.


## Make the weights explicit

~~~c
UmiAiHybridRetrievalSettings settings =
    umi_ai_hybrid_retrieval_settings_default();
settings.lexical_weight = 0.75;
settings.vector_weight = 0.25;
size_t count = umi_ai_hybrid_retrieval_rank(
    "target", chunks, chunk_count, &store, &embedding,
    &settings, NULL, results, result_capacity);
~~~


Weights must be finite, but the service does not automatically normalize them. Existing signed weights remain supported. A candidate limit of zero or a value beyond the supported limit retains the established clamp. Document the policy your application chooses instead of relying on users to infer it from a settings screen.


## Finite inputs can still overflow

Two individually finite contributions can sum to infinity. The laboratory sets both weights to DBL_MAX to exercise this boundary with a single merged candidate. The shared result validator rejects the resulting non-finite score before reranker callbacks or output publication. The previously accepted result array remains unchanged.


When both vector arguments are present, malformed vector data is a refusal rather than a silent lexical-only blend. Supplying either vector argument as null deliberately selects the existing lexical fallback. These are different states: an unavailable optional route can be a supported mode, while a supplied but corrupted route requires investigation.


## Practice

Run hybrid and explain the expected score using the two contributions. Try a reviewed finite weighting in a separate experiment and record the resulting order. Keep arithmetic validation separate from retrieval-quality evaluation. The latter needs representative questions, known relevant documents and a declared measurement; this tiny fixture only checks composition, merging and failure preservation.


## Read and run the client

[Setup, expected output and troubleshooting](../../../../labs/native/framework-retrieval-ownership/README.md) · [C23 example source](../../../../labs/native/framework-retrieval-ownership/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Select top matches without losing stable order](retrieval-stable-top-matches.md) · [Next: Keep callback failures from publishing partial scores](retrieval-callback-ownership.md)
