<!--
Bits2Banking
File: content/simple-steps/framework-sdk-venue-report/09-reuse-the-report-in-a-client.md

PURPOSE:
Separate the future display from the existing parsing and output rules.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reuse the report in a different client

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Imagine the same report in a desktop window or an internal service. The application still needs one definition of a valid venue record. Keep that policy in the model so each entry point can use the same result and failure behaviour.

1. Open `main.c` and mark the responsibilities in order. The CLI reads an input path, calls the report function, then formats or saves the result.
2. Draw a second caller with a file picker and a results area. Place the potentially blocking file operations on a worker. Hand a completed report back to the display’s owning thread when it is ready to update.
3. Write two display outcomes from the existing tests. A successful sample updates the displayed numbers. A refused row shows its number and leaves the earlier result on screen.
4. Run the original tests before replacing any CLI display code. Use their expected values to plan the checks for the new client.

```powershell
ctest --test-dir $build -R '^learning\.venue\.(good|number|cli\.refuse_bad)$' --output-on-failure --no-tests=error
```

**Check your result.** Your sketch has one report model and a clear handoff to the display. The source lab contains the CLI and its checks. The drawing is a design exercise for a later client.

[Previous — Run and change a check](08-run-and-change-one-check.md) · [Next — Find a missing implementation](10-find-a-missing-implementation.md) · [Framework applications and GTK4](../../lessons/umicom-development/05-introduction-to-gtk4.md)
