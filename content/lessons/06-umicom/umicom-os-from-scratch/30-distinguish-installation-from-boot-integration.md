<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/30-distinguish-installation-from-boot-integration.md

PURPOSE:
Distinguish installation from boot integration

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Distinguish installation from boot integration

## Setup recap

Keep the native probe build and observation from lesson 28. Read docs/foundation/cvm-preview.md and the OS image workflow before preparing a guest. This lesson explains the packaging boundary; it does not instruct you to replace an existing boot image or add an unreviewed startup service.

## What installation actually changes

The probe install rule places its executable under usr/libexec relative to the chosen installation prefix. A staging directory is an ordinary folder that holds candidate installed files. Populating it does not update the restrictive root-filesystem inventory, rebuild the archive or make PID 1 launch anything.

A Linux guest also needs a Linux-target executable with the appropriate runtime dependencies. A static link can reduce dynamic-library requirements, but does not prove architecture compatibility, boot readiness or correct service ordering. These remain separate questions.

## Review the integration contract

The current CVM probe has deliberately not been added to the normal root-filesystem or PID-1 service inventory. Its successful native process check is useful evidence for that executable only. The Kernel CVM envelope uses a different native EXIT interface and cannot substitute for this Linux user-space program.

1. Identify the exact target architecture and operating-system interface of the candidate executable.
2. Review the image inventory and archive validation rules before proposing an installed path.
3. Decide whether the tool is manual-only or a startup service; review ordering and failure behaviour if it is a service.
4. Rebuild the relevant image and preserve its identity before guest execution.
5. Record normal startup, recovery and service-failure observations independently.

## Exercise

Write a proposed integration record with four columns: source identity, built artifact, staged file and boot-image entry. Leave the boot-image entry unverified when only native compilation and installation have occurred. Explain what new evidence would be needed to fill it.

For troubleshooting, locate the first boundary where the expected artifact is missing. A correct probe transcript cannot repair a missing image manifest entry. A complete archive cannot prove that the process launched. Keep these claims distinct so a later failure can be diagnosed from the right layer.

## Read the source

[Open the OS source](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/cvm-preview.md). Use the matching checkout for qualification.

## Continue learning

[Course contents](index.md) · [Previous: Reuse the Framework preview command](29-reuse-the-framework-preview-command.md) · [Next lesson](31-describe-a-source-build-before-running-it.md)
