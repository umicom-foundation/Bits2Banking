# Understand SEF startup and restart

## A service has a managed lifecycle

A normal command-line program starts at main and may immediately perform work. A managed operating-system service must coordinate its initialization with the system that starts or replaces it.

MINIX's System Event Framework, SEF, supplies lifecycle handling. Use the [v3.3.0 sef.h declarations](https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/v3.3.0/minix/include/minix/sef.h) as the version-specific reference. Some wiki descriptions are older than the interface they discuss.

## Follow the original lab

The [Umicom status-driver lab](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/minix/status-driver) registers fresh-start and restart initialization callbacks, calls sef_startup, then enters the character-driver task loop. The initialization announces the driver.

The example owns only a fixed response string. Restart therefore does not need to reconstruct a persistent counter. No live-update callback is registered, and no live-update support is claimed.

## Worked lifecycle distinction

A fresh start establishes an initial state. A restart after failure may reconstruct that state from a durable source or begin an explicitly stateless service again. A live update must transfer a compatible state while preserving the relevant protocol obligations. Those are different operations.

Calling a function “restart” does not prove outstanding client requests or grants survive. Define what clients should observe when the service disappears and returns.

## Exercise and answer

A driver increments an in-memory counter on every request. After restart, the counter returns to zero. Is that necessarily a bug? Answer: it depends on the documented contract. If the counter is diagnostic per-instance data, reset may be correct. If it controls durable business or filesystem identity, losing it is unacceptable.

## Review task

Identify every piece of state in status_driver.c. Explain why the fixed text needs no migration and why adding mutable state would require a new lifecycle design. Compile with release-matched headers before trying a guest launch. The lab has been authored and compared with official declarations, but its guest lifecycle remains unexecuted.

[Course contents](index.md)
