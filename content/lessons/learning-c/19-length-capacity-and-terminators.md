# Length, capacity and the end of a string

An array is a row of elements. Its capacity says how many elements fit. Its current length says how many contain the data you mean to use. Those numbers can differ. A C string adds another rule: a zero-valued character marks its end. Understanding these three facts prevents many out-of-bounds reads and writes.

## Setup recap

You can do the first exercise on paper. For the practical part, install a C23 compiler, CMake and Ninja using [terminal setup](terminal-lab.md). The Framework exercise also requires the installed SDK described in [the hashing lab](../umicom-development/37-use-a-framework-function-in-a-lab.md). That page supplies the complete PowerShell and Bash configure commands. Use a practice copy so experiments do not change your application sources.

## 1. Count the elements

```c
char name[8] = "Ada";
```

| Index | 0 | 1 | 2 | 3 | 4–7 |
|---|---|---|---|---|---|
| Stored value | A | d | a | zero | zero |

The capacity is eight characters. The string length is three. The terminator is at index three. Initialising an array this way also zero-initialises the remaining elements. You may not write `name[8]`: the last valid index is seven.

`sizeof(name)` is eight because `name` is an array here. `strlen(name)` is three because it counts characters before the first zero. `strlen` requires an accessible terminator; it does not know the capacity and cannot make a damaged buffer safe.

## 2. Follow a real Framework call

In the `framework-hash` lab, `UmiSha256Buffer("abc", 3U, hex)` reads exactly three bytes. It does not search for a terminator. It can therefore hash binary data containing zero bytes. The output `hex` needs 65 characters: 64 readable digest digits plus one terminator.

This distinction is essential when an application imports a media file or reads a protocol message. The bytes of a file are not necessarily a C string. The application must preserve the actual byte count.

## 3. Observe a one-byte difference

From the configured `framework-hash` practice folder:

```powershell
cmake --build build --parallel 2
& '.\build\btb-framework-hash.exe' known
```

In Bash, use `./build/btb-framework-hash known` after the same build command. Read the `Known` function. Change only `3U` to `4U` in your practice copy, rebuild, and run again. The reference comparison should fail: the fourth byte is the zero terminator. Restore the original length and repeat.

Do not try larger lengths. The string literal has four elements; requesting more would ask the function to read outside that array. A length-taking API still relies on the caller to describe valid storage.

## 4. Explain the units

Framework's byte tokeniser accepts a byte count, an output capacity in `uint32_t` elements, and a pointer receiving the number of tokens. For `uint32_t tokens[10]`, the capacity is ten tokens, not the number of bytes returned by `sizeof(tokens)`. Use `sizeof(tokens) / sizeof(tokens[0])` while the array is still visible to obtain its element count.

An array parameter in a C function usually becomes a pointer. `sizeof` that parameter measures the pointer, not the original array. Pass capacity separately rather than trying to recover it inside the function.

## Check your understanding

How much space does the string `Bank` need? Five characters: four letters and the terminator. Can a four-byte binary record contain zero? Yes; its explicit length preserves all four bytes. Would `strlen` reliably measure that record? No; it would stop at its first zero or read beyond the record if none occurs.

If an output appears truncated, inspect the capacity and result code before changing the display. If a test crashes, check every pointer/length pair, not just the final line. Read the existing [bounded span lesson](11-bounded-spans-and-rejection.md), then continue to [allocation outputs and lifetimes](20-allocation-outputs-and-lifetimes.md). Return to [Learning C](index.md) for the complete sequence.

## Exercise and explanation

Why do 64 hexadecimal digits need 65 characters of storage?

The final character stores the zero terminator required by a C string.

[Previous lesson](08-connect-to-systems-lessons.md) · [Next lesson](20-allocation-outputs-and-lifetimes.md)

