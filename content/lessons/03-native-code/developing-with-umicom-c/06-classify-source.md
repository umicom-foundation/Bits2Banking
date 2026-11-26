<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/developing-with-umicom-c/06-classify-source.md

PURPOSE:
Read a tagged source inventory and observe a deliberately incomplete envelope.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Classify two language regions

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

One source envelope can mark regions that contain text in different languages. Open [the brew recipe envelope](../../../labs/native/umicom-c-brew-time/brew-time-regions.umc). It contains a small Umicom C program and a Python string with two characters that resemble the closing delimiter.

1. Run the read-only classifier. In PowerShell, convert the JSON report into objects you can inspect.

   ~~~powershell
   $Regions = & $Uc regions (Join-Path $Lab 'brew-time-regions.umc') --json | ConvertFrom-Json
   $Regions.classificationOnly
   $Regions.regions | Format-Table language, offset, bytes
   ~~~

2. Find the Umicom and Python entries. Offsets and lengths refer to original file bytes. An ordinary Umicom span may appear outside the explicit tags. Check that the string stays inside the Python region even though its text contains a closing-marker lookalike.
3. Inspect [the incomplete envelope](../../../labs/native/umicom-c-brew-time/brew-time-unclosed-region.umc). Expect a diagnostic, no JSON report and a nonzero exit status.

   ~~~powershell
   & $Uc regions (Join-Path $Lab 'brew-time-unclosed-region.umc') --json
   $LASTEXITCODE
   ~~~

4. For a repair exercise, copy the incomplete envelope into your practice folder, add its closing marker on a new line and run the first command with that path. Verify that the report now has classificationOnly set to True. Each language still needs a separate compiler or interpreter to execute its code.

[Previous step — Try an edit before accepting it](05-preview-and-commit.md) · [Next step — Inspect and link native x64 output](07-link-a-constant.md)
