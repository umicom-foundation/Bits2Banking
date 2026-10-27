# Video script 21 — Online softmax by hand

**Series:** Mathematics for AI · **Course lead:** Sammy Hegab · Umicom Foundation  
**Companion:** Units 126–129, especially Unit 127.

## Scene 1 — Why subtract the maximum?

**Voiceover:** “Softmax turns scores into positive weights summing to one. Directly exponentiating a score such as one thousand can overflow a floating-point datatype. Subtracting the highest score preserves the ratios without constructing such a large exponential.”

**Board:** Write the two scores `1` and `2`. Shift by `2` to obtain `−1,0`; exponentiate to approximately `0.367879,1`. Sum them, then calculate probabilities `0.268941,0.731059`.

## Scene 2 — A running maximum and numerator

**Voiceover:** “Instead of storing every score, we can maintain the running maximum `m`, an unnormalised weight sum `l`, and a weighted-value sum `o`. For each next *valid* score `s`, compute `mNew=max(m,s)`. Rescale the old totals by `exp(m−mNew)` and add the new score’s contribution.”

**Board:** Begin with the first score `1`, value `2`: `m=1,l=1,o=2`. Introduce next score `2`, value `4`: `a=exp(-1)=0.367879`, `b=1`, then `l=1.367879`, `o=4.735758`. Final `o/l≈3.462117`.

## Scene 3 — Boundaries

**Voiceover:** “The first valid score requires an explicit initialisation step; do not compute `−∞−(−∞)`. Ignore masked slots. If every slot is masked, report an invalid attention row instead of dividing by zero. Nonfinite unmasked data must be rejected.”

**Board:** Cross out a masked slot and draw a clear `no valid score → error` gate.

## Scene 4 — The connection to C23

**Voiceover:** “This recurrence is one idea behind efficient attention implementations, but an accepted Umicom Framework kernel must first prove the same result as the existing decoder. Different floating-point accumulation orders can cause small differences.”

**Further reading:** [Mathematics Unit 127](../../../lessons/11-maths-for-ai/127-derive-stable-online-softmax.md), Milakov and Gimelshein (2018), *Online normalizer calculation for softmax*, https://arxiv.org/abs/1805.02867.

*Service to Many Leads to Greatness.*
