<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/retrieval-stable-top-matches.md

PURPOSE:
Select top matches without losing stable order

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Select top matches without losing stable order

## Request only the results you can consume

A search can inspect many stored entries while returning only a small number. The requested output capacity controls how many indices and scores the caller can receive. It does not change how many active entries the store owns. The reference service keeps the best scores in descending order instead of sorting the whole store in place.


Read TopMatches in the laboratory. Its four vectors produce scores one, zero, minus one and one against the query. Requesting three outputs should return indices 0, 3 and 1. The two best entries have equal scores, so the earlier insertion remains first. Predicting that order makes it easier to spot an accidental tie reversal.


## Read exactly the published count

~~~c
size_t indices[3];
double scores[3];
size_t count = umi_ai_vector_store_search(
    &store, &query, indices, scores, 3U);
for (size_t i = 0U; i < count; ++i) {
    const UmiAiChunk *chunk = &store.entries[indices[i]].chunk;
    /* Read chunk while the store remains unchanged. */
}
~~~


The returned indices refer to the current store. They are not permanent identifiers or owned chunk copies. A later mutation or replacement can change what an index means. Copy the required record into application-owned storage when it must outlive the current observation, and preserve its document identity for later source validation.


## Understand refusal and neutral scores

Zero output capacity is a no-op. Invalid input or malformed stored state also returns zero and leaves output arrays untouched. A valid empty store produces zero too, so a count alone cannot explain the outcome. Explicit validators provide the storage decision; the UI supplies the user-facing explanation.


Different dimensions and zero-magnitude vectors retain the existing neutral cosine score. They are not silently removed from the top-match algorithm. This matters when a store contains negative scores: a neutral candidate can rank above an opposite direction. If your product requires one embedding model and dimension, enforce that policy when ingesting data rather than assuming this reference store does it.


## Practice

Run top, then predict the result for capacities one, two and four before making a practice edit. Explain which output slots are valid after each call. Finally, describe a lifetime mistake in which a UI retains an index while another action rebuilds the store. A stable tie rule makes ranking reproducible for unchanged input; it does not solve ownership across mutations.


## Read and run the client

[Setup, expected output and troubleshooting](../../../../labs/native/framework-retrieval-ownership/README.md) · [C23 example source](../../../../labs/native/framework-retrieval-ownership/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Admit the complete vector store before searching](retrieval-store-admission.md) · [Next: Combine lexical and vector evidence with finite weights](retrieval-hybrid-weights.md)
