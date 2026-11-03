# Authoring lessons for several media

Markdown and HTML are the editable sources of the learning library. Books, PDF documents, Word documents and teaching video scripts are editions made from reviewed sources. A video script may need spoken explanations of a diagram; a printed book needs the diagram itself and a caption. Treat those adaptations as editorial work, not identical copies.

## Plan the lesson before choosing a format

1. State one learning objective in plain language: for example, “Display a line of text with a C program.”
2. List the concepts the reader already needs. Link an earlier lesson for each unfamiliar prerequisite.
3. Explain each new word before relying on it. Introduce source text, then the expected result, then how each line contributes.
4. Give a small complete example, a trace or diagram, and an exercise with a worked answer.
5. Connect the example to a real file in the Umicom source collection. Explain which part the learner should read and why.
6. End with a check of understanding and one clear next step. Put advanced applications in an optional section.

Keep public lessons addressed to learners. Do not include personal correspondence, delivery notes, private logs or promises that an untested feature works.

## Keep one identity across formats

The registry `knowledge/registries/lesson-media.json` records an HTML path and a Markdown path for each browser lesson. A course's `course.json`, where supplied, records the lesson order and manuscript links. Keep existing addresses when reorganising a course so that older links still work.

1. Locate both versions through the registry before editing.
2. Compare headings, explanations, exercises, source paths and code examples. Existing pairs are not automatically identical.
3. Choose which version carries the teaching change. Transfer the same correction into its counterpart, retaining any useful explanation unique to that format.
4. Preserve code characters exactly. In HTML write `&lt;stdio.h&gt;`; in a Markdown code fence write `<stdio.h>`. Do not remove angle-bracket text as if it were always an HTML tag.
5. Give every image an explanation. Preserve a written alternative for interactive examples that a book cannot run.
6. Review local links from both file locations. A relative path is interpreted from the file that contains it.
7. Update the course contents, manuscript link and navigation together when changing the reading order.

An `aliasOf` field identifies an older browser address that intentionally shares a manuscript with the current introduction. Follow that canonical HTML address when reviewing the shared Markdown text; preserve both browser addresses for existing links. Do not count an alias as a second independent manuscript.

The registry's “existing-versions-preserved” relationship means that both existing sources were retained, not that an editor has confirmed equivalent content. “converted-from-html” records how a manuscript began. It does not make future HTML edits automatically update Markdown.

## Prepare a content pack

A Studio content module contains a learning manifest and declared resources. Its SHA-256 values identify exact bytes; they do not identify a trusted author or execute examples. After reviewing a changed HTML resource, regenerate its checksum in the pack using the repository's pack authoring process. A stale checksum should be corrected after review, not disabled in the reader.

Content modules do not install native plugins or language servers. Those capabilities need separate implementation and security review. Do not describe the current content catalogue as an executable extension marketplace.

## Prepare derived editions

Maintain an edition list containing lesson identities, reading order, source revision and selected source format. For a book, add chapter introductions and a glossary. For a video script, add narration, on-screen code and expected demonstration results. For Word or PDF, check page breaks, tables, code wrapping, figure captions and links after rendering.

Keep the source revision alongside an exported edition so readers can tell which code it explains. Correct the Markdown and HTML sources before regenerating a derivative. There is no complete automated export pipeline for every format yet; record an export as generated only after that export has actually been produced and reviewed.
