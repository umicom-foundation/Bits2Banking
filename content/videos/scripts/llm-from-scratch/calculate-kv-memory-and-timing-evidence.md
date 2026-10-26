# Calculate KV Memory and Measure Timing Honestly

**Bits to Banking · Umicom Foundation**  
**Author and narrator:** Sammy Hegab  
**Format:** Educational narration and storyboard (not a completed recording)

## Intended learning outcome

By the end, viewers should distinguish mathematical claims, executable native C23 functionality and the evidence required to publish a trustworthy engineering result. The example data are fictional and contain no customer information.

## Scene 1: A familiar table

**Visual direction:** Display clean, readable numbers or code declarations. Avoid irrelevant decoration or hidden transitions.

**Narration:** Start with rows and columns to explain token count, channel count and memory per float.

**On-screen question:** Which quantities are calculated, which have been measured, and which still require independent validation?

## Scene 2: Memory arithmetic

**Visual direction:** Display clean, readable numbers or code declarations. Avoid irrelevant decoration or hidden transitions.

**Narration:** Compute 2 K/V arrays times two layers times eight positions times eight channels times four bytes, obtaining 1,024 bytes of raw payload. Explain what is excluded.

**On-screen question:** Which quantities are calculated, which have been measured, and which still require independent validation?

## Scene 3: Workload arithmetic

**Visual direction:** Display clean, readable numbers or code declarations. Avoid irrelevant decoration or hidden transitions.

**Narration:** Explain the 192 full-reference rows and 112 hypothetical growing-prefix rows under eight context positions, a three-token prompt, twelve samples and two layers.

**On-screen question:** Which quantities are calculated, which have been measured, and which still require independent validation?

## Scene 4: A performance surprise

**Visual direction:** Display clean, readable numbers or code declarations. Avoid irrelevant decoration or hidden transitions.

**Narration:** A measured cache median of 9.1 ms against 8.4 ms for the reference is slower, despite fewer rows. Show how allocation and memory traffic can explain it.

**On-screen question:** Which quantities are calculated, which have been measured, and which still require independent validation?

## Scene 5: Review and exercise

**Visual direction:** Display clean, readable numbers or code declarations. Avoid irrelevant decoration or hidden transitions.

**Narration:** Ask the learner to compute raw bytes for three layers, ten positions and sixteen channels, then compare their answer with Mathematics Unit 75.

**On-screen question:** Which quantities are calculated, which have been measured, and which still require independent validation?

## Suggested learner activity

Ask viewers to open the related Markdown source and HTML companion and calculate at least one numerical result without consulting a running application. Then compare that result with the documented native Framework API and its dedicated CTest, if available. Do not treat an unrun or failed test as a pass.

## Publication note

The storyboard may be recorded or edited by an educator. It does not represent a finished video, production model benchmark or approved dataset.

*Service to Many Leads to Greatness.*
