# Incremental functions and failure contracts

Some work arrives in pieces. A file reader might receive a few kilobytes at a time; a network connection might deliver parts of one message. An incremental function keeps state between calls so it can process those pieces in order. This lab follows Framework's digest context and checks what happens when callers break a rule.

## Setup recap

You need C23, CMake, Ninja, a compatible Framework `base` SDK and the `framework-hash` practice folder. [The preceding SDK lab](37-use-a-framework-function-in-a-lab.md) gives every installation link and command. If starting here, complete its copy and configure steps, then run the `known` case. It establishes a reference result before you investigate state. No blockchain account, network service or GPU is needed.

## 1. Draw the life of one context

```text
uninitialised → Init → Update("a") → Update("bc") → Final → finished
                         ↑ repeated updates allowed ↑
finished → Init → ready for a different digest
```

`UmiSha256` holds the working state. The caller owns that object. `UmiSha256Init` starts it; `UmiSha256Update` adds bytes; `UmiSha256Final` writes the 32 digest bytes. `UmiSha256Hex` converts those bytes into readable characters. The conversion uses a separate output array so the input and output do not overlap.

Open `Chunks` in `main.c`. Notice that its two updates add three bytes in total, in the same order as `abc`. Splitting a stream into pieces does not insert separators. Reversing those pieces changes the input.

## 2. Exercise the incremental path

PowerShell, from the configured practice folder:

```powershell
cmake --build build --parallel 2
& '.\build\btb-framework-hash.exe' chunks
ctest --test-dir build -R '^bits2banking\.framework_hash\.(chunks|rejected)$' --output-on-failure --no-tests=error
```

Bash:

```bash
cmake --build build --parallel 2
./build/btb-framework-hash chunks
ctest --test-dir build -R '^bits2banking\.framework_hash\.(chunks|rejected)$' --output-on-failure --no-tests=error
```

The expected message says that ordered pieces produce the same digest. The selected CTest run should contain two cases. An empty selection is an error because `--no-tests=error` is present.

## 3. Read the refusal checks

In `Rejected`, passing a null address with a nonzero length must return `UMI_STATUS_INVALID_ARGUMENT`. There are no bytes at that address to read. The program then hashes `abc` using the same context and checks the reference digest. This verifies that the refused update did not corrupt the context.

Next the program fills an output array with `0xA5`, retains a copy, and calls `Final` a second time. A second finish is invalid. Comparing the arrays checks that failure did not overwrite the caller's output. The value `0xA5` is a recognisable test pattern, not a secret or a real digest.

| Question | Evidence to inspect |
|---|---|
| Did the operation succeed? | Returned `UmiStatus` |
| Did a refused update damage later work? | A subsequent known digest |
| Did failure modify output? | Byte comparison against the retained pattern |
| Can this context be used for a new message? | Explicitly call `Init` again |

## 4. Extend the contract exercise

In a practice copy, add a zero-length update between the two chunks using `NULL, 0U`. The header permits this; the final digest should remain unchanged. Then swap the chunks. The reference check should fail. Restore the order before finishing.

A compiler error about an unknown function usually means the header or SDK is wrong. A failing digest comparison means the input, order or implementation needs investigation. Do not replace the expected digest with whatever the program prints: that would remove the independent check.

## Apply the idea elsewhere

The same questions apply when an editor saves a document or a media job accepts a clip: who owns state, which operation advances it, and what remains unchanged after refusal? Look up each service's own contract; do not assume every Framework function shares SHA-256's failure behaviour.

Read [`sha256.h`](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/base/sha256.h) beside the consumer. Continue through the [functionality learning map](functionality-lab-map.md) or return to the [Framework course](index.md).

[Next: Trace an event to a shared Framework rule](39-trace-an-event-to-a-framework-rule.md)
