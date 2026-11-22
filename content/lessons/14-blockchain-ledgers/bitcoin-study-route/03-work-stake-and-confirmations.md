![Umicom](../../../assets/branding/umicom-wordmark.svg)

# 3. Compare work, stake and confirmations

Imagine several readers have accepted the same earlier ledger and now receive two different proposed histories. First each reader checks whether the new entries follow the rules. If both histories are valid, the protocol provides a fork choice. A **fork** is the point where candidate histories diverge.

## Try a paper fork

Give each block a toy amount of work. Count only the blocks after the divergence because the earlier work is the same on both branches.

| Branch | Work of each new block | Cumulative work after the fork |
| --- | --- | ---: |
| A | 3, 3, 3 | 9 |
| B | 5, 5 | 10 |

Under the classroom rule, a reader that has checked both branches selects B because it carries more work. The values in the exercise are fixed labels. In Bitcoin, each block's contribution comes from its target, and the node also checks the consensus rules that determine valid targets. Use [the proof-of-work difficulty lesson](../008-derive-proof-of-work-difficulty-and-expected-attempts.md) to see how a smaller target makes success less likely on each try. [Bitcoin white paper, sections 4–5](https://bitcoin.org/en/bitcoin-paper)

If a payment appears in a block on the chain a node accepts, that block gives it its first confirmation. Each later block on that chain adds a confirmation. A change in accepted history can remove the transaction from the node's accepted chain. Additional confirmations reduce some reorganisation risks under the network and hash-rate assumptions in the model. The number is a depth measurement, not a guarantee about future network behaviour. [Bitcoin white paper, section 11](https://bitcoin.org/en/bitcoin-paper)

## Compare proof of work and proof of stake

In proof of work, the cost is connected to repeating computations until a hash meets a target. In proof of stake, the protocol uses eligible staked capital in choosing participants or weighting their votes. Ethereum is one example. Its validators propose and attest to blocks, and its rules provide rewards, penalties and conditions for checkpoint finality. Different proof-of-stake protocols define those rules differently. A threshold from Bitcoin's hash-rate model cannot be transferred to a proof-of-stake protocol without reading its rules. [Ethereum proof-of-stake documentation](https://ethereum.org/developers/docs/consensus-mechanisms/pos/)

### Check your understanding

1. Suppose the last block in branch B makes an invalid spending claim. Is its larger score enough to select it?
2. Suppose you checked a payment in a block and two more blocks followed on the same accepted chain. How many confirmations does the payment have in that view?
3. Name one comparison you can test in an offline C lab and one you would need a separate network study to answer.

<details>
<summary>Worked answers</summary>

1. The invalid candidate is refused. The work comparison is applied to valid candidates.
2. Three. Include the block containing the transaction itself.
3. You can check that a changed record fails the lab's validation rules. You need separate network evidence for how two geographically distributed nodes receive and reconcile competing candidates.

</details>

[Previous lesson: Trust and control](02-trust-consensus-and-majority.md) · [Course outline](index.md) · [Next lesson: Run the offline classroom chain](../classroom-chain/index.md) · [Umicom icon](../../../assets/branding/umicom-icon.svg)
