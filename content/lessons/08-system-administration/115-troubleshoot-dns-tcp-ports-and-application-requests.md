# Chapter 115 — Troubleshoot DNS, TCP ports and application requests

**Bits to Banking · System Administration From Zero · Stage 9**  
**Audience:** Absolute beginners, adults, returning professionals and supervised younger learners.  
**Safety:** Observe only your own computer or an explicitly authorised practice environment. Live changes are not required.

## Why this matters

A request crosses several distinct stages: DNS name resolution, routing, firewall rules, listening socket and application processing. **DNS** translates a hostname into an address. **TCP** creates a connection to a port. An HTTP response proves that an HTTP endpoint answered; it does not prove a business action such as saving a Notes document succeeded.

Use **localhost / 127.0.0.1**, which means your current computer, before any remote tests. Earlier C23 HTTP exercises used example port 8765, which is normally closed when the lab is not running. A refused connection may simply mean no listener. Do not scan someone else's network or disable a firewall to make an exercise appear green.

![Diagram: Troubleshoot DNS, TCP ports and application requests](../../assets/diagrams/sysadmin-fleet-inventory-update46.svg)

## Learning objectives

After the lesson you should be able to explain the new terminology, run and understand a small read-only observation, distinguish observations from assumptions, and record the next safe action when a check is incomplete. A professional answer can be **not checked**, **not authorised** or **requires escalation**.

## Step-by-step Windows laboratory — PowerShell 7

Open Start, type **PowerShell**, and choose PowerShell 7 where available. Do not type the `PS C:\...>` prompt. Run each command one line at a time. PowerShell 5.1 may also run these read-only commands where the associated feature is installed.

```powershell
Resolve-DnsName localhost
Test-NetConnection -ComputerName 127.0.0.1 -Port 8765
Get-NetTCPConnection -State Listen | Select-Object -First 10 LocalAddress, LocalPort
```

**Interpret the result:** The output will describe *your* computer, not the fictional Umicom hosts. Names, dates and versions will differ. Record the time and the important fields. If the command cannot run or permission is denied, mark the observation incomplete rather than inventing a value. A command's exit status only reports the command's own work.

## Step-by-step Linux laboratory — Terminal

On Linux use an account you own or are permitted to use, preferably in a disposable VM. These are observational commands unless the lesson explicitly describes a practice file you create in your home directory; you do not need `sudo`.

```bash
getent hosts localhost
ss -ltn | head -n 12
curl --head --max-time 5 http://127.0.0.1:8765/
```

**Interpret the result:** Not all distributions install the same management tools or use systemd. Preserve errors as troubleshooting evidence. Do not install random replacements, change unit files or edit firewall rules to make classroom output look identical to a screenshot.

### Interpret each network layer separately

`Resolve-DnsName`/`getent hosts` answer name lookup questions. `Test-NetConnection` with `-Port` attempts a TCP connection; the intended port must actually have a listener for it to pass. A `curl` HTTP result of 404 shows an application server answered but could not find that path; it is not the same as TCP connection refused. If the learner's computer does not have a test server listening on 8765, the expected result is simply failure to connect—record it as an intentional classroom observation.

## Worked Umicom example

A failed localhost TCP check does not prove an internet fault. HTTP 404 means a server responded but the requested resource was absent. HTTP 403 is an access decision, not an invitation to bypass authorisation. For fictional Notes gateway→storage, check DNS, port, protocol and permitted Notes save separately.

## Exercises

Create a table listing what DNS success, TCP success, HTTP 200 and Notes save success each prove. Why are they not interchangeable?

## Suggested answer and review criteria

A complete answer names the host, exact observation, source, timestamp with a time-zone offset, and reviewer or next owner. It also states what the command **does not** prove. In particular, a process Running is not proof of a completed Notes save, and an old release restored after failure does not make the failed proposed release successful.

## Common questions

**What if my command gives an error?** Read the exact message and check where you are with `Get-Location` on Windows or `pwd` on Linux. If the tool is not installed, note that fact. If it requires permissions you do not have, stop and contact the owner.

**What if my output differs from the book?** Computers differ. Compare the *fields and meaning* rather than expecting the same host name, drive size or process list. Never fabricate a result.

**Can I apply these commands to another person's machine?** Only after permission has been given and the information has been classified appropriately. This course never grants system-administration authority.

**Further practice:** Review [Chapter 108](108-capstone-seven-day-operations-plan.md) for the seven-day plan, then complete the Stage 9 workbook and [Chapter 120](120-capstone-investigate-two-fictional-umicom-notes-hosts.md) for the two-host exercise.
