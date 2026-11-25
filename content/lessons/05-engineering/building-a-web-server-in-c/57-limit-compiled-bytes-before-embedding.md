<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/57-limit-compiled-bytes-before-embedding.md

PURPOSE:
Limit compiled bytes before embedding

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Limit compiled bytes before embedding

Imagine putting a stack of cards into a box that holds 4,096 cards. Count only until you know whether the stack fits. Looking at one more card than the box can hold gives you enough information to refuse a longer stack.

## 1. Find the two checks in the WebServer build

The local Umicom WebServer can embed a compiled Umicom C application into its own executable. **Embedding** means putting those bytes in a generated C header so the server and browser route can use the same contents. During configuration, the current browser example accepts a file from one byte through 4096 bytes.

First the configure step checks the selected file and its reported size. The shared initializer then reads the file and produces the C bytes. A file can change after the first size check. The initializer therefore reads at most 4097 bytes and compares the number it actually received with the 4096-byte budget.

| Bytes seen by the bounded read | Decision |
| --- | --- |
| 0 | Refuse an empty compiled application resource. |
| 1 through 4096 | The byte buffer fits. Continue preparing the C initializer. |
| 4097 | The budget has been exceeded. Refuse the resource. |

The configure check concerns the resource size. The Umicom C runtime separately checks whether the content is a valid application before the service starts.

## 2. Read the same rule in C

~~~c
#include <stdbool.h>
#include <stddef.h>

static bool ResourceFits(size_t observed_bytes, size_t limit)
{
    /* A configured application needs at least one byte and must fit its budget. */
    return observed_bytes != 0U && observed_bytes <= limit;
}
~~~

~~~text
READ at most the limit plus one byte
IF no bytes arrived, refuse the resource
IF the extra byte is present, refuse the resource
OTHERWISE turn the admitted bytes into a C initializer
~~~

Work out the decisions for 0, 4, 5 and 6 bytes when the limit is 5. An input of six bytes already exceeds the limit. The program can decide without reading any more.

## 3. Try the configure-only evidence

From the Framework source directory, set `$framework` to its absolute path. Choose a new practice directory for each case. The fixture supplies its own small ordinary input.

~~~powershell
$framework = (Get-Location).Path
cmake "-DROOT=$framework" "-DDEST=$framework/build/resource-exact" -DCASE=exact -P "$framework/tests/build_configuration/check_embedded_resource_limit.cmake"
cmake "-DROOT=$framework" "-DDEST=$framework/build/resource-too-large" -DCASE=too-large -P "$framework/tests/build_configuration/check_embedded_resource_limit.cmake"
~~~

Both fixture commands should succeed. The first checks the exact initializer for 4096 bytes. The second checks that its child command refused 4097 bytes. A successful test of a refusal means the refusal happened as expected. Existing artwork and SDK resources still use their earlier shared initializer call.

The configure step uses CMake's counted binary read because the C header must exist before the native executable is compiled. [CMake file reading](https://cmake.org/cmake/help/latest/command/file.html#reading)

[Course contents](index.md) · [Previous lesson · Keep a FastCGI connector and its backend separate](56-keep-a-fastcgi-connector-and-its-backend-separate.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/57-limit-compiled-bytes-before-embedding.html)
