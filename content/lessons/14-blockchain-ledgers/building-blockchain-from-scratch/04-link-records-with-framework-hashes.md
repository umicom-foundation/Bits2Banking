# Link records with Framework hashes

A digest chain records each entry together with a digest of the preceding history. This makes a changed history disagree with a previously retained head digest. This practical lesson builds on the course's exact eight-byte teaching record and uses Framework's existing SHA-256 service. It does not create a currency or connect to a financial network.

## Setup recap

Use C23, CMake, Ninja and an installed Framework SDK with `base`. Follow [the SDK hashing lab](../../umicom-development/37-use-a-framework-function-in-a-lab.md) for complete PowerShell and Bash setup, copying, configuration and troubleshooting. Read [the exact record format](01-an-exact-record-format.md) if you are starting here: each record has a four-byte sequence number followed by a four-byte amount, both unsigned and little-endian. These are learning values, not real transactions.

## 1. Define the bytes being hashed

Open `Chain` and `HashLink` in `labs/native/framework-hash/main.c`. The first record is:

```text
01 00 00 00 | 19 00 00 00
sequence 1 | amount 25 (hexadecimal 19)
```

`HashLink` hashes three fields in order: the fixed ASCII format tag `UMICOM-LEARNING-LINK` without its zero terminator, the previous 32 digest bytes, and the eight record bytes. The fixed lengths remove ambiguity about field boundaries. The format tag separates this teaching construction from unrelated uses of the hash.

```text
zero starting digest + record 1 → first digest
first digest + record 2 → head digest retained for comparison
```

The actual implementation also prefixes the format tag on each link. Do not hash a C structure's raw memory: padding and byte order can vary. This example declares the exact bytes explicitly.

## 2. Run the chain scenario

From the configured practice folder, PowerShell:

```powershell
cmake --build build --parallel 2
& '.\build\btb-framework-hash.exe' chain
ctest --test-dir build -R '^bits2banking\.framework_hash\.(known|chain)$' --output-on-failure --no-tests=error
```

Bash uses `./build/btb-framework-hash chain`; the build and CTest commands are otherwise identical. The expected result says replay matches the retained head and changed history does not. The selected test run contains two cases, including an independent known digest check.

## 3. Follow the altered history

The program changes the first amount from 25 to 26, calculates a new first digest and then a new head. That head differs from the retained original. Finally it replays the unmodified records and confirms equality with the original head.

This is a small controlled demonstration. It does not prove that every possible pair of inputs has different digests. Nor does it establish who wrote a record. A person able to replace both the records and your reference head could recompute a consistent alternative history. A useful system needs a trusted way to retain or authenticate its reference, plus validation and storage rules.

## 4. Plan the next implementation carefully

A signature can bind data to a signing key; authorisation determines what that key may do. Consensus defines how participants agree on history. Durable storage defines what survives a crash. These are separate problems, none supplied automatically by hashing two records.

Exercise: keep the original records and trustedHead unchanged. In a practice copy, make an alteredSecond array from second, then change only its amount byte from 30 to 31. Hash firstHash followed by alteredSecond into a separate output and require that it differs from trustedHead. The first digest stays the same; the recomputed head changes. If you edit second before both calculations, you change the reference as well and no longer check tampering against the original history. Explain why record validation must precede accepting a new head: a cryptographically valid hash can describe an invalid business operation.

If `known` fails, investigate the hash input or SDK before studying chains. If `chain` fails, inspect field order and exact lengths. Continue with [history and recovery](03-history-replay-and-recovery.md) to relate this memory-only exercise to persistence, or return to [Building Blockchain from Scratch](index.md).

[Next: Define the bytes before hashing a record](05-define-the-bytes-before-hashing.md)
