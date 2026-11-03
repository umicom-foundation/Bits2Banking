# Umicom Framework Development

Follow First application, then Build, test and investigate a change. Continue with one source-study project at a time.

[Beginner sequence](../../start/learning-sequence.md) · [Browser course](../../courses/umicom-development/index.html)

## First application: one example from source to a window

After Learning C, follow the exercise counter through its Framework interface, build description, console and GTK4 window. The C introduction is a recap, not a replacement for the C course.

1. [Introduction to C programming](01-introduction-to-c.md)
2. [Introduction to Umicom Framework](02-introduction-to-framework.md)
3. [Introduction to CMake](03-introduction-to-cmake.md)
4. [Use an installed Framework SDK](06-use-an-installed-sdk.md)
5. [Umicom Framework Development](04-framework-development.md)
6. [Introduction to GTK4](05-introduction-to-gtk4.md)

## Build, test and investigate a change

Use the same project to learn incremental builds, diagnostics and test commands. Continue with test data and skipped coverage after understanding a normal run.

1. [Build only what changed](07-build-only-what-changed.md)
2. [Read build and test evidence](08-read-build-and-test-evidence.md)
3. [Understand which program a test runs](09-understand-test-commands.md)
4. [Keep test data separate from your work](30-keep-test-data-separate.md)
5. [Understand skipped tests and host coverage](31-understand-skipped-tests-and-host-coverage.md)

## Shared services and application lifetimes

Further source studies after the first application. Follow registration and inspection before asynchronous work, waiting and connection boundaries.

1. [Register shared application services](11-register-shared-services.md)
2. [Inspect application services](12-inspect-application-services.md)
3. [Close background work safely](10-close-background-work.md)
4. [Understand waiting and timeouts](28-understand-waiting-and-timeouts.md)
5. [Follow protocol message boundaries](22-follow-protocol-message-boundaries.md)
6. [Validate a tool connection](25-validate-a-tool-connection.md)

## Project study: an offline learning reader

A separate project after shared services. Start with the reader and safe example copying, then add help, checkpoints, text and images in that order.

1. [Build an offline learning reader](13-build-an-offline-learning-reader.md)
2. [Copy examples without overwriting your work](14-copy-examples-without-overwriting.md)
3. [Connect commands to helpful guides](15-connect-commands-to-guides.md)
4. [Connect keyboard and button help](21-connect-keyboard-and-button-help.md)
5. [Keep learning checkpoints with their source revision](16-keep-revision-bound-checkpoints.md)
6. [Keep reading state consistent](17-keep-reading-state-consistent.md)
7. [Store checkpoints on a worker](18-store-checkpoints-on-a-worker.md)
8. [Remember locations without inheriting trust](19-remember-locations-without-inheriting-trust.md)
9. [Preserve structure when reading code](20-preserve-structure-when-reading-code.md)
10. [Carry image pixels from a worker to a window](23-carry-image-pixels-to-a-window.md)
11. [Find text with shared Framework services](24-find-text-with-shared-services.md)
12. [Search verified learning resources](26-search-verified-learning-resources.md)
13. [Open search results without losing your place](27-open-search-results-without-losing-your-place.md)

## Project study: application workspaces

After GTK4 events and shared services, study projects, panels, keyboard focus and retained work.

1. [Remember projects without deleting their files](29-remember-projects-without-deleting-files.md)
2. [Use Studio, Trader and Media workspaces](32-use-application-workspaces.md)
3. [Navigate panels with the keyboard](33-follow-keyboard-focus.md)
4. [Check layouts without losing your work](34-check-layout-and-draft-retention.md)

## Optional application study: calendar data

A trading-data example after the core development route; it is not a prerequisite for C or GTK4.

1. [Read calendar data without inventing values](35-read-calendar-data-without-inventing-values.md)

## Practise with the source

The [Framework project walkthrough](../../umicom/development-path.md) maps each file to its role and explains how to change, build and check the example.
