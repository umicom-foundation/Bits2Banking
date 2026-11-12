![Umicom](../../assets/branding/umicom-logo.svg)

# Report unsupported compiler policy without weakening it

## Separate requested intent from supported spelling

A policy records intent, such as treating warnings as errors or enabling a sanitizer. A driver dialect defines how to request that behavior. Choosing the right text still does not establish that an installed compiler version, target and runtime support it. A dependable application keeps these layers visible instead of translating every unfamiliar family through the same GNU-style arguments.



The Framework policy service currently maps C and C++ compile plans for GCC, Clang and MSVC. Other languages, families and actions are refused by this service. Provider syntax-check planning remains a separate path; its existence does not mean code-generation policy is automatically meaningful for checking. Set plan metadata before composing policy and handle NOT_IMPLEMENTED as an explicit capability result.



## Inspect the result before presenting success

~~~c
plan.language = UMI_COMPILER_LANGUAGE_C;
plan.action = UMI_COMPILER_ACTION_COMPILE;
UmiCompilerPolicy policy = umi_compiler_policy_debug();
policy.sanitizers = UMI_COMPILER_SANITIZER_ADDRESS;
UmiStatus status = umi_compiler_policy_append_arguments(
    &policy, UMI_COMPILER_FAMILY_MSVC, &plan);
~~~



The policy scenario checks the MSVC address-sanitizer spelling in the resulting argument data, then requests an unsupported sanitizer and compares the previous plan bytes. This demonstrates mapping and refusal, not sanitizer execution. Runtime libraries, compatible compiler options and linker configuration require separate qualification. The lab deliberately uses no driver process.



## Preserve an unsupported requirement

Reproducible output needs more than a convenient compiler flag. Paths, timestamps, dependencies, environment and toolchain identity can affect bytes. Framework retains reproducible intent in the release-policy factory but currently refuses to append it because the service lacks a complete reproducibility contract. Clearing the field automatically would hide a requirement. An application should report the limitation and let an explicit workflow decide whether a different policy is acceptable.



Atomic composition preserves the old plan when any requested mapping is refused or when a later append reaches capacity. It does not promise that an accepted plan will build everywhere. Some accepted switches remain target dependent, and compilation policy does not configure all linker or runtime requirements. The exact mapping tests and real toolchain experiments therefore belong to different qualification layers.



## Practice

Design three status messages: a policy dialect was accepted, a requested intent is unsupported, and a compiler execution failed. State what evidence each message requires. Run the policy scenario after qualifying the installed SDK, then write down the missing evidence for an actual sanitizer-enabled application. Keep the application’s requested policy intact while reporting the current support boundary.



## Source and practice

[Compiler publication laboratory](../../../labs/native/framework-compiler-publication/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-publication-policy.html)

[Previous lesson](compiler-publication-command-refresh.md) · [Course index](index.md)

Sammy Hegab · Umicom Foundation · MIT
