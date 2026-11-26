<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/swift-payment-messages.md

PURPOSE:
Provide practical first steps and a result to check for Swift Payment Messages and ISO 20022.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Swift Payment Messages and ISO 20022

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Write the example instruction ID, currency and amount on paper. Label it as the payment instruction. [Follow the Payment and Message Roles](../../courses/swift-payment-messages/lessons/01-follow-payment-message-roles.html)
2. Read the three local records and match them by instruction ID. Mark which record is a status report and which represents settlement evidence. [Normalize Message Evidence for Review](../../courses/swift-payment-messages/lessons/02-normalize-message-evidence.html)
3. Replay the same status in the local C23 exercise and check the final record after settlement evidence arrives. [Apply Payment Evidence in C23](../../courses/swift-payment-messages/lessons/03-apply-payment-evidence-in-c.html)

**Check your result.** A status report updates the instruction’s business status. Settlement stays pending until its own evidence is received.

[Continue in the full course](../../courses/swift-payment-messages/index.html) · [All course guides](index.md)
