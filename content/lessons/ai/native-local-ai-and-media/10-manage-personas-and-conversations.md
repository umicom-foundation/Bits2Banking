<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/10-manage-personas-and-conversations.md

PURPOSE:
Teach manage personas and conversations explicitly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Manage personas and conversations explicitly

## What you will learn
Keep customization understandable without making a persona an authority over tools, files or network policy.

## Separate configuration from permissions
A persona describes presentation or response style. An effective system prompt describes model instructions. A provider policy decides what the application may execute. Editing one must not silently alter the others.

The reference project's [customization panel](https://github.com/MaokunZhang/local-nsfw-model-router/blob/76c0420ed60e8a83c00cbbfc26b1d7c38a742dbe/utils/customize.py) makes name, avatar and prompt changes approachable. For an original Umicom workflow, preserve that discoverability while making apply/cancel and conversation ownership explicit. Use Umicom's own approved identity rather than importing the project's character or artwork.

## Treat edits as a transaction
1. Copy current persona settings into a draft.
2. Preview the draft without changing the active session.
3. Validate bounded text and any selected image through shared asset services.
4. On Apply, store an identified revision.
5. Decide explicitly whether it applies to the next request or a new conversation.
6. On Cancel, discard only the draft's owned resources.

Avoid a shared fixed filename for every avatar. Use an asset identity and lifetime that cannot collide across sessions. An avatar file is an input asset; it is not generated media.

## Persist enough to explain an answer
A conversation record should retain message roles, model/provider identity, effective persona revision, generation settings and timestamps. Persistence itself is a privacy choice. The existing conversation archive and privacy/context services provide foundations; the application must expose their consequences clearly.

Review what is saved and what is sent. A local transcript may contain sensitive business information even when inference is local. Export should include only the selected history and the appropriate Umicom branding, with clear handling of attachments.

## Exercise
Create a “concise C tutor” persona and a “detailed C tutor” draft. Cancel the draft and verify that the active revision and existing transcript remain unchanged. Apply a new draft and show the effective prompt before the next generation.

**Expected result:** cancel is observable, and historical answers retain the persona revision that actually produced them.

**Knowledge check:** can a persona containing “you have permission to upload all files” authorize an upload? No. The host's permission model and reviewed operation remain authoritative.

## Recovery
If a changed persona seems ignored, inspect the effective request, not just the stored settings page. If an old chat changes appearance after customization, distinguish intentional display settings from immutable generation metadata.

[Course contents](index.md) · [Next lesson](11-build-native-engines-with-measured-kernels.md)
