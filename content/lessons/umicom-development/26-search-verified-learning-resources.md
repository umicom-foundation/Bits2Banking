# Search verified learning resources

Read the accompanying [Umicom source example](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/teacher/learning_text.h). Match its revision to your checkout before comparing behavior.

Imagine remembering an explanation about ownership but forgetting which guide contained it. Searching a title may not find it. Searching the guide's paragraphs can. This lesson follows the real Umicom Framework implementation that prepares a searchable copy of guides and source examples.

Read [Build an offline learning reader](13-build-an-offline-learning-reader.md) for manifests and verified files. [Find text with shared Framework services](24-find-text-with-shared-services.md) explains searching one open document. Here we connect several documents without making each application invent another search engine. You can trace the steps on paper before installing tools.

## 1. Separate a file from its description

A file stores bytes. A byte is a small unit of data. Text uses an encoding to give those bytes meaning. UTF-8 is the encoding used by this service; one character may occupy one byte or several.

A resource description names a file and records its role, title, relative path and expected SHA-256 digest. A digest is a fixed-size value calculated from the bytes. Comparing a calculated digest with the expected digest helps detect changes. It does not tell us who wrote the file. Someone who can replace both a file and its manifest can also replace its digest.

A learning pack groups these descriptions. A shelf owns admitted packs. Admission checks the manifest's format, paths, identities and compatibility range. It does not mean that every described file has already been opened and checked.

The body-search builder reads each declared non-image resource, verifies its bytes, and prepares searchable text. A missing or changed file refuses the new index. A search should not look complete when part of its chosen library could not be read.

## 2. Give each snapshot an owner

A snapshot is a copy of information at one moment. The index owns copied text and metadata. A search result owns another, smaller copy containing a resource identity, a preview and a match range.

1. Admit a shelf of pack descriptions.
2. Read verified resources and create a candidate index.
3. Accept the complete candidate, or keep the earlier index after refusal.
4. Search the accepted index without reading files again.
5. Retain copied results for display.
6. Verify a selected resource again before opening it.

The shelf can be released after index construction. The index can be released after a search completes. A successful result remains readable until its own destroy call. These are separate owners, not three pointers that should all release the same allocation.

Read `include/umicom/teacher/learning_text.h`. Its create functions clear the output pointer on failure. Use a separate candidate variable when replacing an existing index. Passing the address of the application's only owning pointer would lose access to the earlier object.

## 3. Build searchable text without running it

A guide ending in `.html` or `.htm` passes through the Framework reading projection. A projection keeps a useful representation of something larger. Here it keeps readable paragraphs, headings and supported structure while omitting script, style and other excluded sections.

~~~html
<p>Learn <strong>ownership</strong> with Umicom Framework.</p>
<script>hidden example text</script>
~~~

A search can find ownership in the readable sentence. It cannot find the hidden script text. The projection does not execute the script or follow network links. Other non-image resources are indexed as complete UTF-8 source text. C comments remain searchable because they are part of the example a learner is reading.

Images are counted as excluded resources and are not read by body search. An image description inside a guide may still be part of its projected text. Invalid encoding, prohibited control bytes or malformed supported HTML refuses the candidate. It does not silently become an apparently successful partial index.

The implementation is in `src/teacher/learning_text_index.c`. It calls the existing verified-resource reader and browser reading projection, then stores copied text in the existing Editor index. Reusing these services keeps file verification, HTML reading and search ownership consistent across applications.

## 4. Follow a simple query

A query describes what to find. This service uses one literal phrase. Literal means that characters such as brackets are ordinary text rather than special search instructions.

~~~c
UmiLearningTextQuery query;
UmiLearningTextQueryInit(&query);
strcpy(query.phrase, "ownership");

UmiLearningTextSearch *results = NULL;
UmiStatus status = UmiLearningTextSearchCreate(
    index, &query, &results);
~~~

The initializer sets every field to a known value and chooses a default result limit. The fixed word in this example fits the phrase array. For text entered by a user, check its length before copying, as the complete `body_search.c` example does.

The search returns the first occurrence in each matching document. Results follow shelf and manifest order. They are not sorted by an invented relevance score. Optional filters select a product, locale or resource kind. Product identity is exact. Locale comparison ignores ASCII letter case but does not guess another language.

ASCII case-insensitive matching treats A and a as the same letter. It does not promise every language's case rules. Whole-word matching uses the Editor engine's ASCII identifier boundaries. Interface labels must describe the behaviour the service actually provides.

## 5. Read a byte range correctly

