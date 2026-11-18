<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/28-look-up-records-with-associative-arrays.md

PURPOSE:
Look up records without confusing storage with learning

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Look up records without confusing storage with learning

[Course contents](index.md)

## What you will build

You will build a small dictionary that associates a document label with a reviewed-record count. You will distinguish a missing entry from an entry whose count is zero, observe what assignment shares, make an independent copy and print a stable report. This extends the earlier collection and ownership lessons with one complete program. It also answers a common question in model training: a dictionary is a useful storage structure, but creating one does not train a model.

Read the earlier lessons about expressions, arrays, read-only views and assertions first. You need a D compiler and a terminal. The example uses the normal D runtime and standard library; it is not a BetterC example and does not add D to the Framework implementation. The downloadable source has not yet been compiled on the course maintainer’s D toolchain. The commands below are the reproducible checks to run on your selected compiler release.


## 1. Give each piece of data a meaning

Imagine reviewing two collections named alpha and beta. A key identifies a collection. A value records how many entries have been reviewed. In this lesson the key is a string and the value is an unsigned integer named uint. Alpha has two reviewed entries; beta has none. The absence of a collection is a different state from the presence of a collection with zero reviewed entries.

~~~d
uint[string] reviewed;
reviewed["alpha"] = 2;
reviewed["beta"] = 0;
assert(reviewed.length == 2);
~~~

D writes the value type before the square brackets and the key type inside them. Read uint[string] as “an unsigned integer associated with each string key.” The declaration initially describes an empty associative array. Assigning a value to a new key inserts an entry. Assigning to an existing key replaces its value. The length counts entries; it does not count characters or report allocated bytes. A hash table, which is a common implementation technique for associative arrays, computes a position from a key and handles collisions when different keys lead to the same position.


## 2. Look up before reading an uncertain key

~~~d
if (auto count = "alpha" in reviewed)
    ++*count;
else
    return 1;
assert(("beta" in reviewed) !is null);
assert(("missing" in reviewed) is null);
~~~

The in expression searches the associative array. When the key exists, its result is a pointer to the corresponding value. When the key does not exist, the result is null. A pointer identifies another location in memory; it is not the stored count itself. The condition checks the pointer before the body dereferences it. In ++*count, the star accesses the pointed-to integer and the two plus signs increment that integer. Alpha changes from two to three.

The identity operators is and !is make the null checks explicit. Beta has a real entry whose integer value is zero, so its lookup pointer is not null. The missing key has no entry and returns null. Do not replace these two states with an unchecked indexed read or a test that treats the stored zero as absence. A search result is a short-lived borrow of container storage. Keep its use local, and do not retain a pointer across operations that can invalidate that storage or remove its entry.


## 3. Observe sharing before choosing a copy

~~~d
auto sharedView = reviewed;
sharedView["alpha"] = 4;
assert(reviewed["alpha"] == 4);

auto independent = reviewed.dup;
independent["alpha"] = 9;
assert(reviewed["alpha"] == 4);
assert(independent.remove("beta"));
assert(("beta" in reviewed) !is null);
~~~

Assignment of this populated associative array gives another reference to its storage. Changing an existing entry through sharedView is therefore visible through reviewed. The name sharedView is descriptive; it does not create a read-only type or a special language feature. Be especially careful with empty associative arrays: sharing examples involving populated storage must not be generalized into a promise that every later assignment through every empty reference is visible everywhere.

The dup property creates a separate associative-array container. In this example its integer values are copied, so changing independent’s alpha value and removing its beta entry do not change reviewed. Duplication is not automatically a deep copy of every object reachable from a value. If values were class references or mutable arrays, those values could still refer to shared objects. Write the ownership contract for the actual key and value types before choosing a copy operation.

Remove returns whether an entry was removed. Its result makes a useful assertion when the setup requires the entry to exist. Removing an entry does not reverse earlier changes through other references, securely erase sensitive data, or certify that the runtime immediately returns all backing memory to the operating system.


## 4. Produce a report in a defined order

