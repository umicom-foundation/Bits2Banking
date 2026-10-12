# Chapter 199 — Release tags, immutable evidence and reproducible Umicom builds

**Bits to Banking · Release engineering · Umicom Foundation**
**Prerequisites:** [CMake, Ninja and tests](18-build-and-tests.md), [publishable Git commits](196-audit-git-add-a-and-commit.md).

## A version label is not a tested release

Git branches are movable references, while a tag identifies a chosen point in history. An **annotated tag** carries metadata and a message in a separate Git object. It can be useful for marking a reviewed Bits2Banking publication or a verified Framework dependency. A tag alone does not prove that the source built, that tests ran or that the expected artifacts were produced. Those claims need recorded evidence: source commit IDs, toolchain, build settings, test results and package checksums.

For a combined Umicom release, the Framework child commit and the application or OS parent commit must be distinguished. The parent gitlink proves which Framework revision was recorded. A separate Framework tag may be useful, but users should not assume the same tag name in two repositories identifies equivalent source trees.

## Read and inspect tags

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git tag --list
git show --no-patch --decorate HEAD
git log -1 --format=fuller
```

In a reviewed practice repository, after tests pass and the intended `main` commit has been pushed, create an annotated tag with an appropriate unique release name:

```powershell
git tag -a learning-update-31 -m "Validated Git engineering learning batch"
git show --no-patch learning-update-31
```

If authorised, publish that tag explicitly:

```powershell
git push origin learning-update-31
```

Do **not** run these creation commands in the real Bits2Banking repository merely because a chapter contains them. They are a teaching illustration; tag names and release timing are a maintainer decision. Check that the tag does not exist before attempting creation, and never silently move a published release tag.

## A release manifest should answer concrete questions

| Question | Evidence |
|---|---|
| Which source? | Full Git commit SHA and repository URL. |
| Which dependencies? | Framework gitlink SHA, package versions and toolchain configuration. |
| Which checks ran? | CMake generator, compiler, CTest summary and platform. |
| What was published? | Manifest of files, sizes and SHA-256 checksums. |
| What did not run? | Explicit platform or integration gaps (for example Windows UCRT64). |

For a Bits2Banking learning ZIP, a SHA-256 file is a corruption-detection aid. It does not by itself authenticate the author's identity or guarantee the package is safe. A signed release needs a separate trust chain and key policy.

## Practical release gate

Review the proposed package in Beyond Compare, verify its manifest and its direct-to-main Git commit, run the native C23 tests, and run MkDocs strict publication checks where the existing Python-based publisher is available. No new Python code is required to use an already installed publisher. Do not report a Windows pass based only on a Linux build, or a full repository pass based only on one focused CTest project.

**Next:** [Integrate Framework and OS without duplicate commits](200-coordinate-umicom-repositories.md).
