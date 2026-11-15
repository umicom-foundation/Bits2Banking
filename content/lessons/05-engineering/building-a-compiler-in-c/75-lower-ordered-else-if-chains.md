<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/75-lower-ordered-else-if-chains.md

PURPOSE:
Lower ordered else-if chains

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Lower ordered else-if chains

An else-if chain tests conditions in order and chooses at most one update body. This is useful when categories are mutually exclusive: negative, zero and positive values, for example. The existing Umicom C forward-branch runtime already has the operations needed for this behavior. This lesson extends source parsing, then checks that the extension preserves source locations, parser bounds and the runtime’s completed-result contract.

## 1. Predict the selected path

~~~c
int main(void)
{
    int value = 1;
    if (0) {
        value = 7;
    } else if (1) {
        value = 42;
    } else {
        value = 9;
    }
    return value;
}

~~~

The first condition is zero, so the first body is skipped. The second condition is nonzero, so value becomes 42. The final else does not run. Change the first condition to one and the result becomes seven; the second condition is not evaluated. Change both conditions to zero and the final else produces nine. Without a final else, all-false conditions leave the earlier local value unchanged.

Each update body still needs braces. The grammar allows assignments, compound assignments and further conditional statements inside those braces. Branch-local declarations, early returns, standalone nested scopes, loops and calls remain unsupported. Declare local variables before the chain and keep the required final return after the top-level statements. This is an explicitly bounded language profile, not a claim of complete C23 support.

## 2. Inspect the lowering in C

The parser already emits JUMP_IF_ZERO after an if condition. When it sees else, it emits a JUMP that skips the entire false path after a true body. The extension chooses between a braced body and another conditional statement at that false-path position. The earlier jump is patched only after the remaining chain is compiled, so an early match skips every later condition and body.

~~~c
/* In the existing else branch, after its false target is patched: */
if (parser->token.kind == UMC_TOKEN_IF)
    if_statement(parser, depth + 1U);
else
    if_body(parser, depth + 1U);
patch_forward(parser, join);
~~~

This excerpt belongs to the private parser in src/compiler.c; it is not a standalone application API. Its functions share one parser status. Once an error occurs, emission stops and the compile result count remains zero. Partial instruction storage must never be executed after a failed compile. The superseded braced-only function remains in a disabled block so its behavior and ownership decisions can be reviewed.

## 3. Count accepted records and executed steps separately

The example produces sixteen records. Indices zero and one initialize the local. The first condition occupies indices two and three; its true update is four and five, followed by a jump at six. The second condition is seven and eight; its true update is nine and ten, followed by a jump at eleven. The final else is twelve and thirteen. Reading the local and returning are fourteen and fifteen.

For the example’s false-then-true path, execution visits 0, 1, 2, 3, 7, 8, 9, 10, 11, 14 and 15. That is eleven steps. A budget of ten reaches RETURN without enough fuel and must not publish a completed result. Accepted record count includes all alternatives, while fuel charges only attempted execution. Forward-only targets make the complete record count a sufficient upper bound for this profile.

## 4. Compile and inspect an artifact

1. Configure and build Umicom C with your normal native Debug or Windows UCRT64 preset. Confirm that the linked compiler reports the else-if capability before relying on a newer header.
2. Run the check and trace commands below from the Umicom C repository. Use your actual build directory when it differs from the example.
3. Choose a new bytecode destination, compile it, then execute it with eleven steps and with ten steps. Preserve the failed result as failure evidence.
4. Compare source trace with bytecode trace. Both should identify the same attempted instruction path and source offsets. The leading source header changes byte offsets, not the selected operations.

~~~powershell
.\build\windows-ucrt64-debug\bin\umicom-c.exe profile
.\build\windows-ucrt64-debug\bin\umicom-c.exe check .\examples\conditional_chain.uc
.\build\windows-ucrt64-debug\bin\umicom-c.exe trace .\examples\conditional_chain.uc
.\build\windows-ucrt64-debug\bin\umicom-c.exe compile .\examples\conditional_chain.uc .\build\conditional-chain.umcb
.\build\windows-ucrt64-debug\bin\umicom-c.exe exec .\build\conditional-chain.umcb --max-steps 11
.\build\windows-ucrt64-debug\bin\umicom-c.exe exec .\build\conditional-chain.umcb --max-steps 10
~~~

Compilation refuses to overwrite an existing artifact. Use a fresh destination when repeating the exercise. Expect result 42 and eleven executed instructions with the complete budget; the smaller budget reports exhaustion. These expected outcomes describe the contract to verify in your environment. They do not establish that an independently installed SDK or application links the same compiler.

## 5. Preserve runtime and capability boundaries

Chained conditions use existing format-4 branch records. No opcode number, bytecode header, runtime feature bit or older artifact changes. The source compiler adds UMC_FEATURE_ELSE_IF_CHAINS, bit 8192. Its current complete feature mask is 16103, while the runtime mask stays 411 and supported wire-version mask stays 30. Applications should test the individual source bit rather than compare a permanently frozen complete mask.

A runtime-only consumer can execute admitted branch bytecode without knowing the source spelling that produced it. Conversely, a new header does not teach an old linked compiler to parse else if. Framework’s preview adapter delegates parsing and execution to the linked Umicom C components. Its own regression checks completion and error ownership; it must not reimplement branch semantics in the UI.

## 6. Test errors and shared depth limits

All conditions and bodies must parse and reference initialized locals, even when an earlier condition is always true. An unknown variable in a later skipped body is still a compile-time error. Arithmetic faults are different: a later 1/0 condition is harmless when an earlier body is selected, but faults if execution reaches that condition. The failure reports the division operator’s source offset and preserves the caller’s previous completed result.

Every nested if consumes one level from the shared statement/expression depth budget. Else-if spelling is recursive, so it must not reset that budget. A chain of 63 simple literal conditions fits the current nominal limit of 64; a 64th condition is refused. Adding another unary level at the deepest condition can also exhaust the budget. Program capacity and source-byte limits remain separate admission checks.

1. Run the else-if value, refusal, fault, depth, wire, fuel, capacity and location cases. Review failures rather than relaxing their assertions.
2. Run the native-C comparison over defined small integer inputs. It independently computes expected results using ordinary native conditions.
3. Run the earlier braced-if tests too. Existing plain if/else wire fixtures must remain unchanged.
4. Run the CLI test to verify source/bytecode trace parity, exact fuel and refusal to overwrite existing inputs or outputs.

~~~powershell
ctest --test-dir .\build\windows-ucrt64-debug -R "umicom\.c\.(else-if|if-statement|cli-else-if|cli-if-statement)" --output-on-failure
~~~

## Exercise and troubleshooting

Write a classifier that returns one for a negative local, two for zero and three for a positive local. Put a deliberately invalid arithmetic expression in a later condition, then predict which inputs reach it. Confirm both successful values and failure source locations. Next remove a brace: the parser should reject the source without producing an executable artifact.

If the syntax is rejected unexpectedly, check the linked compiler capability and ensure every body is braced. If a long chain is refused, inspect combined expression and statement depth before changing program capacity. If an old runtime rejects emitted bytes, inspect the canonical wire version and the consumer’s admitted formats. Keep compiler tests, runtime-only tests and application integration evidence separate when reporting what was actually qualified.

[Course contents](index.md) · [Previous lesson](74-lower-braced-conditional-statements.md)

[Next lesson: Add checked signed remainder without breaking bytecode](76-add-checked-signed-remainder.md)
