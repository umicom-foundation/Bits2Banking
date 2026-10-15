# Chapter 126 — Know what software is installed before updating it

*System Administration From Zero · Stage 10 · Umicom Foundation*

Updating software is often a good security practice. However, a system running business applications cannot safely install arbitrary updates without checking whether they work together.

A **software inventory** records the important programs and versions on a computer. It helps an administrator answer questions such as, “Is this computer missing a security update?” and “Will this version of the compiler work with the project?”

## Start with tools you recognise

Open PowerShell and enter:

```powershell
git --version
cmake --version
winget --version
```

If Git or CMake is installed and available on your PATH, you should see version information. If a command is not recognised, that does not prove the software is absent—it may not be installed, or its directory may be missing from PATH. For a command PowerShell can find, inspect its location:

```powershell
Get-Command git, cmake, winget -ErrorAction SilentlyContinue |
    Select-Object Name, Source
```

To inspect what the Windows package manager knows about installed applications:

```powershell
winget list
```

This command can take time and may display both programs managed by winget and others detected by Windows. We are inspecting only; we are not installing or removing anything.

## Linux has package managers too

On Debian- or Ubuntu-based Linux systems you can inspect a package with:

```bash
apt list --installed 2>/dev/null | head
```

This shows a small sample. On Fedora, another package-management system is used. The exact commands depend on the distribution.

## Why versions matter for Umicom

Imagine an Umicom application built using a particular C compiler and GTK runtime. A dependency update might fix a vulnerability but also change behaviour or require rebuilding the application. The correct response is to read the compatibility requirements, test in a suitable environment, preserve a rollback plan and install through an approved maintenance process.

This principle is even more important for licensed platforms such as Calypso, where the supported JDK, database, deployment method and APIs depend on the release and patch.

## Try it yourself

Write down the versions of Git, CMake and one text editor on your computer. Note the exact command that produced each version and the date you checked it.

**Question:** Why is “newest available” not always equivalent to “approved for this production system”? **Answer:** Supported combinations, application compatibility, testing and recovery arrangements matter as well as the age of a component.
