<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/06-run-the-framework-group-lab.md

PURPOSE:
Run a native Framework dataset-partition lab

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Run a native Framework dataset-partition lab

[Course contents](index.md)
This lesson uses the actual C API rather than a second implementation of the splitting algorithm. An array of uint64_t values holds source-group identifiers. An array of unsigned char receives one byte per row: zero for training, one for evaluation. The caller owns both arrays.

~~~c
#include <umicom/ai/training/dataset_split.h>
uint64_t groups[] = {100, 100, 200, 300, 300, 400};
unsigned char evaluation[6] = {0};
UmiStatus status = UmiAiTrainingSplitGroups(
    groups, 6, 1, 42, evaluation, 6);
~~~

1. Open labs/framework/training-groups in the Bits2Banking repository. Read its README before using the source-checkout teaching harness; this lab does not claim installed-SDK support.
2. Configure in an empty build directory, then build and run CTest using the documented commands.
3. Read each output row. Rows zero and one must have identical membership, as must rows three and four.
4. Run with the same group set and seed again. Membership is deterministic.
5. Read the test that passes an invalid evaluation count. Its sentinel output remains unchanged; callers must check status before consuming results.

The four numeric arguments after the arrays are row count, evaluation-group count, seed and output capacity in their declared positions. A seed initializes a deterministic pseudo-random generator. It is not a security key. Output capacity is the number of bytes available to receive row membership. Keeping count and capacity explicit helps prevent buffer overruns in C.

The implementation sorts unique group IDs before shuffling. Reordering rows or adding another row to an existing group does not alter group membership when the unique set, seed and selected group count stay the same. Adding a new unique group can alter the partition; persist a dataset version and reviewed split rather than promising append-only stability.


## Limits and recovery

Use the matching Framework source revision containing this API. Do not paste a guessed declaration into the client. The source-checkout harness tests selected production sources; installed-SDK packaging and consumer qualification are separate work. The lab does not tokenize text or train a model.


## Continue learning

[Previous: Keep related sources out of different partitions](05-split-sources-before-chunking.md) · [Course contents](index.md) · [Next: Understand tokens, chat templates and loss masks](07-tokenization-templates-and-masks.md)
