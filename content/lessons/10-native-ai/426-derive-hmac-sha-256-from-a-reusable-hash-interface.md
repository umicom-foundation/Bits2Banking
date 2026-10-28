# LLM from Scratch — Lesson 426: Derive HMAC-SHA-256 from a reusable hash interface

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Understand why the inner and outer hash passes are necessary without implementing another SHA-256 engine.

## Concept and mechanism

HMAC first pads or hashes the secret to SHA-256’s 64-byte block, then computes H((K xor opad) || H((K xor ipad) || m)). It uses the established cryptographic compression function twice under distinct constants. In native Umicom code, the portable SHA-256 streaming API remains the sole SHA implementation; the HMAC layer is a short reusable Framework component.

## Guided reasoning

1. Check the key is nonempty and the message is explicitly bounded.
2. Hash keys longer than 64 bytes into the initial key block.
3. Build separate 0x36 and 0x5c pads.
4. Hash inner then outer bytes.
5. Test the complete 32-byte result against published vectors.

## Worked example

An HMAC-SHA-256 message with a 20-byte key does not consume 20 bytes as-is in the SHA block: the key is zero-padded to 64 bytes, then combined with the 64-byte ipad and opad patterns in the two passes.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

HMAC does not encrypt the update or replace credential provisioning and key rotation.

## Test your understanding

**Question:** If an HMAC key is 90 bytes long, which material is XORed with the 64-byte pads?

<details><summary>Reveal the worked answer</summary>

Hash the 90-byte key with SHA-256, then pad the resulting 32-byte digest to 64 bytes before applying ipad/opad. This follows HMAC’s long-key handling.

</details>

## Reading and source

- [RFC 2104, HMAC: Keyed-Hashing for Message Authentication](https://www.rfc-editor.org/rfc/rfc2104.html)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
