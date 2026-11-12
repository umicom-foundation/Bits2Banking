![Umicom](../../../assets/branding/umicom-logo.svg)

# Distinguish a stored profile from a usable compiler

A toolchain profile records what an application knows about compilers and related tools. The record can describe a successful discovery, a missing executable or a failed probe. Saving that information is useful even when the tool cannot build anything. This lesson separates a well-formed record from evidence that a selected compiler is usable.

## Read the named state

An enumeration gives names to a finite set of states. Its numeric order is not a quality ranking. A condition such as state greater than or equal to FOUND can accidentally admit FAILED if FAILED has a larger numeric value. Read the contract and match the named states that the operation actually supports.

~~~c
if (tool->state != UMI_TOOL_FOUND && tool->state != UMI_TOOL_VALIDATED)
    return UMI_STATUS_UNAVAILABLE;
~~~

This fragment illustrates admission at a compiler bridge; it is not a standalone discovery function. The bridge also checks the selected kind and bounded text. FOUND and VALIDATED are admitted metadata, not fresh proof that a driver still exists. Another program could replace an executable after discovery.

## Check storage before interpreting it

umi_toolchain_profile_storage_valid checks record compatibility, fixed-string termination and declared known tool slots. A fixed string needs a terminating zero inside its array. Without that bound, ordinary string functions can read beyond the object. The validator accepts empty draft fields and explicit FAILED states. Catalogue insertion additionally requires a nonempty identifier.

## Work through the lab

- Open the Storage function in the shared lab source. MakeProfile creates synthetic metadata; it does not run a compiler.
- Observe that FAILED remains valid storage. Conversion to a compiler profile returns UNAVAILABLE and leaves the receiving bytes unchanged.
- Inspect the final case, which fills display_name with nonzero bytes. Explain why this is malformed storage even though the tool state has a recognized name.

## Exercise and review

Write a two-column decision table: can this record be stored, and can this selected tool be converted? Include an empty draft, a failed selected compiler, a terminated path and an unterminated display name. A useful answer gives different decisions for the failed tool: its history is representable, but it cannot supply a usable compiler selection. Keep that distinction in status messages and regression checks.

## Source and practice

Use the [installed C23 lab guide](../../../../labs/native/framework-toolchain-selection/README.md) and [complete source](../../../../labs/native/framework-toolchain-selection/main.c). The examples are authored; no build or execution result is implied.

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Investigate command failures through focused regression checks](17-command-planning-regression-lab.md) · [Next: Prepare a child environment without changing the parent shell](19-child-environments-and-path.md)

[HTML lesson](../../../courses/learning-build-systems/lessons/18-profile-storage-and-tool-usability.html)

Sammy Hegab · Umicom Foundation · MIT
