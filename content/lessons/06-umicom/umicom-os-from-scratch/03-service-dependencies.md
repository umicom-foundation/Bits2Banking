# Plan startup before executing it

The boot configuration is a small declarative language. A declaration states what is needed; it does not contain shell commands. The parser restricts executable paths, limits the number of services and rejects a dependency that is absent or circular.

```text
UMICOM_OS_BOOT 1
hostname=lesson
service=display|/usr/libexec/umicom-display|storage|1000
service=storage|/usr/libexec/umicom-storage|-|2000
```

Each service has an identifier, executable path, one prerequisite or `-`, and a timeout in milliseconds. Current accepted timeout values are 100 through 30000. Identifiers are deliberately narrow ASCII tokens. Configuration must finish with a newline.

## Inspect the implementation

1. Find `Service` in `boot/foundation/config.c` and identify its four field checks.
2. Find `Order`. It chooses a service only when its prerequisite has already been chosen.
3. Change storage's prerequisite to display in the lab input. Predict the result before building.
4. Restore the valid input. Change an executable path to `/bin/sh`; explain why the grammar rejects it.

## Review without launch

The OS target `umicom-os-boot-plan` accepts a configuration filename and displays its accepted order. Its output ends with `executed=false`. Do not treat a valid plan as evidence that the named executable exists or succeeds; actual service supervision is a separate step.

<details>

<summary>Why not execute services while parsing lines?</summary>

A later invalid line could leave the system partly started. Validating the whole graph first separates admission from execution and makes failure easier to reason about.

</details>

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/07-applications-os-and-kernel.md), then use the [connected learning map](../../../courses/learning-paths.html#os) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-os-from-scratch/lessons/03-service-dependencies.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: Build one real OS component](02-build-the-parser.md)

[Next: Keep rejected state separate from recovery](04-failure-and-recovery.md)
