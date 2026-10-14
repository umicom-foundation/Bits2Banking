# System Administration course — practice workbook and assessment

**Course:** Bits2Banking — System Administration From Zero  
**Status fields:** PASS, NEEDS HELP, NOT RUN; do not invent a PASS when you cannot perform a step.

## Prepare one safe training folder

In Windows PowerShell 7:

```powershell
New-Item -ItemType Directory -Path "$HOME\UmicomLearning\Notes" -Force
Set-Location "$HOME\UmicomLearning\Notes"
Get-Location
```

Write the displayed folder in your notebook. This is your training space, **not** a live Umicom repository.

## Twelve practical evidence checks

| # | Task | Expected observation | Your result |
|---|---|---|---|
| 1 | Run `$PSVersionTable.PSVersion` | Version and edition identified. | ______ |
| 2 | Run `Get-Location` | Correct sandbox directory displayed. | ______ |
| 3 | Run `whoami` | Signed-in account printed. | ______ |
| 4 | Open `README.md` in Notepad | Text editor opens file without executing it. | ______ |
| 5 | Read using `Get-Content` | Saved text displayed. | ______ |
| 6 | Run `Get-Process` | A bounded list of process IDs printed. | ______ |
| 7 | Run `Get-Service` | Some Windows service statuses observed. | ______ |
| 8 | Run `Get-PSDrive -PSProvider FileSystem` | Free capacity displayed. | ______ |
| 9 | Copy README and compare SHA-256 | Matching content hashes. | ______ |
| 10 | Run `Resolve-DnsName github.com` | Name lookup succeeds or an explicit network error is recorded. | ______ |
| 11 | Run `git status` in a practice Git repository | Expected staged/unstaged status observed. | ______ |
| 12 | Run `ctest` for the C23 read-only text lab | Actual test totals recorded, not assumed. | ______ |

### Do not change system protection for the exercise

No test requires `Remove-Item -Recurse -Force`, `git reset --hard`, `git clean -fd`, `sudo chmod -R`, disabling security controls, a forced Git push, or access to anybody else's files.

## Support ticket handover template

**Observed problem:** ______________________________________________  
**Expected result:** ______________________________________________  
**Observed actual result:** _________________________________________  
**Date/time and time zone:** ________________________________________  
**Machine OS / shell / relevant tool versions:** ______________________  
**Working directory used:** ________________________________________  
**Reproduction steps:** ____________________________________________  
**Evidence collected:** ____________________________________________  
**Actions taken (including none):** ________________________________  
**Outcome:** PASS / NEEDS HELP / NOT RUN  
**Unverified assumptions and next safe check:** ______________________

## Model response: practice document cannot be read

> I opened PowerShell 7 as an ordinary user, checked my location, confirmed that `README.md` was missing from the Notes practice folder, and did not change any system-level files. I will return to Chapter 6 to create the file in the correct location and then retry `Get-Content`. I cannot yet claim the document was successfully restored.

## Instructor marking guidance

Mark **PASS** when the learner can explain each command's purpose, distinguish read-only operations from changes, and present real evidence. Mark **NOT RUN** if a required tool or network is unavailable. Mark **NEEDS HELP** if the learner uses the wrong directory or misinterprets an error. Support improvement rather than penalising the learner for reporting limitations accurately.
