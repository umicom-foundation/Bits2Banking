<!--
Umicom Bits2Banking
File: labs/native/framework-project-recipes/README.md

PURPOSE:
Build and study the installed Framework project recipe client.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Prepare project recipes through Framework

This C23 console lab consumes the installed **Umicom::developer** target. It observes catalogue entries, owned variables, validated requests, complete memory previews and destination selection. It opens no project files, creates no directories and launches no tools or windows. The teaching recipe is a two-file fixture, not a complete distributable application.

Start with [Select a project recipe](../../../content/courses/umicom-development/lessons/project-select-a-catalogue-recipe.html) and follow the eight lessons. The final lessons explain the separate native CLI creation and GTK qualification workflows.

## Prepare one installed SDK

1. Install a Framework revision containing the shared variable validator, transactional generation-plan builder and native project commands.
2. Identify the installed prefix and its producer revision. The example below uses C:/umicom/installed/framework; substitute your actual prefix consistently.
3. Select a compatible compiler, architecture and runtime. Source headers from one revision must not be mixed with older installed archives.
4. Run each command separately and stop on errors. These instructions do not record an executed pass.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-project-recipes -B .\build\framework-project-recipes -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-project-recipes --parallel 2
ctest --test-dir .\build\framework-project-recipes --output-on-failure --no-tests=error
~~~

The CMake configuration checks package origin, SDK environment metadata and the installed developer target. It never falls back to a producer source tree. If a cached build directory resolves another SDK, use a fresh consumer directory. On Linux, choose a separate directory, matching compiler and absolute SDK prefix; the executable has no .exe suffix.

## Observe individual scenarios

~~~powershell
& .\build\framework-project-recipes\project-recipes.exe preview
& .\build\framework-project-recipes\project-recipes.exe late-failure
& .\build\framework-project-recipes\project-recipes.exe gtk-branding
~~~

| Scenario | Required observation |
| --- | --- |
| catalogue | Every returned recipe validates; console identity is present; index at count is absent. |
| variables | The stored value survives caller-buffer mutation and can be copied to another variable. |
| invalid-variable | Malformed owned text is refused before rendering changes the previous output. |
| request | Standard variables include RECIPE_STUDY_GENERATED_H. |
| invalid-request | An invalid target is refused with an explanation. |
| preview | Two owned file paths and text-byte counts are printed. |
| late-failure | An unset variable in the second file leaves the accepted plan unchanged. |
| duplicate | Different recipe paths rendering to one destination are refused without replacing the plan. |
| aliased-root | The current plan root can be read while preparing its replacement. |
| destination | The pure destination chooser returns the expected combined path. |
| reserved-folder | A reserved device name is refused without replacing the output. |
| gtk-branding | Rendered GTK source connects shared build and window identity services. |

Exit zero means the selected scenario observed its expected scoped outcome. An assertion prints its location and returns one. Missing or unknown scenario arguments return two. Expected output is not proof that this source or your installed SDK has been executed successfully.

## Read the boundaries

- recipe.c holds static borrowed recipe text and initializes explicit owned request values. It contains no renderer.
- inputs.c exercises shared catalogue, variable, request and destination services.
- preview.c owns large plans on the heap and compares complete accepted state across controlled refusals.
- main.c selects the requested scenario and reports its outcome.
- lab.h declares only the teaching client boundaries. CMakeLists.txt links the installed target.

Framework application branding embeds the canonical ICO on Windows and stages the shared artwork according to its deployment policy. The terminal controls its own font. Course pages use the approved SVG/ICO and local typography. The gtk-branding case checks generated source calls, not native icon appearance or a managed GTK font profile.

## Continue to a real application

Use the native CLI lesson to list, preview and explicitly create a built-in GTK starter in a destination you choose. Creation rerenders the current recipe and may leave new partial files on an I/O failure. Inspect them before retrying. The API does not resolve every filesystem alias or provide a race-proof creation transaction. Configure, compile, test, install and launch are separate owner-run steps.

Keep the first diagnostic and the SDK identity when a consumer build fails. Do not weaken an expected status to conceal a stale installation. Record actual evidence in [QUALIFICATION.md](QUALIFICATION.md), including failures and skipped coverage.
