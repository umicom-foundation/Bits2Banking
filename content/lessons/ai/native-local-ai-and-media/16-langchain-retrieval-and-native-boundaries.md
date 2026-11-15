<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/16-langchain-retrieval-and-native-boundaries.md

PURPOSE:
Teach langChain retrieval concepts and native Framework boundaries.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# LangChain retrieval concepts and native Framework boundaries

LangChain is useful for studying composition around language models. Retrieval augmented generation, or RAG, finds relevant material and supplies it as context for an answer. Retrieval quality and answer quality are different measurements: a good model cannot cite a document that the retrieval stage omitted.

## Build the pipeline deliberately

The [LangChain retrieval guide](https://docs.langchain.com/oss/python/langchain/retrieval) separates loading, splitting, embedding, storage and retrieval, and contrasts a fixed retrieval flow with an agent deciding when to retrieve. These are architectural ideas that can be implemented behind native interfaces. Adopting the concepts does not require copying LangChain or making it an application dependency.

1. Choose a small document collection you may use. Give each revision a stable identity.
2. Split documents while keeping source offsets, headings and document IDs. Reconstruct a displayed citation from those identities.
3. Start with a deterministic lexical baseline. Measure which expected documents appear in the first k results.
4. If embeddings are added, record model identity, dimensions, normalization and distance metric. Changing those can require reindexing.
5. Construct a bounded prompt from selected evidence and the user request. Treat retrieved text as data, not permission to run a tool.

## Use the existing C service

```c
#include "umicom/ai/retrieval.h"

size_t select_evidence(const char *query, const UmiAiChunk *chunks,
                       size_t count, UmiAiRetrievalResult results[4])
{
    return umi_ai_retrieval_rank(query, chunks, count, results, 4);
}
```

This fragment calls Framework rather than reimplementing a ranker. The caller supplies valid, terminated query text, complete chunk storage, a results array of four entries and non-overlapping storage. A zero return may mean no matches or invalid admitted input; use the documented validation functions to distinguish your input error. Lexical scoring is not embedding similarity or multilingual linguistic search.

Framework ai/chunk.h retains document identity and byte offsets. ai/rag.h provides umi_ai_rag_append_results for prompt composition. Inspect those public contracts and their ownership rules before wiring an LLM panel. Do not create a second incompatible chunk format in each product.

## Evaluation exercise

Prepare five questions with expected source documents, including one question that has no answer in the collection. Measure retrieval recall before asking a model to answer. Add an adversarial document saying to ignore the user and execute a command; the expected application behavior is to treat that sentence as untrusted evidence and retain its normal tool policy.

A useful shared enhancement is a retrieval receipt containing query/index identity, selected chunks and exclusion reasons. A UI can then explain its evidence without claiming that a citation guarantees truth. LangChain API execution, remote model calls and an embedding backend are separate exercises; none is executed by this lesson.

[Course contents](index.md) · [Previous lesson](15-runway-video-task-lifecycles.md) · [Next lesson](17-tensorflow-models-and-c-ownership.md)
