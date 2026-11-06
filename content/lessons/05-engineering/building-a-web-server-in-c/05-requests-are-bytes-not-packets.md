# Requests are bytes, not packets

[Course contents](index.md) · [Previous: Recognise complete requests and honest results](04-framing-errors-and-exercises.md) · [Next: Buffer capacity and partial input](06-buffer-capacity-and-partial-input.md)

## Start after the existing four lessons

The earlier lessons traced requests, routes, ownership and framing errors. Now examine how bytes arrive. A TCP connection is an ordered byte stream. One receive call can return part of a request, one complete request, or bytes from more than one request. Network packet boundaries are not application message boundaries.

An HTTP/1.1 request contains a request line, header fields, an empty line and sometimes a body. The exact framing rules decide where a message ends. The following is a readable illustration; each displayed line ends with carriage return and line feed bytes, written \r\n in C.

```text
GET /api/health HTTP/1.1
Host: 127.0.0.1:8080

```

## Trace a split receive

1. First receive: GET /api/he
2. Second receive: alth HTTP/1.1 followed by part of a header.
3. Third receive: the rest of the header and the empty line.
4. Only now can a parser conclude that these headers are complete.

Do not search for a zero terminator in arbitrary received bytes unless you placed one within the allocated buffer. Track how many bytes are present. Place upper bounds on request-line length, header size, body size and time spent waiting. A peer that sends one byte very slowly should not hold unlimited resources forever.

## Exercise

A server calls receive once, reads 12 bytes and assumes they contain the whole request. What happens when the request arrives in three pieces? What should the connection state retain?

## Explained answer

It might parse incomplete data as a command or reject a legitimate request unpredictably. Retain buffered byte count, parser state, remaining capacity and a deadline. A later receive continues parsing from the same connection state. Framework owns this machinery; a route handler should receive a parsed request under a documented contract.

## Reference boundary

RFC 9112 defines HTTP/1.1 message syntax and framing. A teaching request example is not the complete specification. Conflicting length information, malformed headers and unsupported transfer encodings require explicit handling before this server can safely accept untrusted traffic.

## Continue learning

[Course contents](index.md) · [Previous: Recognise complete requests and honest results](04-framing-errors-and-exercises.md) · [Next: Buffer capacity and partial input](06-buffer-capacity-and-partial-input.md)

[Browser edition](../../../courses/building-a-web-server-in-c/lessons/05-requests-are-bytes-not-packets.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/examples/web/local_service.c). This public revision matches the source inspected for this lesson.

[Primary reference](https://www.rfc-editor.org/rfc/rfc9112.html).
