# Chapter 125 — Read a computer's log before guessing what failed

*System Administration From Zero · Stage 10 · Umicom Foundation*

When a car makes an unusual noise, a mechanic may look for clues before replacing a part. A system administrator should work the same way. Computers leave **logs**: records of events such as service starts, failed connections and application errors.

A log is a useful clue, but it is not automatically the whole truth. A message saying “service started” does not prove that a customer's transaction completed.

## Windows Event Viewer and PowerShell

Windows has several event logs. The **System** log often contains information about hardware, drivers and services. The **Application** log can contain events written by programs. **Security** events are subject to the system's audit configuration and access rights.

Open Event Viewer from the Start menu if you prefer a graphical view. Or open PowerShell and read a small sample from the Application log:

```powershell
Get-WinEvent -LogName Application -MaxEvents 5 |
    Select-Object TimeCreated, Id, LevelDisplayName, ProviderName
```

A row normally includes a timestamp, event ID, level and source. `MaxEvents 5` keeps the exercise manageable. This command reads data; it does not clear any log. If you receive an access or availability error, record it rather than running PowerShell as administrator without a reason.

To see the complete message for a particular event, inspect it in Event Viewer or select its `Message` property. Remember that event messages may include personal or system-specific information. Do not publish raw logs without reviewing sensitive content.

## Reading Linux service logs

Many Linux systems use **systemd-journald** to collect service events. On a machine that uses systemd, try:

```bash
journalctl --user --since '1 hour ago' --no-pager
```

This examines your user journal if one is available. For a specific service you are authorised to inspect, administrators often use `journalctl -u SERVICE_NAME`. Do not invent a service name; inspect the real one first.

## What should you look for?

Suppose Umicom Notes fails to start at 09:15. Find entries near 09:15, not a random error from last month. Record the application version, host, local time and time zone. One failure may trigger several later errors, so the first relevant failure in the sequence is often the best clue.

For example, “cannot open data directory” suggests permissions or a missing path. “Connection timed out” suggests a dependency or network issue. Those messages point to investigations; they are not automatic diagnoses.

## Practice

Choose one harmless event from your own system. Record its time, provider, event ID and message in a private note. In one sentence, explain what the log **establishes** and what it **does not establish**.

A strong answer might say: “The event shows that Windows attempted to start a service at 09:15 and reported an error; it does not, on its own, explain why the underlying application failed.”
