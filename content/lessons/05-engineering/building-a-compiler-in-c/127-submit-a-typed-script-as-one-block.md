<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/127-submit-a-typed-script-as-one-block.md

PURPOSE:
Submit a typed script as one block

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Submit a typed script as one block

Imagine checking a short practice checklist before accepting its final value. In the typed console, `--block` makes the lines one submission. A usable block can return a value. If a line fails, the block is refused as a whole. This all-or-nothing rule is called **atomic submission**.

## 1. Follow one complete block

Save these lines as `typed-block.ucs`. The fixed Boolean named `admitted` holds `1` because `42` is nonzero. The local `flag` begins at `1` too. The `if` body sets it to `0`, so the last line calculates `41 + 0 + 1`.

~~~c
const bool admitted=42;
bool flag=-7;
if (admitted) {
flag=0;
}
return 41+flag+sizeof(flag);
~~~

~~~text
umicom-c script --typed --block typed-block.ucs
~~~

The checked command succeeded with one output line, `42`. The `--typed` option comes before `--block`. The filename supplies the whole block.

~~~text
READ the supplied lines as one typed block
EVALUATE the block as a single submission
IF the submission succeeds, publish its value
IF it fails, publish its diagnostic and refuse the submission
~~~

## 2. Locate a refusal

Save this second block as `refused-block.ucs` and feed the file through standard input. The second line asks for division by zero.

~~~c
bool flag=1;
flag=1/0;
return flag;
~~~

~~~powershell
Get-Content -Raw -LiteralPath './refused-block.ucs' | umicom-c script --typed --block --stdin
~~~

The checked command exits with status `1`. Standard output stays empty. Standard error, the stream used for the diagnostic, contains this line.

~~~text
2:7: division by zero or signed arithmetic overflow
~~~

Read `2:7` as line two, column seven. On `flag=1/0;`, count `f`, `l`, `a`, `g`, `=` and `1` first. The slash is seventh. This example reaches the division-by-zero case of the diagnostic. The initial declaration produces no separate `ok` here because the whole block was the submission.

## 3. Compare two paper runs

For the accepted block, predict what happens if `admitted` starts at `0`. The `if` body is skipped, leaving `flag` equal to `1`. The predicted block value is `43`. For the refused block, mark where the diagnostic starts and write “empty” under expected standard output. Keep the expected exit and the two output streams on separate lines in your test notes.

[Course contents](index.md) · [Previous lesson · Keep the accepted value during a console preview](126-keep-the-accepted-value-during-a-console-preview.md) · [Group console checks by what they submit](../automated-testing-with-umicom/15-group-console-checks-by-what-they-submit.md) · [Next lesson · Read a signed cast in complete C](128-read-a-signed-cast-in-complete-c.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/127-submit-a-typed-script-as-one-block.html)
