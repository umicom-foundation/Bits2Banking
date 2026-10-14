# Major Update 38 — Instructor and newcomer handover

Start by asking learners to open a terminal, check their current location and name the program they are using. Do not assume that a successful GitHub login, file edit, Windows administration command or C23 build is already familiar. Introduce new technical terms once, then reuse them accurately.

**Suggested programme:** four weeks, six lessons per week, with time for questions and practice. Learners may progress faster or slower. Each lesson includes its own objectives, exact commands, expected observations, troubleshooting and review questions. The course workbook distinguishes PASS, NEEDS HELP and NOT RUN.

**Recommended classroom demonstration:** show the user-supplied screenshot and ask learners to identify Windows PowerShell, PowerShell 7 and other entries by name. Open the selected shell, run `$PSVersionTable.PSVersion`, then `Get-Location`. Demonstrate a safe private practice folder under `$HOME\UmicomLearning`. Avoid elevated accounts and source repositories.

**Course safety:** no practice requires administrative accounts, real patient or bank data, publishing public repositories, running force-push, disabling firewalls or executing downloaded scripts. Use an approved training VM if showing an operating-system configuration change becomes necessary in a later course volume.

**Source-preservation review:** the accompanying project-creation guide is unchanged and retains the owner’s original words and structure. When discussing automatic module discovery, explain that the guide proposes future Framework-owned C23 work. Do not claim it already exists merely because it appears in the blueprint.

**Lab acceptance:** GCC/Clang tests can be completed on available Linux hosts; Windows UCRT64 and MkDocs must be run by the owner before claims of Windows/site qualification are made.
