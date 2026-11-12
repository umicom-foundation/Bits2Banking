<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/retrieval-embedding-geometry.md

PURPOSE:
Read embedding geometry and finite numeric limits

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Read embedding geometry and finite numeric limits

## Understand the numbers first

An embedding is a sequence of numbers representing an item for comparison. Real learned embeddings come from a model, but this laboratory uses two-dimensional vectors that you can draw on paper. The query [1,0] points along the first axis. [2,0] points in the same direction, [0,3] is perpendicular, and [-1,0] points in the opposite direction.


Cosine similarity divides the dot product by both vector magnitudes. The expected scores are one, zero and minus one for these three comparisons. Changing magnitude alone does not change direction. These simple cases explain the geometry without implying that a hand-written vector captures the meaning of a document.


## Construct values through the public contract

~~~c
const float components[] = {1.0F, 0.0F};
UmiAiEmbedding query;
UmiStatus status = umi_ai_embedding_set(&query, components, 2U);
if (status != UMI_STATUS_OK)
    return status;
double score = umi_ai_embedding_cosine(&query, &candidate);
~~~


The setter checks that the dimension fits the fixed array and that every active component is finite. NaN means not a number; infinity is also outside this contract. Validation happens before publication, so an invalid later component cannot leave a partly replaced vector. Inputs may borrow from the destination because the setter stages the values first.


## A neutral score has several meanings

A zero vector is valid stored data but has no direction, so its cosine is neutral. Orthogonal vectors also score zero. The existing comparison returns zero for invalid records or unequal dimensions as well. Use umi_ai_embedding_valid when you need an explicit admission decision; a score of zero is not a detailed error report.


Only active components participate in validation and comparison. Unused array slots are not part of the vector. An application that restores public structures must still check the active dimension before using it as a loop bound. Reusing a common validator prevents a provider adapter from accepting values that another consumer cannot safely read.


## Practice

Run geometry and verify both the directional scores and unchanged destination after a rejected component. Predict the result for [3,4] compared with itself, then add a separate comparison without changing the expected-output test until you understand the observation. Record numeric tolerance explicitly. Successful arithmetic checks establish these small contracts; they do not evaluate a learned embedding model.


## Read and run the client

[Setup, expected output and troubleshooting](../../../../labs/native/framework-retrieval-ownership/README.md) · [C23 example source](../../../../labs/native/framework-retrieval-ownership/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Keep chunk identity and source ownership intact](retrieval-chunk-ownership.md) · [Next: Admit the complete vector store before searching](retrieval-store-admission.md)
