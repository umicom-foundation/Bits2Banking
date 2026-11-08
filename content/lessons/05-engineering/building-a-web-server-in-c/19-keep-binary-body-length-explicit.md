<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/19-keep-binary-body-length-explicit.md

PURPOSE:
Keep binary body length explicit

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep binary body length explicit

## Prepare

Build or read the incremental stream lab. Locate the body array containing A, zero and B. Review the difference between a byte span and a NUL-terminated C string before changing the example.

## Count the actual bytes

The array has three elements. Its middle zero is data, not an instruction to stop receiving the body. The header declares Content-Length: 3, and the stream remains BUSY until all three bytes have arrived. The parsed request also carries body_length, which must be used when copying or comparing the body.

~~~c
unsigned char body[] = {'A', 0U, 'B'};
/* sizeof(body) is 3; a string-length operation would not describe it. */
~~~

## Observe the expected result

Run btb-http-stream after a successful build. Its body line should report length 3 and hexadecimal bytes 41 00 42. This is an expected observation, not a recorded pass. The Framework many-fragments scenario also supplies arbitrary byte values in a larger body, including CR and LF.

## Preserve the representation

Do not route binary data through a helper that assumes a text string. If the application later interprets a form or JSON body, that is another parsing step with its own input rules. Transport framing establishes how many bytes belong to the message; it does not establish their application meaning.

## Exercise and worked answer

A learner copies request->body with a function that stops at the first zero and sees only A. Is the stream missing bytes? Inspect body_length and compare the three-byte span first. In this example the string operation discarded the rest. Use the explicit length and choose a representation appropriate for the intended content.

## Recover from disagreement

Keep the exact wire bytes, declared length, fragment sizes and resulting body length. A hex dump is clearer than a text screenshot when zeros are involved. Sanitize real request contents before publishing evidence. Repeating the same command without recording its byte inputs makes boundary failures hard to reproduce.

## Read the source

[labs/native/framework-http-contracts/stream.c](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/stream.c). Use the matching local revision when working offline.

## Continue learning

[Course contents](index.md) · [Previous: Scan new header bytes and reuse strict rules](18-scan-only-new-header-bytes.md) · [Next: Bound input and keep terminal errors visible](20-bound-input-and-terminal-errors.md)
