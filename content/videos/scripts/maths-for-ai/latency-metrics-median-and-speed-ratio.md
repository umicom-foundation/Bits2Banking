# Mathematics Video — Latency, Median and Speed Ratios

**Bits to Banking · Umicom Foundation**  
**Author and narrator:** Sammy Hegab  
**Companion reading:** Mathematics Units 161–166 and 170.

## Narration

Timing a language model starts with units. A nanosecond is one billionth of a second; a millisecond is one thousandth. If an event begins at 2,000,000,000 nanoseconds and finishes at 2,012,000,000, the elapsed time is 12,000,000 nanoseconds, or 12 milliseconds. A monotonic timer keeps this subtraction meaningful even when the computer's wall clock is adjusted.

Next separate the first token from the whole response. Suppose queueing consumes 3 milliseconds, prefill consumes 9, and initial sampling consumes 2. Time to first token is 14 milliseconds. If the next four tokens each need 5 milliseconds, a five-token answer takes 34 milliseconds in total. Thirty-four divided by five gives the average entire-response time per token, but the decode-phase time per later token is still five milliseconds.

Suppose our reference measurements are 7, 8, 8, 10 and 18 milliseconds. The median is the central value, 8. The range is 18 minus 7, or 11 milliseconds. The median is less sensitive to the slowest observation than the average, but neither statistic replaces the raw data or describes the tail of a production service.

A performance ratio has a direction. If the reference takes 18 milliseconds and the cached candidate takes 15, divide reference by candidate to get 1.2. The candidate is 1.2 times as fast for that particular pair. The reduction in runtime is three divided by eighteen, or 16.67 percent. These numbers are related but not interchangeable.

Finally compare all logits before celebrating a smaller time. A candidate that changes the model's prediction is not an accepted optimisation. Numerical tolerances must be declared before examining results.

## Visual storyboard

| Frame | Picture | Numerical point |
|---|---|---|
| 1 | Nanosecond ruler | 1 ms = 1,000,000 ns |
| 2 | Prompt plus five-output timeline | TTFT = 3 + 9 + 2 = 14 ms |
| 3 | Sorted five-bar latency chart | Median = 8 ms |
| 4 | Two paired timer bars | 18 ÷ 15 = 1.2× |
| 5 | Two close-but-not-identical logit vectors | Error ≤ absolute + relative threshold |

## Exercise

With reference median 12 ms and candidate median 15 ms, calculate the speed ratio. Answer: 12/15 = 0.8×, meaning the candidate is slower for this measured case.

*Service to Many Leads to Greatness.*
