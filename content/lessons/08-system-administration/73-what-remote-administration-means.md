# Chapter 73 — What remote administration means, and why permission comes first

**Bits to Banking · System Administration From Zero · Stage 6 · Umicom Foundation**  
**Audience:** Absolute beginners, school-age learners with supervision, adults and returning professionals.  
**Starting point:** You can open PowerShell 7 or a Linux terminal and run `Get-Location` or `pwd`.  
**Safety:** Read-only first; there is no connection to an unfamiliar server in this lesson.

## Why a system administrator needs this skill

Imagine the Umicom Notes application is running on a computer in another room. You see its screen when you stand beside it, but how could an authorised administrator check it from a different machine? **Remote administration** means inspecting or managing another computer through a network. It can be convenient, but it crosses a security boundary: the remote machine must recognise *who* is requesting access, *which* device they mean and *what* they are allowed to do.

This chapter is about understanding that boundary, not opening it. No one should try a remote login just because an address or username appears in a tutorial. For class exercises, use a training VM you own or one explicitly provided by your instructor.

![A remote client, network and managed host](../../assets/diagrams/sysadmin-ssh-trust-boundary-update43.svg)

## Vocabulary in ordinary language

| Word | Meaning | Umicom example |
|---|---|---|
| **Local computer** | The machine you are using. | Your Windows laptop. |
| **Remote host** | Another machine reached over a network. | An approved Linux VM running a Notes demonstration. |
| **Client** | Software that asks another system for a service. | The `ssh` command on your laptop. |
| **Server** | Software that answers a particular kind of request. | An SSH server on the approved VM. |
| **Account** | A named identity with specific access rights. | `notes-operator`, not a shared administrator account. |
| **Authentication** | Checking that the requester controls their claimed identity. | A permitted SSH key or other supported factor. |
| **Authorisation** | Deciding what that identity can do. | Read service status, but not modify payments or production data. |
| **Host identity** | Evidence that you reached the intended computer. | A previously verified SSH host-key fingerprint. |

The difference between authentication and authorisation is especially important. Being able to log in does **not** mean someone may change files, restart a service or access an unrelated repository.

## Windows — start from a familiar prompt

**Step 1.** Open Windows Terminal and select **PowerShell**. If only *Windows PowerShell* appears, you may use it for these read-only commands. Check your shell:

```powershell
$PSVersionTable.PSVersion
Get-Location
```

**Expected:** A version number and the directory you are currently in. You do not type the `PS C:\...>` prompt itself.

**Step 2.** Ask the computer for its own name. This does not contact another machine:

```powershell
$env:COMPUTERNAME
```

**Expected:** Your Windows computer's name. It may differ from the label printed on its case.

**Step 3.** Check whether an SSH client is installed, without making a connection:

```powershell
Get-Command ssh -ErrorAction SilentlyContinue | Select-Object Name, Source
ssh -V
```

**Expected:** If present, the command location and an OpenSSH version. Some OpenSSH versions print their version to the error stream; that is not by itself a login failure. If the command is missing, record *SSH client not installed* and do not guess a replacement executable.

## Linux — use an ordinary account

Open Terminal, then type:

```bash
pwd
hostname
command -v ssh
ssh -V
```

`pwd` shows your current folder, `hostname` prints the local machine name, and `command -v` checks whether an SSH client exists. **No command here attempts a login.** Never use `sudo` merely to inspect the client version.

## Worked example: the wrong host

A teacher says the exercise server is `notes.training.invalid`. That name is deliberately fictional: `.invalid` is reserved for names that should not resolve in normal public DNS. Before doing anything, the student must establish the actual authorised host name or address and the identity-checking procedure. Typing a random address into `ssh` is not a substitute.

A professional access request records the purpose, accountable owner, authorised identity, permitted resources, start/end time, host identity method and a plan to stop or recover from errors. In Umicom, a Master Controller may coordinate a service, but application permission and security decisions remain with their authorised Framework and operating-system owners.

## Practice without a server

Draw three boxes labelled **your computer**, **network** and **approved server**. Put an `ssh` client in the first box and an SSH server in the last. Mark two checks: *verify remote host identity* and *authenticate your own account*. Now add a third check: *authorise a specific read-only task*. Explain which checks you must complete before you could inspect a real Umicom service.

## Problems and safe responses

| What you see | What it might mean | Safe next action |
|---|---|---|
| `ssh` is not recognised | Client missing or not on `PATH`. | Check `Get-Command ssh` or `command -v ssh`; do not install a server accidentally. |
| You do not know the remote hostname | The target has not been identified. | Ask the owner; do not scan arbitrary hosts. |
| You see a request to run as Administrator/root | The example requires more privilege. | Stop; this lesson needs none. |

## Check your understanding

1. **Recall:** Does successful login automatically give permission to edit other people's data? **Answer:** No; authorisation is a separate decision.
2. **Explain:** Why must the remote machine prove its identity? **Answer:** Otherwise you might provide credentials to the wrong host.
3. **Apply:** What is the safer first step if a server address is missing? **Answer:** Obtain the approved address and verification procedure from its owner.

**Record:** The commands you ran, actual output (without sensitive identifiers if sharing), and whether a client was installed. **Next:** Chapter 74 — recognising ports and listening processes.
