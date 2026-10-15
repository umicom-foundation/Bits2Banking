# Chapter 77 — Service identities, least privilege and audit responsibility

**Bits to Banking · System Administration From Zero · Stage 6 · Umicom Foundation**  
**Prerequisite:** Chapters 73–76.  
**Practical mode:** Read-only observation; do not create or modify operating-system accounts.

## Why services have identities

A person opening Umicom Notes has one identity. The Notes storage service may run under a different **service identity**. Separating them limits what each process can access and allows incidents to be traced back to their source. For example, a Notes API needs to read its own configuration and save notes through an approved store; it should not have unrestricted authority over banking ledgers, browser files or other users' documents.

The principle of **least privilege** means providing only the permissions required for a specified function. It is not a command to make every file unreadable. The administrator must first understand the application's actual work, files and dependencies, then grant the smallest sufficient rights. Permissions should be reviewed whenever that work changes.

![Identity, permission and scope checks before remote access](../../assets/diagrams/sysadmin-admin-change-gates-update43.svg)

## Human account versus service account

| Dimension | Human account | Service identity |
|---|---|---|
| Purpose | Person uses interactive tools. | Application runs an approved workload. |
| Typical login | Interactive with MFA when supported. | Often non-interactive, subject to platform policy. |
| Rights | Based on staff role and task. | Based on the narrow service contract. |
| Audit | Who made a change and when. | Which workload performed an operation. |
| Lifecycle | Joiner, role change, leaver. | Deployment, rotation, revocation, retirement. |

A **shared administrator account** makes accountability difficult. A student's convenient default of “run everything as administrator” is especially dangerous on systems with real data.

## Windows — inspect your current identity

Open PowerShell 7:

```powershell
whoami
whoami /groups
Get-Process -Id $PID | Select-Object ProcessName, Id
```

`whoami` reports the account associated with the current process. `/groups` shows its group memberships and may produce many entries. This reveals capabilities associated with your own session; do not assume a group name alone proves a particular operation will succeed. `$PID` refers to the current PowerShell process.

If available, inspect the *name and state only* of a familiar service:

```powershell
Get-Service | Select-Object -First 10 Name, Status, DisplayName
```

This does **not** reveal its complete service security configuration or effective file permissions. Reading that properly may require specific system rights and documented tooling.

## Linux — read your account and process identity

```bash
whoami
id
ps -p $$ -o pid,user,comm
```

`id` lists your numeric user/group identifiers and their names. These values are not passwords. `ps` shows the current terminal shell process. Services may run under a different non-interactive account such as `notes-service`; do not assume that a Linux process with a familiar name runs as the same user as your shell.

For services on systems using systemd, a read-only example is:

```bash
systemctl --user list-units --type=service --no-pager
```

This lists your user-managed services; it does not start, stop or enable anything. Some environments may have no user systemd instance.

## Worked Umicom scenario

Consider a fictional Notes system with three roles: a person who writes notes, a service that saves approved notes, and a support operator who reads service health. They should not all have the same authority. The writer needs access to their documents, the service needs narrowly scoped storage operations, and support needs logs and diagnostics **without** access to note contents. The Framework Data Server remains the authoritative persistence boundary for Umicom-owned state; frontends must not bypass it.

Now imagine a support technician wants to investigate a slow service. If they are allowed to read status and logs, do not automatically give them permission to delete database files or turn off audit logging. A reviewable change request records who requested access and who independently approved it.

## Guided practical exercise

Create a permissions matrix on paper or in a text document:

| Task | Notes user | Notes service | Support operator |
|---|---|---|---|
| Read their own note | Yes | When authorised for processing | No |
| Write a validated note through the service | Yes | Yes | No |
| Read service readiness | Maybe | Yes | Yes |
| Modify global security rules | No | No | Only a separately authorised administrator |

Challenge the matrix: what happens if a temporary support account is never removed? How could audit records distinguish the three roles?

## Common mistakes

Using Administrator/root as a universal repair technique hides permissions defects, increases blast radius and may produce files owned by the wrong account. Making directories world-writable (`chmod -R 777`) is not a diagnostic tool. Creating a service identity is an approved provisioning change, not a default classroom exercise.

## Review questions

1. What does least privilege mean? **Answer:** Only the access actually required for the task.
2. Why avoid a shared support login? **Answer:** It weakens accountability and controlled revocation.
3. Do group memberships prove a service has correct filesystem access? **Answer:** Not completely; actual resource policies and access-control entries also matter.

**Next:** Chapter 78 — firewall rules and network exposure.
