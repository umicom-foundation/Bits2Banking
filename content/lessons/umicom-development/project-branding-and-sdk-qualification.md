<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/project-branding-and-sdk-qualification.md

PURPOSE:
Qualify generated application branding and the installed SDK boundary

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Qualify generated application branding and the installed SDK boundary

After preparing the installed-SDK lab in its README, run this scenario. Commands below are qualification instructions, not recorded results.

~~~powershell
& .\build\framework-project-recipes\project-recipes.exe gtk-branding
~~~

## Reuse the shared identity

The GTK starter recipes connect their build target to umicom_apply_application_branding and their window to umi_gtk4_ws_apply_window_identity. These services stage the supplied SVG artwork and integrate the Windows ICO where applicable. A client should not redraw the Umicom symbol, embed a replacement emoji or copy identity logic into each generated application. The installed SDK and its resource catalogue provide the reusable boundary.

## Understand what this lab checks

The gtk-branding scenario renders the C23 GTK recipe in memory and looks for the shared build and window identity calls. This is useful evidence that the recipe connects those APIs. It does not execute CMake, inspect an executable resource or display a window. A string-presence check cannot show that a shell, taskbar or window manager actually presents the intended icon.

| Qualification layer | Observation to collect |
| --- | --- |
| Recipe rendering | Expected shared calls and generated identities |
| SDK consumer build | Matching headers, archives and package origin |
| Executable packaging | Canonical ICO and staged SVG resources |
| Native launch | Window identity and resource lookup on the target host |
| Visual review | Logo proportions, readable fonts, contrast and DPI behavior |

## Keep typography honest

The course pages use the shared approved font stack: Segoe UI Variable Text or Segoe UI for prose and Cascadia Code or Consolas for code, with local fallbacks. The small generated GTK window still inherits the toolkit’s font settings; the recipe has not implemented a complete managed appearance panel or branded content header. Report those limits instead of claiming visual parity with a full Studio mockup.

## Build against one installed SDK

The lab CMake file requires an absolute installed prefix, checks that the chosen package configuration belongs to it, verifies the exported SDK environment metadata and links Umicom::developer. It does not add a source checkout as a fallback. This is intentional: a consumer build should reveal an incomplete installation rather than silently finding missing files in the producer tree. Use a compiler and runtime compatible with that SDK.

## Run the qualification sequence

Follow the lab README to configure a fresh build directory, build once and run all twelve registered scenarios. Record the SDK producer revision, consumer revision, compiler and test output. Then separately create and build a GTK application through the native CLI. Inspect its installed resources and launch it on the intended desktop. None of those actions is implied by reading this lesson or by a successful static source review.

## Recover from mismatched evidence

An undefined reference to the new variable validator can mean the headers and installed archive come from different revisions. A missing resource helper can mean the installation is incomplete. Keep the original diagnostic, select a coherent SDK and configure a new consumer directory before changing application code. A clean-machine launch is valuable because resources accidentally found in a development checkout can otherwise hide deployment errors.

## Source and next steps

[Lab build and source guide](../../../labs/native/framework-project-recipes/README.md) · [Qualification record](../../../labs/native/framework-project-recipes/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/project-branding-and-sdk-qualification.html)

<!-- Earlier end-of-module navigation retained for review:
[Previous lesson](project-native-cli-explicit-creation.md) · [Course index](../../courses/umicom-development/index.html)
-->
[Previous lesson](project-native-cli-explicit-creation.md) · [Course index](../../courses/umicom-development/index.html) · [Next lesson](storage-portable-path-admission.md)
