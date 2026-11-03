# A quantity needs a unit and a delivery context

Learn why units, delivery evidence and finality matter across different asset types.

Lesson 1 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **commodity** is a traded material or resource. A quantity must name its unit: 12 kilograms is different from 12 tonnes. Physical delivery also needs quality, location and timing. A price without those terms may describe a different product from the one expected.

For a metric mass example, 2 tonnes equals 2,000 kilograms. Converting 2,501 kilograms to whole tonnes does not give an exact integer. Silently truncating to 2 would lose 501 kilograms. Either retain a finer scale or apply an explicit, agreed rounding rule.

```text
2 tonnes × 1,000 kilograms per tonne = 2,000 kilograms
2,501 kilograms ÷ 1,000 = 2.501 tonnes
whole-tonne-only output cannot represent the second result exactly
```

Framework's quantity conversion uses a rational factor: a numerator divided by a denominator. That is a ratio of integers. Its checked application can refuse a conversion that loses precision. Refusal is useful information; it tells the caller to choose a representation that can express the result.

## Describe one delivery

1. Choose a fictional material and a unit.
2. Write quantity, grade, delivery location and due date.
3. Convert the quantity to a smaller unit and check the arithmetic.
4. Convert a non-divisible quantity back and explain the refusal.
5. Record delivery evidence separately from a warehouse receipt or a promised shipment.

Do not use a simple mass conversion to convert tonnes to litres. That conversion depends on density and possibly temperature and product conditions. A mathematically valid ratio can still be the wrong business rule.

An inventory lot records a particular holding. A delivery obligation records what is owed. A movement record describes what actually changed location. Keeping these distinct prevents a promised delivery from appearing as already available stock.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\finance\commodity\quantity_conversion.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiCommodityQuantityConversion {
    char from_code[UMI_COMMODITY_CODE_CAPACITY];
    char to_code[UMI_COMMODITY_CODE_CAPACITY];
    int64_t numerator;
    int64_t denominator;
} UmiCommodityQuantityConversion;

/* Build a direct rational conversion between compatible units. */
UmiStatus umi_commodity_quantity_conversion_init(UmiCommodityQuantityConversion *value, const char *from_code, const char *to_code, int64_t numerator, int64_t denominator);

/* Convert integer minor units and reject results that would lose precision. */
UmiStatus umi_commodity_quantity_conversion_apply(const UmiCommodityQuantityConversion *value, int64_t input_units, int64_t *out_units);

#ifdef __cplusplus
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Read the numerator and denominator fields and the apply contract. Find its precision and overflow handling in src/finance/commodity/quantity_conversion.c.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Why should a conversion function reject 2,501 kilograms to whole tonnes instead of returning 2?

### Worked answer

Returning 2 silently loses quantity. A checked function exposes the precision problem so the caller can use a suitable scale or a reviewed rounding policy.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/commodities-and-digital-assets/lessons/quantity-and-delivery.html) · [Learning sequence](../../../../start/learning-sequence.md)
