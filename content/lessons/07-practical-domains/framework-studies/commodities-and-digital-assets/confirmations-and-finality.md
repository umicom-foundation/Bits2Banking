# A ledger observation is not always final

Learn why units, delivery evidence and finality matter across different asset types.

Lesson 2 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **distributed ledger** is a record maintained across multiple participants. A transaction may be observed before it is considered final under the network's rules. **Confirmation** and **finality** describe evidence and policy about whether later history can change that observation.

A **reorganisation** replaces part of the history a node previously regarded as canonical. A deposit seen in an earlier block may need to be reconsidered. Crediting spendable funds immediately after the first observation can therefore create an obligation the application cannot safely support.

```text
transaction observed → check network and block → evaluate policy
                                             ↓
                               pending credit or accepted credit
                               reorganisation → review evidence
```

The appropriate policy depends on the network and risk model. This lesson uses no universal confirmation threshold. A percentage of agreeing computers alone does not establish security: independent identity, voting weight, adversary assumptions and the protocol all matter.

## Track a fictional deposit

1. Record network, asset, transaction identity and observed block.
2. Keep the deposit pending while evaluating the configured policy.
3. Record the evidence supporting any later acceptance.
4. Imagine the block leaves the canonical chain. Identify which balances and downstream actions need review.
5. Preserve the original observation and the later correction as separate events.

A wallet address is not a private key. A **private key** authorises cryptographic operations and must not be copied into a teaching dataset. A reference to a protected key lets a service request signing without distributing the key itself. A signing request also needs policy and approval; possession of an address is not authority to spend.

Framework has confirmation-policy and settlement-finality contracts. Their presence does not prove a complete network, custody system or secure consensus implementation. Read their limits before building a client around them.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\finance\digital_asset\confirmation_policy.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiDigitalConfirmationPolicy {
    UmiDigitalAssetId network_id;
    uint32_t required_confirmations;
    uint32_t final_confirmations;
    bool active;
} UmiDigitalConfirmationPolicy;

/* Initialise a bounded confirmation policy record for reusable Framework workflows. */
UmiStatus umi_digital_asset_confirmation_policy_init(UmiDigitalConfirmationPolicy *value, const char *network_id, uint32_t required_confirmations, uint32_t final_confirmations);

/* Validate the invariant fields required before this record enters a workflow. */
bool umi_digital_asset_confirmation_policy_valid(const UmiDigitalConfirmationPolicy *value);

/** Transfer this value using the portable format described in value_archive.h.
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Compare confirmation_policy.h with settlement_finality.h and chain_observation.h. List the evidence each represents and which network behaviour must be supplied by an adapter.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Why keep the earlier block observation after a reorganisation?

### Worked answer

It explains why the application previously treated the deposit as pending or accepted. Replacing it silently would remove evidence needed to investigate and reconcile the correction.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/commodities-and-digital-assets/lessons/confirmations-and-finality.html) · [Learning sequence](../../../../start/learning-sequence.md)
