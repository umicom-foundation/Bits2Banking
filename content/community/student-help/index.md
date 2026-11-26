<!--
Umicom Bits2Banking
File: content/community/student-help/index.md

PURPOSE:
Help students find a short answer and its source in the learning library.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Ask about your next step

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Ask a short question about the starter guides. You can ask “How do I update PowerShell 7?” or “How do I compile my first C program?” The helper chooses an answer from this page and links you to the full lesson. Your question stays in this browser tab.

<form data-btb-help-form>
  <p><label for="btb-question">Your question</label></p>
  <p><input id="btb-question" name="question" type="text" maxlength="240" autocomplete="off" size="36" required disabled></p>
  <p><button class="md-button md-button--primary" type="submit" disabled>Ask</button></p>
</form>
<p id="btb-help-status" role="status" aria-live="polite">You can read the answers below while question matching loads.</p>
<div id="btb-help-result"></div>

## Browse the answers

<details data-btb-answer="1" markdown="1">
<summary>Get started with PowerShell 7</summary>

1. Open PowerShell from the Windows Start menu.
2. Type `$PSVersionTable.PSVersion` and look at the `Major` value.
3. If you see `5`, follow the installation guide. If you already see `7`, use the update section when you need a newer release.

If you see **`5`**, search Start for **PowerShell 7** and check its version if you find it. If it is missing, run `winget install --id Microsoft.PowerShell --exact --source winget` from a Windows terminal. You can keep Windows PowerShell 5.1 installed.

If you see **`7`** and installed PowerShell with WinGet, run `winget upgrade --id Microsoft.PowerShell --exact`. If you used another installer, follow the update guide for that method. Open PowerShell 7 again after the update and confirm the version.