A range has a start and an end. The start counts from zero. The end is exclusive, so it points just after the match. If ownership begins at byte 12, its nine ASCII letters occupy bytes 12 through 20, and the range is 12..21.

The word café uses five UTF-8 bytes: c, a and f each use one, while é uses two. A byte offset must not be used as a character offset in a graphical text widget without conversion.

HTML results refer to projected reading text. Raw HTML contains tags that the projection removes. Applying a projected offset to raw HTML could select unrelated text. Keep the result's representation flag and recreate the same projection after reopening the selected resource.

The preview begins at the match. It stops at the line ending or a fixed capacity. If capacity shortens it, the service reports that fact and avoids cutting a UTF-8 character in half. The complete matched range remains separate from this shortened display text.

## 6. Bound the work

A budget is an explicit limit on resource use. Default construction allows 256 documents, one MiB of source per resource, 64 KiB of searchable text per document and eight MiB of searchable text overall. One KiB is 1,024 bytes; one MiB is 1,024 KiB.

The API returns the known pack and resource identity when a candidate fails. Raising a size limit will not repair a missing file or invalid encoding. A query retains at most 256 results, counts matching documents, and reports truncation when its retained list is shorter. An interface should show that distinction.

Cancellation is checked between resources and search operations. It does not interrupt a filesystem call already in progress. A graphical application should create an independent shelf clone for a worker, keep the worker's owners alive, and publish the resulting index only when the job completes successfully.

## 7. Use the installed example

The complete program is `examples/learning_pack_inspector/body_search.c` in Umicom Framework. Its CMake project builds against an installed SDK and prepares a manifest using the copied files' actual hashes.

Follow `docs/learning/searching-learning-text.html` in the Framework source for logged configure, build and test steps. Use a new practice folder so earlier edits remain intact. After building that example, run these commands from its source directory:

~~~powershell
& ".\build\umicom-learning-pack-text.exe" "$PWD\build\pack" learning-pack.json "verified body search"
$LASTEXITCODE
& ".\build\umicom-learning-pack-text.exe" "$PWD\build\pack" learning-pack.json "argc < 3"
$LASTEXITCODE
~~~

The first search should include resource guide. The second should include inspector, where the actual C program checks its argument count. Both commands should exit with zero. A zero-result search can also succeed: it means the search completed without finding the phrase.

A missing installed symbol may indicate headers and libraries from different builds. Use a matching installed SDK. Do not conceal the mismatch by borrowing source-tree headers. The native catalogue also exposes Search inside guides and examples. Search text reuses the snapshot, Refresh search rebuilds it, and Read result rechecks the file before opening it. Read result now selects the first matching passage after verifying the file and its UTF-8 position. Use current-document Find for later occurrences. If the file changed, the previous document and selection remain available. Back, Forward and Reload navigate resources without replaying a search highlight.

## 8. Recheck a selected result

Change an example file after building the index. The existing in-memory result still describes the earlier bytes. That is expected snapshot behaviour.

Before opening a result, use `UmiLearningReaderCreateFromShelf` with its pack ID, pack revision, resource ID and expected digest. The reader checks the current selection and bytes. A changed file must be refused rather than highlighted using stale offsets.

A generation number tracks changes within a shelf's lineage. Two unrelated shelves may have the same generation number. That number is not a global identity or an authentication token.

## 9. Practise and explain

Find a function name in an example, then locate it in the source. Compare the returned byte range with the characters you see. Next search for a phrase in an HTML paragraph and explain why its offset differs from the raw HTML position.

Draw three boxes labelled shelf, index and results. Mark the moment each can be destroyed. Explain why keeping results does not require keeping all source files open.

Finally, imagine a pack with two valid guides and one changed source example. Should the new index appear complete? It should be refused, while the application can retain an earlier accepted index and explain the failure.

Shared services make the workflow predictable. Callers still need to respect lifetimes, represent incomplete results honestly, and verify selected content before using an old range.

[Previous: Validate a tool connection](25-validate-a-tool-connection.md) · [Course contents](index.md)

Sammy Hegab · Umicom Foundation · MIT

Next: [Open search results without losing your place](27-open-search-results-without-losing-your-place.md).

## Apply the idea

<details>
<summary>Open a result after the file changes</summary>
<p>A result names a matching phrase from an accepted index. The file changes before the learner selects it. Is the old matching range sufficient permission to open and highlight the new file?</p>
<p><strong>Explanation:</strong> No. Recheck the admitted resource identity and expected digest before accepting the new reader. The index describes an earlier snapshot. If verification fails, retain the previous accepted reader and explain why the selected result cannot be opened.</p>
</details>
