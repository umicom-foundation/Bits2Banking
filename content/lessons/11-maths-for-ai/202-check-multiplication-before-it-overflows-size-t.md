# Mathematics for AI — Unit 202: Check multiplication before it overflows size_t

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Basic arithmetic and the preceding mathematics units.

## Learning objective

Establish a safe arithmetic procedure for shape and budget products.

## Step-by-step derivation

Unsigned multiplication may wrap without undefined behaviour, but a wrapped allocation size is unsafe. Before computing `a × b`, check `a == 0 || b <= SIZE_MAX/a`. If the condition is false, return a capacity error without writing the output report. Repeat at every stage: `2 × layers × tokens × heads × headChannels × scalarBytes`. Checking only the final result is too late, because intermediate products may already have wrapped.

## Check your understanding

**Exercise:** Why is a post-multiplication comparison not sufficient?

<details><summary>Show the worked solution</summary>

The multiplication may have overflowed before the comparison, giving a misleading small result.

</details>

## Native C23 connection

Use the Framework's existing checked `InferenceMemoryPlan`, `StackedKvStore` and `StackedKvPool` contracts. Arithmetic estimates do not themselves prove safe allocation, neural accuracy or measured latency.

## Continue learning

[Previous unit](201-prove-reservation-accounting-across-a-release.md) · [Next unit](203-index-layer-major-stored-projections.md) · [Browser unit](../../courses/maths-for-ai/lessons/202-check-multiplication-before-it-overflows-size-t.html)

*Service to Many Leads to Greatness.*
