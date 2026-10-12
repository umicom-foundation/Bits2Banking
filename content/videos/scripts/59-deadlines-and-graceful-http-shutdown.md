# Episode 59 — Deadlines and Graceful Shutdown in C23

**Estimated duration:** 16–20 minutes.  
**Companion lessons:** [Chapter 169](../../lessons/05-engineering/169-monotonic-timeouts-and-graceful-shutdown.md), [Chapter 170](../../lessons/05-engineering/170-test-and-diagnose-the-nonblocking-server.md) and [Chapter 171](../../lessons/05-engineering/171-connect-reactors-to-umicom-service-ownership.md).  
**Teaching resources:** `nonblocking_policy.c`, deterministic CTest suite, shutdown/deadline SVG diagram.

## 00:00–03:00 — Three kinds of time

**On screen:** Timeline from connection acceptance to the three-second idle boundary and ten-second total boundary.

**Narration:**

"A nonblocking socket server still has to decide how long it will retain an idle connection. A client might send a header fragment and never finish it. A second client might send one byte every few seconds, just enough to keep the connection active indefinitely if we only use a simple idle timeout.

"We therefore assign each accepted connection two budgets. Three seconds without useful byte progress is an idle failure. Ten seconds from acceptance is an overall expiry, regardless of how frequently the peer sends data. The budgets use the system's monotonic clock because a wall-clock correction should not extend a waiting service indefinitely."

## 03:00–06:20 — Deterministic deadline arithmetic

**On screen:** `BtbNbLifetimeExpired` and worked example with openedAt = 1,000, lastProgress = 2,000.

**Narration:**

"The correct comparison subtracts timestamps only after checking that time has not moved backwards. If we build a deadline by adding an offset near the end of the unsigned integer range, it could overflow. Subtraction with a monotonic-order check avoids that problem.

"Notice exactly what counts as useful progress. A positive result from `recv` or `send` renews the idle timer. A temporary would-block result does not, and neither does waking up from `select` without any socket activity. These details make the observed timeout contract predictable."

**Exercise on screen:** At what timestamp does an idle connection expire if it last progressed at 2,000 ms? What if its opening time was 1,000 ms and it keeps receiving data every two seconds?

## 06:20–09:10 — One safe release path

**On screen:** The five-state connection diagram; highlight `BtbNbRelease`.

**Narration:**

"Every slot owns a socket. It may also own an opened static file. Those resources cannot be released merely because another subsystem requests cancellation. They are released when the owner has finished its final accounting, marked any incomplete response and closed its handles.

"An important distinction from the banking world is that sending a response is not the same as committing a payment or executing an order. A successful socket send tells us that the local operating system accepted bytes. It does not prove that the remote process completed the business action. Our service therefore keeps completion, business audit and remote acknowledgements separate."

## 09:10–12:20 — Ctrl+C and quiescence

**On screen:** `gNbStopRequested` is set; the loop stops admission and drains open slots.

**Narration:**

"When a learner presses Ctrl+C, the signal handler does not close a socket or free memory. It changes one atomic flag. The event loop observes that flag and closes the listener, so no further clients are admitted. Existing clients still receive read and write turns until their responses finish, their budgets expire or the eleven-second maximum shutdown grace is reached.

"Only after every accepted socket has been released does the server return to its caller. Then `main.c` can stop the route service and close the static root it owns. This is how a simple programme demonstrates the same responsibility principle that Umicom's supervised services and financial engines require."

## 12:20–15:30 — Run the native tests

**On screen:** PowerShell build and test commands, then open `test_nonblocking.c`.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
ctest --test-dir ".\output\learning-build\http-loopback-server" `
    -R "nonblocking" --output-on-failure
```

**Narration:**

"The deadline tests do not wait for a real clock. We give the policy synthetic timestamps and assert what happens one millisecond before expiry and exactly at expiry. We also test time moving backwards, resource states that are no longer active and thousands of deterministic state transitions. This is more reliable than asking a test process to sleep repeatedly and hoping that the operating system schedules it at exactly the same time on every computer.

"A separate optional socket test launches the actual C23 executable on loopback. It checks an incomplete header next to a successful second request, GET and HEAD, weak ETags, registered routes, missing files and a real idle timeout. On a POSIX host it also asks the programme to shut down cleanly. On Windows, manual Ctrl+C observation remains a release-qualification step."

## 15:30–18:30 — Compare with Umicom Framework

**On screen:** Framework Web Server public header, Kernel file-service documentation, and the five new chapter links.

**Narration:**

"These are teaching mechanisms, not a new production web server for Umicom applications. Real application logic belongs behind the Framework's stable service contracts and the correct application controllers. The C23 laboratory demonstrates why those contracts specify ownership, failure, deadlines, admission and shutdown.

"We have added capability without deleting the old teaching path. We have not introduced a thread pool or changed the Kernel, Framework or any financial application. The next chapter group can move to bounded asynchronous work handoff, but only after the thread and lifetime contracts are explicit and tested."

**Closing exercise:** Draw the shutdown sequence of a fictional treasury dashboard. Label the listener, route service, business query service and Data Server. Which of those components is allowed to alter a payment record?  
**Final card:** Chapters 169–171 → nonblocking source and CTests → safe service lifetimes. "Pay knowledge forward: learn, contribute and help the next learner."
