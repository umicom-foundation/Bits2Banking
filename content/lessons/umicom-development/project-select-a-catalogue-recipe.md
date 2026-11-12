<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/project-select-a-catalogue-recipe.md

PURPOSE:
Select a project recipe by its stable identity

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Select a project recipe by its stable identity

After preparing the installed-SDK lab in its README, run this scenario. Commands below are qualification instructions, not recorded results.

~~~powershell
& .\build\framework-project-recipes\project-recipes.exe catalogue
~~~

## Start with the installed catalogue

A project recipe describes files that a generator can prepare. Its title is for people; its identifier is for stored settings, commands and comparisons. Build a small client that enumerates the installed Framework catalogue before writing a project picker. The available recipes depend on the Framework revision selected by the application. A course screenshot cannot establish which recipes your binary contains.

~~~c
size_t count = umi_developer_project_builtin_template_count();
for (size_t i = 0; i < count; ++i) {
    const UmiDeveloperProjectTemplate *recipe =
        umi_developer_project_builtin_template_at(i);
    /* Check the pointer and validator before presenting its fields. */
}
~~~

## Follow the real client

Open inputs.c in the linked lab. The catalogue scenario checks each returned pointer, validates its structure and prints its stable identity and file count. It also requires the C23 console recipe and checks that the index immediately after the catalogue returns no entry. This is a public API exercise: the lab does not include Framework implementation files or maintain a second list of recipe definitions.

## Keep descriptions and capability evidence separate

A recipe can declare that it supports tests or installation because it emits the corresponding build instructions. Those declarations do not show that a compiler, GTK development package or signing tool is available on this computer. Present the declaration as a recipe property, then use the appropriate build and environment services to collect actual evidence. Do not label a project Ready merely because its catalogue entry exists.

| Value | Use | Do not infer |
| --- | --- | --- |
| template_id | Persist the selected recipe identity | An immutable version of its content |
| title | Display readable choices | A stable lookup key |
| file_count | Explain the expected recipe size | The number successfully written |
| supports_tests | Describe generated build support | That tests have executed |

## Try a controlled change

Run the catalogue scenario after building the lab. Copy two identifiers from the output into your notes. Compare the console and GTK recipes by reading their current generated build text in the preview workflow. Keep the selected identifier as data; do not turn the displayed title into a shell command. If a saved identifier disappears after an SDK change, report an unavailable choice and ask the application user to select a replacement rather than silently choosing the first item.

## Expected observation and diagnosis

The scenario should print the available identifiers and exit zero after its checks. A missing console entry or invalid record is a failed expectation, not permission to weaken the test. Record the selected SDK prefix, its producer revision and the diagnostic. A missing symbol at link time usually directs investigation toward an older or mismatched installed library; changing the course source cannot update that installation.

## Source and next steps

[Lab build and source guide](../../../labs/native/framework-project-recipes/README.md) · [Qualification record](../../../labs/native/framework-project-recipes/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/project-select-a-catalogue-recipe.html)

[Previous lesson](recovery-layered-qualification.md) · [Course index](../../courses/umicom-development/index.html) · [Next lesson](project-borrowed-recipes-owned-variables.md)
