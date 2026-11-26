<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/67-keep-boot-option-text-in-its-argument.md

PURPOSE:
Keep boot option text in its argument

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep boot option text in its argument

A **boot argument** is a piece of text passed to the kernel at startup. It can name a feature or give it a value. The parser needs to know where one argument ends before deciding whether it describes an Umicom boot option.

## Before you begin

Have a text editor or a sheet of paper ready. Copy the sample command line and mark its spaces and quotation marks before splitting it into arguments. To run the optional checks, use an existing Umicom OS foundation-test build.

## Read the argument before looking at its value

Double quotes keep spaces within the same argument. In `module.note="example umicom.recovery=1 sample"`, the name is `module.note`. The text `umicom.recovery=1` is part of that value. The value leaves recovery at the parser's default. A top-level `umicom.recovery=1` outside that value is a different input.

Linux also uses a standalone `--` to finish kernel options and leave the rest for the initial user-space program. The Umicom OS boot parser recognizes that boundary. A value such as `module.note="--"` still belongs to `module.note`. It does not finish the kernel argument list. [Linux kernel parameters](https://docs.kernel.org/admin-guide/kernel-parameters.html)

| Text supplied to a parser fixture | Expected recovery state |
| --- | --- |
| `module.note="example umicom.recovery=1 sample"` | Preserve the default state |
| `module.note="two words" umicom.recovery=1` | Read the top-level option |
| `-- umicom.recovery=1` | Preserve the default state |
| `module.note="--" umicom.recovery=1` | Read the top-level option |

## Trace a safe parser exercise

Use these strings as data in `umicomOS/tests/foundation/test_config.c`. The cases call `UmiOsBootOptionsParse` and examine its returned data. They exercise no power control. Find the case with a quote that never closes. The normal result is a parse refusal with earlier caller output preserved.

~~~text
SCAN from the first character of an argument
KEEP spaces inside a double-quoted value in that argument
IF the argument is the standalone boundary, finish reading boot options
IF the complete argument is an admitted Umicom option, record its value
PUBLISH the new options after the input passes validation
~~~

From the Umicom OS checkout, use the directory of your configured foundation-test build. If that directory is `build/native-foundation`, run `ctest --test-dir build/native-foundation -R 'options-(quoted-data|init-divider|quoted-init-divider|open-quote|directive-spelling)' --output-on-failure --no-tests=error`. Expect five named cases with the current test registrations. If CTest finds none, confirm the build directory and its source revision.

This exercise distinguishes parser evidence from startup evidence. A parser returning a valid flag establishes how it read the string. A separate operating-system test establishes what a launched system does with an admitted flag.

[Course contents](index.md) · [Previous: Check the minimum space for a FAT32 volume](66-check-the-minimum-space-for-fat32.md) · [HTML edition](../../../courses/umicom-os-from-scratch/lessons/67-keep-boot-option-text-in-its-argument.html)

[Next lesson · Count the slots both GPT tables need](68-count-the-slots-both-gpt-tables-need.md)
