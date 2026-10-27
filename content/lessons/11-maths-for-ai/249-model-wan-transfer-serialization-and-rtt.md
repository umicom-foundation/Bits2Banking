# Mathematics for AI — Unit 249: Model WAN transmission lower bounds

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** arithmetic, fractions, basic vectors and Unit 248.

## Learning outcome

Calculate, check and interpret one quantity used in a native distributed-learning system. Separate mathematical assumptions, theoretical bounds, reserved metadata and actual measured performance.

## Step-by-step worked calculation

For a 64 KiB update (65,536 bytes) and 10 megabits per second (decimal), serialization alone takes 65,536×8 / 10,000,000 s = 0.0524288 s =52.4288 ms. If a request/response requires one 100 ms RTT, the simple lower bound is 152.4288 ms, not including queueing, framing, TLS, packet loss or training.

## Application to a C23 learning network

A robust implementation checks dimensions and integer bounds **before** modifying stored state. The existing Framework federated aggregation and new job-admission services treat sample counts, model vectors and transfer reservations as different units. None of the arithmetic presented here proves that remote training was carried out honestly.

## Independent exercise

**Question:** At 20 Mbps instead of 10 Mbps, with RTT still 100 ms, what is the simple bound?

<details><summary>Reveal the complete solution</summary>
<p>Serialization halves to 26.2144 ms; bound 126.2144 ms. Do not treat it as a measured connection.</p>
</details>

## Units, assumptions and interpretation

Preserve byte versus bit, decimal MB versus binary MiB, sample count versus token count, and reported resource forecasts versus observed measurements. If the calculation describes a statistical model, state its independence assumptions; if it describes a rejected update, do not silently change the aggregation algorithm.

## Further study

[Related LLM Lesson 397](../10-native-ai/397-compose-admission-with-the-existing-fedavg-owner.md) · [Mathematics learning path](../../courses/maths-for-ai/federated-job-mathematics.html).

*Service to Many Leads to Greatness.*
