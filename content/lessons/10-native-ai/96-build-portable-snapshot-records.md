# Lesson 96 — Build Portable and Verifiable Snapshot Records

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Learning objectives

Read an explicit binary format, explain fixed-width integers and checksums, and distinguish accidental corruption detection from publisher authentication. We use a portable native C23 snapshot, not direct memory dumping or an executable script.

## 1. Why writing a C structure to disk can fail

A compiler may insert padding between members of a C `struct`. An integer can occupy different byte orders on different processor families. A pointer refers to a location in the current process and has no meaning after restart. Consequently, taking `sizeof(struct)` bytes from memory and treating them as a permanent model file is not an interoperable storage contract.

The Framework's adapter snapshot writes a header with explicit offsets, version, projection-selection mask, rank, completed steps and the exact frozen-decoder SHA-256. Its payload contains separate per-projection checkpoints encoded through the **existing** Framework adapter checkpoint service. A final SHA-256 covers the full preceding record.

## 2. Read a little-endian integer

Suppose a four-byte unsigned integer contains the decimal value 258. Its hexadecimal value is `0x00000102`. In little-endian order the bytes are `02 01 00 00`. To decode it, multiply the four byte values by powers of 256 and add: `2 + 1×256 + 0 + 0 = 258`.

A reader should not cast a raw byte pointer to `uint32_t *` and assume alignment or machine endianness. It must validate the length **before** accessing the bytes and assemble the value using bounded unsigned arithmetic.

## 3. A layered integrity check

A restored projection passes three distinct questions. First, is the **outer** record structurally valid with the declared length and digest? Second, does each **inner adapter checkpoint** have a valid format, finite FP32 weights and matching frozen projection? Third, does the **live decoder** match the exact checkpoint SHA-256 declared by the snapshot? Only then may a fully constructed adapter become visible to the caller.

The whole-record SHA-256 can detect corrupted bytes, but an attacker who can replace both record and digest can calculate a new digest. The Framework must independently authenticate and approve an external file; no unsigned hash can prove who authorised it.

## 4. Failure atomicity

Imagine a valid destination buffer containing the previous snapshot. The new encoded result requires 900 bytes, but its capacity is 850. The service must return `UMI_STATUS_CAPACITY_EXCEEDED` while leaving **all 850 existing bytes** and the caller's written-count variable unchanged. A failed restore likewise leaves its output adapter pointer untouched.

The implementation stages all bytes privately before the final copy. Partial records must not be presented as successful new snapshots.

## Practice

**Question:** Why is a SHA-256 value insufficient to trust an arbitrary downloaded model? **Answer:** It proves only a relationship between the bytes and the digest supplied. It does not establish that a trusted publisher signed or approved those bytes.

**Question:** What should a parser do with an unknown binary-format revision? **Answer:** Reject it. Guessing a layout could misinterpret roles, step counts or weights.

Continue to [the deterministic training cursor](97-resume-deterministic-sgd-mid-epoch.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
