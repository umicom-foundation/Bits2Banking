<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/retrieval-store-admission.md

PURPOSE:
Admit the complete vector store before searching

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Admit the complete vector store before searching

## A count is a claim about storage

The reference vector store owns a fixed array of entries and an active count. Each entry combines a chunk and an embedding. A public structure can be filled without calling its initializer, so the count must be checked before it drives indexing. A value larger than the array capacity is malformed state, not a request to grow the array.


Read StoreAdmission in the laboratory. It inserts one real entry, then deliberately corrupts only the count in its isolated fixture. Both search and addition must refuse that owner. The example compares the complete store and output values after refusal, proving more than an error status by itself could demonstrate.


## Use shared admission

~~~c
if (!umi_ai_vector_store_valid(&store))
    return UMI_STATUS_INVALID_STATE;
UmiStatus status = umi_ai_vector_store_add(
    &store, &chunk, &embedding);
if (status != UMI_STATUS_OK)
    return status;
~~~


The validator checks every active chunk and embedding, not just the first row or the row likely to score highest. This prevents a malformed later entry from being hidden behind an early result. Inactive slots are ignored. An initialized empty store is valid, and the current service permits duplicate chunk identities and mixed embedding dimensions.


## Separate capacity from corruption

A valid full store returns CAPACITY_EXCEEDED when another entry is added. A malformed existing store returns INVALID_STATE. Invalid incoming records return INVALID_ARGUMENT. These distinctions help an application explain whether it needs more room, a corrected producer or different input. Silently clamping a corrupted count would hide the source of the problem and could expose unrelated entries.


Insertion stages both incoming records before publishing the next slot and count. Callers can borrow from an existing or unused entry without losing the source during the write. That local alias support does not make the store thread-safe. A product must still define who owns it and synchronize concurrent reads and mutations.


## Practice

Run store and explain why an expected refusal produces a successful laboratory exit. Then trace the full-capacity path in Framework without changing the fixture count to bypass it. Draw the distinction between active entries, allocated slots and requested output capacity. Each is a different boundary, and confusing them can cause either unsafe access or unnecessary rejection of valid data.


## Read and run the client

[Setup, expected output and troubleshooting](../../../../labs/native/framework-retrieval-ownership/README.md) · [C23 example source](../../../../labs/native/framework-retrieval-ownership/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Read embedding geometry and finite numeric limits](retrieval-embedding-geometry.md) · [Next: Select top matches without losing stable order](retrieval-stable-top-matches.md)
