# Statement reconciliation

This optional C23 API example consumes the installed Umicom::bank_feed target. It uses
invented transaction data and performs no file writes or network requests.

Read the [integration guide](../../../content/umicom/examples/statement-reconciliation.md)
for build commands, expected output and exercises. Keep the installed headers
and library from the same Framework build.

## SDK prerequisite

The configured installation prefix must already contain
`lib/cmake/UmicomFramework/UmicomFrameworkConfig.cmake` and the matching
`bank_feed` headers and compiled library. Setting `CMAKE_PREFIX_PATH` does
not create an SDK.

The integration guide includes the full Applications configure, build and
installation sequence, followed by this example's three regression checks.
Follow those steps in order and stop if any command fails. Do not point
`UmicomFramework_DIR` at a generated build-tree configuration to bypass a
missing installation.
