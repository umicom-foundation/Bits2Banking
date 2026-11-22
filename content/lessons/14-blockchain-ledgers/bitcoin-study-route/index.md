![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Bitcoin, money and blockchain from first principles

Start with a familiar question. If two people have different copies of a payment record, who decides which copy counts? This course follows the question from a bank account to Bitcoin and finishes with a small native C ledger you can inspect offline. You can start with paper and a pencil. The final exercises introduce the tools one at a time.

## Study in order

| Step | Lesson | What you will be able to show |
| --- | --- | --- |
| 1 | [Where new money comes from](01-money-creation.md) | Explain what changes when a bank makes a loan, when a borrower repays it and when Bitcoin issues a block subsidy. |
| 2 | [Who decides which ledger to trust?](02-trust-consensus-and-majority.md) | Distinguish a central operator, a trusted hash and a network of validating participants. |
| 3 | [How a hash links records](../introduction-to-blockchain/index.md) | Sketch a block, its fingerprint and the pointer to earlier history. |
| 4 | [Why miners try many inputs](../008-derive-proof-of-work-difficulty-and-expected-attempts.md) | Explain a target, a nonce and why a rare hash takes work to find. |
| 5 | [Confirmation, reordering and proof of stake](03-work-stake-and-confirmations.md) | Compare two valid branches on paper and explain which claims consensus can support. |
| 6 | [Bitcoin payments and transaction checks](../introduction-to-bitcoin/index.md) | Explain how a payment spends earlier outputs and how a node checks spending rules. |
| 7 | [Read Bitcoin Core by responsibility](../introduction-to-bitcoin-source-code/index.md) | Locate the separate responsibilities for validation and desktop presentation. |
| 8 | [Build and verify a classroom chain](../classroom-chain/index.md) | Run a local C lab and check its rules, replay and error evidence. |

Bitcoin Core uses C++ for its node implementation and Qt for its optional desktop interface. Our classroom core uses C, with small Assembly and D exercises at language boundaries. GTK4 is the presentation layer for displaying validated results. Start by verifying the console result, then apply the [graphics course](../../03-native-code/graphics-from-scratch/index.md) to display it. [Bitcoin Core build documentation](https://github.com/bitcoin/bitcoin/blob/v28.0/doc/build-unix.md) · [Bitcoin Core interfaces](https://github.com/bitcoin/bitcoin/blob/master/src/interfaces/README.md)

## A capstone you can explain without reading code

Write a page showing how you would account for a newly issued amount, check a valid record and handle two competing valid histories. Give each rule a reason. Then mark separately which parts your classroom lab can demonstrate and which require an actual peer network. For an extra exercise, draw the final ledger status with the [native graphics library](../../03-native-code/graphics-from-scratch/index.md) or state one of its decision rules in [executable pseudocode](../../03-native-code/pseudocode-to-native/index.md).

[Start with money creation](01-money-creation.md) · [Finance and systems course list](../../../start/finance-and-systems.md) · [Umicom icon](../../../assets/branding/umicom-icon.svg)
