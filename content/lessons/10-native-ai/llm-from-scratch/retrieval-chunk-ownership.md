<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/retrieval-chunk-ownership.md

PURPOSE:
Keep chunk identity and source ownership intact

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Keep chunk identity and source ownership intact

## A chunk is more than a string

A retrievable chunk contains its text, a document identifier, a chunk identifier and source offsets. The constructor generates an identifier by joining the document ID, a colon and the chunk index. Offsets count bytes, so do not interpret them as screen columns or Unicode character positions. An editor needs a separate mapping from source bytes to its visible coordinates.


Open ChunkOwnership in the laboratory. It starts with the word sample, then passes the destination document ID and a pointer to the second text byte back into the constructor. Those pointers borrow storage from the very record being replaced. Clearing the record first would erase the input before it could be read.


## Capture before publishing

~~~c
UmiStatus status = umi_ai_chunk_set(
    &chunk, chunk.document_id, 7U, 10U, chunk.text + 1U);
if (status != UMI_STATUS_OK)
    return status;
~~~


Framework prepares a separate candidate, reads both borrowed strings and formats the generated ID before publishing. The example becomes guide:7, with text ample and offsets 10 through 15. A failed replacement preserves the previous complete record. This is useful when a document browser is editing metadata that the user has already accepted.


## Distinguish the two length limits

A document ID may fit its own array while the generated chunk ID does not fit after the colon and index are appended. Both capacities must be checked. The text must terminate inside its own capacity, and adding its byte length to the start offset must not overflow size_t. Refusing that addition is preferable to producing a wrapped end position that points somewhere unrelated.


The storage validator intentionally checks string termination without inventing provenance rules. Existing callers may construct a chunk with an ID and text but leave document metadata and offsets empty. Such a record can be safe to consume while still lacking enough information for a source citation. Your application should state that distinction.


## Practice

Run chunk and inspect the overflow refusal. Compare the complete record before and after it; checking only the return status would miss accidental partial edits. As a written exercise, calculate the generated ID length for a long document name and a multi-digit index. Then identify what additional evidence a source-navigation feature would need before highlighting the referenced bytes.


## Read and run the client

[Setup, expected output and troubleshooting](../../../../labs/native/framework-retrieval-ownership/README.md) · [C23 example source](../../../../labs/native/framework-retrieval-ownership/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Separate retrieval from model training](retrieval-and-model-training.md) · [Next: Read embedding geometry and finite numeric limits](retrieval-embedding-geometry.md)
