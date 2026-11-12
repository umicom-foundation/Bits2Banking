<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/weight-management-framework/01-define-the-observation-contract.md

PURPOSE:
Define the observation before the screen

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Define the observation before the screen

## Before you begin
Know basic C structures, functions and return values. Keep a current Framework source checkout available for reading. This course starts with a small observation log that can support a weight-management application. It does not calculate an ideal weight or give medical advice.

## Follow one piece of data
A complete observation contains a chosen calendar date, a mass in integer grams and an optional note. The first version deliberately excludes an account system, cloud synchronization, medical classification and automatic target setting.

~~~c
typedef struct UmiWeightLogEntry {
    char observed_on[11];
    uint32_t mass_grams;
    char note[256];
} UmiWeightLogEntry;
~~~

Read the real declaration in include/umicom/healthcare/weight_log.h. The date occupies ten characters plus a terminator. The mass unit is part of the contract. A value of 80250 means 80.250 kg, not 80250 kg.

1. List which values a user supplies.
2. Identify the values the host supplies: record identity, access authority and the acknowledged storage revision.
3. Draw the boundary between a mutable draft and a copied validated observation.
4. Write down which parts remain outside this first client.

## Reuse the shared engine
umi_weight_log_schema returns a borrowed immutable schema. Existing structured-form services own date admission, typed answers, editing revisions and snapshots. The weight module adds a domain schema and an exact input conversion; desktop and browser code must not maintain independent validation rules.

The broad numeric capacity is an encoding bound. It is intentionally not a claim about a healthy human range. A future clinical feature would need separate requirements and qualified expertise.

## Exercise and expected result
Create three fictional examples on paper: a complete record, a missing mass, and an impossible date. Classify each as a complete observation or a refused/incomplete draft. The missing mass must not silently become zero. The impossible date must not be repaired by changing the user's meaning.

## Recovery
If two clients disagree about units or required fields, inspect the schema version and SDK identity before patching either screen. Keep older saved schema versions readable through an explicit migration plan. Changing a unit label without converting and versioning stored values corrupts meaning.

The course proceeds from this contract to an executable C example, then to existing desktop/web service boundaries and a mobile port plan. It does not present those later platform clients as already shipped.


[Course contents](index.md) · [Next lesson](02-convert-kilograms-without-rounding.md)
