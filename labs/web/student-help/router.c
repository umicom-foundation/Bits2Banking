/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/web/student-help/router.c
 *
 * PURPOSE:
 *   Match beginner questions to existing site answers without a remote service.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stddef.h>

enum { QueryCapacity = 256 };

/* These identifiers match the answer sections on the published help page.
 * The router returns a choice without generating or executing any command. */
enum HelpAnswer {
    NoMatch, PowerShellStart, PowerShellInstall, PowerShellUpdate,
    PowerShellVersion, WinGetUnavailable, OtherPowerShellPlatform,
    SystemSpecs, WorkFolder, CTools, FirstC, GitLocal, GitClone,
    CMakeProject, FrameworkSdk, BootMedia, UmicomC, BuildLog,
    ReflectionWorkshop, FrameworkSnapshot, SetupWizard, ContributorWiki,
    KernelLaunchKit, SdkHeaderIdentity, StudioBuildArguments
};

static unsigned char queryBuffer[QueryCapacity];

/* The browser copies UTF-8 bytes here for a single synchronous call. */
unsigned char *BtbStudentHelpQuery(void)
{
    return queryBuffer;
}

size_t BtbStudentHelpCapacity(void)
{
    return sizeof queryBuffer;
}

static void Normalise(size_t length, char out[QueryCapacity + 1])
{
    size_t written = 0;
    int separate = 0;
    /* Start with English keywords. Punctuation and non-ASCII bytes can
     * separate words but never become part of a command or a substring match. */
    for (size_t i = 0; i < length; ++i) {
        unsigned char ch = queryBuffer[i];
        if (ch >= 'A' && ch <= 'Z') ch += 'a' - 'A';
        if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) {
            if (separate) out[written++] = ' ';
            out[written++] = (char)ch;
            separate = 0;
        } else {
            separate = written != 0;
        }
    }
    out[written] = '\0';
}

static int Has(const char *text, const char *term)
{
    /* Match an entire word or phrase so "C" does not match "check". */
    for (size_t i = 0; text[i]; ++i) {
        if (i && text[i - 1] != ' ') continue;
        size_t j = 0;
        while (term[j] && text[i + j] == term[j]) ++j;
        if (!term[j] && (!text[i + j] || text[i + j] == ' ')) return 1;
    }
    return 0;
}

#define ANY(text, ...) HasAny((text), (const char *const[]){__VA_ARGS__, NULL})

static int HasAny(const char *text, const char *const terms[])
{
    for (size_t i = 0; terms[i]; ++i) {
        if (Has(text, terms[i])) return 1;
    }
    return 0;
}

static enum HelpAnswer ShellAnswer(const char *text, int asksWinGet, int asksPowerShell)
{
    /* Start with platform and tool availability so a Windows command is
     * never offered as instructions for a known different operating system. */
    if (asksPowerShell && ANY(text, "mac", "macos", "linux", "ubuntu", "debian", "fedora", "wsl")) {
        return OtherPowerShellPlatform;
    }
    if (asksWinGet && ANY(text, "not recognized", "not recognised", "isn t recognized",
                          "isn t recognised", "cannot find", "can t find",
                          "could not find", "not installed", "not found", "missing", "not available",
                          "no winget", "unknown command")) {
        return WinGetUnavailable;
    }
    if (!asksPowerShell) return NoMatch;
    const int install = ANY(text, "install", "setup", "set up", "download");
    const int update = ANY(text, "update", "upgrade", "updating", "upgrading", "newer", "latest");
    /* The previous phrase rule is retained for review. Normalisation turns
     * "install/update" into "install update", which the rule did not cover. */
#if 0
    if (install && update && (Has(text, "install or update") || Has(text, "install and update"))) {
        return PowerShellStart;
    }
    /* Moving from the bundled 5.1 shell is a side-by-side installation. */
    if (install || (update && Has(text, "5 1"))) return PowerShellInstall;
#endif
    /* Use an identified 5.1 starting point before asking the learner to choose.
     * When both actions appear without that cue, the short guide checks the
     * current shell first and explains both paths regardless of punctuation. */
    if ((install || update) && Has(text, "5 1")) return PowerShellInstall;
    if (install && update) return PowerShellStart;
    if (install) return PowerShellInstall;
    if (update) return PowerShellUpdate;
    if (Has(text, "installation")) return PowerShellInstall;
    if (ANY(text, "version", "major", "open", "start", "psversiontable", "which", "check")) {
        return PowerShellVersion;
    }
    return PowerShellStart;
}

