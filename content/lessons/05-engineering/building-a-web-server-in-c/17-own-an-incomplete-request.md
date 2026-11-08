<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/17-own-an-incomplete-request.md

PURPOSE:
Own an incomplete request across reads

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Own an incomplete request across reads

## Prepare

Complete the framing and exchange labs from lessons 9–16. Install a matching Framework SDK that includes umicom/web/request_stream.h. Open stream.c in labs/native/framework-http-contracts. Build with the README commands only when your toolchain and SDK are ready; reading the ownership diagram needs no running server.

## Give partial input an owner

A transport buffer may be reused after each read. The new UmiWebRequestStream copies fed bytes into its own bounded allocation, so the caller can reuse that temporary input. The stream remains owned by one thread until destroyed. An incomplete request is ordinary state, represented by BUSY, rather than an empty successful request.

~~~c
UmiWebRequestStream *stream = NULL;
UmiStatus status = UmiWebRequestStreamCreate(1024U, &stream);
/* Check status before feeding any bytes. */
~~~

## Follow the lab

The program first feeds a complete header declaring a three-byte body. Inspect reports the received header size and expected total, but the status remains BUSY. The program feeds A, changes its original buffer to X, then feeds NUL and B. Parsing must still produce A, NUL, B because the earlier byte was copied.

## Keep two lifetimes separate

The stream owns wire bytes. UmiWebRequestStreamParse produces a separate caller-owned UmiWebRequest through the existing strict parser. Destroying the stream does not invalidate that parsed value. The lab allocates the large request structure on the heap so a small thread stack need not hold it.

## Exercise and worked answer

After Feed returns BUSY, may the caller overwrite its input array? Yes, the bytes supplied by that successful bounded feed have been copied. May it destroy the stream and then continue feeding through the old pointer? No, the owner has released the object. Draw separate boxes for the temporary array, stream allocation and parsed request.

## Recover with the right evidence

If the owned body unexpectedly changes, keep the exact feed sequence and inspect whether the application accidentally reused a borrowed pointer elsewhere. If the new API fails to link, check that the installed library matches the header. Do not implement a second accumulator in the lab to conceal an SDK mismatch.

## Read the source

[labs/native/framework-http-contracts/stream.c](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/stream.c). Use the matching local revision when working offline.

## Continue learning

[Course contents](index.md) · [Previous: Distinguish dispatch from delivery](16-distinguish-dispatch-from-delivery.md) · [Next: Scan new header bytes and reuse strict rules](18-scan-only-new-header-bytes.md)
