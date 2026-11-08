<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/19-select-the-preview-build-profile.md

PURPOSE:
Select the preview build profile

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Select the preview build profile

A compiler reads a program and translates it into another representation. An IDE adds editing, project navigation and commands around that compiler. In this module, Umicom C accepts a deliberately small arithmetic language. Umicom Framework supplies the project recipe and Studio presents it. We follow the connection between those three responsibilities.

## Prepare the tools

1. Open PowerShell on Windows or a terminal running bash on Linux. A terminal accepts written commands; each command below starts an existing program.
2. Find your Umicom C executable. Run `umicom-c --version`. If it is not found, add its actual installation directory to PATH for this terminal or use its full path. PATH is the list of folders searched for program names.
3. Run `cmake --version` and `ninja --version`. CMake prepares a build description; Ninja follows that description. Install any missing tool through your platform's normal package manager.
4. Choose a practice destination, such as `C:\umicom\examples\arithmetic-preview`. The Studio starter requires a new folder: choose its parent first and do not create the final folder in advance.
5. In a Studio build containing the new Framework recipe, use **File → New Project**, choose **Umicom C Arithmetic Preview**, enter project details and the new destination, then create it. Generation creates text files only. It does not install dependencies or run the program.

The terminal exercises use that generated project independently of Studio's interface. See [Learning CMake](../../../courses/learning-cmake/index.html) for a longer introduction.

## Names must describe real settings

A preset is a named configuration. A build profile is information Studio uses to invoke tools: project directory, preset and optional run program. A profile naming a nonexistent preset cannot configure even when generated source is correct.

The arithmetic starter uses `preview` and `build/preview`. The VHDL starter uses `simulation`. Ordinary native C projects retain platform-specific settings. Framework selects these values in the project model; `UmiBuildProfileFromProject` transfers them to a build profile.

1. Open `CMakePresets.json` in the arithmetic project.
2. Find configure preset `preview`. Its generator is Ninja; its binary directory holds generated build files.
3. Run `cmake --preset preview`. If Umicom C is outside PATH, pass its actual full path:

```powershell
cmake --preset preview -DUMICOM_C_EXECUTABLE="C:/umicom/installed/umicom-c/bin/umicom-c.exe"
```

On Linux an absolute path such as `/home/learner/tools/bin/umicom-c` serves the same purpose. Change these examples to your real location.

4. Read the output. A missing tool should stop configuration. Successful configuration prepares a build; it does not run source.
5. In Studio's Build Settings, compare the preset with `preview`. Do not substitute a desktop preset simply because the host is Windows.

## Why the native Run program is empty

This is a meta project: its output is checked source for an interpreter, not a newly linked desktop executable. Use the explicit `preview` build target in the next lesson. Empty native launch settings do not mean successful native compilation.

## Review question

Which file establishes that a preset exists, and which function places its name in the model? Answer: the generated presets file and Framework's project service. Agreement between them is a contract covered by the generated-profile regression.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/developer_project/service.c).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Previous: Follow a Framework project recipe](18-follow-a-framework-project-recipe.md) · [Next: Check only affected preview inputs](20-check-only-affected-preview-inputs.md)

[Written course contents](index.md)
