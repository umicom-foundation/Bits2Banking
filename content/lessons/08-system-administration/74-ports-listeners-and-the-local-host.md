# Chapter 74 — Understand ports, listeners and the local host

**Bits to Banking · System Administration From Zero · Stage 6 · Umicom Foundation**  
**Prerequisite:** Chapter 73; familiarity with a terminal prompt.  
**Safety:** Only inspect your own machine; do not scan networks or change firewall rules.

## The problem: one computer can offer many services

A computer can display a website, accept an SSH connection and host a database at the same time. An **IP address** identifies a network endpoint; a **port number** helps the operating system deliver a connection to a particular service on that endpoint. Think of an office building: the street address gets you to the building, while the room number directs you to a specific office. A port is not a password and opening one does not automatically make the service secure.

A process that is ready to accept connections is called a **listener**. `127.0.0.1` is the IPv4 loopback address: connections to it remain on the local computer. `0.0.0.0` as a listening address means the process accepts IPv4 connections on all its local interfaces, subject to firewall and routing rules. The difference matters before turning a teaching web server into a network service.

![Listener binding and network exposure](../../assets/diagrams/sysadmin-firewall-zone-update43.svg)

## Terms to learn

| Term | Plain-language definition | Example |
|---|---|---|
| **TCP** | A transport for a reliable ordered stream of bytes. | SSH and many HTTPS connections. |
| **Listener** | Program waiting for connections on an address and port. | A local Umicom learning HTTP server. |
| **Loopback** | Network path to the same computer. | `127.0.0.1:8765`. |
| **Established connection** | A two-way TCP conversation that exists now. | Browser to local training server. |
| **PID** | Process identifier assigned by the operating system. | The number shown beside a listening process. |

A TCP listener is not proof that the application is healthy. It may accept a connection but fail to read configuration, find its database or finish a user's request.

## Windows — read listening TCP endpoints

**Step 1.** Open PowerShell 7. Check the command first:

```powershell
Get-Command Get-NetTCPConnection -ErrorAction SilentlyContinue
```

If it exists, list a few local TCP listeners:

```powershell
Get-NetTCPConnection -State Listen |
    Select-Object -First 12 LocalAddress, LocalPort, OwningProcess
```

**Expected:** A table of addresses, ports and process IDs. Some machines restrict some network details; an access-denied result is evidence to record, not a reason to use Administrator rights automatically.

**Step 2.** Ask which process owns one PID you observed. Replace `1234` with an actual displayed number:

```powershell
Get-Process -Id 1234 | Select-Object Id, ProcessName
```

**Expected:** A process name. A process can exit between the two commands; a *not found* response can therefore be normal.

**Step 3.** Check one specific local port only if you know that a practice service is intentionally running on it:

```powershell
Test-NetConnection -ComputerName 127.0.0.1 -Port 8765
```

`TcpTestSucceeded: False` means no TCP connection was made; it is not proof of a broken computer. A listener may simply be absent. `True` proves TCP connection establishment, **not** business readiness or identity.

## Linux — inspect your own sockets

```bash
ss -ltn
```

`-l` means listening, `-t` means TCP and `-n` means numeric addresses and ports. A non-root user may not see the owning process name. Resist the temptation to add `sudo` until you have an authorised reason.

To observe a specifically permitted local port:

```bash
ss -ltn '( sport = :8765 )'
```

An empty result is expected if the teaching server is not running. These commands do not install or enable a service.

## Worked Umicom scenario

A student starts the previously built C23 loopback HTTP laboratory on port 8765. The browser reaches the teaching page using `http://127.0.0.1:8765/`. Another laptop cannot connect, because the process was deliberately bound to loopback. **Do not change the binding to `0.0.0.0` simply to make it accessible.** Exposing a service requires an approved threat model, authentication, transport protection, firewall review and operational ownership.

## Guided exercise

Write down three observations: a local listening address, a port number, and whether a process name was available. Identify whether the listener is loopback-only or potentially accessible on other interfaces. If no suitable practice listener exists, record *not observed*; do not create a public listener just to complete the worksheet.

## Troubleshooting

| Observation | Interpretation | Next safe check |
|---|---|---|
| Port appears but the application fails | TCP listener is not a readiness guarantee. | Inspect authorised application logs and dependency health. |
| `Connection refused` | Nothing accepted the connection at that endpoint. | Check the intended address and whether the service was meant to start. |
| `Timed out` | No timely response; path or firewall could be involved. | Check DNS, route and approved firewall policy without changing them. |
| `0.0.0.0` appears | Wildcard listener across local IPv4 interfaces. | Flag for security review; do not assume internet reachability. |

## Review questions with answers

1. What does `127.0.0.1` mean? **Answer:** The local computer's IPv4 loopback address.
2. Does a successful TCP connection prove SSH host identity? **Answer:** No.
3. Why does an unrecognised port deserve investigation? **Answer:** It could be unexpected exposure or a legitimate service; identify the owner before acting.

**Next:** Chapter 75 — understanding SSH host identity before connecting.
