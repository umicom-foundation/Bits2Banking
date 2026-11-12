<!--
Umicom Bits2Banking
File: labs/native/framework-project-recipes/QUALIFICATION.md

PURPOSE:
Record source, SDK and scenario identity without conflating memory preview with application qualification.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Qualify the project recipe client

The source and twelve cases are authored. Compiler, test, filesystem, generated-project and GUI results must be recorded by the person running them.

## Identify the inputs

Record the consumer commit and working-file changes, Framework SDK producer commit, installed prefix, compiler version, architecture, runtime and operating system. Keep configure output so another reader can see which package configuration was selected. A source checkout revision alone cannot identify an installed archive.

## Run and preserve evidence

1. Follow README.md using a new consumer build directory and the intended SDK.
2. Preserve configure and build output, even when they fail.
3. Run CTest with --output-on-failure and --no-tests=error; retain all twelve case outcomes and timings.
4. Investigate any failed assertion before repeating it. Record both attempts rather than replacing the first result.
5. Run the CLI creation exercises only in an explicitly selected new destination. Record the preview, create command, exit codes and resulting file identities.
6. Build and launch the generated GTK application separately. Inspect canonical ICO/SVG resources, resource lookup, window identity, text readability and DPI behavior on the intended host.

| Evidence | Result to record |
| --- | --- |
| Consumer configuration | Not run / selected package path / diagnostic |
| Consumer compilation | Not run / completed / first failure |
| Twelve memory scenarios | Individual pass, failure or skip |
| Preview without creation | Destination unchanged / unexpected effect |
| Explicit new creation | Completed / refused / partial new files |
| Existing destination refusal | Existing content identity before and after |
| Generated build and tests | Separate commands and outcomes |
| Native branding review | Resource identity and observed desktop behavior |

The memory lab does not qualify filesystem alias containment, concurrent writers, rollback, installation, signing, boot media or native GUI interaction. Its gtk-branding case observes rendered text only. Keep these limits attached to any summary of results.
