# Mathematics for AI — Unit 127: Derive stable online softmax

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab · **Prerequisite:** Basic arithmetic and an interest in neural networks.

## What will you learn?

Calculate a running softmax numerator without materialising every normalised score.

## Step-by-step calculation

For scores `s_i`, maintain running maximum `m`, sum of shifted exponentials `l`, and weighted value numerator vector `o`. When the next valid score `s` and value vector `v` arrive, set `mNew=max(m,s)`, `a=exp(m-mNew)`, `b=exp(s-mNew)`, then `lNew=a×l+b` and `oNew=a×o+b×v`. Final output is `o/l`. Initialise `m=-∞`, `l=0`, `o=zero vector`; the first **valid, finite** score needs special handling to avoid evaluating `-∞ - (-∞)`. Masked rows are skipped.

For scores `[1,2]` and scalar values `[2,4]`, after the first score `m=1,l=1,o=2`. The second gives `mNew=2,a=exp(-1)≈0.367879,b=1`, so `l≈1.367879`, `o≈0.735758+4=4.735758`. Thus `o/l≈3.462117`, matching direct stable-softmax weighting. Floating-point reduction order can cause small numerical differences.

**Notation guide:** `H` = number of attention heads; `T` = valid causal token count; `D` = channels per head; `L` = Transformer layers. The symbols describe *example data*, not the size or performance of an actual deployed model.

## Work it out yourself

**Question:** What happens if every score is masked?

<details>
<summary>Show the worked answer</summary>

There is no valid first score, so `l` stays zero. Reject the row explicitly instead of dividing by zero.

</details>

## Connect the numbers with native C23

[LLM Lesson 237](../10-native-ai/237-budget-single-query-scratch-memory.md) explains where this calculation belongs in the planned single-query kernel. The numerical implementation remains Framework-owned; these educational numbers are for checking reasoning, not a substitute for integrated decoder tests.

## Continue learning

[Previous unit](126-calculate-scaled-dot-products-and-temperature.md) · [Browser mathematics path](../../courses/maths-for-ai/single-query-attention-mathematics.html) · [Next unit](128-accumulate-weighted-values.md)

*Service to Many Leads to Greatness.*
