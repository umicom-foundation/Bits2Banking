<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/project-application-identities.md

PURPOSE:
Keep display names, targets and application identities distinct

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Keep display names, targets and application identities distinct

After preparing the installed-SDK lab in its README, run this scenario. Commands below are qualification instructions, not recorded results.

~~~powershell
& .\build\framework-project-recipes\project-recipes.exe request
~~~

## Prepare one explicit request

A project wizard asks for several names because they serve different consumers. The display name is human-facing. The build target becomes a CMake target and executable name. The application identifier identifies the application to native facilities. The repository name describes the project folder or repository. Giving all of them the same unrestricted text can produce invalid source or build files.

| Field | Lab value | Role |
| --- | --- | --- |
| application_name | Umicom Recipe Study | Human-facing title |
| application_id | org.umicom.recipe.study | Application identity |
| repository_name | recipe-study | Repository/folder identity |
| target_name | recipe_study | Build target |
| template_id | learning.recipe.console | Recipe selection |

## Use the shared admission rule

LabRequest initializes the public request and copies fixed, bounded literals into its owned fields. For user-entered text, use checked copies and preserve the original text when reporting refusal. The current request validator accepts a restricted ASCII naming profile. Spaces are allowed in the display name; the target must begin with a letter or underscore and continue with letters, digits or underscores. This is a source-generation contract, not a complete validator for every downstream toolkit or packaging system.

~~~c
char message[256];
UmiStatus status = umi_developer_project_generation_request_validate(
    &request, message, sizeof message);
if (status == UMI_STATUS_OK)
    status = umi_developer_project_generation_request_variables(
        &request, &variables);
~~~

## Derive common values once

The standard-variable service prepares values such as APPLICATION_NAME, TARGET_NAME, TARGET_UPPER and HEADER_GUARD. The request scenario expects RECIPE_STUDY_GENERATED_H. A thin application client should call this service rather than copy its uppercase and separator rules. That keeps the CLI, Studio and a teaching client aligned when the reusable contract changes.

## Observe a refusal

Run invalid-request after request. It replaces the target with 9bad-target and requires INVALID_ARGUMENT. Read the returned explanation before editing the input. The bad target combines two problems: its initial digit and its hyphen. In a learner copy, test those independently so you understand which rule each example exercises. Keep a valid display name with spaces to show that target restrictions must not accidentally be applied to every field.

## Carry the limits forward

Validation does not check whether the destination exists, reserve a folder, invoke CMake or register an application with the operating system. The dry_run field belongs to generation execution; pure plan rendering already has no filesystem writes. When you later create a GTK application, still qualify its application identifier and deployment assets against the actual GTK and operating-system environment. A valid request is one prerequisite in a longer workflow.

## Source and next steps

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Lab build and source guide](../../../labs/native/framework-project-recipes/README.md) · [Qualification record](../../../labs/native/framework-project-recipes/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/project-application-identities.html)
-->
[Lab build and source guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-project-recipes/README.md) · [Qualification record](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-project-recipes/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/project-application-identities.html)

[Previous lesson](project-borrowed-recipes-owned-variables.md) · [Course index](../../courses/umicom-development/index.html) · [Next lesson](project-preview-owned-plan.md)
