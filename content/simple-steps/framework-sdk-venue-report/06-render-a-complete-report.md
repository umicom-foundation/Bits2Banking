<!--
Bits2Banking
File: content/simple-steps/framework-sdk-venue-report/06-render-a-complete-report.md

PURPOSE:
Teach capacity checks and complete publication for a caller-owned result buffer.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Render the report within a fixed space

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The summary is a set of values in memory. It becomes a report when the program writes those values as readable lines. The renderer also needs room for the closing zero byte that C uses to mark the end of text.

1. Open `BtbVenueRender`. Find the temporary text array and the check on the value returned by `snprintf`.
2. Find the copy into the destination. It happens only after the whole report fits. The supplied length counts report bytes and leaves out the closing zero byte.
3. In `check_render`, find the intentionally too-short output containing `old`, then find the second test that supplies exactly enough space.
4. Run the focused check.

```powershell
ctest --test-dir $build -R '^learning\.venue\.render$' --output-on-failure --no-tests=error
```

**Check your result.** The check passes for both sizes. A too-short destination retains its earlier text and length. A destination with one byte for each report byte plus one for the closing zero accepts the report.

[Previous — Check a fingerprint](05-check-the-source-fingerprint.md) · [Next — Publish a new receipt](07-publish-a-new-receipt.md)
