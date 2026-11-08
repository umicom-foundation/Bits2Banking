# Use grants for bounded data transfer

## Authority to copy bytes

Large data should not be moved by pretending a small IPC message is an arbitrary shared-memory buffer. MINIX memory grants describe controlled access to another process's data. The [official grants guide](https://wiki.minix3.org/doku.php?id=developersguide:memorygrants) explains the model and its service privilege requirements.

In the status-driver read callback, the request carries an endpoint and grant. The driver computes an allowed portion of its fixed response, then calls sys_safecopyto. A successful copy returns the byte count; a failed copy returns the error. This does not grant the driver arbitrary access to the requester's memory.

## Bound the source before copying

The original helper first checks whether position is at or past the response length. Only then does it subtract position from length. It limits requested bytes to that remainder. This avoids an overflowing position + requested expression.

For a ten-byte response, position nine and an enormous request produce exactly one byte. Position ten produces EOF. A zero request produces zero bytes without inventing a read.

## Exercise and answer

A safecopy call fails but the driver returns the requested count. What will the caller believe? Answer: that bytes were transferred when they were not. Return the actual error; do not convert transport failure into successful progress.

## Practical checks

Study the source bounds in read_window.c and the transfer boundary in status_driver.c separately. The authored host test covers the former. It cannot construct a valid privileged MINIX grant or prove the latter works.

In an approved guest harness, test short reads, offsets, EOF and an invalid grant. Retain the exact error and environment. Do not expose broad device I/O rights to this read-only status service.

A grant's lifetime and permission are part of its contract. Restart or update can affect that contract, so a future stateful driver needs additional recovery design rather than assuming copied data and process replacement are independent.

[Course contents](index.md)
