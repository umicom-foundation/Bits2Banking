<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/project-borrowed-recipes-owned-variables.md

PURPOSE:
Separate borrowed recipes from owned variable values

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Separate borrowed recipes from owned variable values

After preparing the installed-SDK lab in its README, run this scenario. Commands below are qualification instructions, not recorded results.

~~~powershell
& .\build\framework-project-recipes\project-recipes.exe variables
~~~

## Identify the memory owner

The recipe fixture in recipe.c contains pointers to static strings. Framework borrows those strings while it validates and renders the recipe. The variable set instead stores names and values inside bounded arrays. This distinction lets the caller change an input buffer after setting a variable without changing the stored value. It also explains why a pointer returned by the getter should be treated as a temporary view, not independent storage.

~~~c
char value[] = "First name";
umi_developer_project_variable_set(&variables, "NAME", value);
value[0] = 'X';
const char *view = umi_developer_project_variable_get(&variables, "NAME");
/* The stored value remains "First name". Check every returned status. */
~~~

## Read the two scenarios together

The variables scenario copies a caller buffer, changes that buffer and verifies the owned value. It then passes a borrowed stored value into another setter call. The implementation prepares a candidate before mutating the owner, so overlapping input remains readable during preparation. Reacquire getter results after a mutation; this keeps client code correct if the internal representation changes later.

## A fixed array still needs admission

A public C structure can be malformed even when its storage is allocated. A count may exceed capacity, or an occupied character array may have no terminating zero. The invalid-variable scenario deliberately fills a value array without a terminator. The shared validator refuses it, lookup returns no value and rendering refuses before changing the supplied output. This is different from an unknown variable name in otherwise valid storage.

| Storage condition | Expected boundary |
| --- | --- |
| Valid name with empty value | An empty value is allowed |
| Unknown name in a valid set | Lookup returns no value |
| Unterminated occupied value | Validation refuses the owner |
| Full set replacing an existing name | Capacity alone need not forbid replacement |
| Full set adding another name | Append is refused |

## Extend the exercise

Add a local experiment that uses a value exactly one byte shorter than the public value capacity, leaving room for its terminator. Then try a value that needs one extra byte. Compare the complete variable set before and after the refused call. Do not truncate the value to hide the error: a truncated application identity can refer to a different application. Keep these experiments in a separate learner copy until their expected outcomes have been reviewed.

## Ownership is not concurrency control

Copying strings does not make simultaneous mutations safe. Route edits through the owning service or another explicitly serialized context. The revision is a bounded state indicator; it is not a lock or a timestamp. Record executed observations separately from your reasoning about the implementation. This lab supplies scenarios to run, not evidence that a particular SDK has passed them.

## Source and next steps

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Lab build and source guide](../../../labs/native/framework-project-recipes/README.md) · [Qualification record](../../../labs/native/framework-project-recipes/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/project-borrowed-recipes-owned-variables.html)
-->
[Lab build and source guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-project-recipes/README.md) · [Qualification record](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-project-recipes/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/project-borrowed-recipes-owned-variables.html)

[Previous lesson](project-select-a-catalogue-recipe.md) · [Course index](../../courses/umicom-development/index.html) · [Next lesson](project-application-identities.md)
