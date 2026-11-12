<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/18-qualify-the-client-and-product-separately.md

PURPOSE:
Qualify the example, SDK and product at separate boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Qualify the example, SDK and product at separate boundaries

## A source file is not a test result

This module supplies a real C23 client, owner commands and expected outcomes. The client has not been compiled or run during authoring. Static review can find missing local includes, broken lesson links or inconsistent package hashes; it cannot establish that the exported SDK links or the example behaves correctly.

## Run the layers in order

- Build and qualify the intended Framework source revision.
- Install a matching SDK with its headers, libraries and package metadata together.
- Configure this existing order-lifecycle laboratory against that SDK.
- Build both laboratory executables and run their registered tests.
- Run a named execution scenario and compare its printed explanation with the retained state checks.
- Qualify the actual Trader or TMS UI separately with its own source and runtime identity.

## Read the owner commands

~~~powershell
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure -R "^learning[.]trading[.]order-execution[.]"
.\build\btb-order-execution.exe cancel
~~~

Run these commands from the laboratory after following its README configuration steps. Stop on errors. An undefined symbol can mean newer headers were paired with older libraries; copying one header is not a complete SDK update. A failed configure or build means subsequent test output may describe a stale executable.

## Record useful evidence

| Record | Why it matters |
| --- | --- |
| Framework and example revisions | Identifies the source being qualified |
| Compiler, architecture and SDK prefix | Distinguishes incompatible installations |
| Configure/build exit results | Shows whether the intended executable was produced |
| Named test output and skips | Separates passed, failed and missing coverage |
| UI workflow observations | Establishes interaction beyond service calls |

## Exercise and answer

If all eight local scenarios pass, is Trader production-ready? No. These scenarios cover local owner behavior with synthetic inputs. They do not test native focus, broker transport, durable recovery, venue policy, security or settlement. Report the observed layer precisely and preserve limitations.

## Continue development

Use an unexplained failure to trace the public contract, the shared owner and the input evidence. Add a regression for the actual cause. Avoid replacing shared behavior in the application merely to make one demonstration look successful.

## Use the complete laboratory

[Read the source, owner commands and expected results](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). In an offline checkout, open labs/framework/order-lifecycle/README.md. Build and runtime qualification remains unexecuted for this authored continuation.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/18-qualify-the-client-and-product-separately.html)

[Continue: validity and local capability](19-separate-validity-from-capability.md).
