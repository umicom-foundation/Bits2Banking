<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/09-status-messages-and-page-language.md

PURPOSE:
Explain the lesson: Explain loading and failure in the page.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Explain loading and failure in the page

## Set up
Read the browser activity lab's README for the Emscripten build and local HTTP-server command. Open the served page. A text editor is enough for the source-reading portion.

The page initially shows a loading message in an element with `role="status"`. A status region communicates changes in the page's operation. Its text should remain useful even when a person cannot see a colour or animation.

## Trace three states
1. Loading: the button is unavailable and the page says the C module is loading.
2. Ready: the module exists, the button is enabled and the page reports readiness.
3. Failed load: the button remains unavailable and the page gives recovery guidance.

These states should agree. An enabled button beside a load-failure message creates a confusing promise.

## Design better wording
Write one short message for each state. Keep technical details in a troubleshooting section, but give the person a useful next step. “Check the build files and HTTP server” explains where to begin without showing private system details.

**Exercise:** distinguish a module-load failure from an activity-capacity refusal. Expected answer: the first prevents the service from being available; the second is a result from an available service.

## Check accessibility
Read the document language and visible labels. Use a screen reader if available and record how status changes are announced. The presence of an ARIA role is an implementation choice, not proof that the whole workflow has been checked with assistive technology.

## Recover
If the status never changes, inspect the browser console and network requests. If it reports success but the count is unchanged, trace the returned C value and output assignment. Preserve the initial failure evidence instead of replacing it with a generic “works on my machine” note.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/index.html). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-use-real-buttons-and-outputs.md) · [Next lesson](10-relative-resources-and-http.md)

