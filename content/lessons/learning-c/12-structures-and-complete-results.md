# Group related values in a structure

Use the actual Kernel contract record to learn how C keeps related values together.

## 1. Why separate variables become hard to follow

A program discovering its environment receives several answers: version, available service routes, word width, byte order, page size and request limits. Seven unrelated variables can be mixed up when passed between functions. A **structure**, written `struct`, gives related fields one named type. Each field still has its own name and type.

```text
typedef struct UmicomUserContract {
    UmicomU64 version;
    UmicomU64 features;
    UmicomU64 wordBits;
    UmicomU64 byteOrder;
    UmicomU64 pageBytes;
    UmicomU64 copyLimit;
    UmicomU64 callLimit;
} UmicomUserContract;
```

This is the definition in `include/umicom/user/native_contract.h`. `typedef` introduces the shorter name `UmicomUserContract`. It does not allocate a record. The declaration `UmicomUserContract value;` creates an object with these fields.

## 2. Read one field

`value.copyLimit` selects a field from an object. The dot connects the object name and field name. If you have a pointer named `outContract`, `outContract->copyLimit` accesses that field through the pointer. The pointer must refer to a live object; the arrow does not check ownership for you.

## 3. Do not publish half an answer

The real reader, `programs/support/native_contract.c`, first fills a local record and validates it. It copies fields to the caller's record only after every required answer is acceptable. On refusal, the caller's existing bytes remain unchanged. This is an all-or-nothing result contract for this synchronous function, not a general thread-safe atomic operation.

 <svg viewbox="0 0 700 110" role="img" aria-label="The caller receives a complete result only after validation succeeds." style="width:100%;max-width:700px"><title>The caller receives a complete result only after validation succeeds.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Collect replies locally</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Check every required field</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Publish the complete record</text></svg>

The caller receives a complete result only after validation succeeds.

## 4. Observe the failure test

`tests/native_contract/contract_tests.c` fills an output record with a known byte value, keeps a copy and supplies an invalid reply. It checks that the function reports an error and that every output byte still matches the copy. That catches a function which reports failure after already overwriting part of the answer.

## 5. Avoid treating structures as file formats

C may place padding between fields for alignment. Alignment describes where a type may be placed in memory. A structure's in-memory bytes are not automatically a portable network message or disk format. Umicom's ABI discovery sends scalar register values and constructs a local C record; it does not transmit this structure's raw bytes.

## Exercise

A reader receives version and page size successfully but the final limit query is unavailable. Should it update two fields and return an error, or leave the previous output intact?

<details>

<summary>Answer</summary>

This API promises unchanged output on failure, so it must leave the entire output intact. Another API could document a partial-result design, but callers must not be forced to guess which design applies.

</details>

Continue to [function pointers](13-function-pointers-and-test-doubles.md) to see how the same reader is tested without starting a Kernel.

## Read the source

Open [umicom-kernel/include/umicom/user/native_contract.h](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/user/native_contract.h) to compare the explanation with the current source. Repository contents can change; use the commit shown by GitHub when recording your observations.

[Words explained](../../courses/learning-c/glossary.html) · [Practical lab guide](../../courses/learning-c/practical-guide.html) · [Connected learning routes](../../courses/learning-paths.html)

---

[Read this lesson in HTML](../../courses/learning-c/lessons/12-structures-and-complete-results.html) · [Learning sequence](../../start/learning-sequence.md)

## Continue this module

Working with more information · Lesson 2 of 4.

[Previous: Keep several values in an array](09-arrays-and-valid-positions.md) · [Next: Let a function read memory you still own](10-pointers-and-borrowing.md)
