<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/18-follow-a-framework-project-recipe.md

PURPOSE:
Follow a Framework project recipe

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Follow a Framework project recipe

A compiler reads a program and translates it into another representation. An IDE adds editing, project navigation and commands around that compiler. In this module, Umicom C accepts a deliberately small arithmetic language. Umicom Framework supplies the project recipe and Studio presents it. We follow the connection between those three responsibilities.

## Prepare the tools

1. Open PowerShell on Windows or a terminal running bash on Linux. A terminal accepts written commands; each command below starts an existing program.
2. Find your Umicom C executable. Run `umicom-c --version`. If it is not found, add its actual installation directory to PATH for this terminal or use its full path. PATH is the list of folders searched for program names.
3. Run `cmake --version` and `ninja --version`. CMake prepares a build description; Ninja follows that description. Install any missing tool through your platform's normal package manager.
4. Choose a practice destination, such as `C:\umicom\examples\arithmetic-preview`. The Studio starter requires a new folder: choose its parent first and do not create the final folder in advance.
5. In a Studio build containing the new Framework recipe, use **File → New Project**, choose **Umicom C Arithmetic Preview**, enter project details and the new destination, then create it. Generation creates text files only. It does not install dependencies or run the program.

The terminal exercises use that generated project independently of Studio's interface. See [Learning CMake](../../../courses/learning-cmake/index.html) for a longer introduction.

## One owner for generated projects

A recipe describes the files a new project needs. A generator combines that recipe with values such as a project name and destination. Studio requests that shared operation rather than maintaining another copy of every starter.

The Umicom C preview recipe supplies eight files: `CMakeLists.txt`, `CMakePresets.json`, the main source, two deliberately invalid sources, a CMake test driver, a README and `.gitignore`. The last file tells Git which generated build products should remain outside source history.

1. Read the file table in Framework's `src/developer_project/templates/umicom_c_preview.c`. Each entry pairs a relative destination with text to write.
2. Follow registration in `builtin_templates.c`. Registration makes a recipe discoverable; a menu does not need another hard-coded list.
3. Read `UmiGtk4NewProjectDialogPrepare` in the GTK adapter. It lists CMake recipes from the catalogue. The dialog owns fields and selection; Framework owns generation.
4. Read `UmiDeveloperProjectCreateNew`. It rejects an already existing destination, preventing a starter from replacing another project's source.
5. Compare your generated files with the recipe. Inspect text; do not copy Framework's implementation into an application.

A path such as `src/main.uc` is relative to the project root. An absolute path starts at a filesystem root. Relative recipe paths make a starter usable in a folder selected by the learner.

## Experiment

Try creating another project in the same destination. Expect a refusal, with existing source unchanged. Cancel and choose another new folder. If your build behaves differently, retain the folder and report the exact steps.

## Check your understanding

Adding a catalogue entry makes a recipe selectable. It does not install a compiler, establish trust in arbitrary project commands or prove that tests pass. Those are separate responsibilities.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/developer_project/generator.c).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Previous: Open an arithmetic project in Studio](17-open-an-arithmetic-project-in-studio.md) · [Next: Select the preview build profile](19-select-the-preview-build-profile.md)

[Written course contents](index.md)
