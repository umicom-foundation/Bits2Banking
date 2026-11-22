![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Run a native classroom chain

[Course contents](index.md) · [Next: Replay balances and choose a valid fork](02-replay-balances-and-choose-a-valid-fork.md)

## Read the opening ledger

A ledger is a record of changes you can add up. In this exercise A starts with 12 practice units, while B and C start with zero. A sends 5 to B. If that transfer passes validation, the rule issues 2 new units to the account named by the block. When the reward goes to C, the result is A = 7, B = 5, C = 2 and the total is 14. The transfer has moved five existing units. Issuance explains the increase of two.

Each record groups one transfer and its reward. A cryptographic hash is a fixed-size fingerprint of bytes. The program writes its record into 60 exact bytes, hashes those bytes with the shared Framework SHA-256 implementation and records the 32-byte result. A link to the previous digest makes the ordering independently checkable. A digest establishes a match between bytes and a fingerprint. Real payments also require authorization, commonly through a digital signature and the spending conditions attached to an earlier output. [Bitcoin Developer Guide on transactions](https://developer.bitcoin.org/devguide/transactions.html)

| Byte offset | Length | Classroom field |
| --- | ---: | --- |
| 0 | 4 | `BTB1` classroom format marker |
| 4 | 32 | Previous digest, or the fixed opening digest in block 1 |
| 36 | 4 | Height, starting at 1 |
| 40–55 | 16 | Sender, receiver, units and reward account, four bytes each |
| 56 | 4 | Nonce, a counter changed during the search |

Each four-byte integer is written least significant byte first. The program supplies these bytes explicitly in `block_digest`. The raw in-memory C structure can contain padding and can differ across computers. Bitcoin has a separately specified 80-byte block header and uses SHA-256 twice for its work proof. This classroom format hashes a different record once. [Bitcoin Developer Reference on block headers](https://developer.bitcoin.org/reference/block_chain.html#block-headers)

## Build the lab

1. Open PowerShell in the Bits2Banking repository. The example assumes the Framework checkout is at `../Umicom-Applications/framework`. If your copy lives elsewhere, give its path to `UMICOM_FRAMEWORK_SOURCE`.
2. With your C23 compiler and Ninja on `PATH`, run the following commands. Stop at the first error.

   ```powershell
   $framework = (Resolve-Path '../Umicom-Applications/framework').Path
   cmake -S labs/native/classroom-chain -B build/classroom-chain -G Ninja "-DUMICOM_FRAMEWORK_SOURCE:PATH=$framework" -DBUILD_TESTING=ON
   cmake --build build/classroom-chain
   ctest --test-dir build/classroom-chain --output-on-failure --no-tests=error
   & ./build/classroom-chain/bits2banking-classroom-chain-demo.exe
   ```

3. Look for `Altered history rejected before comparing work.` and `accepted branch: 3 blocks, 18 classroom units`. Read [the replay lesson](02-replay-balances-and-choose-a-valid-fork.md) to account for those 18 units.
4. Open `labs/native/classroom-chain/test_chain.c` and find the first-block fingerprint comparison. The first valid nonce for A sending 5 to B with a reward to C is 82. The digest begins `00c69665`. Your proof should match the entire test string.

If CMake reports a missing Framework checkout, give `UMICOM_FRAMEWORK_SOURCE` the absolute path to the directory containing `include/umicom` and `src/base/sha256.c`. If the test finds different proof bytes, check field offsets and integer byte order before touching the target. On Linux use `./build/classroom-chain/bits2banking-classroom-chain-demo` to run the executable.

## Try it on paper

The rule accepts a digest whose first byte is zero. Which values pass, `00` or `01`? If the digest distributes leading bytes evenly, what fraction of attempts do you expect to pass?

**Worked answer.** Only `00` passes. One of the 256 byte values qualifies, so the chance per attempt in this model is 1/256. That gives an expected 256 attempts. A particular record might succeed sooner or later. The demonstration bounds the search to keep the exercise finite.

[Course contents](index.md) · [Next: Replay balances and choose a valid fork](02-replay-balances-and-choose-a-valid-fork.md)
