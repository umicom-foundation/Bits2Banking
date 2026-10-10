# Umicom source code and project documentation

The lessons in this guide are connected to the Umicom projects themselves. A repository is a collection of source files and their recorded history. You can read the code on GitHub before installing anything on your computer.

## Main repositories

| Project | Source repository | What to explore |
| --- | --- | --- |
| Umicom Framework | [umicom-framework](https://github.com/umicom-foundation/umicom-framework) | Reusable C23 libraries, public headers, module lifecycle, examples and tests |
| Umicom Applications | [umicom-applications](https://github.com/umicom-foundation/umicom-applications) | The application superproject, submodules, build presets and integration guides |
| Umicom Kernel | [umicom-kernel](https://github.com/umicom-foundation/umicom-kernel) | Native kernel research, architecture bring-up, memory, interrupts and testing |
| Umicom OS | [umicom-os](https://github.com/umicom-foundation/umicom-os) | Operating-system images, boot/recovery experiments and user-space services |
| Umicom Studio IDE | [umicom-studio-ide-module](https://github.com/umicom-foundation/umicom-studio-ide-module) | Studio product code; a thin consumer of Framework capabilities |
| Umicom Desk | [umicom-desktop-module](https://github.com/umicom-foundation/umicom-desktop-module) | Desktop shell, application launch and workspaces |
| Umicom Trader | [umicom-trader-module](https://github.com/umicom-foundation/umicom-trader-module) | Trading application, markets and workstation workflows |
| Umicom Open TMS | [umicom-tms-module](https://github.com/umicom-foundation/umicom-tms-module) | Treasury and trade-management application |
| Umicom Bank | [umicom-bank-module](https://github.com/umicom-foundation/umicom-bank-module) | Customer, account, payment and ledger application |
| Bits to Banking | [Bits2Banking](https://github.com/umicom-foundation/Bits2Banking) | Written lessons, books, diagrams, videos and educational examples |

## Find a real code example

Open the [Framework example of the Master Controller](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/framework_demo/main.c). The file defines a Slave Controller, declares required capabilities and connects its lifecycle to the Master Controller.

A second path is the [Framework learning examples](https://github.com/umicom-foundation/umicom-framework/tree/main/examples/learning). They include small programmes about binary numbers, C, memory and practical applications. The [notes project](https://github.com/umicom-foundation/umicom-framework/tree/main/examples/learning/projects/notes) grows the same concepts into a document application.

When reading an example, begin with the README or main source file. Find the public header that defines a function, inspect the implementation and then open the relevant tests. These steps show not just what the code does but how its behaviour is checked.

## Build and test

Each repository has its own build commands. The [Umicom development setup](../lessons/06-umicom/24-development-setup.md) explains how to prepare a Windows toolchain and clone the application superproject. The [Kernel documentation](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BUILD_AND_TEST.md) and [OS first-boot guide](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/first-boot.html) describe their separate build and simulation environments.

Source code changes are made in the owning project, not in the educational website. To improve a lesson or fix a broken link, contribute to [Bits2Banking](https://github.com/umicom-foundation/Bits2Banking) instead.
