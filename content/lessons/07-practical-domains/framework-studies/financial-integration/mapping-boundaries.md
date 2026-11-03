# Translate meaning, not just field names

Translate data without losing meaning and trace one controlled lifecycle across services.

Lesson 1 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

An **adapter** translates between systems with different interfaces. A **canonical model** is the shared representation used inside an application family. Translation is successful only if the business meaning survives, not merely if two fields share a similar name.

Suppose one message stores an amount as the decimal text “12.50” with currency GBP, while an internal example uses integer pence. The correct conversion is 1,250 minor units. Parsing “12.50” as the integer 12 loses information. Assuming every currency uses two decimal places also creates errors.

```text
external data → parse → validate meaning → canonical value
canonical value → explicit mapping → external format
           rejected fields → visible diagnostic
```

Dates need similar care. A calendar date is not a timestamp. A timestamp includes a position on a time scale, often with a timezone or UTC interpretation. Converting a timestamp into a business date requires a stated rule; the machine's current locale is not a safe substitute.

## Write a mapping table

1. Use columns for source field, target field, unit, required status and refusal rule.
2. Map amount and currency together.
3. Specify how absent values differ from zero.
4. Include an unsupported value and record a visible rejection.
5. Keep the source identifier so an operator can trace the transformation.

Across Java and C, memory and error conventions also differ. A boundary must define string encoding, ownership, size limits and error translation. Do not pass runtime-specific objects as raw portable records. A small versioned contract is easier to inspect and test.

Historical vendor training material can explain service boundaries and workflows. Exact vendor classes and deployment commands depend on a licensed release. These lessons use Umicom source and invented messages, not unverified vendor signatures.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\integration\fabric\message_contract.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiFabricMessageContract {
    char contract_id[UMI_FABRIC_ID_CAPACITY];
    char schema_id[UMI_FABRIC_ID_CAPACITY];
    UmiFabricVersion version;
    uint64_t max_payload_bytes;
    UmiFabricDeliveryMode delivery_mode;
} UmiFabricMessageContract;

/**
 * Initialise fabric message contract from caller-provided values so later operations
 * receive a known state.
 */
UmiStatus umi_fabric_message_contract_init(UmiFabricMessageContract *item, const char *contract_id, const char *schema_id, UmiFabricVersion version, uint64_t max_payload_bytes, UmiFabricDeliveryMode delivery_mode);
/**
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Read message_contract.h and message_header.h. Identify validation metadata and separate it from business-specific conversion rules that an adapter must supply.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Should an unknown currency code silently become the system's default currency?

### Worked answer

No. That changes the meaning of the amount. Refuse or route the item for explicit repair while preserving the original input.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/financial-integration/lessons/mapping-boundaries.html) · [Learning sequence](../../../../start/learning-sequence.md)
