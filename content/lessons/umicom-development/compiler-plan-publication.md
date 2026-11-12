<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/compiler-plan-publication.md

PURPOSE:
Publish a compiler plan only after every argument is accepted

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Publish a compiler plan only after every argument is accepted

## Follow a later failure

A provider translates an admitted request into a command description. Preparing the first argument does not mean the complete plan will fit. A long source path, a formatted definition or the total number of options may fail after earlier entries have been prepared. A client still needs its previous accepted plan when that happens.


The publication scenario begins with a plan containing the argument previous. It then uses a properly terminated source path that fits the request but exceeds one plan argument. Framework prepares the new plan privately and returns CAPACITY_EXCEEDED. The client checks the complete previous plan before printing the expected observation.


~~~c
UmiStatus status = umi_compiler_provider_plan(
    &provider, &request, &plan);
if (status != UMI_STATUS_OK) {
    /* plan still contains the previously accepted value. */
    return status;
}
~~~


## Choose a publication boundary that owns cleanup

The provider allocates a temporary plan because its inline argument matrix is large. Every provider-specific argument step writes there. If any step fails, Framework frees the candidate and returns the original failure status. Only a complete accepted plan is copied into the destination. Allocation failure also leaves the destination unchanged.


This is failure isolation, not thread synchronization. The caller still keeps its input records readable and serializes access while planning and publication occur. A second thread mutating the request between validation and consumption would violate the contract even though the destination uses a temporary candidate.


## Distinguish a plan from an executed command

The existing provider mapping is retained. The planner can describe compiler arguments without starting a process. Recognition of an action enum does not establish that every provider implements linking, archiving or syntax-check behavior. Keep those capabilities tied to their own mappings and tests instead of inferring them from an OK metadata result.


## Practice failure preservation

Run publication and inspect the source that creates the long path. Explain why this is a late failure rather than a malformed count. Then propose a second fixture where each option is individually short but their aggregate exceeds the plan argument capacity. State which prior values must remain readable after refusal.


For the review exercise, compare a temporary plan with a plain struct copy that contains internal pointers. The temporary publication approach needs one extra step before cleanup: rebuilding every borrowed argument pointer in the receiving owner. Copying bytes alone cannot establish that lifetime. The next lesson demonstrates the receiving object explicitly.


## Source and practice

[Compiler ownership laboratory and owner commands](../../../labs/native/framework-compiler-ownership/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-plan-publication.html)

[Previous lesson](compiler-request-composition.md) · [Next lesson](compiler-borrowed-arguments.md) · [Course index](index.md)
