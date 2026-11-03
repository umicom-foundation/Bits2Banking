# Storage duration and freestanding code

A C declaration describes a value, but it also affects where the value lives and what work the compiler may generate to initialise it.

## Begin with a real Kernel table

The Kernel console's `abi` command prints labelled metadata. In `kernel/console_shell.c`, each table row associates a label with a selector:

```text
static const struct {
    const char *label;
    UmicomU64 selector;
} fields[] = {
    {"abi.word-bits=", UMICOM_USER_ABI_QUERY_WORD_BITS},
    {"abi.page-bytes=", UMICOM_USER_ABI_QUERY_PAGE_BYTES}
};
```

This extract shows two rows from the larger table. A structure groups fields; an array stores several structures of the same type. `const char *` lets the program read label characters through the pointer without modifying them through that pointer.

## Understand two independent words

`const` restricts modification through the declared object. It does not by itself give the object permanent storage. `static` on this block-scope declaration gives the table static storage duration: the object exists for the program's lifetime, not only for the current function call. The name is still visible only within its block.

 <svg viewbox="0 0 700 110" role="img" aria-label="The console reads the same table rather than initialising a fresh automatic aggregate for each invocation." style="width:100%;max-width:700px"><title>The console reads the same table rather than initialising a fresh automatic aggregate for each invocation.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Immutable table</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Static storage</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Read on each command</text></svg>

The console reads the same table rather than initialising a fresh automatic aggregate for each invocation.

Without `static`, an ordinary local table has automatic storage duration. Its lifetime begins when execution reaches its declaration and ends when its block exits. Implementations commonly place such objects on the call stack, although C specifies lifetime rather than a particular physical stack layout.

## Read what the compiler needs

A compiler can initialise an aggregate by copying bytes from constant data. Depending on its target and optimisation settings, it may emit a call to `memcpy` even when the source does not contain that function name. A hosted application normally links supporting runtime libraries. A freestanding Kernel using `-nostdlib` does not automatically provide them.

That is why a file may compile but fail when linked. Compiling translates a source file into an object; linking combines objects and resolves referenced symbols. “Undefined symbol: memcpy” means a reference had no linked definition. Adding a random host library is not a correct Kernel fix.

## Choose storage to match ownership

The console table is fixed metadata: all callers should read the same contents. Static const storage fits that ownership. A mutable scratch buffer would need different reasoning. Making every local variable static could accidentally share state across callers, break reentrancy and preserve data longer than intended.

A **reentrant** operation can be entered again before an earlier call finishes, for example through a callback. Shared mutable storage needs an explicit design; changing storage duration is not a universal performance trick.

## Work through the decision

1. List which fields change after initialisation. For this table, none do.
2. Ask whether each invocation needs a private copy. Here, it does not.
3. Compile and link the actual freestanding debug target, not only a hosted example.
4. Inspect failures under the supported optimisation profiles too. One successful optimisation setting cannot prove another needs no runtime helper.

## Exercise

Would a static array be a good default for a function that builds a different person's editable document on every call?

<details>

<summary>Answer</summary>

No. Those documents need independent ownership and lifetimes. Reusing one shared mutable array could mix callers' state. The Kernel table is suitable because it is immutable metadata, not because static is always safer.

</details>

## Read the source

Open [umicom-kernel/kernel/console_shell.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/console_shell.c) to compare the explanation with the current source. Repository contents can change; use the commit shown by GitHub when recording your observations.

[Words explained](../../courses/learning-c/glossary.html) · [Practical lab guide](../../courses/learning-c/practical-guide.html) · [Connected learning routes](../../courses/learning-paths.html)

---

[Read this lesson in HTML](../../courses/learning-c/lessons/14-storage-duration-and-freestanding-code.html) · [Learning sequence](../../start/learning-sequence.md)

## Continue this module

Further study: systems programming · Lesson 3 of 6.

[Previous: Pass a function to separate policy from mechanism](13-function-pointers-and-test-doubles.md) · [Next: Keep counts, offsets and progress separate](16-counts-offsets-and-progress.md)
