# Teaching system administration basics

Start by asking learners to open a terminal, check their current location and name the program they are using. Do not assume that a successful GitHub login, file edit, Windows administration command or C23 build is already familiar. Introduce new technical terms once, then reuse them accurately.

**Suggested programme:** four weeks, six lessons per week, with time for questions and practice. Learners may progress faster or slower. Each lesson includes its own objectives, exact commands, expected observations, troubleshooting and review questions. The course workbook distinguishes PASS, NEEDS HELP and NOT RUN.

**Recommended classroom demonstration:** open Windows Start search and ask learners to identify Windows PowerShell, PowerShell 7 and other entries by name. Open the selected shell, run `$PSVersionTable.PSVersion`, then `Get-Location`. Demonstrate a safe private practice folder under `$HOME\UmicomLearning`. Avoid elevated accounts and source repositories.

**Course safety:** no practice requires administrative accounts, real patient or bank data, publishing public repositories, running force-push, disabling firewalls or executing downloaded scripts. Use an approved training VM if showing an operating-system configuration change becomes necessary in a later course volume.

**Lab acceptance:** GCC/Clang tests can be completed on available Linux hosts; Windows UCRT64 and MkDocs checks must be run on the corresponding host before claiming Windows or website qualification.