~~~d
auto orderedKeys = reviewed.keys;
sort(orderedKeys);
foreach (key; orderedKeys)
    writeln(key, "=", reviewed[key]);
writeln("independent alpha=", independent["alpha"]);
~~~

An associative array does not promise insertion-order traversal. A report whose order changes between runs is awkward to compare. The keys property supplies an array of keys; sorting that array makes this small example’s output deterministic for the two simple ASCII labels. Foreach visits each element in that sorted array. The key is known to exist because the container stays unchanged while the loop reads it.

Import sort from std.algorithm.sorting and writeln from std.stdio as shown in the complete source. Sorting keys for display is not a general serialization format. A real file format still needs character encoding, separators, escaping, number representation and version rules. Different Unicode normalization forms or locale-aware ordering require an explicit policy; this example does not invent one.


## 5. Compile and run the complete file

Open the native-language-boundary lab, read record_lookup.d from beginning to end and locate every assertion. An assertion checks a condition that should hold and reports a failure when it does not. Keep assertions enabled while learning. Do not use a release option that removes the evidence you are trying to collect.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
dmd --version
dmd -w -checkaction=context record_lookup.d -of=record_lookup.exe
.\record_lookup.exe
~~~

Run one line at a time and stop on an error. The executable should print alpha=4, beta=0 and independent alpha=9 on separate lines, then return exit code zero. Inspect $LASTEXITCODE immediately after running it. If dmd is not found, return to the installation lesson and confirm the compiler’s bin directory in that terminal. If an option is unsupported by your release, consult that release’s help rather than discarding all checks. If compilation fails, do not run an old executable from a previous attempt.


## 6. Relate the example to Framework applications

A model catalogue may map a model identifier to metadata. A document importer may map a source identifier to a count. A job panel may map a job identifier to a status. These are applications of keyed lookup, not reasons to pass a D runtime container directly across a C interface. Native Framework services need explicit types, capacities, ownership and failure results. A thin D client can translate a reviewed record into the existing C contract while keeping its D-owned strings and arrays alive for the documented duration.

A normal D associative array may allocate through its runtime. This is not suitable for an interrupt handler or a Kernel path that prohibits allocation. For bounded native services, a fixed-capacity C table may make memory and failure behavior easier to reason about. Choose the representation from the service’s contract; do not assume that changing language alone prevents leaks or excessive memory use.


## 7. Separate a dictionary, a dataset and a vector index

A dictionary answers a question such as “what count belongs to alpha?” A dataset contains examples that a training process can consume. A vector index supports searches over numerical representations, often called embeddings. A model contains learned parameters. These four objects can cooperate, but none substitutes for the others. Converting a document to key/value pairs does not tell a trainer which tokens to predict, which labels are correct or how to evaluate improvement.

For supervised fine-tuning, the dataset normally needs a documented record schema, permitted content, input/output boundaries, splits and tokenization rules. JSON objects can represent those records on disk, while D associative arrays can help inspect them in a teaching tool. Retrieval-augmented generation can index embeddings without updating the language model’s weights. The data-preparation course explains these separate workflows with native examples.


## Practice and recovery

1. Before running, write down the contents of reviewed after each assignment. Track sharedView as a reference to the same populated container. Draw independent as a second container.
2. Add a third reviewed collection named gamma with value one. Predict the sorted output before rebuilding.
3. Look up an absent key with in and print a message without inserting it. Verify that the length remains unchanged.
4. Replace an integer value with a reference-containing type only in a separate practice copy. Explain which parts dup would and would not duplicate before writing any mutation.
5. If an assertion fails, record the compiler version, source and first failing assertion. Restore the small original example and change one operation at a time.


## Further reading

- [Complete D source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/native-language-boundary/record_lookup.d)
- [Native language lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/native-language-boundary/README.md)
- [D associative-array specification](https://dlang.org/spec/hash-map.html)
- [LLM data preparation course](../../../courses/preparing-llm-training-data/index.html)

[Previous: Separate read-only views from independent copies](27-separate-read-only-views-from-independent-copies.md)

[Next: Turn field metadata into explicit checks](29-turn-field-metadata-into-explicit-checks.md)
