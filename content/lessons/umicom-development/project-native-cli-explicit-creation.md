<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/project-native-cli-explicit-creation.md

PURPOSE:
Move from a native CLI preview to explicit project creation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Move from a native CLI preview to explicit project creation

After preparing the installed-SDK lab in its README, run this scenario. Commands below are qualification instructions, not recorded results.

~~~powershell
& .\build\framework-project-recipes\project-recipes.exe preview
~~~

## Use the same service through a terminal client

The native umicom project commands are a presentation layer over the shared project catalogue, variable preparation and generation services. Begin by listing templates. Then supply the recipe, display name, application identity, target, parent and folder explicitly. This makes the intended project reviewable and avoids relying on whichever working directory happened to launch the terminal.

~~~powershell
umicom project templates
umicom project plan --template developer.template.c23-gtk4 --name "Umicom Recipe Study" --id org.umicom.recipe.study --target recipe_study --parent C:/umicom/projects --folder recipe-study --show-files
~~~

## Read before authorizing creation

The plan command renders text and reports the proposed destination without writing project files. Review both paths and contents. It does not check destination existence or save an immutable plan token. A later create command renders the selected recipe again using its current implementation. If the CLI binary or recipe source changes between commands, repeat the preview and compare it before creation.

~~~powershell
umicom project create --template developer.template.c23-gtk4 --name "Umicom Recipe Study" --id org.umicom.recipe.study --target recipe_study --parent C:/umicom/projects --folder recipe-study --apply
~~~

## Interpret completion precisely

The explicit --apply option authorizes the CLI to attempt project creation. It is not used on plan. Existing destinations are refused, and the command does not run Git, CMake, a package manager or the generated application. Exit zero reports completion of this scoped operation. Exit two indicates command admission or option misuse; exit one indicates service, I/O or output failure. Inspect the printed diagnostic as well as the exit code.

## Handle partial effects

Creation is not rollback-based. A filesystem error or a later model-registration failure can leave new partial files. Keep the report and inspect the destination before deciding how to recover. Do not rerun the command repeatedly or delete the folder automatically. A concurrent writer is outside the supported creation contract. The preview does not reserve the destination against another process.

## Exercise the interface deliberately

In a separate disposable parent chosen by you, first omit --apply and verify refusal without a project directory. Then preview and create once with valid options. Finally try creation at the same destination and verify that it is refused without changing existing content. These are owner-run filesystem exercises; the memory-only course lab does not execute them. Record commands, exit codes and destination content identities if you use them as qualification evidence.

## Continue through the generated guide

Read the generated README before configuring. The GTK recipe requires a compatible Framework SDK with its GTK component and branding helper, alongside the native toolkit toolchain. Successful file creation cannot establish that those dependencies are present. Keep build, test, install and launch observations as separate stages, preserving the first failure instead of continuing through errors.

## Source and next steps

[Lab build and source guide](../../../labs/native/framework-project-recipes/README.md) · [Qualification record](../../../labs/native/framework-project-recipes/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/project-native-cli-explicit-creation.html)

[Previous lesson](project-select-a-new-destination.md) · [Course index](../../courses/umicom-development/index.html) · [Next lesson](project-branding-and-sdk-qualification.md)
