<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/130-observe-a-message-with-query-rights.md

PURPOSE:
Observe a message with query rights

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Observe a message with query rights

A kernel **message channel** lets two endpoints exchange bounded pieces of data. An endpoint capability records which operations its holder may request. A program can ask whether data is ready without asking the kernel to deliver that data.

## Read the rights one at a time

| Operation | What the caller asks | Effect on a queued message |
| --- | --- | --- |
| Query | Report allowed readiness and the next message length | Keep it queued |
| Peek | Inspect the front message through an allowed read operation | Keep it queued |
| Receive | Deliver the front message through an allowed read operation | Remove it on successful delivery |

A **query-only** capability admits a metadata request. The hosted `query-only-front` fixture calls `UmicomKernelMessageQuery` and observes one queued message, one payload byte and clear readiness flags. The flags describe the operations allowed by the endpoint’s rights. The same fixture then checks that peeking with this capability returns `UMICOM_MESSAGE_ACCESS_DENIED`.

## Follow the result without consuming anything

1. Open `tests/message_channels/message_tests.c` in the Umicom Kernel source and find the query-only case.
2. Find the code that makes a message available at the other endpoint. Read the length the test expects.
3. Trace the query call and the later peek. Note which rights the endpoint owns at both steps.
4. Point CTest at your existing hosted Kernel build. Replace `build/hosted` with the directory that contains the configured tests. Expect one passing test, with the allowed metadata request and the refused peek checked together.

~~~powershell
ctest --test-dir build/hosted -R '^kernel\.message_channels\.query-only-front$' --output-on-failure
~~~

If CTest reports no tests, check the directory with `ctest --test-dir build/hosted -N`. The hosted Kernel configuration contains the message-channel suite.

~~~text
LOOK UP the endpoint and its admitted query capability
CHECK the queued metadata before reporting readiness
RETURN the allowed readiness and length
LEAVE the message and its receive permission unchanged
~~~

## Connect it to multikernel work

A service can use query metadata to schedule its own next action. A separate capability decides whether that service may consume the message. Keep this separation when a future transport moves messages across processor-local services. The hosted queue case exercises one local kernel contract with synthetic endpoints.

[Course contents](index.md) · [Previous lesson · Set up the x64 Kernel stack](129-set-up-the-x64-kernel-stack.md) · [Next lesson · Check the front message header](131-check-the-front-message-header.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/130-observe-a-message-with-query-rights.html)
