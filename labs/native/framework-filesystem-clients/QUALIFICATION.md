<!--
Umicom Bits2Banking
File: labs/native/framework-filesystem-clients/QUALIFICATION.md

PURPOSE:
Record source, installed SDK, native storage and branding observations independently.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Qualify the filesystem client lab

These are acceptance steps. No compiler, native scenario or visual pass is
established by the authored lab or by source inspection.

1. Record the Framework producer revision, installed SDK prefix and this
   consumer's source revision.
2. Record compiler identity, target architecture, runtime, operating system and
   filesystem. Keep configure output showing the selected package origin.
3. Build the lab, then run all fifteen CTest scenarios from the same build tree.
   Stop and retain a complete diagnostic on a failed step.
4. Preserve the printed run folders. Compare binary bytes and zero-length files
   directly; a text viewer cannot establish every binary observation.
5. Confirm preview/name scenarios do not create a new project fixture. Their
   successful output is not proof of destination availability.
6. Inspect the produced executable metadata and Windows ICO resource where
   applicable. Review the lesson SVG/ICO references and font fallback in the
   published learning environment.
7. Run Framework's wider rooted file/directory and checked project-creation
   qualification, including capability skips and injected partial-I/O cases.
   Keep those results separate from the public SDK lab.
8. Build, test and launch any generated application only as a separate reviewed
   workflow. The storage lab does none of those operations.

| Evidence | Recorded identity/result |
| --- | --- |
| Framework revision and installed prefix | Not yet recorded |
| Consumer source revision | Not yet recorded |
| Compiler, architecture and runtime | Not yet recorded |
| Operating system and filesystem | Not yet recorded |
| Configure/build output | Not yet recorded |
| Fifteen scenario outcomes | Not yet recorded |
| Retained fixture paths | Not yet recorded |
| Native link/partial-I/O wider coverage | Not yet recorded |
| Executable metadata and icon | Not yet recorded |
| Lesson rendering and font fallback | Not yet recorded |

The lab does not establish isolation from privileged writers, changes between
separate rooted operations, power-loss durability, every filesystem alias rule,
device writing or bootability. Native regression evidence must identify the
exact source and environment tested. Preserve failures and skips independently
of successful scenarios.
