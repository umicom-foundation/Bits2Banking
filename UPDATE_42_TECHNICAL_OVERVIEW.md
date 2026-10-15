# Bits2Banking Major Update 42 — Technical overview

## Objective and scope

Update 42 extends the established *System Administration From Zero* course from 60 to 72 chapters. It teaches VMs, host/guest boundaries, QEMU, RISC-V boot stages, disk images, account permissions, reproducible toolchains, private CMake staging, runtime dependencies, application readiness and honest release evidence. Engineering Chapters 300–303 connect these concepts to a new **ISO C23** laboratory.

This is strictly a Bits2Banking educational repository batch. It does not modify `umicom-framework`, `Umicom-Applications`, `umicom-kernel` or `umicomOS`.

## Native source structure

```text
labs/native/deployment-rehearsal/
├── CMakeLists.txt
├── README.md
├── deployment_review.h
├── deployment_review.c
├── test_deployment.c
└── main.c
```

The new CMake target **imports the existing** `maintenance-review` target from Update 41, which imports `service-readiness` (Update 40) and `sysadmin-evidence` (Update 39). No prior code is reimplemented or removed.

The new stage review stores a copied `BtbMaintenanceReview` and `BtbDeploymentPlan`, then validates fictional stage evidence supplied by the caller. It refuses mismatched source revisions or package digest strings, detects incomplete and stale captures, distinguishes pending from blocked and qualified, and reports rollback and independently restored outcomes separately. All invalid operations preserve caller-owned state.

## Explicit limits

The laboratory never reads a real repository, calculates a real SHA-256 digest, signs a package, opens a socket, launches a background service, changes a registry entry, modifies the OS, creates or mounts a virtual disk, or deploys a real Umicom application. Hash-like fields are **format-checked teaching inputs only**. The `practice-` staging label is a model attribute, not a validated operating-system pathname.

An optional CMake `install()` rule copies only the built example executable into a **user-selected private prefix**. This action is separate from the in-memory C23 review model. The learner must inspect the intended destination and avoid replacing important files.

## Reusing Umicom Framework in production

The production boundaries remain with Umicom Framework. Before promoting any of these teaching concepts to real software, inspect its native `UmiVcsWorkingTreeRead`, repository submodule-lock contract, `UmiBuildAutomation`, compiler diagnostic parser, approved installation/runtime staging, security permissions and service lifecycle APIs. User-space products remain thin consumers; Umicom Kernel and the minimal recovery environment have their own independent responsibilities.

The examples are designed to help learners understand these architectural boundaries, **not** to replace the Framework services with parallel implementations.

## Documentation and publishing

The update includes 12 new course Markdown chapters (61–72), four engineering chapters (300–303), five video scripts (116–120), seven source SVG diagrams, five Stage 5 reference and assessment documents, and a standalone offline HTML edition incorporating all 72 course chapters. Existing 60 prior chapters are preserved byte-for-byte in the offline book.

`UPDATE_42_MKDOCS_NAV_SNIPPET.yml` supplies additive navigation lines. The existing MkDocs configuration remains untouched so prior books and navigation are not overwritten. Windows UCRT64 and the complete MkDocs build still require host verification.
