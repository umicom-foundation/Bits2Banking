<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/native-project-qualification-evidence.md

PURPOSE:
Qualify a native workflow without confusing authored tests with results

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Qualify a native workflow without confusing authored tests with results

Read the focused native project guide first. Code fragments below explain the shared Framework implementation; they are not standalone applications or recorded execution results.

## Choose the layer

Source review establishes which code is present and how ownership is intended to work. Compilation checks types and linking for one toolchain. GTK tests observe event delivery and native lifetime on a particular runtime. Building and launching generated source are further operations. A passing formatter test cannot establish a responsive GUI, and a source write cannot establish that its generated project builds.



| Evidence | Useful observation | Separate question |
| --- | --- | --- |
| Static review | Ordering, guards, preservation | Compiler acceptance |
| Injected writer GTK cases | Thread and completion ownership | Native filesystem behavior |
| Real-writer form cases | Source creation and adoption | Generated application execution |
| Studio first-use cases | Actual host close and replacement | Other products and deployment |



## Use the actual build owner

Framework has its own windows-ucrt64-debug preset. Studio participates in the Applications windows-ucrt64-all-debug preset; the module has no standalone CMakePresets.json. Follow the focused guide rather than inventing a similarly named module preset. Compile the changed Framework and Studio together so the host can link the activity-query symbol.



## Keep categories separate

Twenty worker scenarios hold dispatch and then release a real GTask thread. Their injected writer creates no files. Existing developer-dialog, simulation-starter and settings-lifetime scenarios use the real writer. Three new Studio scenarios use the actual workbench. Keep these categories separate instead of turning their combined count into a claim that every native path is complete.



## Inspect branding where it appears

Lessons reference approved Umicom SVG and ICO assets and the established learning stylesheet. That stylesheet supplies interface and code font families with local fallbacks. Native forms reuse Framework identity and layout. Inspect rendered pages and executable metadata after the owner-run build; valid references and hashes do not prove actual font rendering or installed icons.



## Finish the qualification record

- Record producer and consumer revisions, compiler, GTK/GLib runtime and exact commands.
- Retain complete logs and failed fixture paths; record skips separately.
- Classify failures as compilation, event lifetime, writing, adoption or presentation.
- Mark unexecuted stages unverified and retain earlier implementations for engineering review.



## Source and next steps

[Native project source and qualification guide](../../../docs/guides/native-project-forms.md) · [HTML edition](../../courses/umicom-development/lessons/native-project-qualification-evidence.html)

<!-- Retain the former course endpoint for review.
[Previous lesson](native-project-host-shutdown.md) · [Course index](index.md)
-->
[Previous lesson](native-project-host-shutdown.md) · [Next lesson](build-history-admitted-preparation.md) · [Course index](index.md)
