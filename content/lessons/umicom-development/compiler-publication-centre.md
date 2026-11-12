![Umicom](../../assets/branding/umicom-logo.svg)

# Preserve both owners when compiler planning is refused

## Find the publication boundary

A compiler centre combines a provider, profile, manifest and compilation database. Planning a unit appears to be one action in an application, but internally it has several possible failure points. A provider can refuse the request, policy arguments can exceed capacity, or the database can be unable to record the command. Publishing the output plan too early makes a failed operation look partly successful to the caller.



The transaction scenario first obtains an accepted plan, then exhausts the database revision and requests another directory. The request reaches a later publication boundary, where it must be refused. The lab compares all bytes of the centre and output with their previous snapshots. This is stronger than checking a count alone: unused storage and borrowed-pointer values must also survive a refused operation.



## Pass the project directory explicitly

~~~c
UmiStatus status = umi_compiler_centre_plan_unit_in_directory(
    centre, "project", "main", "C:/projects/example", &plan);
if (status != UMI_STATUS_OK) {
    /* Keep the previous plan and display the refusal. */
}
~~~



The directory is recorded in the returned plan and command entry. The service does not change the process directory or resolve filesystem paths. The older entry point remains available with a relative dot directory. That compatibility convention depends on the eventual executor’s location; an application should prefer explicit project ownership when it has that information.



## Stage before changing live state

Framework prepares a request and command entry in temporary heap storage. Provider and policy operations work on this candidate. The database service then admits and inserts or replaces the complete entry. Only after success does the centre publish the output plan and increment its revision. Argument views are rebuilt in each receiving owner, so they do not point into freed temporary storage.



This guarantee assumes serialized access. It is not a lock-free transaction, a disk journal or protection against process termination during a memory copy. The application must exclude concurrent readers and writers for the full call. Output storage also cannot be embedded inside the centre; that overlap is refused because it could corrupt the owner being updated.



## Practice

List every point at which the operation can still return failure. Mark the last fallible step and the copies that follow it. Explain why moving output publication before that step breaks the contract. Run the transaction case after installing the matching SDK, retain its diagnostic if it fails, and report memory-state preservation separately from compiler execution or crash recovery.



## Source and practice

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Compiler publication laboratory](../../../labs/native/framework-compiler-publication/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-publication-centre.html)
-->
[Compiler publication laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-compiler-publication/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-publication-centre.html)

[Previous lesson](compiler-publication-metadata-keys.md) · [Next lesson](compiler-publication-command-refresh.md) · [Course index](index.md)

Sammy Hegab · Umicom Foundation · MIT
