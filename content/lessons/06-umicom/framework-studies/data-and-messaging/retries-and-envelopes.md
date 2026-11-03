# Recognise the same message twice

Connect storage, message identity, retries and recovery without confusing a request with completion.

Lesson 2 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **message** carries information between components. Its **payload** is the business content. An **envelope** adds context such as identity, origin or correlation. A correlation identifier helps connect related operations in logs without copying their entire payloads.

A sender may deliver a request successfully but lose the reply. Retrying is sensible only if the receiver can recognise what has already happened. **Idempotency** means repeating the same logical operation does not create a second business effect. It requires an agreed identifier and rules; it does not come from a “retry” button alone.

```text
request PAY-17 → receiver commits once → reply lost
request PAY-17 → receiver finds receipt → returns same outcome
request PAY-17 with changed amount → reject identity conflict
```

Using a fresh identifier on every attempt hides the relationship between retries. Reusing an identifier for different content is also wrong. A robust design binds the identifier to the intended operation and retains enough evidence to distinguish an exact retry from conflicting reuse.

An **outbox** records messages to send alongside the business transaction. A dispatcher sends them later. An **inbox** records received identities and processing outcomes. Neither word guarantees delivery exactly once. Duplicate delivery remains possible, so the receiver must protect the business effect.

## Trace three arrivals

1. Write a request with ID P7 and amount 250.
2. Record a successful receipt for P7.
3. Receive P7/250 again. Return the known outcome.
4. Receive P7/300. Refuse the conflict and retain the original evidence.

Framework's message envelope describes payload length and a payload hash separately from header metadata. A hash can help detect a content change. It is not automatically a cryptographic signature, identity proof, authorisation decision or durable duplicate journal.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\integration\fabric\message_envelope.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiFabricMessageEnvelope { UmiFabricMessageHeader header; uint64_t payload_length; uint64_t payload_hash; bool compressed; } UmiFabricMessageEnvelope;
/**
 * Initialise fabric message envelope from caller-provided values so later operations
 * receive a known state.
 */
UmiStatus umi_fabric_message_envelope_init(UmiFabricMessageEnvelope *envelope,const UmiFabricMessageHeader *header,const void *payload,size_t payload_length,bool compressed);
/**
 * Provide the fabric message envelope matches operation used by this module and its client
 * applications.
 */
bool umi_fabric_message_envelope_matches(const UmiFabricMessageEnvelope *envelope,const void *payload,size_t payload_length);

#ifdef __cplusplus
}
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Read UmiFabricMessageEnvelope and its initializer. Find which metadata is copied and which operations validate the envelope. Compare it with the payment instruction's idempotency key.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Why is “message received” different from “payment settled”?

### Worked answer

Receipt proves that a boundary accepted some information. Settlement is a later business fact requiring its own evidence. Acknowledging a message must not move a payment directly to settled.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/data-and-messaging/lessons/retries-and-envelopes.html) · [Learning sequence](../../../../start/learning-sequence.md)
