# Stage 6 workbook — safe remote administration and incident response

**Umicom Foundation · System Administration From Zero · Chapters 73–84**

This workbook is designed for students of any age. Each exercise begins with a question, asks for an observation, and ends with a short explanation. **Never include real credentials or confidential information in a submitted answer.** An unavailable tool or missing approved training host is a valid outcome; record it rather than simulate a success.

## Exercise A — A remote connection has several gates

On paper, draw a local computer, network, remote host, SSH user, and policy reviewer. Label who checks **host identity**, who checks **user authentication** and who can **authorise a task**. Write one sentence explaining why a TCP connection does not give permission to change a server.

**Suggested answer:** TCP reachability only shows that a connection can be established; server identity, user identity and action permissions are separate controls.

## Exercise B — Identify a local listener

Run one read-only listener command from Chapter 74. Record the selected local address and port, and whether the associated process name was available. Circle `127.0.0.1` for loopback, or another address if observed. **Do not create a new public listener.**

**Suggested answer:** A `127.0.0.1` listener receives local IPv4 connections only. A wildcard address is broader but not necessarily reachable from the internet.

## Exercise C — SSH host-key change

Your training SSH client reports that a familiar host's key has changed. List your next three actions.

**Suggested answer:** Stop the login; retain a sanitised report of the warning and destination; verify the intended host and approved fingerprint through a different trusted channel. Never bypass host-key checking.

## Exercise D — Public versus private keys

If you choose the Chapter 76 training key exercise, record the names of the two generated files and only the public key's fingerprint. Do not attach the private key to your coursework. Explain why a key pair does not provide a server account automatically.

**Suggested answer:** The remote system must separately authorise a specific public key for a permitted identity and scope.

## Exercise E — Firewalls and DNS

Classify each fictional problem: (1) a DNS name does not resolve, (2) a port is not listening, (3) the TLS certificate's hostname differs, (4) a Notes action returns an application error. For each, identify the stage where you should collect evidence and one unsafe shortcut to avoid.

**Suggested answer:** DNS, listener/TCP, TLS identity and application respectively. Avoid disabling security checks, arbitrary port exposure and changes without evidence.

## Exercise F — Hash a local practice copy

Follow Chapter 81 using a harmless training text document. Compare both SHA-256 values. State whether the file bytes match and whether that proves you were authorised to upload them to any remote host.

**Suggested answer:** Matching digests support content equality, not permission to transfer data.

## Exercise G — C23 review negative cases

After building the `remote-access-review` lab with previous Updates 39–42 present, run the `host-key`, `rollback`, `stale` and `atomic-output` named tests. Record the actual result, not the published reference test count. Explain why `REVIEWABLE` is not a real SSH access grant.

## Final assessment (20 marks)

| Task | Marks | Evidence |
|---|---:|---|
| Remote trust-boundary diagram | 3 | Correct separation of identity and authorisation |
| Local listener observation | 3 | Accurate address/port, no changes |
| SSH-host warning response | 3 | Stops and verifies independently |
| Least-privilege matrix | 3 | Human/service/support permissions differ |
| Layered DNS/TCP/TLS diagnosis | 3 | No security-bypass shortcuts |
| C23 negative-test evidence | 3 | Actual test names and outputs |
| Redacted incident handover | 2 | Known, unknown, next action and owner |

**A pass requires no critical safety breach.** Never publish a private key, bypass host-key validation, force a firewall change, invent a test result or claim production authorisation based on fictional C23 flags. A student who reports an accurate “not tested” meets the evidence requirement better than one who invents success.