[Install and open PowerShell 7](../../simple-steps/powershell-setup.md) · [Update PowerShell 7](../../simple-steps/powershell-setup.md#update-an-existing-powershell-7-installation)

</details>

<details data-btb-answer="2" markdown="1">
<summary>Install PowerShell 7 on Windows</summary>

1. Open **Windows PowerShell** from Start. Run `winget --version` to check that WinGet is available.
2. Type `winget install --id Microsoft.PowerShell --exact --source winget`. Read any prompt before you confirm it.
3. After installation, open **PowerShell 7** from Start. Type `$PSVersionTable.PSVersion` and check that `Major` is `7`.

PowerShell 7 can sit alongside Windows PowerShell 5.1.

[Bits2Banking installation guide](../../simple-steps/powershell-setup.md) · [Microsoft’s Windows installation instructions](https://learn.microsoft.com/en-us/powershell/scripting/install/install-powershell-on-windows)

</details>

<details data-btb-answer="3" markdown="1">
<summary>Update an existing PowerShell 7 installation</summary>

1. Type `$PSVersionTable.PSVersion` in PowerShell 7 and note the result.
2. If you installed with WinGet, run `winget list --id Microsoft.PowerShell --exact --upgrade-available`.
3. If an update appears, type `winget upgrade --id Microsoft.PowerShell --exact`. When it finishes, open a fresh PowerShell 7 window and check the version again.

Use your original installation method if you installed another way. The update can wait if WinGet offers no newer version.

[Bits2Banking update steps](../../simple-steps/powershell-setup.md#update-an-existing-powershell-7-installation) · [Microsoft’s PowerShell guide](https://learn.microsoft.com/en-us/powershell/scripting/install/install-powershell-on-windows)

</details>

<details data-btb-answer="4" markdown="1">
<summary>Find the PowerShell version you opened</summary>

1. Run `$PSVersionTable.PSVersion`.
2. Check the `Major` column. If it shows `5`, look for **PowerShell 7** separately in Start. An existing installation can also be opened by typing `pwsh`.
3. Run the version check again in the new window and look for `7`.

[Open and verify PowerShell 7](../../simple-steps/powershell-setup.md) · [Terminal lesson](../lessons/01-open-your-terminal.md)

</details>

<details data-btb-answer="5" markdown="1">
<summary>When Windows cannot find WinGet</summary>

1. In your Windows terminal run `winget --version` to confirm what is missing.
2. If the command cannot be found, use the official Microsoft guide to choose a Windows installer for your computer. The Bits2Banking setup guide links to it.
3. Open PowerShell 7 after setup and verify `Major` is `7` with `$PSVersionTable.PSVersion`.

[Bits2Banking setup guide](../../simple-steps/powershell-setup.md) · [Official Windows installer options](https://learn.microsoft.com/en-us/powershell/scripting/install/install-powershell-on-windows)

</details>

<details data-btb-answer="6" markdown="1">
<summary>Use the instructions for your operating system</summary>

The Bits2Banking PowerShell setup page teaches Windows. Select your exact operating system or Linux distribution in Microsoft’s installation guide. Once PowerShell opens, `$PSVersionTable.PSVersion` shows the version in that session.

[Bits2Banking Windows setup](../../simple-steps/powershell-setup.md) · [Microsoft’s platform-specific installation guides](https://learn.microsoft.com/en-us/powershell/scripting/install/installing-powershell)

</details>

<details data-btb-answer="7" markdown="1">
<summary>Check your system and free space</summary>

Open the system checks guide. Use its Windows commands to read the processor, installed memory and free space. Check the drive where you plan to keep your project.

[Check your computer](../../simple-steps/system-checks.md)

</details>

<details data-btb-answer="8" markdown="1">
<summary>Find or create your practice folder</summary>

Run `Get-Location` to see your current folder. Choose a separate practice folder and follow the guide to create and enter it. Run `Get-Location` again to confirm the path changed.

[Create your practice folder](../../simple-steps/work-folder.md)

</details>

<details data-btb-answer="9" markdown="1">
<summary>Set up the Windows C tools</summary>

Use one toolchain for the whole starter project. Follow the Windows UCRT64 setup, then check the versions of GCC, CMake and Ninja in the guide before building anything.

[Set up your C development tools](../../simple-steps/toolchain.md)

</details>

<details data-btb-answer="10" markdown="1">
<summary>Write, build and run a first C program</summary>

Save the starter source as `coffee.c` in your practice folder. Use the C23 GCC command from the build step. Check that it created `coffee.exe`, then run it and compare the displayed result to the lesson.

[Write the first C program](../../simple-steps/c.md#5-write-the-program) · [Build it](../../simple-steps/c.md#6-build-the-program) · [Run it](../../simple-steps/c.md#7-run-it-and-change-one-thing)

</details>

<details data-btb-answer="11" markdown="1">
<summary>Create or inspect a local Git repository</summary>

Open your practice folder and run `git status`. If you have a new folder for a first repository, follow the guide to initialize it and check the files before saving a commit.

[Create a local Git repository](../../simple-steps/git-local.md)

</details>

<details data-btb-answer="12" markdown="1">
<summary>Clone a Git repository</summary>

Copy the repository URL from a repository you can access. Follow the clone guide in a different scratch folder. Compare the first commit in the clone with the repository you expected.

[Clone your repository](../../simple-steps/git-clone.md)

</details>

<details data-btb-answer="13" markdown="1">
<summary>Build and test a CMake project</summary>

Use the guide’s separate configure, build and test commands in order. Stop at the first failure. If configure fails, solve that before reading the build or test output.

[Build and test with CMake](../../simple-steps/build-project.md)

</details>

<details data-btb-answer="14" markdown="1">
<summary>Build with an installed Umicom Framework SDK</summary>

Find your installed SDK folder and confirm it has the CMake package file named in the workshop. Use the same toolchain as the SDK. The venue project takes you from the sample input to a tested receipt one step at a time.

[Installed Framework SDK workshop](../../simple-steps/framework-sdk-venue-report/index.md)

</details>

<details data-btb-answer="15" markdown="1">
<summary>Identify the right Umicom ISO or boot image</summary>

Start by matching your product, processor and firmware to the documented image. Inspect a regular file and read the evidence before choosing a device. The guide distinguishes a native RISC-V Kernel VM from Umicom OS media and explains which checks each supports.

[Prepare and check boot media](../../simple-steps/boot-media/index.md)

</details>

<details data-btb-answer="16" markdown="1">
<summary>Start developing in Umicom C</summary>

Open the course and follow its first supported example. Record the tool you used and whether the step interprets or compiles source before comparing the outputs.

[Develop with Umicom C](../../lessons/03-native-code/developing-with-umicom-c/index.md)

</details>

<details data-btb-answer="17" markdown="1">
<summary>Read a build error or failed test</summary>

Find the first failing command and capture its first useful diagnostic. Note which project and build folder produced it. The same guide shows how to distinguish configuration, compilation and test failures.

[Read a build log and choose the next step](../lessons/12-read-a-build-log.md)

</details>

<details data-btb-answer="18" markdown="1">
<summary>How do I get started with reflection?</summary>

1. Pick one language in the [reflection workshop](../../lessons/03-native-code/reflection-workshop/index.md).
2. Run or trace the sample and write down one observed field or type.
3. Check when the language made the observation. In native C23, the example combines compile-time type information with a catalogue you define.

</details>

<details data-btb-answer="19" markdown="1">
<summary>How can I keep Framework metadata after a registry changes?</summary>

1. Follow the [Framework metadata snapshot lesson](../../lessons/03-native-code/reflection-workshop/08-keep-a-framework-metadata-snapshot.md).
2. Capture a snapshot through the registry API.
3. Remove the original entry in the example and compare the saved fields. Release the snapshot through its own API when you finish.

</details>

<details data-btb-answer="20" markdown="1">
<summary>How do I review a boot choice in the Windows Setup Centre?</summary>

1. Open Umicom Setup Centre and choose **Boot and install**.
2. Select the product, machine, source, edition and output. Choose Foundation explicitly to try the Linux preview.
3. Read the result and check the next action in the [Setup Centre user guide](../../umicom/setup-centre-boot-planning.md). A physical USB route needs its own review and qualification.

</details>

<details data-btb-answer="21" markdown="1">
<summary>Where do I start contributing to Umicom?</summary>

1. Open the [contributor wiki](../../wiki/index.md) and choose one project.
2. Run one small example and keep its expected result.
3. Change one thing and check again. Include the command and observed result when you describe the change.

</details>

<details data-btb-answer="22" markdown="1">
<summary>Check a prebuilt RISC-V Kernel launch kit</summary>

1. Confirm that the extracted folder contains `identity.json`, `umicom-system.elf` and `umicom-recovery.elf`.
2. Obtain the SHA-256 for `identity.json` from a trusted publisher record separate from the kit.
3. Run the [launch-kit verification steps](../../simple-steps/boot-media/verify-kernel-launch-kit.md). Open the QEMU guide after the file check reports success.

</details>

<details data-btb-answer="23" markdown="1">
<summary>When Framework reports a header identity mismatch</summary>

1. Find the public header directory in the configure error.
2. Compare that directory with your intended SDK prefix. The exported and observed SHA-256 values show whether the chosen header set agrees with its CMake export.
3. Follow the [SDK header identity guide](../../wiki/sdk-header-identity.md) to choose one complete SDK and use a fresh build directory.

</details>

<details data-btb-answer="24" markdown="1">
<summary>When Studio refuses a build argument</summary>

1. Run `umicom-studio-build --help` using your current console executable.
2. Check whether the option needs another word. For example, `--phase` needs a phase name.
3. Compare the output and exit status with the [Studio build command guide](../../wiki/studio-build.md).

</details>

[Learning in Simple Steps](../../simple-steps/index.md) · [Course library](../../courses/index.html)
