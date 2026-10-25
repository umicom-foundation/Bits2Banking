# Mathematics for AI — Unit 1: Numbers, Fractions and Percentages

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## What you will learn

By the end of this lesson, you should be able to identify the *part* and the *whole*, convert fractions into decimals and percentages, simplify a ratio, and describe a measured change without confusing a work count with elapsed time. Only division and multiplication are required.

## 1. Start with a count

Suppose a fictional Umicom Desk has **five** support requests and **two** are awaiting an answer. The fraction of requests awaiting an answer is

**Calculation:** `2 ÷ 5 = 0.4`

Here **2** is the *numerator*: the number selected. **5** is the *denominator*: the total number in the group. A fraction describes a relationship; it need not mean that an object was physically cut into pieces.

A percentage expresses the same relationship *per hundred*:

**Calculation:** `percentage = (part ÷ whole) × 100%`

For the support requests, `(2/5)×100%=40%`. In a group with the same proportions but 100 requests, 40 would be awaiting an answer.

**Important:** identify the denominator *before* calculating. Dividing by the wrong group can produce an arithmetically correct but misleading result.

## 2. A native-AI workload example

A teaching experiment processes **96 token rows** without an incremental technique. The revised calculation avoids **40 rows**, leaving **56 rows** of work.

The fraction of the original rows avoided is:

**Calculation:** `40 ÷ 96 = 5 ÷ 12 ≈ 0.41666…`

Multiplying by 100 gives approximately **41.7% fewer computed rows**. The whole is the *original 96 rows*, not the remaining 56. This example measures arithmetic work; it does **not** demonstrate 41.7% lower wall-clock latency. A real performance experiment must also measure execution time, memory traffic, compiler settings, data sizes and repeatability.

The notation `≈` means **approximately equal**. The exact fraction is `5/12`; 41.7% is rounded to one decimal place.

## 3. Ratios and units

The ratio **2:3** compares two parts—for example, two teaching items to three validation items. If those groups are disjoint and make up the whole, the fraction of teaching items is `2/(2+3)=2/5`. A ratio is not automatically a percentage until a suitable whole is identified.

Always attach the unit: **token rows**, **requests**, **seconds**, **bytes**, or **£**. Adding unlike units or treating an operation count as a duration destroys the meaning of a result. Numbers in AI are useful only when their definitions are understood.

## 4. Another common trap: percentage points

If a proportion increases from **20% to 25%**, that is an increase of **5 percentage points**. Relative to the original 20%, the percentage increase is `(25-20)/20×100%=25%`. These are different statements. When reporting model accuracy or a benchmark, name which one you mean.

## 5. Practice

1. A synthetic banking dataset contains 60 transactions; nine are flagged for review. What percentage is flagged?
2. A learner completes 18 of 24 exercises. Express the result as a simplified fraction and a percentage.
3. An experiment falls from 120 calculated rows to 90 rows. What percentage of the original work was avoided?
4. Why is “25% faster” not a valid conclusion solely from a 25% reduction in calculated token rows?

<details>
<summary>Show worked answers</summary>

1. Part 9; whole 60. `9/60=0.15`, therefore **15%**. This is a fictional classroom example.
2. `18/24=3/4=0.75=75%`.
3. Avoided work is `120-90=30` rows. `30/120×100%=25%`.
4. Row counts do not measure elapsed time. The execution path can have different memory, allocation, dispatch, caching and synchronisation costs.

</details>

## 6. Check your understanding

Explain in your own words why the denominator is the *baseline*, and give one example of a statement with the correct number but the wrong unit. This skill will become essential when interpreting decoder statistics and model evaluations.

**Companion reading:** [Illustrated Unit 1](../../courses/maths-for-ai/lessons/01-counting-ratios-and-percentages.html) · [Next: Variables and Functions](02-variables-and-functions.md) · [Mathematics course index](index.md).
