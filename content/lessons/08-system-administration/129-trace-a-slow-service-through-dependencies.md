# Chapter 129 — The application is slow. Which part is responsible?

*System Administration From Zero · Stage 10 · Umicom Foundation*

A colleague reports, “Umicom Notes takes twenty seconds to open a page.” It is tempting to blame the application, but the visible delay could come from several places: the computer, the network, the storage service or a database.

Troubleshooting is easier when we follow the path of one request instead of changing everything at once.

## Draw the path

A simplified Notes request might travel through:

> User clicks Open → application requests a note → service checks permissions → storage loads it → response reaches the application → screen updates.

Every arrow is a potential delay. A service can be **running** and still be **unready** because a required dependency is unavailable. A green process indicator does not prove that the full business operation has finished.

## Start with facts, not guesses

Ask the user which operation is slow, when the problem started and whether it affects everyone. Then record a small timestamped test that you are authorised to perform. Avoid running a heavy benchmark on a production system without approval.

On Windows, you can inspect a few active processes:

```powershell
Get-Process | Sort-Object CPU -Descending |
    Select-Object -First 10 ProcessName, Id, CPU, WorkingSet
```

`CPU` here is accumulated processor time, not a current percentage. A process high on this list has used substantial CPU time since it started; that alone does not prove it caused the current slow request.

If you have a known **authorised test hostname**, check how its name resolves:

```powershell
Resolve-DnsName example.com
```

Use a real practice host you are allowed to query. A successful DNS result does not prove that the application service is reachable.

## Linux comparison

On Linux you can inspect load and processes with:

```bash
uptime
ps -eo pid,comm,%cpu,%mem --sort=-%cpu | head
```

A busy CPU is one possible cause. A database waiting on a lock or an unreachable remote service may cause long delays while CPU use remains low.

## A simple incident timeline

Write three times: when the user clicked, when the service received the request and when the reply completed. If possible, add database or storage timing. The interval where the request waited is where deeper investigation should begin.

**Exercise:** A page takes 20 seconds to open. The application's own processing takes 100 milliseconds, while its storage request takes nearly 19 seconds. Should the first fix be rewriting the screen? **Answer:** Probably not; first investigate storage responsiveness, permissions, contention and related dependencies. A short UI operation is not evidence that the whole request is healthy.
