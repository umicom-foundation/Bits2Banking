![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Keep source groups together

Rows from one document or video must stay in the same chosen partition. This lab calls Framework UmiAiTrainingSplitGroups; it does not reimplement the algorithm. Four source groups span six invented rows.

## Run from the Bits2Banking root

Use a C23 compiler, CMake and Ninja. Set the source path to your matching Framework checkout. These commands assume the sibling Umicom-Applications layout; replace that path if your folders differ.

~~~powershell
cmake -S labs/framework/training-groups -B build/training-groups -G Ninja -DUMICOM_FRAMEWORK_SOURCE=../Umicom-Applications/framework
cmake --build build/training-groups
ctest --test-dir build/training-groups --output-on-failure
& ".\build\training-groups\training_groups.exe"
~~~

Stop after any failed command. The program prints six row/group/partition lines. Exactly one unique group is evaluation. Rows sharing 100 or 300 stay together. The test checks repetition and unchanged sentinel bytes after an invalid request.

This builds two actual Framework sources in a small teaching harness. It neither configures the complete Framework nor verifies an installed SDK export. If source is missing, use the matching revision; do not copy declarations from an unrelated SDK. No model, network, GPU, document importer or trainer is involved.

## Read the sample records

corpus.jsonl contains original invented text with the same group identifiers. It illustrates data preparation; main.c does not parse it and it is not a universal trainer schema. The fixed C array separates the partition contract from parsing.

## Extend carefully

Assign groups before chunking or augmentation. Keep related revisions and overlapping clips together. The API accepts at most 4096 rows and chooses by unique-group count, not row percentage. It is not chronological or stratified and does not detect duplicates. Preserve a dataset version and partition manifest; adding a new group can change membership.
