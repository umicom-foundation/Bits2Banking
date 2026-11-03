# C interfaces and ownership across languages

Follow a request from a window to a shared service, and learn how C interfaces connect native components.

Lesson 2 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **header** is a source file describing names and types other source files may use. An **implementation** contains the instructions behind those names. A compiler translates source into machine instructions; a linker connects references between translated files. Two files can compile separately and still fail to link if a requested function has no matching definition.

A C **pointer** refers to a location in memory. It does not by itself say who owns that memory or how long it remains valid. An **opaque handle** is a pointer to a type whose internal fields are hidden from callers. Framework's learning-pack API uses this arrangement to keep the pack's internal representation private.

```text
caller creates handle → reads through public functions → destroys handle
                         internal fields stay private
```

`UmiLearningPackCreate` returns an admitted pack through an output pointer. Its contract says it copies metadata. The input JSON can therefore be released after the call returns. `UmiLearningPackDestroy` ends the pack's lifetime. A later access through the old handle is invalid even if the address still looks plausible.

A **C ABI**, or application binary interface, is the compiled calling agreement. C++ and Java integrations need more than similar syntax: types, sizes, calling convention, error handling and ownership must agree. Do not expose a C++ container or a Java object as though it were a portable C structure. Use a narrow adapter and explicit conversion. Java's runtime-managed objects also require a real interoperation mechanism; writing a C-looking declaration alone is insufficient.

## Work through a lifetime

1. Write “JSON input” and “pack handle” on separate lines.
2. After successful creation, cross out the input line. The copied metadata remains available.
3. After destruction, cross out the handle line too.
4. Mark every read after that point as a bug. Moving a window or changing a tab cannot extend the handle's lifetime.

This source-reading activity needs no compiler. When later writing code, check the status before using an output and release each owned resource exactly once.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\teacher\learning_pack.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef enum UmiLearningResourceKind {
    UMI_LEARNING_RESOURCE_LESSON = 1,
    UMI_LEARNING_RESOURCE_GUIDE = 2,
    UMI_LEARNING_RESOURCE_EXAMPLE = 3,
    UMI_LEARNING_RESOURCE_IMAGE = 4
} UmiLearningResourceKind;

typedef struct UmiLearningPackInfo {
    char id[UMI_TEACHER_ID_CAPACITY];
    char title[UMI_TEACHER_TEXT_CAPACITY];
    char product[UMI_TEACHER_ID_CAPACITY];
    char locale[UMI_LEARNING_PACK_LOCALE_CAPACITY];
    uint64_t revision;
    UmiVersion minimum_version;
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Read Create, Clone, ReadResource and FreeBytes. Make a two-column list of each returned object and the function responsible for releasing it.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Can a checksum make a dangling pointer safe?

### Worked answer

No. A checksum checks bytes under defined conditions. A dangling pointer refers to storage whose lifetime has ended. Correct ownership and lifetime rules must come first.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/framework-boundaries/lessons/native-boundaries.html) · [Learning sequence](../../../../start/learning-sequence.md)
