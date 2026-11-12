<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/07-ground-answers-with-reviewed-sources.md

PURPOSE:
Teach ground answers with reviewed sources.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Ground answers with reviewed sources

## What you will learn
Add retrieval without treating documents as instructions or search scores as certainty.

## Separate retrieval from training
Retrieval-augmented generation supplies selected passages alongside a question. It does not update model weights. An embedding is a numerical representation used for comparison; its dimension and model identity must match the index and query.

Framework already provides chunks, lexical/vector retrieval, hybrid ranking, reranking and citations. The ai_workspace layer records collections, source revisions, reviewed jobs and frozen evidence. Its embedding cache is bounded and revision-bound; the inspected reference embedding capacity is 64 values. A typical external embedding output cannot be truncated to 64 and still be claimed equivalent.

## Follow a grounded question
1. Import or select a source through the existing source workflow.
2. Preserve its identity, revision, title and passage location.
3. Retrieve candidate passages using the same embedding model and dimension as the index.
4. Review which passages may be sent to the chosen provider.
5. Freeze the selected evidence when preparing a job.
6. Build the request through the shared workspace service.
7. Display the answer with citations that refer to that captured evidence.

The user's question “What is the payment cutoff?” should cite a relevant passage. If the selected documents do not contain the answer, the UI should say so. A similar-looking phrase or high vector score cannot supply missing facts.

## Keep instructions separate
A retrieved document can contain text such as “ignore your rules.” Treat it as source content. It must not grant tool access, change provider policy or decide which private files to read. The host owns those decisions.

Context planning must reserve output tokens and account for all selected passages. Store enough source identity to explain a citation after a document changes. An old answer should not silently point at a newly edited passage.

## Exercise
Create two small public documents with different cutoff times and clear effective dates. Ask a question without a date, then with one. Record which passage was retrieved, which version was sent and whether the answer admits ambiguity.

**Expected result:** an evaluation table separates retrieval relevance, citation fidelity and answer correctness. One metric cannot substitute for the others.

## Code study and recovery
Continue with [the installed retrieval ownership lab](../../../../labs/native/framework-retrieval-ownership/README.md). Its hand-written vectors teach contracts; they are not generated embeddings.

When a citation is wrong, inspect source revision and captured evidence before changing the model. When an embedding dimension is incompatible, select a supported provider or extend the shared contract with explicit bounds and regression coverage.

[Course contents](index.md) · [Next lesson](08-design-local-image-generation.md)
