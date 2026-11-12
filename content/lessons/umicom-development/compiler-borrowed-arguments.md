<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/compiler-borrowed-arguments.md

PURPOSE:
Rebase borrowed argument views after copying a plan

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Rebase borrowed argument views after copying a plan

## See the two kinds of fields

A compiler plan owns its inline argument bytes. Its argument_view entries are pointers to those bytes. Copying the struct copies both the bytes and the pointer values, but the copied pointers still refer to the original plan until they are rebuilt. This is a general C ownership issue, not a compiler-specific language feature.


~~~c
UmiCompilerPlan copied = plan;
const char *const *view =
    umi_compiler_plan_arguments(&copied);
if (view == NULL) return UMI_STATUS_INVALID_STATE;
for (size_t index = 0; index < copied.argument_count; ++index) {
    /* view[index] points into copied.arguments[index]. */
}
~~~


## Validate owned storage without trusting cached pointers

Storage validation checks the inline strings and count. It deliberately does not dereference argument_view, because those cached pointers may still belong to another object after a value copy. The view accessor first admits the owned storage and then rebuilds each active pointer into the receiving plan.


Consume exactly argument_count entries. The pointer array has the same capacity as the argument array and does not promise an additional NULL sentinel. A process-launch API that requires a sentinel needs an explicitly sized adapter. Reading until NULL could continue beyond a full view even though every stored argument is valid.


## Keep publication and lifetime connected

Successful provider publication performs this rebasing before freeing its temporary plan. A successful incremental append also rebuilds active views. The views scenario checks that the published plan points into itself and that a later copy points into the copy after the accessor runs. Those are address-ownership checks, not comparisons of pointer numbers for display.


A borrowed view does not extend the plan lifetime. Do not keep it after destroying, replacing or concurrently mutating the owner. If an asynchronous process service needs longer ownership, use its established argument-copying contract rather than storing this pointer array indefinitely.


## Practice revision and lifetime reasoning

Run views, then revision. At UINT64_MAX a new argument is refused without modifying owner bytes, but the stored argument remains readable. Rebuilding a derived pointer cache does not create a new semantic argument revision. Explain why that distinction allows observation without authorizing another append.


For the exercise, sketch two plan objects and draw where each pointer goes before and after rebasing. Then describe a failure that equal argument text would not reveal: a view can print the expected text today while still borrowing storage that will be freed tomorrow. Address ownership and cleanup order are essential parts of the evidence.


## Source and practice

[Compiler ownership laboratory and owner commands](../../../labs/native/framework-compiler-ownership/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-borrowed-arguments.html)

[Previous lesson](compiler-plan-publication.md) · [Next lesson](compiler-installed-qualification.md) · [Course index](index.md)
