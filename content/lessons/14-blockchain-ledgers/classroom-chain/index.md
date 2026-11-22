![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Build a classroom proof-of-work chain

Three students track 12 imaginary units. Start with that paper ledger, then write and run a small program that validates an entire history of payments. The same experiment shows how a hash links blocks, why a proof must be verified, how new units enter under a shared rule and what happens when two valid histories disagree.

Start with [Introduction to Blockchain](../../../courses/introduction-to-blockchain/index.html) and [Introduction to Bitcoin](../../../courses/introduction-to-bitcoin/index.html). For the original wire format, take [Building Bitcoin from Scratch Using Assembly and C](../../../courses/building-bitcoin-in-c/index.html). The classroom construction uses its own record format so you can concentrate on one rule at a time.

1. [Run a native classroom chain](01-run-a-native-classroom-chain.md). Learn what the program commits to and check the first proof against a known result.
2. [Replay balances and choose a valid fork](02-replay-balances-and-choose-a-valid-fork.md). Trace the amounts and explain why an invalid longer history loses.
3. [Connect Assembly, D and GTK4](03-connect-assembly-d-and-gtk4.md). Keep the validated C rules separate from language adapters and presentation.

You can read all three lessons with a pencil and paper. Programming practice uses a C23 toolchain, CMake, Ninja and the reviewed Umicom Framework checkout. The optional x86-64 exercise additionally uses a compatible assembler. The source is in `labs/native/classroom-chain` in the Bits2Banking repository.

The exercise has three synthetic accounts and a fixed classroom issuance rule. Everything runs in memory, offline. Production Bitcoin validation, transferable currency, signing, networking, wallet management and persistence are separate subjects. [Bitcoin developer guide](https://developer.bitcoin.org/devguide/block_chain.html)
