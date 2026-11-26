<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/inspect-and-copy.md

PURPOSE:
Rehearse a verified image transfer between two regular files.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# 10. Rehearse a verified transfer

A media writer can erase the selected device. Learn the review and readback sequence first with an ordinary file. This exercise makes a small synthetic partition-table image, and every output stays in a new folder under your profile.

1. Use an existing Framework build containing both `umicom-media.exe` and `umicom-media-image-example.exe`. The [Framework media lesson](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/prepare-and-check-boot-media.html) lists the targets. In PowerShell, locate their folder and create a new local workspace.

   ~~~powershell
   $Bin = Read-Host 'Absolute path to the Framework build bin folder'
   $Media = Join-Path $Bin 'umicom-media.exe'
   $Practice = Join-Path $env:USERPROFILE ("media-practice-" + [guid]::NewGuid().ToString("N"))
   New-Item -ItemType Directory -Path $Practice -ErrorAction Stop | Out-Null
   $Image = Join-Path $Practice 'practice.img'
   $Copy = Join-Path $Practice 'verified-copy.img'
   & (Join-Path $Bin 'umicom-media-image-example.exe') --output $Image
   if ($LASTEXITCODE -ne 0) { throw 'Could not create the practice file.' }
   & $Media inspect --image $Image
   if ($LASTEXITCODE -ne 0) { throw 'Image inspection did not complete.' }
   ~~~

   Look for 2,097,152 bytes, an SHA-256 value and `MBR: yes`. The example contains no system files. Leave it in the practice folder.

2. Review the destination. Check that its name ends in `verified-copy.img` in the new folder. Review should print a fingerprint and a confirmation beginning with `CREATE`. It should leave the destination absent.

   ~~~powershell
   & $Media review --image $Image --output $Copy
   if ($LASTEXITCODE -ne 0) { throw 'Could not review the file destination.' }
   Test-Path -LiteralPath $Copy
   ~~~

3. Enter the exact tokens displayed by that review. The copy tool rechecks the source and destination. Read both independent hashes afterward.

   ~~~powershell
   $Fingerprint = Read-Host 'Full fingerprint from the last review'
   $Confirmation = Read-Host 'Complete confirmation from the last review'
   & $Media copy --image $Image --output $Copy --expect $Fingerprint --confirm $Confirmation
   if ($LASTEXITCODE -ne 0) { throw 'The file copy did not complete.' }
   & $Media verify --image $Image --output $Copy
   if ($LASTEXITCODE -ne 0) { throw 'The copy bytes did not verify.' }
   Get-FileHash -Algorithm SHA256 -LiteralPath $Image, $Copy
   ~~~

4. Try the same copy command a second time. Expect refusal and a nonzero status. Confirm the existing copy’s hash has not changed. Use a different unused filename for another legitimate transfer, then review it again.

If a copy is interrupted, keep any output as evidence and classify it by the observed result. Record the initial cancellation and any later byte comparison as separate observations.

**Check yourself.** Before the transfer the plan existed and the destination did not. After it the two files match. A second attempt preserves the existing destination. Document the three observations separately.

[Previous · File-backed UEFI disk](os-uefi-disk-image.md) · [Next · Physical readiness](physical-readiness.md) · [Full C23 SDK lab](../../lessons/06-umicom/umicom-os-from-scratch/42-copy-and-verify-regular-file-media.md)
