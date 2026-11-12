<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/compiler-record-ownership.md

PURPOSE:
Construct compiler metadata without losing the previous value

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Construct compiler metadata without losing the previous value

## Start with values rather than processes

A compiler target is a description, not a running compiler. Its fields identify an architecture, an operating system and an object format. An ABI profile adds metadata about calling and representation conventions. These descriptions are useful to a project editor before any external tool is started. Framework owns their construction and compatibility policy so the CLI and native application do not invent different rules.


Before this lesson, review C structures, pointers, array bounds and terminating zero bytes. Read TargetAlias and AbiAlias in the laboratory. The client supplies a real target string and checks every status. It does not assume that a successful metadata operation proves that an SDK is installed or a binary can be linked.


## Keep the accepted value until replacement succeeds

~~~c
UmiCompilerTarget target;
UmiStatus status = umi_compiler_target_parse(
    "x86_64-unknown-linux-gnu", &target);
if (status != UMI_STATUS_OK) return status;
status = umi_compiler_target_parse("unfinished", &target);
/* The previous accepted target remains after PARSE_ERROR. */
~~~


The initializer prepares a temporary record and publishes it only after parsing succeeds. This gives an editor a useful failure contract: an incomplete replacement cannot destroy the last accepted configuration. The temporary record is small enough for local storage; larger Framework constructors use temporary heap storage for the same publication principle.


## Recognize when an input belongs to the output

Calling the parser with target.triple as its input creates an alias. If the initializer clears target before reading that string, it also destroys its own input. Staging consumes the input first. The ABI example exercises two aliases at once: profile.abi_id and profile.target both belong to the destination profile. Both must survive until the replacement is ready.


~~~c
status = umi_compiler_abi_init(
    &profile, profile.abi_id, UMI_COMPILER_ABI_CPP,
    &profile.target);
~~~


## Practice and state the limit

Run the target and abi scenarios after building the matching installed client. Explain why a failed replacement can be a successful laboratory observation. Then identify which bytes must remain unchanged when the target is incomplete. Compare that requirement with merely checking that the function returned an error.


For a written exercise, distinguish metadata compatibility from demonstrated interoperability. The current target comparison checks its established architecture, operating-system, format and pointer-width fields. It does not newly qualify every environment or vendor distinction. A real cross-toolchain project needs compiler, linker and runtime evidence in addition to this bounded description.


## Source and practice

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Compiler ownership laboratory and owner commands](../../../labs/native/framework-compiler-ownership/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-record-ownership.html)
-->
[Compiler ownership laboratory and owner commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-compiler-ownership/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-record-ownership.html)

[Previous lesson](ui-values-installed-qualification.md) · [Next lesson](compiler-catalogue-admission.md) · [Course index](index.md)
