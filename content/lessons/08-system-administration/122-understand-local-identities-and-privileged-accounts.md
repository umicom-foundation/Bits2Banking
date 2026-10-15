# Chapter 122 — Who can sign in, and what can they change?

*System Administration From Zero · Stage 10 · Umicom Foundation*

A school library does not give every visitor the keys to its storeroom. Likewise, a computer should not give every user the right to install software, read other people's private files or change important system settings.

A **user account** identifies somebody—or, sometimes, a service—that can access the computer. **Permissions** determine which actions that identity may perform. An **administrator account** has broader powers, so it should be used only when those powers are genuinely needed.

## Your everyday account is not your whole identity

A typical user can open applications and edit their own documents. A system administrator may need to install approved updates or configure services. A program running in the background may use a **service account**, which is intended for a particular machine job rather than ordinary interactive use.

This is the principle of **least privilege**: give an identity the access it needs, and no more. It helps protect both the organisation and the user against accidents.

## Check the account you are using on Windows

Open PowerShell and type:

```powershell
whoami
```

You will see an account name, often with the computer or domain name. To inspect your security group memberships:

```powershell
whoami /groups
```

This may produce a long list. You do not need to understand every entry. Look for familiar group names and notice that an account can belong to several groups. On Windows, *being a member* of an administrator group does not always mean the current terminal is elevated; User Account Control affects the active permissions.

To inspect local user names on a supported Windows edition, enter:

```powershell
Get-LocalUser | Select-Object Name, Enabled
```

The output may include built-in and disabled accounts. Do not delete or enable accounts because a name looks unusual.

## The Linux equivalent

On your own Linux computer, type:

```bash
whoami
id
```

`whoami` reports the current account; `id` shows its numerical user ID and groups. These are **read-only** commands. Root (UID 0) is the most privileged identity on many Unix-like systems. Avoid working as root for routine exercises.

## A decision to practise

Imagine an Umicom Notes service must read and write its own private data directory. Should it run as the computer's most powerful administrator? Usually not. It should normally use a dedicated identity with the minimum required rights and an approved recovery arrangement.

Write one example each of an ordinary user task, an administrator task and a service-account task. Then explain why each should use a different permission level.

**Suggested answer:** reading your own notes is an everyday task; installing an approved system update is administrative; writing application data under controlled service permissions is a service-account task. Keeping them separate limits the damage from mistakes or compromise.
