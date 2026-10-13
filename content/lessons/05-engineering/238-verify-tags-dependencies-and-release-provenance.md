# Chapter 238 — Verify tags, dependencies and release provenance

**Bits to Banking · Release engineering · Umicom Foundation**  
**Prerequisites:** Chapters 228–237 · **Duration:** 60 minutes.

## A tag is a pointer, not a test report

Once a Framework revision and Umicom OS integration have been reviewed, a release may need a stable name. Git supports lightweight and **annotated** tags. An annotated tag has its own object containing a target, tag name, tagger and message. Signed tags can provide an additional cryptographic identity check when the organisation has configured an approved signing key, but signature validity is still not a substitute for build, tests and dependency evidence.

## Read-only release examination

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git tag --list
git describe --tags --always
git show-ref --tags
git rev-parse HEAD
git rev-parse --show-object-format
```

A tag does not necessarily reference the current HEAD. Inspect a specific known tag with:

```powershell
git show --no-patch <EXISTING_TAG>
git rev-parse <EXISTING_TAG>^{}
```

`^{}` peels annotated tags to the referenced object. Use an existing real tag; do not type the placeholder literally. If no tags exist, that is not a build failure. Your release process may be using commit SHAs and manifests instead.

## Controlled tag creation after acceptance

Only after tests and a release decision has been approved, the authorised maintainer could create an annotated tag on the **intended** commit:

```powershell
git tag -a "learning-demo-2026-10" -m "Review-qualified teaching release"
git show --no-patch "learning-demo-2026-10"
```

**Do not execute this example in a real shared Framework repository merely for practice.** Use a disposable learning repository for the exercise. Tag names are deliberately separate from C ABI names, which should not carry artificial version suffixes. Publishing a tag is a separate authorised step (`git push origin <tag>`) and does not happen implicitly with `git push origin main`.

## Record reproducible evidence, not claims

A useful release record identifies the root project SHA, Framework child SHA, toolchain profile, configured build target, test scope, evidence time and distribution artifact hash. Test evidence from Framework `F1` must not be reused to approve OS integration on `F2` without retesting.

| Gate | Concrete evidence | Failure state |
|---|---|---|
| Source | Exact parent/child SHAs and staged diff | Unknown pin, unreviewed source |
| Compiler | Compiler version, flags, target triple | Environment mismatch |
| Unit/integration | CTest output tied to source | Not run / failed |
| GUI/startup | Icon/double-click startup and runtime dependencies | Not run / missing resources |
| OS boot | Real QEMU boot transcript when boot layer changed | Not run / boot failure |
| Publication | Git refs and artifact digest | Unpublished / wrong ref |

A successful C23 lab in Bits2Banking does not certify the full Framework or Umicom OS. Keep those acceptance domains distinct.

## Native Framework services to reuse

Umicom Framework already provides repository verification/locking commands and release/build facilities. Before proposing a new packaging or evidence utility, inspect its source, public headers and tests. Reuse the Framework's SHA-256 and process abstractions where applicable. Bits2Banking's `git-three-way` lab neither hashes a package nor touches a Git repository.

## Exercise

Draft a release manifest for a fictional Umicom Bank training build. Leave actual SHA and test fields marked **NOT RUN** until verified. Explain why knowing a tag name is insufficient to reproduce an application when it depends on a gitlinked Framework revision and specific GTK4 runtime resources.

**Next:** complete the protected, main-only contribution and publish sequence.
