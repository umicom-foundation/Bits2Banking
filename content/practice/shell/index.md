<!--
Umicom Bits2Banking
File: content/practice/shell/index.md

PURPOSE:
Teach folder commands through a browser-local C23 exercise.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Practise Bash and PowerShell commands

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use a small practice workspace to find a folder, open a report and check whether a command succeeded. The two shells have separate practice folders. Commands stay in this browser tab and only read the lesson’s files.

<form data-btb-shell-form>
  <p><label for="btb-shell-dialect">Practice shell</label></p>
  <p><select id="btb-shell-dialect" name="dialect" disabled><option value="0">Bash</option><option value="1">PowerShell</option></select></p>
  <p><label for="btb-shell-command">Command</label></p>
  <p><input id="btb-shell-command" name="command" type="text" maxlength="192" size="32" autocomplete="off" spellcheck="false" required disabled></p>
  <p><button name="run" class="md-button md-button--primary" type="submit" disabled>Run</button> <button name="reset" class="md-button" type="button" disabled>Reset folder</button></p>
</form>
<p id="btb-shell-status" role="status" aria-live="polite">The worked steps below remain available while the practice module loads.</p>
<pre id="btb-shell-output" aria-label="Practice command output" tabindex="0"></pre>

## Follow the same task in both shells

Run one line at a time. Select the shell that matches the column. **Reset folder** returns it to the starting folder.

| Step | Bash | PowerShell | What to look for |
| --- | --- | --- | --- |
| 1. Find the current folder | `pwd` | `Get-Location` | Bash shows `/practice`. PowerShell shows `C:\practice`. |
| 2. List its contents | `ls` | `Get-ChildItem` | The two choices are `reports` and `samples`. |
| 3. Open the reports folder | `cd reports` | `Set-Location reports` | The command succeeds without output. |
| 4. Read the report | `cat "closing notes.txt"` | `Get-Content "closing notes.txt"` | The three lines read Approved, Pending and Approved. |
| 5. Try a missing file | `cat missing.txt` | `Get-Content missing.txt` | The exercise reports that the file is missing. |
| 6. Check that failure | `echo $?` | `$?` | Bash shows `1`. PowerShell shows `False`. |
| 7. Go back | `cd ..` | `Set-Location ..` | Repeat step 1 to confirm that you are back at the starting folder. |

Try step 4 without the quotes. The exercise refuses the extra word. Put the quotes back to keep the full filename together as one argument.

## Continue in a real terminal

This exercise implements the table’s command forms with a few fixed paths. It reports file and folder names as plain text. Use the local course for pipelines, shell variables, command options and real PowerShell objects.


## Run the same exercise in a desktop terminal

From a source checkout with a C23 compiler, build the command-line exercise. This uses the same C workspace and report as the browser form. Type each lesson command into the running exercise, or pipe several lines as shown below.

~~~powershell
New-Item -ItemType Directory -Force build | Out-Null
gcc -std=c23 labs/web/shell-practice/shell.c labs/web/shell-practice/shell_cli.c -o build/shell-practice.exe
@'
pwd
cd reports
cat "closing notes.txt"
'@ | .\build\shell-practice.exe bash
~~~

Expect the starting folder and the same three lines as in step 4. Use `powershell` in place of `bash` with the PowerShell column's commands.

[Shell practice course](../../lessons/02-programming/shell-practice/index.md) · [Learning in Simple Steps](../../simple-steps/index.md)
