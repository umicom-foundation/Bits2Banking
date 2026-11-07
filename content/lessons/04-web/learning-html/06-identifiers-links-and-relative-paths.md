<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/06-identifiers-links-and-relative-paths.md

PURPOSE:
Explain the lesson: Follow a page link to the correct resource.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow a page link to the correct resource

## A page has more than one address

A web address identifies a resource such as a page, stylesheet or program. A fragment, introduced by a hash sign, identifies a location inside a page. A filesystem path identifies a file on a particular computer. These are related concepts, but a published page cannot assume it can read another visitor's disk.

## Setup recap

Use an editor and the [browser activity lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/README.md). Build and serve the lab for the execution exercise. For a paper exercise, draw a folder containing index.html, page.js, activity.js and activity.wasm. No installation is needed for that drawing.

## Resolve one reference

The page contains:

~~~html
<script type="module" src="./page.js"></script>
~~~

The dot means the current directory. From /activity/index.html this reference asks for /activity/page.js. It does not ask for the caller's working directory in a terminal. The browser resolves a module's own imports relative to that module's URL.

A page fragment such as #main has a different role. It moves to an element with id="main". Each id should identify one element; duplicate identities make navigation and scripting ambiguous.

## Lab

1. Open the browser developer tools and select the Network view.
2. Reload the served lab.
3. Find the requests for page.js and the generated module.
4. Check each full URL and response status.
5. Open the Console view and read the first error, if any.
6. Compare the requested spelling, including letter case, with the files.
7. Move the complete lab directory to another served subdirectory and repeat.

A link that worked on a case-insensitive local filesystem can fail on another server. Use consistent file names rather than relying on that difference.

## Exercise and explanation

A page at /courses/activity/index.html requests ../assets/style.css. Which directory contains the requested file? /courses/assets/. One pair of dots moves up one level; it does not mean the website root.

## Publishing lesson editions

Standalone HTML should link to published HTML routes or explicit source URLs. A relative Markdown filename is a source document, not necessarily a page served by the website. Keep the Markdown edition available through a deliberate link, and verify both editions after changing navigation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/index.html). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-buttons-status-and-a-loading-page.md)


[Next: Read a small application page](07-read-a-small-application-page.md)
