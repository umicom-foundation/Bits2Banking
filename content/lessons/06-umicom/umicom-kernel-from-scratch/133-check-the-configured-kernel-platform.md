<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/133-check-the-configured-kernel-platform.md

PURPOSE:
Check the configured Kernel platform

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check the configured Kernel platform

Imagine you are reviewing a saved Umicom Kernel build record. The source and linked image still have the same fingerprints, but the saved virtual machine label has changed. This lesson follows the review on paper. You only need the example on this page.

## 1. Ask what each field tells you

A **fingerprint**, also called a **digest**, is a string calculated from data. SHA-256 is the method this record uses. The source fingerprint describes the selected source inventory. The image fingerprint describes the selected linked ELF files. **ELF** is a file format used here for the linked Kernel image and other build outputs.

The same record holds three labels taken from the selected build settings. Read each as an answer to a different question.

| Saved field | Question it answers | Practice value |
| --- | --- | --- |
| `sourceSha256` | Which source file records did this capture identify? | The saved source fingerprint |
| `imagesSha256` | Which linked ELF file records did this capture identify? | The saved image fingerprint |
| `ARCHITECTURE` | Which processor instruction family did the configuration select? | `riscv64`, the 64-bit RISC-V family |
| `ABI` | What agreement did the build select for separately compiled code? | `lp64`, a RISC-V integer calling convention with 64-bit C long values and pointers |
| `MACHINE` | Which virtual board and machine option did the build record? | `virt,aclint=off` |

**ABI** stands for **application binary interface**. It includes rules such as where a function receives arguments and how large a pointer is. The machine label describes the board setting for a guest, which is a program or system prepared to run inside the emulator. Here `virt` names a virtual board and `aclint=off` is an explicit setting for its local interrupt devices.

## 2. Compare a saved record with the intended build

This is an extract from a synthetic receipt. The receipt’s full source and image fingerprints come from fixed exercise inputs. The image bytes in that exercise are plain text. There is no executable Kernel in the exercise.

~~~json
{
  "sourceSha256": "a397a4cd51c802c4125e27a7b4497ee4be2411e7c4b9c1b7789fea70cd71c385",
  "imagesSha256": "1a7932fba9b443d43d5e3aed159d4557ec3666a9cc77067324bc5226247afd1d",
  "ARCHITECTURE": "riscv64",
  "ABI": "lp64",
  "MACHINE": "virt,aclint=off"
}
~~~

Copy the five keys onto paper. Keep the two fingerprint values fixed. Use these expected configuration values for every row below, except where the exercise says to omit an expected value.

~~~text
Expected ARCHITECTURE = riscv64
Expected ABI          = lp64
Expected MACHINE      = virt,aclint=off
~~~

The configured Kernel identity check uses matching architecture, ABI and machine settings for capture and verification. The ordinary manual file-identity check compares the source and ELF records and checks the record’s scope. For a manual review that also needs the configured labels, read the build settings and supply all three values with `VERIFY_CONFIGURED_CONTEXT` enabled. For the paper exercise, recognize these options without running a command.

~~~text
-DVERIFY_CONFIGURED_CONTEXT=ON
-DARCHITECTURE=riscv64
-DABI=lp64
-DMACHINE=virt,aclint=off
~~~

## 3. Change one item and predict the report

Start with the original five keys for each row. Compare on paper before reading the decision. The six rows reproduce the outcomes checked with fixed, inert data.

| Change for this round | Expected configured identity decision |
| --- | --- |
| Keep all three labels and expectations as shown. | The saved identity agrees. |
| Replace the saved architecture with `x86_64`. | Report a difference for `ARCHITECTURE`. |
| Replace the saved ABI with `ilp32`. | Report a difference for `ABI`. |
| Replace the saved machine label with `virt`. | Report a difference for `MACHINE`. |
| Remove the saved machine label. | Report a difference for `MACHINE`. |
| Keep the saved record and leave out the expected machine value. | Ask for a nonempty `MACHINE` expectation. |

The machine comparison uses the full saved string. `virt` and `virt,aclint=off` are different strings even if an emulator’s default setting would produce the same behaviour.

Here is the order to follow in your next paper review.

~~~text
CHECK the saved format, source file records, linked ELF records and scope fields
IF configured label checking is enabled
    REQUIRE an expected architecture, ABI and machine
    COMPARE the three labels in that order
    REPORT the first differing or missing saved label
RECORD the identity result
KEEP any runtime test result with its own evidence
~~~

Now imagine the saved ELF fingerprint differs and the saved machine label also differs. The file comparison comes first, so address the ELF evidence before interpreting the label result. Keep the original receipt. Confirm which build directory supplied the selected image and which settings supplied the expected machine label.

## 4. Choose the next evidence

A matching identity says the selected source and ELF records agree with the saved fingerprints and, when configured checking is enabled, that the three labels agree. A claim that the operating system reached its first boot screen needs a separate test record that identifies the linked image, the environment in which it ran and the observed outcome. The exercises here compare saved data with configured expectations and involve no build, firmware or guest.

In the Umicom Kernel checkout, `docs/BUILD_IDENTITY.md` describes the review. The matching capture and standard verification settings are in `cmake/Qualification.cmake`. Keep each result with the configuration and artifact records you would use to explain it to another contributor.

[RISC-V ABI specification](https://riscv-non-isa.github.io/riscv-elf-psabi-doc/) · [QEMU virtual board settings](https://www.qemu.org/docs/master/system/riscv/virt.html#machine-specific-options)

[Course contents](index.md) · [Previous lesson · Read the scope of a Kernel build identity](132-read-the-scope-of-a-kernel-build-identity.md) · [Related lesson · Distinguish input identity from guest evidence](108-distinguish-input-identity-from-guest-evidence.md) · [Umicom OS · Qualify produced images in stages](../umicom-os-from-scratch/48-qualify-produced-images-in-stages.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/133-check-the-configured-kernel-platform.html)

[Next lesson · Count complete boot handoff records](134-count-complete-boot-handoff-records.md)
