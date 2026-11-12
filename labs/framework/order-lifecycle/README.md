![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Local order lifecycle laboratory

An order is a request to trade. Acceptance means that this local adapter retained the request; it does not mean that an exchange executed it. This C23 program uses synthetic identifiers and Umicom Framework's simulated broker. It never connects to an account, sends an order over a network or produces a real fill.

## Prepare your tools

Install a C23 compiler, CMake 3.26 or later and Ninja. Install a matching Umicom Framework SDK containing the trading component and the current simulated-broker validation. An SDK is a set of headers, libraries and package files used to build another program. Use the compiler and architecture that match that SDK.

On Windows, open PowerShell and enter each command separately. Adjust the SDK location to your installation. Stop when a command reports an error.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\order-lifecycle"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
& ".\build\btb-order-lifecycle.exe"
~~~

On Linux or macOS, open a terminal in this laboratory directory and use a matching native SDK.

~~~bash
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom-sdk" -DBUILD_TESTING=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
./build/btb-order-lifecycle
~~~

The first command writes build instructions; the second compiles the program; the third runs its checks; the fourth starts the same program directly. A missing package indicates an incorrect SDK prefix or absent trading component. An undefined symbol often means headers and libraries came from different SDK revisions. Repair the installation instead of copying isolated headers.

## Expected output

~~~text
Accepted local request; revision 1. No fill has occurred.
Duplicate identifier refused; one order remains.
Cancelled local request; revision 2. Repeated cancellation changes nothing.
Local session reset. No broker account or network was used.
~~~

## Follow the program

1. The three zero initializers create known storage, a callback table and a request. The caller owns their lifetime.
2. Literal copies fill identifiers and include their terminating zero byte. These are fixed lesson strings, not a method for accepting arbitrary user input.
3. The request selects a side, limit order type, day duration, quantity, price and simulation mode. These names are enums: a finite set of declared choices.
4. The create function fills the broker table. Calling its connect member chooses the local simulation mode. The instance pointer identifies this storage.
5. Submission validates the request, checks the mode and adds one order. Finding it returns a borrowed pointer into the book. The pointer does not own or free that memory.
6. Submitting the same identifier is refused. Cancellation advances revision one to two; repeating it succeeds without advancing again.
7. Destruction resets the book. The program clears its borrowed pointer before the reset and does not use it again.

## Try a controlled change

Set quantity to zero and run again. The acceptance check should fail, because a valid request requires a positive finite quantity. Restore it to 2.0. Next, change only the request environment to paper while keeping the connection in simulation: submission should be refused. Changing the enum cannot connect this adapter to a broker's paper account; this provider is entirely local.

For each experiment record the changed line, expected result, observed result and executable revision. Do not change a check to accept an unexplained failure. Continue with [the trading course](../../../content/courses/framework-and-finance/trading-and-posttrade/index.html).


## Continue with execution events

The second executable, `btb-order-execution`, uses the public trading workspace to retain synthetic fills. It reuses Framework for order state, position arithmetic, execution identity and replay. The application does not implement another fill engine.

Use the same configure and build commands above with a current matching SDK, then select a scenario:

~~~powershell
ctest --test-dir build --output-on-failure -R "^learning[.]trading[.]order-execution[.]"
& ".\build\btb-order-execution.exe" partial
& ".\build\btb-order-execution.exe" cancel
& ".\build\btb-order-execution.exe" tiny
~~~

On Linux or macOS the equivalent direct command is `./build/btb-order-execution cancel`. The client is terminal-only. No broker transport, native UI, account, external order or settlement service is used.

| Scenario | Expected observation after the first partial fill |
| --- | --- |
| partial | One execution and a position for half the requested quantity |
| replay | Exact repeated report adds no revision, execution or position quantity |
| conflict | Same ID with a different price returns ALREADY_EXISTS and retains prior state |
| cancel | Repeated cancellation and exact earlier replay change nothing; a new fill is refused |
| filled | A distinct second fill completes the quantity; replaying it changes nothing |
| tiny | Half of a binary-exact tiny request remains a partial fill |
| overfill | A new report larger than the remainder is refused without changing the position |
| invalid | A zero-quantity report is refused before publication |

Each successful scenario first prints:

~~~text
One partial fill retained; position contains only the executed quantity.
~~~

The partial and tiny cases then finish. Other cases also print a line naming the scenario and confirming the expected revision, evidence and position checks. Every successful case ends with:

~~~text
Local demonstration complete; no broker transport or settlement was used.
~~~

These are expected results, not captured execution evidence. The client and its eight checks are authored and await owner compilation and execution. An incorrect SDK can fail to link even when source inspection succeeds. Keep installed headers and libraries at the same qualified revision.

Read `execution.c` in order: create the owner; populate a synthetic instrument; submit a request; copy the selected order identity; retain the first fill; choose one recovery or refusal scenario; inspect state; release the owner. The active failure macro always reaches the cleanup label. It does not disappear in a release build.

The continuation in [the trading course](../../../content/courses/framework-and-finance/trading-and-posttrade/index.html) explains why exact replay is checked before new-event capacity, why cancellation retains positions and why display rounding cannot authorize a fill. Revision-exhaustion and malformed-owner cases belong to Framework's internal regression fixtures; the installed client never edits private workspace fields.


## Observe a local capability refusal

The additional `policy-ioc` and `policy-fok` scenarios stop before constructing a fill. They retain a denied preview, preserve the requested draft policy and require submission to leave the order, position and execution counts at zero.

~~~powershell
& ".\build\btb-order-execution.exe" policy-ioc
& ".\build\btb-order-execution.exe" policy-fok
~~~

Expected output for either scenario:

~~~text
Unsupported local policy explained; draft retained and no order created.
Local demonstration complete; no broker transport or settlement was used.
~~~

These extend the original eight fill scenarios to ten. IOC/FOK require behavior absent from this local retained-order model. DAY/GTC remain local resting requests; callers own session-end cancellation. No automatic calendar expiry or venue matching is claimed.

## Display a full-width revision

The same laboratory now requests the Framework `ui` component for a terminal-only value example. The complete program in `revision_value.c` delegates conversion to `UmiUiValueSetUnsigned`. It demonstrates presentation of a synthetic value, without changing a private workspace revision.

~~~powershell
& ".\build\btb-revision-value.exe" small
& ".\build\btb-revision-value.exe" boundary
& ".\build\btb-revision-value.exe" maximum
ctest --test-dir build --output-on-failure -R "^learning[.]trading[.](order-execution|revision-value)[.]"
~~~

Expected direct output, in command order:

~~~text
INTEGER: 42
STRING: 9223372036854775808
STRING: 18446744073709551615
~~~

The property contract permits either kind. Large identities are decimal strings so they retain every digit and never round through a real number. This client does not start a native window. The five additional checks, the extended client and installed-SDK link remain authored and unexecuted until owner qualification.


## Observe markets through the same owner

The fourth executable, `btb-market-observation`, uses the public Framework workspace and its toolkit-neutral action controller. It creates the synthetic instrument `LAB.MARKET` and releases the workspace through one cleanup path. Quotes, depth and public prints are observations; none of these scenarios contacts a provider, submits an external order or programs hardware.

The installed SDK now needs the `trading`, `ui` and `trading_ui` components. Reconfigure with the earlier commands after installing the matching Framework headers, libraries and resource files. Do not mix a newer header with an older library. The existing shared branding helper embeds the approved Umicom ICO on Windows and stages the canonical SVG masters alongside all four lesson executables. These terminal clients use your terminal's font; their linked lesson pages use the shared Umicom typography.

Run these commands yourself after a successful configure and build:

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\order-lifecycle"
ctest --test-dir build --output-on-failure -R "^learning[.]trading[.]market-observation[.]"
& ".\build\btb-market-observation.exe" depth
& ".\build\btb-market-observation.exe" invalid-depth
& ".\build\btb-market-observation.exe" metadata
& ".\build\btb-market-observation.exe" tape
& ".\build\btb-market-observation.exe" alerts
& ".\build\btb-market-observation.exe" remove
& ".\build\btb-market-observation.exe" protect
& ".\build\btb-market-observation.exe" draft
~~~

Run each command separately and stop on an error. PowerShell does not automatically stop after a failed native command. On Linux or macOS use `./build/btb-market-observation depth` with the equivalent installed SDK and build directory.

| Scenario | Expected observation |
| --- | --- |
| depth | A valid level is retained and the workspace revision advances once |
| invalid-depth | A nonfinite active size is refused without creating depth or changing the revision |
| metadata | A valid record with a different contract multiplier is refused for the existing instrument |
| tape | A paused view retains new public prints and gap evidence; resuming exposes them without creating account fills or positions |
| alerts | A threshold crossing creates an active alert; acknowledgement clears its active state while retaining the rule |
| remove | Removing the instrument removes its associated alert and public-print records |
| protect | Engage and checked reset report their result through the shared action controller |
| draft | Editing quantity invalidates the earlier risk-preview evidence |

A successful depth scenario is expected to end with:

~~~text
Completed synthetic depth scenario through Framework.
~~~

Other scenarios name their own argument in that line. This is an expected message, not a captured run. A failed assertion reports its source line, returns a failure status and still releases the workspace. The checks remain enabled in release builds because they do not rely on the standard `assert` macro.

Read [the market-observation lessons](../../../content/courses/framework-and-finance/trading-and-posttrade/lessons/22-own-a-market-observation-client.html) alongside `market_observation.c`. The program demonstrates supported public operations with ordinary state. Framework's own fixtures separately cover exhausted revisions, damaged retained records and allocation refusal. The installed client must not obtain such states by writing private owner fields or reinitializing a live workspace in place.

If configuration cannot find `trading_ui`, install the matching Framework component before retrying. If resource compilation cannot find the Umicom ICO or SVG files, repair the SDK resource installation rather than substituting an unrelated logo. If a behavior check fails, keep its output with the SDK revision and selected scenario; changing the expected status would conceal the failure.

These eight checks and executable-resource changes are authored and statically inspected. Their compilation, installed-consumer linking, Windows resource appearance and execution remain unverified until owner qualification.


## Continue with identity and navigation lifetime

The fifth executable, **btb-identity-lifetime**, uses the installed trading component. Its complete source is **identity_lifetime.c**. Install a matching Framework SDK that includes **umi_watchlist_validate**, **umi_watchlist_find**, zero-time throttle admission and instrument-associated chart navigation. Existing headers alone are insufficient: the library must contain the same implementation.

Run each command separately from this laboratory directory and stop on errors. These commands are supplied for you to execute; they are not evidence that the client has been compiled or run.

~~~powershell
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build --target btb-identity-lifetime
ctest --test-dir build -R "^learning[.]trading[.]identity-lifetime[.]" --output-on-failure
& ".\build\btb-identity-lifetime.exe" watchlist
& ".\build\btb-identity-lifetime.exe" query
& ".\build\btb-identity-lifetime.exe" quota
& ".\build\btb-identity-lifetime.exe" navigation
~~~

On Linux or macOS, use the same CMake steps with your SDK prefix and invoke **./build/btb-identity-lifetime navigation**. This program uses synthetic identifiers and in-memory state. It opens no window or network connection.

| Scenario | Expected observation |
| --- | --- |
| watchlist | A malformed later active record refuses an earlier lookup and insertion without changing storage |
| query | A missing terminator and output inside the owner are refused; a subsequent valid query returns LAB.A |
| quota | Two attempts at timestamp zero succeed, the third is refused, and timestamp 1000 starts another window |
| navigation | Removing LAB.A leaves LAB.B's view intact; adding LAB.A again starts with default navigation |

Each successful scenario prints one sentence explaining its observation and exits with success. For navigation the expected sentence is:

~~~text
The surviving instrument keeps its chart view; the new instrument starts with defaults.
~~~

The lookup returns an index with a limited lifetime. The query scenario immediately copies the selected instrument while the list remains unchanged. The navigation scenario releases its opaque workspace through the cleanup label on success or failure. The watchlist scenario deliberately corrupts a public caller-owned record for a controlled refusal exercise; ordinary application code should use the service contract instead.

The same branding helper now applies to all five executables, including the Windows ICO and staged SVG assets. Terminal fonts are chosen by the terminal; lesson pages inherit the shared Umicom font stylesheet.

If the new symbols are undefined, compare installed headers, libraries and architecture before rebuilding. If a behavioral requirement fails, preserve the exact scenario and output instead of editing the expected result. Native chart appearance, fonts, broker behavior and installed SDK linking still require their own qualification. Continue with [identity and position](../../../content/courses/framework-and-finance/trading-and-posttrade/lessons/28-distinguish-identity-from-array-position.html).
