<!--
Umicom Bits2Banking
File: content/wiki/course-maintenance.md

PURPOSE:
Show how to add a small verified lesson or a source-grounded student help answer.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Course maintenance

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use the shortest lesson that lets someone do the work and check the result. An existing course can link to a focused worksheet without repeating its full explanation.

1. Find the topic in the [course guide catalogue](../simple-steps/course-guides/index.md). Open the full lesson and confirm the commands or API names in its current source.
2. Write the starting state, one action per numbered step and an expected result. For a command, say which shell or program runs it. Use a training input that does not contain a real account, credential or personal record.
3. Test the beginner path from a fresh workspace when the necessary tools are available. A working preparation command and an example that actually ran are different observations. Record the command, result and any skipped check precisely.
4. Add the link from the short route back to the detailed lesson. When a student help answer points to it, check that the link opens the page with the correct instructions.

**Example.** If someone asks how to update PowerShell 7, separate their first install from an update. Show how they can open PowerShell 7 and check the result. Use [the PowerShell setup guide](../simple-steps/powershell-setup.md) for the current steps.

## Keep the same lesson across devices

1. Keep one reviewed Markdown lesson, one stable course title and one expected result. Link to it from the short guide and the wiki.
2. Keep lesson links relative to the site so they work under the GitHub Pages project path and on another host. Set the published canonical address for the deployment that serves the release.
3. Use the same release’s lesson files and native learning manifests in the desktop catalogue. When a source changes, regenerate its manifest and check the resulting resource digests before distributing the pack.
4. Check reading and links in each client. Keep the written exercise available when an interactive browser control or local compiler is unavailable.

Use [Study Bits2Banking on any device](../start/study-on-any-device.md) for the reader’s route and [the native education tools guide](../umicom/native-education-tools.md) to prepare or serve the reviewed site.

[Student help](../community/student-help/index.md) · [Contributor wiki](index.md)
