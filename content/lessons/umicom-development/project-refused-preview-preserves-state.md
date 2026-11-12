<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/project-refused-preview-preserves-state.md

PURPOSE:
Preserve a reviewed preview when the next recipe fails

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Preserve a reviewed preview when the next recipe fails

After preparing the installed-SDK lab in its README, run this scenario. Commands below are qualification instructions, not recorded results.

~~~powershell
& .\build\framework-project-recipes\project-recipes.exe late-failure
~~~

## Begin with useful state

An application often already displays a valid preview when the user changes a field or recipe. If a new render fails halfway through, clearing the displayed plan would discard useful information and may make the interface appear to accept an incomplete project. The generation-plan builder prepares a private candidate and publishes it only after all files and final path checks succeed.

## Follow a late failure

The lab first renders a valid two-file plan and copies every byte into a comparison snapshot. It then changes only the second file to reference UNSET_VARIABLE. The first file can render successfully, but the second cannot. The expected status is NOT_FOUND and the old plan must remain byte-for-byte unchanged. Checking only file_count would miss accidental edits to paths, content, root metadata or revision.

~~~c
memcpy(before, plan, sizeof *before);
files[1].content_template = "{{UNSET_VARIABLE}}";
UmiStatus status = umi_developer_project_generation_plan_build(
    &recipe, &variables, "C:/learning/replacement", plan);
/* Require NOT_FOUND and memcmp(plan, before, sizeof *plan) == 0. */
~~~

## Check the final validation boundary too

The duplicate scenario uses different recipe path text that renders to the same destination. Its expected ALREADY_EXISTS result must also preserve the earlier plan. This tests the final validation stage rather than a missing variable. In a learner copy, replace the second path with a traversal attempt and predict the refusal before running it. Keep the original accepted plan as the observation baseline.

## Understand aliasing

The aliased-root scenario passes plan->project_root as an input while plan is also the output. A builder that clears output before reading this input would erase its own source string. Candidate preparation avoids that failure: all input reads finish before publication. This guarantee is about readable in-process input storage during the call; it does not permit an unrelated thread to mutate those bytes concurrently.

## Keep transaction claims narrow

Atomic publication here means one complete memory value replaces another on success. It does not mean filesystem creation is transactional. The separate writer can leave newly created partial files after an I/O failure. It also does not make raw render_text transactional for every syntax or capacity error; callers that need an intact previous view should use the plan boundary or their own candidate around the lower-level renderer.

## Diagnose without erasing evidence

If the scenario returns one, retain its exact assertion, scenario name and SDK identity. Compare the current public contract and installed library before modifying expected statuses. A regression may come from selecting an older archive even when your source headers are new. Run the success, late-failure, duplicate and aliased-root cases together after correcting the environment so that a refusal fix does not hide a broken happy path.

## Source and next steps

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Lab build and source guide](../../../labs/native/framework-project-recipes/README.md) · [Qualification record](../../../labs/native/framework-project-recipes/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/project-refused-preview-preserves-state.html)
-->
[Lab build and source guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-project-recipes/README.md) · [Qualification record](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-project-recipes/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/project-refused-preview-preserves-state.html)

[Previous lesson](project-preview-owned-plan.md) · [Course index](../../courses/umicom-development/index.html) · [Next lesson](project-select-a-new-destination.md)
