<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-special-token-reference/04-map-a-diagnostic-back-to-source.md

PURPOSE:
Label the next generated source line and use the reported location to find the teaching example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Map a diagnostic back to source

[Course contents](index.md) · [Previous lesson: Stop reading source at an explicit marker](03-stop-reading-at-a-marker.md) · [Continue to Continue Learning D](../../../courses/learning-d/index.html)

Label the next generated source line and use the reported location to find the teaching example.

## Distinguish a physical line from a logical line

A generator can emit a statement in `practice.d` that came from rule 240 of `statement_rules.d`. `#line` sets the source location for the very next line. The line containing `writeln` below becomes logical line 240. For this lesson the source name is fictional. A real generator should use a location the learner can find.

## Compare the two language mechanisms

The spelling `#line __LINE__ "statement_rules.d"` also fits D’s grammar. It uses the line value in scope at the directive. The lesson uses a fixed number so you can predict the result without counting the lines before the directive.

C also supports `#line` and the `__LINE__` and `__FILE__` macros. D describes `#line` as a special token sequence interpreted by its scanner, and `__LINE__` and `__FILE__` as special keywords. In Studio, read the source path and line in a compiler message to locate the problem. An editor can display the mapping without owning the compiler's lexical behaviour.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `#line` | `#line 240 "statement_rules.d"` | Assign a logical file name and a number to the following source line. The physical file still has its original name and contents. |
| `__LINE__` | `writeln(__LINE__);` | Get the logical source line at the point of use. |
| `__FILE__` | `writeln(__FILE__);` | Get the source file name used at this point. Outside a fixed teaching mapping the path style can vary by compiler. |
| `__FILE_FULL_PATH__` | `writeln(__FILE_FULL_PATH__);` | Get the absolute source path at the point of use. Use a local teaching workspace when observing it. |
| `__MODULE__` | `writeln(__MODULE__);` | Get the module name at the point of use. |
| `__FUNCTION__` | `writeln(__FUNCTION__);` | Get the qualified function name at the point of use. |
| `__PRETTY_FUNCTION__` | `writeln(__PRETTY_FUNCTION__);` | Describe the function with signature details in the compiler's string form. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
SET the next logical position to statement_rules.d line 240
READ the file name and line for the print statement
SHOW both parts together
```

## Run the complete example

Save the whole program as `practice.d`. Open a terminal in that folder, then enter the command shown for your language.

```d
import std.stdio : writeln;

void main()
{
#line 240 "statement_rules.d"
    writeln(__FILE__, " line ", __LINE__);
}
```

```text
dmd -run practice.d
```

Expected output

```text
statement_rules.d line 240
```

If the terminal cannot find dmd, check the D compiler installation for your operating system. If your course uses another documented D compiler, use its build and run instructions. You can still trace the example without installing a compiler.

## Try a change

Insert one empty line immediately after #line and predict the new number. Does the new number tell you the physical location of practice.d?

**Check your answer**

The empty line takes logical number 240. The statement that prints the values moves to logical line 241. The output reports the logical location supplied to the compiler.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [D language specification, Special Tokens](https://dlang.org/spec/lex.html#specialtokens)
