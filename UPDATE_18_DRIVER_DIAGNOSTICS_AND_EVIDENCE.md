# Update 18 — Driver diagnostics and reviewable evidence

This update connects the preceding lessons on interrupt ownership, timers,
blocked IPC and reviewed recovery to bounded evidence collection. It remains
an educational update: there is no claim of a production driver, kernel trace
service, signed audit trail or durable recovery mechanism.

## New native Framework command

`umicom-education evidence-trace --file PATH` checks `UMIEVD1`, a fictional,
versioned teaching format. It validates a 24-byte header, at most 4,096
80-byte records, increasing record ordinals, source slot/owner/generation
identity, nondecreasing logical time, permissible state transitions and a
SHA-256 digest chain over 48 bytes of metadata per record. The first digest
is computed from 32 zero bytes plus the first record's metadata; successive
digests use the previous digest plus new metadata. The inspector reuses the
existing canonical Framework implementation in `src/base/sha256.c`.

The command refuses partial or invalid traces without publishing incomplete
reports. Checkpoints reference a previously observed diagnostic. They are
**not** persisted service snapshots. Recovery markers state that the fictional
model accepted an explicit review; they do not demonstrate device restoration.
Unkeyed SHA-256 does not authenticate an author's identity or protect against
an attacker who replaces and rehashes the entire file.

## New C23 laboratories

- `labs/native/driver-lifecycle` composes the already delivered
  `service-recovery` and `interrupt-ownership` C23 modules. A fictional Notes
  revision must commit before its accepted counter advances; a fault leaves
  uncommitted work for explicit review. The model refuses unsafe stop and
  stale reinitialisation.
- `labs/native/diagnostic-ring` is an eight-slot, in-memory diagnostic queue.
  Once full, it overwrites the oldest record, exposes the number of overwritten
  rows and returns copied snapshots. It refuses backward time and sequence
  exhaustion. It is not durable storage.

## Lessons and references

Chapters 117–121 cover interrupt timeline interpretation, composition of driver
lifecycles, bounded diagnostic records, chained-file integrity and actual
Umicom Kernel source ownership. Episodes 38–39 explain the same concepts
with a running demonstration. Three editable SVG diagrams accompany them.

Authoritative Kernel sources:

- `arch/riscv64/trap.S`
- `kernel/interrupts.c`
- `kernel/trap_guard.c`
- `kernel/virtio_block.c`
- `docs/INTERRUPT_OWNERSHIP.md`

These remain in `umicom-foundation/umicom-kernel`; the delivered ZIP does not
edit or copy them. Existing historical manuscripts, the *Islam: Blueprint for
Life* volume and the current book renderer are preserved.

## Engineering and qualification boundary

The update adds two standalone Framework CTests, five Markdown chapters, two
C23 laboratories with their own tests, two video scripts and three SVGs. The
Framework command and test use C23; other languages are not introduced for
executable implementation. CMake remains necessary for compilation, Markdown
and SVG for content, and YAML for existing MkDocs navigation.

Acceptance in the isolated Linux environment is not evidence of passing
Windows UCRT64, a full MkDocs publication on the user's historical checkout,
GitHub Actions or QEMU. The exact Windows commands appear in
`UPDATE_18_BUILD_TEST_AND_GIT.md`.
