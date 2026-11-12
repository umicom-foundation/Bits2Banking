<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/33-qualify-identity-lifetime-with-the-installed-sdk.md

PURPOSE:
Qualify the identity and lifetime client against one SDK

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
<!-- The approved offline logo alias remains for compatibility review:
![Umicom](../../../../assets/branding/umicom-logo.svg)
New website manuscripts use the preferred supplied wordmark. -->
![Umicom](../../../../assets/branding/umicom-wordmark.svg)

# Qualify the identity and lifetime client against one SDK

## Source, installation and execution are different evidence

The complete identity_lifetime.c client calls exported Framework services. Reading its source can establish which API it intends to use. Compilation checks declarations and types; linking checks that libraries provide the referenced symbols; execution checks the selected behavior in that environment. None substitutes for the others.


## Prepare the existing laboratory

- Install a matching native Framework SDK with trading, ui and trading_ui components required by the existing lab.
- Use the compiler, architecture and runtime compatible with that SDK.
- Open labs/framework/order-lifecycle and configure against its installation prefix.
- Build btb-identity-lifetime, then run its four named CTest cases.
- Keep the commands, output and source/SDK identity together. Stop and diagnose any failure.


## Build and select the new cases

~~~powershell
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build --target btb-identity-lifetime
ctest --test-dir build -R "^learning[.]trading[.]identity-lifetime[.]" --output-on-failure
& ".\build\btb-identity-lifetime.exe" navigation
~~~


Run these PowerShell commands separately from the laboratory directory. On Linux or macOS use the appropriate SDK prefix and ./build/btb-identity-lifetime navigation. The selector covers only the four cases whose executable was built; broader suites require their other targets too.


## Interpret a failure at its boundary

| Observation | First investigation |
| --- | --- |
| Package or component missing | SDK prefix and installed component set |
| Undefined watchlist symbol | Header/library revision and architecture agreement |
| Scenario reports a failed requirement | Exact inputs, status and matching Framework implementation |
| ICO resource missing | Installed canonical branding resources |
| Native chart looks wrong | Separate application presentation and lifecycle evidence |


All five lab executables use the exported Umicom branding helper. Windows resources include the approved ICO and SVG assets are staged from the SDK. Terminal programs use the terminal font; these lesson pages use the shared Umicom stylesheet. No native window is launched by this client.


## Finish with an honest report

Record each scenario as passed, failed or unexecuted based on actual output. The authored examples here are not captured test results. A successful memory-only client proves neither broker connectivity nor native chart appearance. Do not repair an SDK mismatch by copying one header over an unrelated installation.


## Capstone question

A build succeeded but CTest could not find an executable. Is that a passing behavior check? No. Confirm that the selected target was built in the same build directory and configuration, retain the missing-executable evidence, then repeat the intended command. Skipped or not-run coverage must remain separate from passes.

## Complete source and qualification commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md and identity_lifetime.c. Compilation, installed SDK linking and execution remain separate qualification steps.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/33-qualify-identity-lifetime-with-the-installed-sdk.html)
