# Keep counts, offsets and progress separate

A small file-reading loop shows why three integers with similar types can mean different things. Read the code with a table of values before trying to change it.

## What you need

Review [arrays](09-arrays-and-valid-positions.md), [borrowed memory](10-pointers-and-borrowing.md) and [results and errors](07-check-results-and-errors.md). You need no finance or operating-system knowledge. An integer is a whole number; a byte is a unit of stored data; a buffer is memory reserved to hold bytes temporarily.

## One type, several meanings

The Kernel uses `UmicomSize` for byte counts and positions. Sharing a C type does not make the meanings interchangeable.

| Name | Question it answers |
| --- | --- |
| `offset` | How many file bytes precede the starting position? |
| `bytes` | How many bytes did the command request in total? |
| `total` | How many real bytes have arrived so far? |
| `got` | How many bytes arrived in this one operation? |

 <svg viewbox="0 0 700 110" role="img" aria-label="Request size is a limit. Progress counts only the bytes actually returned." style="width:100%;max-width:700px"><title>Request size is a limit. Progress counts only the bytes actually returned.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">requested: 600</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">received: 256</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">remaining: 344</text></svg>

Request size is a limit. Progress counts only the bytes actually returned.

## Read the loop boundary

The real [console range implementation](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/console_file_range.inc) contains this calculation:

```text
while (total < bytes) {
    const UmicomSize remaining = bytes - total;
    const UmicomSize requested =
        remaining < sizeof(shell->io) ? remaining : sizeof(shell->io);
    /* Read at most requested bytes, then inspect both status and got. */
}
```

`while` repeats only while its condition is true. The comparison ensures `bytes - total` cannot become a negative mathematical result before subtraction. The `?:` expression selects its middle expression when the comparison is true and its last expression otherwise. Here it chooses the smaller of the remaining request and the buffer's capacity.

`shell->io` means the `io` member of the structure reached by the `shell` pointer. It is a 256-byte array. `sizeof` obtains that array's byte size; it is not the current file length. This explanation applies to the actual array member. Applying `sizeof` to an ordinary pointer instead measures the pointer itself.

## Trace a successful request

| Iteration | Total before | Remaining | Requested now | Returned now | Total after |
| --- | --- | --- | --- | --- | --- |
| 1 | 0 | 600 | 256 | 256 | 256 |
| 2 | 256 | 344 | 256 | 256 | 512 |
| 3 | 512 | 88 | 88 | 88 | 600 |

The starting offset might be 1000. The next offset is then 1000 + 600 = 1600. Counts and offsets use the same units here but answer different questions. Do not add the requested count if fewer bytes arrived.

## A failure can follow useful progress

A storage provider may return three bytes and an error. The range command displays those three bytes, adds three to progress, stops and reports the error. It does not claim all requested bytes were read. It does not silently retry: repeating an operation may have consequences for other providers, and the error may need investigation.

An OK result with zero returned bytes ends this loop. Without that stopping rule, a loop below EOF could keep requesting the same empty response forever. Conversely, a short positive response is not automatically an error. Always read the provider's contract.

## Prove an addition is bounded

The console admits offsets no larger than 131072 and requests no larger than 4096. Each read must return no more than requested. Therefore `offset + total` stays at most 135168, far below the RV64 integer limit. This is a proof based on earlier checks, not a reason to assume all additions are safe.

In [the real tests](https://github.com/umicom-foundation/umicom-kernel/blob/main/tests/console_shell/range_cases.inc), a provider deliberately returns a partial result with an error. Other tests cross a page boundary, stop at EOF and verify that the original 5000-byte file is unchanged.

## Exercises with answers

1. Starting offset 40, requested count 100, actual count 12: what is next? **52**, not 140.
2. Remaining count 7, buffer size 256: request how much? **7**.
3. Returned count zero and no error: keep looping? **No**; stop according to this reader's EOF contract.
4. Why check `got > requested`? **To detect a broken provider contract before treating an oversized count as valid progress.** That check cannot undo a provider that already wrote outside memory; providers must also enforce their own bounds.

Try the [Kernel file-range exercise](../06-umicom/umicom-kernel-from-scratch/13-read-file-ranges.md) after preparing its environment, or repeat these calculations on paper.

## Check a partial read

You begin at byte offset 1000 and ask for 600 bytes. The first read returns 256 bytes. The second returns 20 bytes and an error. What progress can the command report, and should it issue a third read?

<details>

<summary>Work through the answer</summary>

The actual progress is 256 + 20 = 276 bytes. The next offset would be 1000 + 276 = 1276. The command stops because the second read reported an error, even though it returned useful bytes. Reporting 600 bytes would confuse the requested amount with the completed amount. A later retry must be an explicit decision based on the provider contract.

</details>

## Read the source

Open [umicom-kernel/kernel/console_file_range.inc](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/console_file_range.inc) to compare the explanation with the current source. Repository contents can change; use the commit shown by GitHub when recording your observations.

[Words explained](../../courses/learning-c/glossary.html) · [Practical lab guide](../../courses/learning-c/practical-guide.html) · [Connected learning routes](../../courses/learning-paths.html)

---

[Read this lesson in HTML](../../courses/learning-c/lessons/16-counts-offsets-and-progress.html) · [Learning sequence](../../start/learning-sequence.md)

## Continue this module

Further study: systems programming · Lesson 4 of 6.

[Previous: Storage duration and freestanding code](14-storage-duration-and-freestanding-code.md) · [Next: Represent bytes with bits and hexadecimal](17-bits-and-hexadecimal.md)
