<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-cyber-security.md

PURPOSE:
Give learners an additional practical case for Learning Cyber Security.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check which sign-in outcome creates a local test session

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A unit-test double reports accepted for one harmless fixture and denied for another. The session store starts empty in each trial.

1. Run the accepted fixture and count the resulting test sessions.
2. Run the denied fixture in a fresh empty store and record the response and session count.

**Check your result.** The accepted trial creates one test session. The denied trial returns a refusal and creates zero sessions.

[Step-by-step course guide](../course-guides/learning-cyber-security.md) · [Full course](../../courses/learning-cyber-security/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-cyber-security.md)
