<!--
Umicom Bits2Banking
File: content/lessons/05-ai/generative-ai-foundations/02-caption-and-image-pairs.md

PURPOSE:
Prepare image-caption pairs with provenance

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Prepare image-caption pairs with provenance

[Course contents](index.md)
Text-conditioned image training commonly pairs an image with descriptive text. A caption is a description of what is visible or intended to be learned. It is not a filename, license statement or unrelated search keyword list. Poor captions can teach a confusing relationship between language and appearance.

1. Create or select a few images you have permission to use. Keep unchanged originals and record source, permission and related-group identity.
2. Write a literal caption for each image. Describe visible subject, action, setting and useful style information without inventing details.
3. Record width, height, color mode and orientation after decoding. An EXIF rotation flag may change the visible orientation.
4. Reject corrupt or unsupported files explicitly. Review near-duplicates and alternate crops as related sources.
5. Keep captions and image identifiers paired through every shuffle, resize and split. A mismatched pair is a data defect even if both files parse.

~~~jsonl
{"id":"shape-01","image":"images/blue-square.png","caption":"A blue square on a white background.","group_id":100,"permission":"original exercise"}
{"id":"shape-02","image":"images/red-circle.png","caption":"A red circle on a white background.","group_id":200,"permission":"original exercise"}
~~~

This illustrates a manifest schema; adapt it only after checking the chosen loader. Relative paths should remain within a declared dataset root. The manifest does not embed the image pixels. A key-value record describes where data and metadata live; the model still receives decoded tensors and tokenized text.

Do not assume internet availability grants training rights or permission to reproduce a person’s likeness. Record the actual allowed use. For a beginner exercise, original geometric drawings are easier to audit than a large downloaded collection. Keep private information out of filenames and captions that might be published.


## Exercise

Write two captions for a drawing: one accurate and one containing an object that is absent. Explain which teaches the desired association and why. More words are not automatically a better caption. Have another reader compare the chosen caption with the image.


## Continue learning

[Previous: Start with pixels, frames and generative models](01-pixels-frames-and-models.md) · [Course contents](index.md) · [Next: Resize and batch images without silently changing the task](03-resizing-cropping-and-buckets.md)
