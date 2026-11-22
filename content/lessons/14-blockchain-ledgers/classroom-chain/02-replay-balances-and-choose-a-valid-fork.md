![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Replay balances and choose a valid fork

[Previous: Run a native classroom chain](01-run-a-native-classroom-chain.md) · [Course contents](index.md) · [Next: Connect Assembly, D and GTK4](03-connect-assembly-d-and-gtk4.md)

## Validate from the opening balance

An independent reader starts with A = 12, B = 0, C = 0. For each proposed block, it checks the height, previous digest, proof target, full recomputed digest and allowed transfer. The sender must have enough units before the current block’s reward. The proof and money rules both have to pass. Only after a whole branch passes does the code publish a balance result. Find `classroom_replay` in `labs/native/classroom-chain/chain.c` and follow its checks in order.

The following trace uses the example from the executable. Both branches share block 1. Each later row uses the preceding balance on **its own** branch.

| Record | Transfer | Reward | Result A, B, C |
| --- | --- | --- | --- |
| Shared block 1 | A pays B 5 | C receives 2 | 7, 5, 2 |
| Current block 2 | B pays C 2 | A receives 2 | 9, 3, 4 |
| Candidate block 2 | B pays A 3 | C receives 2 | 10, 2, 4 |
| Candidate block 3 | A pays B 1 | B receives 2 | 9, 5, 4 |

Each valid block has the same proof target in this lab, so three valid blocks carry more work than two. Equally scored histories keep the one the local reader already has. Bitcoin chooses a chain by total accumulated work under its consensus rules. Different valid targets on real histories mean that a raw block count is insufficient. [Bitcoin Developer Guide on proof of work and forks](https://developer.bitcoin.org/devguide/block_chain.html)

### Why a majority matters

If proof production is concentrated, one participant may be able to influence transaction ordering, exclude transactions or replace a recent valid history. A majority of work still has to produce blocks that full nodes accept under the rules they enforce. It gives no ability to sign with someone else’s key or change which issuance a verifying node accepts. Bitcoin confirmations give evidence that more work has accumulated after a transaction. Confirmation depth is a risk measure and a later reorganisation remains possible. [Bitcoin whitepaper](https://bitcoin.org/en/bitcoin-paper)

Proof of stake uses different rules. For example, Ethereum uses stake-weighted validator votes and checkpoints. The relevant thresholds depend on the property being examined, such as choosing the current chain head versus finalizing a checkpoint. See the [proof-of-stake lesson](../032-study-proof-of-stake-validation-and-finality.md). [Ethereum protocol explanation](https://ethereum.org/developers/docs/consensus-mechanisms/pos/)

## Verify the refusal cases

1. Predict what happens if you copy the three-block candidate and increase its first transfer by one while leaving its stored proof unchanged.
2. Run `ctest --test-dir build/classroom-chain -R 'classroom_chain\.(tamper|forks|refusal)$' --output-on-failure --no-tests=error` from the Bits2Banking root.
3. Read the test checks. Identify which check prevents publication of the balances after a changed block. Then find the case in which a real, valid block from a different branch breaks the next block’s link.
4. Trace A attempting to pay 13 from the opening balance, even if A is due the two-unit reward. Explain the rejection in your own words.

**Worked answers.** The modified transfer changes the bytes, so the verifier refuses the copied branch before its length can influence fork choice. A block from a different branch carries its own digest, so the next block’s previous-digest field no longer matches. A has only 12 before reward and cannot fund a 13-unit transfer. In each case the earlier accepted state remains available.

The lab models deterministic verification for already supplied histories. Its account IDs carry no real ownership, and its one-process experiment does not measure peer delay, mining concentration or the probability of a real reorganisation.

[Previous: Run a native classroom chain](01-run-a-native-classroom-chain.md) · [Course contents](index.md) · [Next: Connect Assembly, D and GTK4](03-connect-assembly-d-and-gtk4.md)
