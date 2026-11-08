<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/22-test-every-fragment-boundary.md

PURPOSE:
Test message decisions across fragment boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Test message decisions across fragment boundaries

## Prepare

Open Partitions and ManyFragments in test_request_stream.c. These are authored Framework regression scenarios. Owner qualification builds and executes them; merely reading their assertions is static review.

## Separate the oracle from the transport

Each vector has a complete wire message and an expected final status. The test first checks that expectation with the existing stateless frame reader. It then feeds the same bytes as every possible two-part split. This checks that chunk placement does not change the complete framing decision.

## Choose meaningful boundaries

The split can fall between CR and LF, inside a header name, inside decimal Content-Length, between header and body or at the very end. Empty first or second chunks also matter. Valid requests, duplicate lengths, unsupported features and extra pipelined bytes are included. A separate case feeds a larger request one byte at a time.

## Run and retain actual results

After the owner builds the matching Framework test target, the focused filter below selects the stream cases. Replace the example build folder with the one you actually configured. Check that cases were discovered and keep failed output.

~~~powershell
ctest --test-dir C:/umicom/Umicom-Applications/framework/build/windows-ucrt64-debug --output-on-failure --no-tests=error -R '^framework\.web\.request_stream\.'
~~~

## Exercise and worked answer

A test feeds one whole request and passes. Why is that insufficient for an incremental reader? It never exercises saved scan state across calls. A CR at the end of one chunk must remain pending until the next byte arrives. Test the boundary where state must survive, not only a convenient input size.

## Interpret coverage honestly

All split checks compare final semantic decisions, while delayed-semantic separately documents when an error becomes visible. These checks do not measure network throughput or verify socket deadlines. A failure should retain its vector and split position; a timing claim requires a separately designed measurement.

## Read the source

[Umicom-Applications/framework/tests/web/test_request_stream.c](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/web/test_request_stream.c). Use the matching local revision when working offline.

## Continue learning

[Course contents](index.md) · [Previous: Reset parser state without claiming keep-alive](21-reset-state-without-keeping-a-connection.md) · [Next: Connect parser state to the transport owner](23-connect-stream-state-to-transport-ownership.md)
