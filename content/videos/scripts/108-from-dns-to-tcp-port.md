# Episode 108 — From a Website Name to a Port

**Bits2Banking · Umicom Foundation · Instructor-ready script**  
**Target running time:** 09:00.  
**Audience:** absolute beginners, returning learners and supervised younger students.  
**Recording rule:** Show only your own authorised practice computer or anonymised fictional output. No real bank, healthcare or production records.

## Learning objectives

- Introduce each concept in ordinary language before showing commands.
- Execute commands interactively in PowerShell 7 or Linux, never as newly introduced `.ps1` or `.py` implementation scripts.
- Explain what a correct observation proves and what remains unknown.
- Finish with a concrete exercise and a safe stopping point.

## On-screen preparation

Use the Stage 3 course lesson, its original SVG illustration and an ordinary PowerShell 7 terminal. Enlarge text for accessibility, avoid flashing or rapid transitions, caption the spoken commands and show any error message without cutting off the explanation. The instructor should prepare fictional sample output for environments in which commands are restricted.

## 00:00–01:20 — A vague error is not a diagnosis

**Narration / teaching notes:**

A browser saying Cannot connect could mean the name could not resolve, packets could not find a route, the requested port is not accepting connections or the application itself returned an error. We will not disable firewalls or alter router settings to guess the solution.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 01:20–03:05 — Start with DNS

**Narration / teaching notes:**

Use the reserved example.org domain and Resolve-DnsName when the computer is connected. Explain that the answer can vary and that an IP address is not the same as a listening application. Compare a numeric loopback request, which does not require the same DNS step.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 03:05–05:05 — Inspect transport

**Narration / teaching notes:**

Run Test-NetConnection -ComputerName example.org -Port 443. Explain the meaning of TCP reachability and why a successful transport connection does not prove TLS or HTTP returned correct content.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 05:05–07:15 — Look at local listeners

**Narration / teaching notes:**

Show Get-NetTCPConnection -State Listen with limited output. Explain LocalAddress, LocalPort and OwningProcess. Show fictional examples for 127.0.0.1 and 0.0.0.0. Never ask students to open inbound firewall rules or expose the local training server to the internet.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 07:15–09:00 — Teach a safe report

**Narration / teaching notes:**

Give two fictional traces: DNS succeeds but TCP fails; loopback server is not running. Ask which next observation would distinguish a missing service from an incorrect firewall theory. Close by explaining that Umicom Framework owns real web listeners.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## Practical viewer activity

Pause the video. Write down one command and explain it in plain English. Run it only if your own device permits the operation. Record a real result, an expected result and one limitation. A missing or blocked check is a valid observation, not a failure of the learner.

## Instructor checks

- Did the learner identify the active shell and current location before touching files?
- Did they distinguish an observation from a diagnosis?
- Did they avoid elevated commands and unapproved system changes?
- Did they explain how they would verify the result independently?

## Production boundary

The C23 example is educational and offline. All reusable real system services belong in existing Umicom Framework capabilities or an approved native Framework extension, not PowerShell, Python or duplicated application modules.

**Rights and credits:** Original educational narration for Umicom Foundation. Author/project lead: Sammy Hegab.
