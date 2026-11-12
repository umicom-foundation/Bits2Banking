<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/retrieval-callback-ownership.md

PURPOSE:
Keep callback failures from publishing partial scores

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Keep callback failures from publishing partial scores

## A callback crosses an ownership boundary

A reranker callback receives a query, a borrowed chunk, the current score and application user data. It returns a replacement score. Framework owns the traversal and sorting; the application owns its scoring policy. This arrangement is useful for a product-specific preference without copying the retrieval engine into every application.


The callback must return a finite value and must not retain the temporary chunk pointer, cast away const or mutate the result owner. Those restrictions make the publication guarantee meaningful. External effects, such as incrementing a counter in user data, remain visible even if a later score is rejected.


## Stage the result set

~~~c
UmiAiReranker reranker = {adjust_score, &state};
UmiStatus status = umi_ai_reranker_apply(
    &reranker, "target", results, result_count);
if (status != UMI_STATUS_OK) {
    /* The previous result array remains, if the callback obeyed its contract. */
    return status;
}
~~~


Framework first validates every incoming chunk and score. With a callback, it then copies the result array into owned temporary storage. All callbacks operate on that candidate. Only after every returned score is finite does the service sort and publish the complete array. Allocation failure and invalid later scores therefore cannot expose a partially updated result set.


## Observe effects that cannot be undone

Reranking in the laboratory deliberately returns NaN on its second callback. The client expects INVALID_STATE, two observed calls and an unchanged result array. The counter stays at two because it belongs to the callback owner. Treating the operation as if no callback ran would be incorrect even though result publication was refused.


The next invocation returns negative base scores and succeeds. Descending order still applies to negative numbers: minus one is greater than minus two. A null callback performs the existing stable sort without allocating a candidate array. The service captures the callback descriptor before invocation, so replacing that descriptor during a call does not change the remaining traversal.


## Practice

Run rerank and distinguish the refusal status, retained result bytes and callback call count. Write a scoring callback that reads only its borrowed inputs and returns a small finite adjustment. Then list side effects that would complicate retry, such as writing a file or charging a remote service. Keep those operations outside this teaching callback and design their ownership separately.


## Read and run the client

[Setup, expected output and troubleshooting](../../../../labs/native/framework-retrieval-ownership/README.md) · [C23 example source](../../../../labs/native/framework-retrieval-ownership/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Combine lexical and vector evidence with finite weights](retrieval-hybrid-weights.md) · [Next: Qualify the installed retrieval client and state its limits](retrieval-installed-qualification.md)
