# Framework hashing lab

This C23 consumer calls the installed Umicom Framework `base` component. Framework owns SHA-256; this lab demonstrates input lengths, incremental calls, refusal contracts and a two-record digest chain. The chain is educational, with no money, signing, networking, mining or consensus.

Start with [the complete SDK lab](../../../content/lessons/umicom-development/37-use-a-framework-function-in-a-lab.md). It includes Windows PowerShell and Linux Bash commands, expected results, troubleshooting and source explanations.

`main.c` accepts one scenario: `known`, `chunks`, `changed`, `rejected` or `chain`. `CMakeLists.txt` registers each as a separate CTest case when `BUILD_TESTING` is enabled. An unknown or missing scenario returns exit status 2. A failed contract returns 1; a successful case returns 0.

The installed SDK must match the consumer's operating system, architecture and compiler runtime. Build into a separate `build` folder. The program uses memory only and writes no ledger or account state.

Continue with [digest-linked records](../../../content/lessons/14-blockchain-ledgers/building-blockchain-from-scratch/04-link-records-with-framework-hashes.md) after completing the SDK exercise.
