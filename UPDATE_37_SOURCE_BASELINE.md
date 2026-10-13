# Major Update 37 — Source baseline and preservation record

## Source inspection

The training authoring baseline was checked on 13 October 2026 against the publicly accessible `umicom-foundation/Bits2Banking` `main` tree, its existing `content/lessons/05-engineering`, `content/videos/scripts`, `labs/native`, `NATIVE_SOURCE_POLICY.md`, and prior update conventions. The last packaged update in the supplied conversation was Major Update 36, with Chapters 252–263 and Episodes 86–89. This new package starts at **Chapter 264 and Episode 90**.

Remote references observed during source review: `umicom-foundation/Bits2Banking` `main` at `2488e735b3c68ef236df3ef893710916e35b4168`, and canonical `umicom-foundation/umicom-framework` `main` at `0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796`. These are observation checkpoints, not instructions to reset a moving repository.

The authoring process also inspected the original uploaded Update 36 ZIP structure, including its additive navigation procedure and C23 teaching laboratory. The proposed new paths do not replace the historical chapters or the *Islam: Blueprint for Life* manuscript.

## Ownership and language policy

- Only educational source is included under the `Umicom-Bits2Banking/` ZIP root.
- Only C23 executable source and CMake build metadata are introduced. No `.py` or `.ps1` files are introduced.
- PowerShell commands appear in Markdown instructional code blocks only and are intended for **interactive command entry**.
- The Notes model is a small educational example. It does not attempt to replace Framework document storage, repository inspection, Git automation, compiler parsing or release planning.
- An optional C23 example calls existing `UmiBuildAutomation` through `Umicom::build` in an installed Framework SDK. No Framework source is duplicated and this optional target has not been executed in the standalone validation.
- No Framework, Applications, Kernel, or OS source is included or modified. No existing Bits2Banking file is replaced or deleted by the ZIP.
- Authorship, licensing, established naming conventions and historical learning material are retained. An unchanged screenshot provided by the user is included for the explicit teaching purpose of differentiating Windows PowerShell launchers.

## Publishing limitation

The provided `UPDATE_37_NAVIGATION_AND_REVIEW.md` contains an **additive MkDocs navigation fragment**. It is not a replacement `mkdocs.yml`. Because the user's local site configuration may include unmerged additions from earlier batches, manual review in Beyond Compare is required. Only after the additive navigation change has been reviewed can the strict website build be considered for acceptance.

## Reproducibility

A single top-level directory is used for review and merge. Each file has a SHA-256 entry in `UPDATE_37_FILE_MANIFEST_SHA256.txt`; the download-level checksum is supplied separately. The default C23 lab can be built without the large Umicom Framework dependency and without Python, PowerShell scripts, internet calls or source writes.