enum HelpAnswer BtbStudentHelpAnswer(size_t length)
{
    if (length == 0 || length > sizeof queryBuffer) return NoMatch;

    char text[QueryCapacity + 1];
    Normalise(length, text);

    /* Distinct course names take priority over their generic words.
     * For example, a question on Umicom C should not select the GCC lab. */
    /* Keep specific diagnostic help ahead of the general boot and SDK routes.
     * Each result opens a published exercise for the reported symptom. */
    if (ANY(text, "launch kit", "prebuilt kernel kit", "prebuilt risc v kit") &&
        ANY(text, "verify", "check", "receipt", "fingerprint", "digest"))
        return KernelLaunchKit;
    if (ANY(text, "exported sdk identity", "sdk header mismatch", "sdk header identity",
            "installed headers differ"))
        return SdkHeaderIdentity;
    if (ANY(text, "studio build", "studio ide", "umicom studio") &&
        ANY(text, "phase", "argument", "usage"))
        return StudioBuildArguments;
    /* Match the narrower guide before the broad language, SDK and OS
     * labels so "Umicom C reflection" opens the actual worked exercise. */
    if (ANY(text, "metadata snapshot", "registry snapshot")) return FrameworkSnapshot;
    if (ANY(text, "reflection", "reflect on types", "inspect a type")) return ReflectionWorkshop;
    if (Has(text, "boot and install") ||
        (ANY(text, "setup centre", "setup center") && ANY(text, "boot", "wizard", "install media")))
        return SetupWizard;
    if (ANY(text, "contributor wiki", "contribute to umicom", "contributor guide", "write a lesson"))
        return ContributorWiki;
    if (ANY(text, "umicom c", "uc file", "umicom compiler")) return UmicomC;
    if (ANY(text, "bootable usb", "boot media", "bootable drive", "bootable iso", "boot iso",
            "umicom os", "umicom kernel", "etcher")) return BootMedia;
    if (ANY(text, "framework sdk", "installed sdk", "umicom framework")) return FrameworkSdk;
    if (ANY(text, "git clone", "clone repository", "clone repo", "clone a repository",
            "clone a repo", "clone my repo", "clone my repository")) return GitClone;
    if (ANY(text, "git init", "git status", "first commit", "local git",
            "create a git repository", "create a local repository")) return GitLocal;
    if (ANY(text, "current folder", "current directory", "get location", "new item",
            "practice folder", "practice directory", "pwd", "mkdir")) return WorkFolder;
    if (ANY(text, "system specs", "computer specs", "free disk space", "free space",
            "check ram", "check memory", "windows version", "get computerinfo")) return SystemSpecs;

    const enum HelpAnswer shell = ShellAnswer(text, Has(text, "winget"),
        ANY(text, "powershell", "power shell", "pwsh", "psversiontable"));
    if (shell != NoMatch) return shell;

    if (ANY(text, "build log", "compiler error", "failed test", "first error", "compile error")) {
        return BuildLog;
    }
    if (ANY(text, "c tools", "c toolchain", "ucrt64", "msys2", "install gcc", "set up gcc")) {
        return CTools;
    }
    if (ANY(text, "cmake", "ctest", "ninja")) return CMakeProject;
    if (ANY(text, "c program", "c code", "coffee c", "coffee exe", "hello c") ||
        (Has(text, "gcc") && ANY(text, "compile", "run", "build"))) return FirstC;

    return NoMatch;
}
