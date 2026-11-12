<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/project-preview-owned-plan.md

PURPOSE:
Preview generated files in an owned plan

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Preview generated files in an owned plan

After preparing the installed-SDK lab in its README, run this scenario. Commands below are qualification instructions, not recorded results.

~~~powershell
& .\build\framework-project-recipes\project-recipes.exe preview
~~~

## Make the preview a real data object

A preview should contain the exact paths and text the recipe renderer produced, rather than a hand-written illustration of the expected project. The generation plan stores file content by value. Once rendering returns successfully, the caller can inspect those owned strings without retaining the variable set or temporary recipe strings used during the call. Keep the plan alive for every reader that still refers to it.

~~~c
UmiDeveloperProjectGenerationPlan *plan = calloc(1, sizeof *plan);
if (plan == NULL) return 1;
UmiStatus status = umi_developer_project_generation_plan_build(
    LabRecipe(), &variables, request.project_root, plan);
/* Present files only on OK; release the plan after all readers finish. */
free(plan);
~~~

## Read the lab output

The preview scenario derives standard variables, renders the two-file teaching recipe and prints each path with its text-byte count. It requires src/recipe_study.c as the first path. README.md contains the display name and application identifier. No destination is opened. The root string identifies where a later writer could work; this preview does not check that the path exists or grant permission to write there.

## Budget memory deliberately

The public plan reserves bounded storage for many file bodies. Its text arrays alone can exceed half a megabyte. Placing it in a local variable can consume a substantial part of a native worker thread stack. The lab allocates the plan and its comparison snapshot on the heap, checks both allocations and frees both on success or refusal. A production client may keep one reusable owned preview, but must still handle allocation failure and reader lifetime.

## Do not confuse text rendering with compilation

A renderer substitutes values into text. It cannot prove that the resulting C, CMake, YAML or VHDL is valid in its downstream language. The two-file lab recipe deliberately has no complete build system, even though its metadata illustrates a CMake-oriented project. Use a built-in application recipe for the later build exercise. This distinction prevents a small memory fixture from being mistaken for a shipping application template.

## Explore the output contract

After running preview, inspect total_content_bytes in a debugger or add a temporary print in a learner copy. Compare it with the sum of strlen for the rendered file contents. These are byte counts of terminated text, not Unicode character counts and not on-disk allocation sizes. Change only the display name and observe which generated bodies change. Paths should follow TARGET_NAME, demonstrating why the naming fields are separate.

## Expected result and next step

Exit zero means the scenario observed the expected in-memory plan. It says nothing about filesystem creation, installed dependencies or runtime behavior. Keep the next lesson’s refusal case beside the happy path: an editor must preserve the previous useful preview when a new request cannot be prepared.

## Source and next steps

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Lab build and source guide](../../../labs/native/framework-project-recipes/README.md) · [Qualification record](../../../labs/native/framework-project-recipes/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/project-preview-owned-plan.html)
-->
[Lab build and source guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-project-recipes/README.md) · [Qualification record](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-project-recipes/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/project-preview-owned-plan.html)

[Previous lesson](project-application-identities.md) · [Course index](../../courses/umicom-development/index.html) · [Next lesson](project-refused-preview-preserves-state.md)
