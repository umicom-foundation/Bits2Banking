# Understand exposure and collateral

Distinguish market data, orders, executions, positions and collateral.

Lesson 2 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

**Exposure** is an amount at risk under stated assumptions. **Collateral** is an asset provided as security. **Margin** is a required amount of protection under an agreement or clearing arrangement. These terms are related but are not interchangeable with cash balance.

A **haircut** reduces the value credited to a collateral asset. If an eligible asset is valued at 1,000 and the teaching haircut is 10%, its adjusted value is 900. Against a requirement of 850, that gives 50 of excess coverage. If the asset is ineligible, arithmetic alone must not make it acceptable.

```text
observed value 1,000 → eligibility check → haircut 100 → credited 900
required protection 850 → compare → excess 50
```

The example omits currency conversion, concentration limits and contractual detail. Real collateral decisions depend on the agreement, valuation time, asset quality and settlement status. A promised delivery is not necessarily collateral already received.

## Apply the control gates

1. Write the agreement and eligible asset type.
2. Record the observed value and its timestamp.
3. Apply the stated haircut.
4. Compare adjusted value with the requirement.
5. Repeat with the asset marked ineligible. Stop before treating it as coverage.
6. Repeat with an older price and record why freshness matters.

**Clearing** organises obligations after execution. **Custody** concerns holding and administering assets. **Settlement** fulfils a delivery obligation. A trading screen should distinguish those states rather than label every accepted trade complete.

The Framework collateral contract provides a source-reading anchor. Inspect its actual fields and validation before assuming it implements the whole operational process.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\finance\treasury\collateral_valuation.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiTreasuryCollateralValuation {
    char id[UMI_TREASURY_ID_CAPACITY];
    int64_t gross_value_minor;
    uint32_t haircut_bps;
} UmiTreasuryCollateralValuation;
/**
 * Initialise treasury collateral valuation from caller-provided values so later operations
 * receive a known state.
 */
UmiStatus umi_treasury_collateral_valuation_init(UmiTreasuryCollateralValuation *value,
    const char *id,
    int64_t gross_value_minor,
    uint32_t haircut_bps);
/**
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Read collateral_valuation.h and eligibility_rule.h. Separate arithmetic inputs from eligibility and lifecycle policy.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Can an asset with sufficient market value always satisfy a margin call?

### Worked answer

No. Eligibility, haircut, currency, concentration, timing and delivery rules may prevent it from counting. Value is one input to the decision.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/margin-and-collateral.html) · [Learning sequence](../../../../start/learning-sequence.md)
