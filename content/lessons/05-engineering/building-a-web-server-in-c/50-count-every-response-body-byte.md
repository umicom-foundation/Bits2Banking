<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/50-count-every-response-body-byte.md

PURPOSE:
Count every response body byte

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Count every response body byte

A response body is the data that follows the HTTP headers. Some bodies contain a byte with the value zero. This lesson follows a three-byte body through Umicom Framework’s response formatter. You can do the whole exercise on paper.

## 1. Count the bytes in the C array

Here are the exact three practice bytes.

~~~c
static const unsigned char payload[] = {'a', 0U, 'c'};
~~~

Draw three squares. Write `a` in the first, numeric zero in the second and `c` in the third. In the fixture’s byte encoding they are `61 00 63` in hexadecimal. Hexadecimal gives a compact way to write each byte using two digits. The middle value is a **zero byte**, also called **NUL**. The character `'0'` would be a different byte.

C text strings use a zero byte as the end marker. A text-length operation on these bytes would stop after the first character. A **counted body** carries its own length. In this C array, `sizeof payload` is three because every `unsigned char` occupies one byte. The counted copy keeps all three, including the zero in the middle.

In Umicom Framework, `UmiWebResponseSetBodyBytes` copies the requested bytes into the response’s inline body. **Inline** means the storage is inside the response object. The function places its own zero byte immediately after the copied bytes. That extra marker occupies storage and stays outside the three-byte body.

## 2. Read the headers and the returned byte count

The saved practice response already had status `201 Created`, media type `application/octet-stream`, and the example header `X-Demo: unchanged`. These fields are **metadata**. They describe the response and its data. Changing the inline bytes keeps those fields, including the chosen status. The fixture chooses 201 so you can see what survives a body change.

Here are the header lines from the closed-connection format. The fixture uses HTTP’s carriage-return and line-feed bytes after each line. The empty line ends the header section.

~~~text
HTTP/1.1 201 Created
Content-Type: application/octet-stream
X-Demo: unchanged
Content-Length: 3
Connection: close
~~~

| Formatter exercise | Content-Length in the header | Bytes after the header section |
| --- | --- | --- |
| Body included | 3 | `61 00 63` |
| HEAD, headers only | 3 | None |

If a HEAD response supplies `Content-Length`, that number describes what the corresponding GET would transfer as content. HEAD sends no body. The value is still 3 here because the selected body contains three bytes. The formatter also returns an output count for the complete formatted buffer. In the exercise, that returned count is three bytes smaller for HEAD because it ends at the header boundary.

`UmiWebResponseFormatClosed` takes a Boolean flag for this choice. `false` includes the inline body and `true` emits the headers only. Read the returned status and use the returned output count on success. A counted result can contain zero bytes inside the part you need.

## 3. Check a refusal before using a new result

Start again with the same response and ask for one byte while giving the setter a null pointer. A **null pointer** here means there is no input storage to read. The result is `UMI_STATUS_INVALID_ARGUMENT`. The old body, status and headers stay in place.

A byte array has a fixed number of slots. The inline setter reserves one slot for its trailing marker. The largest payload it accepts is `UMI_WEB_BODY_CAPACITY - 1` bytes. Asking for the full array capacity gives `UMI_STATUS_CAPACITY_EXCEEDED` and leaves the old response intact. A zero-length request can use `NULL` and clears the inline body on success.

~~~text
COPY exactly the requested bytes into the inline body if the arguments are valid
CHECK the returned status before using a new body
FORMAT with the selected response method
CHECK the formatter status before using the returned byte count
~~~

## 4. Follow the body that has its own lifetime

A handler can also use a separate owned body. **Ownership** means the caller is responsible for holding that object while it is needed and releasing it when finished. The saved exercise creates an owned body containing the three bytes `x`, zero and `y` with `UmiWebResponseBodyCreate`. It is a separate object from the inline storage.

1. With the inline body empty, format the headers for the owned body’s three-byte length using `UmiWebResponseFormatClosedHeaders`.
2. Set the inline body to two bytes, `a` and `b`. The owned object still contains its original three bytes. If you now ask to format headers for the owned body, the formatter refuses the mixed choice with `UMI_STATUS_INVALID_ARGUMENT` and gives an output length of zero. Use neither the previous header bytes nor an assumed new response as the result of this call.
3. Choose the owned body for this exercise. Clear the inline body with `UmiWebResponseSetBodyBytes(response, NULL, 0U)`. The owned body keeps its bytes while you format the headers again. Release the owned object with `UmiWebResponseBodyDestroy` when the caller has finished using it.

For a WebServer or Framework application response, write down which object owns the bytes, the length that belongs to that object, and whether the method includes the body. The exercise checks data and formatting in memory. A deployed request has its own test evidence.

[HTTP Semantics on Content-Length](https://www.rfc-editor.org/rfc/rfc9110.html#section-8.6) · [HTTP Semantics on HEAD](https://www.rfc-editor.org/rfc/rfc9110.html#section-9.3.2)

[Course contents](index.md) · [Previous lesson · Read status codes before deciding what to do](49-read-status-codes-before-deciding.md) · [Related lesson · Check export and download headers](48-check-export-and-download-headers.md) · [Related lesson · Read a FastCGI reply before forwarding](41-read-a-fastcgi-reply-before-forwarding.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/50-count-every-response-body-byte.html)
