<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/02-choose-target-operations.md

PURPOSE:
Choose target operations before dispatch

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Choose target operations before dispatch

An **adapter** connects a test runner to one kind of fixture. A desktop adapter and a device adapter can implement different operations. The runner checks the declared contract before requesting any work.

## Read the mask one bit at a time

A bit mask stores multiple yes-or-no settings in one integer. In Framework’s test target header, the `UmiUatOperation` values are separate bits. The owner’s allowed mask and the adapter’s supported mask answer different questions.

| Gate | Question it answers |
| --- | --- |
| Protocol | Do the request and adapter use the required contract version? |
| Binding | Do the target, session and platform identify the same fixture? |
| Permission | Has the owner allowed the operation? |
| Capability | Does the selected adapter implement that operation? |
| Plan | Are all workflow rows valid together? |

A capability can exist while the owner has excluded it from a given fixture. A permitted capability can still be unavailable in an adapter. Check both facts.

~~~c
const uint32_t allowed = UMI_UAT_UI_OBSERVE | UMI_UAT_WORKFLOW;
const uint32_t supported = UMI_UAT_UI_OBSERVE;
const bool agrees_on_workflow = (allowed & supported & UMI_UAT_WORKFLOW) != 0U;
~~~

Both `&` and `|` operate on integer bits. Here `agrees_on_workflow` is false because the support mask excludes the workflow operation.

~~~asm
# An x86 test sets flags from the masked value without storing the result.
testl $4, %eax
~~~

The bit value 4 models the workflow flag at bit position two. In actual C source, use the named Framework constant so the expression stays tied to the header.

## Inspect the callback-free preview

Open `include/umicom/testing/uat_target.h` in Umicom Framework. Find `UmiUatCheckTargetAdmission` and `UmiUatTargetAdmission`. The latter stores the first blocking gate. When an operation row blocks the plan, it stores the row’s zero-based index and its observed operation. Other gates use `SIZE_MAX` as the absent row marker.

1. Compare the request protocol to `UMI_UAT_TARGET_PROTOCOL`.
2. For a workflow refusal, identify the row number in the plan. Index zero means the first row.
3. Change the adapter's supported mask in an in-memory exercise and predict the new outcome before you rerun it.
4. Check that the fixture operation count remains zero when you only request the preview.

The preview tells you about the declared plan and adapter contract. A later test can collect environment readiness and execution results. Keep those records in separate columns so a successful preview does not become a passing test result.

[Course contents](index.md) · [Previous lesson · Write the expected result](01-write-the-expected-result.md) · [Next lesson · Check a workflow and its cleanup](03-check-a-workflow-and-cleanup.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/02-choose-target-operations.html) · [Native C23 lab source](../../../labs/native/automated-testing-preview/main.c) · [SDK build description](../../../labs/native/automated-testing-preview/CMakeLists.txt)
