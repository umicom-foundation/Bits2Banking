# 133. When did it fail? Understand time zones before comparing logs

*System Administration From Zero · Continued practical lessons*

Two colleagues are investigating a slow application. One says, “The error happened at nine o'clock.” The other says, “My log shows ten o'clock.” They might both be correct.

Computers record time in different ways. One log may use the computer's local time, while another uses **UTC** (Coordinated Universal Time), a common reference for timestamps. If we do not identify which one we are reading, we can put events in the wrong order and blame the wrong service.

This lesson helps you read timestamps safely. The commands only **display** information; they do not change the system clock.

## First, know what the clock is showing

Your computer has a date and time setting. It also has a *time zone*: a rule describing how local time relates to UTC. Some locations adjust their clocks at different times of year for daylight saving. A timestamp without a time zone can therefore be ambiguous.

For example, these two timestamps represent the **same instant**:

| Timestamp | Meaning |
|---|---|
| `2026-07-15T09:00:00Z` | 09:00 in UTC (`Z` means UTC) |
| `2026-07-15T10:00:00+01:00` | 10:00 in a zone one hour ahead of UTC |

The apparent one-hour difference disappears once the offset is taken into account. You should not simply subtract the printed clock readings.

A date-only value such as `2026-07-15` is different: it describes a **calendar date**, not a precise instant. That distinction also matters in Treasury Management Systems, where a settlement date is not the same thing as the second at which a payment message was transmitted.

## Windows: read your own computer's time

Open **PowerShell 7** or **Windows PowerShell**. Do not copy the `PS>` prompt if one is visible; type only the command.

```powershell
Get-Date
```

**Expected result:** A date and time in your computer's current local setting. Your result will naturally differ from examples in a textbook.

Next, ask for a timestamp that includes the time-zone offset:

```powershell
Get-Date -Format o
```

You might see something shaped like `2026-07-15T10:00:00.0000000+01:00`. The exact digits and offset depend on your computer and when you run it.

Now inspect the configured time zone:

```powershell
Get-TimeZone
```

**Expected result:** A name and identifier for the time zone. If the command is not recognised, check which PowerShell edition you started and consult `Get-Help Get-TimeZone`; do not start changing settings as a first response.

## Linux: the corresponding observations

In a Linux terminal, try:

```bash
date
date -u
date --iso-8601=seconds
```

`date` normally prints local time. `date -u` prints UTC. The last command prints a timestamp with an explicit offset on systems that support this GNU `date` option. Some Unix systems use different options; the goal is to understand the timestamp format, not memorise one implementation.

On a system using systemd, this may show the time-zone configuration:

```bash
timedatectl status
```

If `timedatectl` is unavailable, that does not prove the computer has no time zone. It means the command or service is not present in that environment.

## Build an incident timeline carefully

Suppose an application log records `09:00Z`, while a service dashboard records `10:00+01:00`. Convert both to a common reference before comparing them. Record the original strings as well; they may be needed to explain how you interpreted the event later.

Also consider **clock accuracy**. If two computers' clocks are not synchronised, even correctly labelled timestamps can disagree. Note any known clock problem and avoid claiming that one event caused another merely because its printed time looks earlier.

For measuring elapsed duration inside software, systems often use a **monotonic clock**, which counts time passage without being disturbed by an administrator setting the wall clock. You do not need to program that today; just remember that a calendar clock and an elapsed-time counter answer different questions.

## Practise on paper

**Question 1.** Log A says `2026-07-15T08:30:00Z`. Log B says `2026-07-15T09:30:00+01:00`. Which happened first?

**Question 2.** A colleague gives you `14:05` with no date or offset. Can you place the event precisely in a multi-machine incident timeline? What else should you ask for?

**Question 3.** Why would a financial system store a trade's **value date** separately from the timestamp when a message was sent?

### Suggested answers

**1:** They describe the same instant.  
**2:** Not reliably. Ask for the date, time zone/UTC offset, host and whether its clock was synchronised.  
**3:** The value date is the business date on which settlement is due; a message might be sent earlier, later or retried. They record different facts.

A reliable administrator makes a timeline another person can follow without having to guess what “nine o'clock” meant.
