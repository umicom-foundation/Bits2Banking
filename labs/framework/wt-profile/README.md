# Wt profile-name laboratory

A Wt server-side form calls Umicom Framework's C profile-name policy. Each application instance owns its input and result widgets. The lab checks a naming rule; it creates no account and stores no credentials. Wt requires C++ at its widget boundary. The reusable policy remains in C23.

## Prepare

Install CMake 3.26 or later, Ninja, a C23 compiler, a compatible C++17 compiler and Wt 4 with its HTTP connector and test library. Match the operating system, architecture, compiler and runtime of the Wt libraries and this application. In particular, an MSVC Wt installation cannot be linked into a MinGW executable. Locate the Wt prefix containing its package configuration and the installed Wt resources directory.

Choose one Framework dependency route: a matching installed SDK with the profile_name component, or the primary Framework source tree containing cmake/UmicomProfileName.cmake. The source route compiles only that small C target; it does not configure the whole Framework. Neither route duplicates the validation algorithm in the lab.

## Configure, build and check events

From this lab directory in PowerShell, replace C:/libraries/wt with your real matching Wt prefix. Stop on an error. This first sequence uses the Framework source route:

~~~powershell
cmake -S . -B build-source -G Ninja -DCMAKE_BUILD_TYPE=Debug '-DCMAKE_PREFIX_PATH=C:/libraries/wt' '-DBTB_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework' -DBUILD_TESTING=ON
cmake --build build-source --parallel 2
ctest --test-dir build-source --output-on-failure -R '^btb\.wt_profile\.'
~~~

For an installed SDK, use a separate folder:

~~~powershell
cmake -S . -B build-sdk -G Ninja -DCMAKE_BUILD_TYPE=Debug '-DCMAKE_PREFIX_PATH=C:/umicom/installed/applications;C:/libraries/wt' -DBUILD_TESTING=ON
cmake --build build-sdk --parallel 2
ctest --test-dir build-sdk --output-on-failure -R '^btb\.wt_profile\.'
~~~

Configuration checks the actual Wt::Wt, Wt::HTTP and Wt::Test targets. If the test target is missing, install the matching libwttest package. Explicitly choosing BUILD_TESTING=OFF permits an application-only build; it supplies no event-test evidence. Do not substitute a successful application build for missing checks.

The nine authored CTest scenarios exercise the real application factory, button and Enter signals, length boundaries, embedded NUL, Unicode, plain output, repeated submissions and a newly created session after the previous one is destroyed. They do not open a socket or run JavaScript in a browser. The Framework policy has its own tests in tests/profile_name. All results must come from the commands you actually execute.

## Launch on loopback

CMake creates an empty public directory below the build folder. Put only intended public assets there. Locate Wt's installed resources directory before running; C:/libraries/wt/share/Wt/resources below is an example installation path, not a guaranteed package layout. Keep application source, logs and credentials outside both public locations.

~~~powershell
Test-Path 'C:/libraries/wt/share/Wt/resources'
.\build-source\btb-wt-profile.exe --docroot 'build-source/public' --resources-dir 'C:/libraries/wt/share/Wt/resources' --http-address 127.0.0.1 --http-port 9090
~~~

Continue only when Test-Path reports True for the real resources directory. For the SDK build replace both build-source paths with build-sdk. On a Unix host use matching Unix package prefixes, then ./build-source/btb-wt-profile with the same options and the real resources path. Keep the terminal open. Visit http://127.0.0.1:9090/ on the same computer and stop the server with Ctrl+C when finished.

## Observe the browser

1. Expect an empty input and the instruction to enter a name.
2. Enter Alice_7 and select Check name. Expect Accepted name: alice_7.
3. Enter ../../other and press Enter. Expect refusal to replace the previous accepted result.
4. Repeat with empty input, a non-ASCII name and 49 ASCII letters. Each is rejected.
5. Open a separate private browser context, enter Bob and confirm the first context's result remains unchanged. Two ordinary tabs can share browser state; record how you created independent contexts.
6. Use Tab, Shift+Tab and Enter. Check the input label with your assistive technology, resize and zoom, and record any inaccessible control or clipped message.
7. Inspect browser Network and Console for missing resources. Stop the server and record the visible connection-loss behaviour.

These observations cover different questions from the in-memory event tests. Save the Framework and Bits2Banking revisions, Wt/compiler versions, configuration commands, actual outcomes and failed diagnostics. No concurrent-session, browser, load or deployment pass is claimed by this source guide.

## Recover from a failure

A missing profile_name component indicates that the SDK may predate the narrow policy target; use a matching SDK or the explicit source route. Undefined symbols require checking headers and link inputs together. A Wt::HTTP or Wt::Test error requires the matching optional library, not a copied header. If a shared library cannot load, fix the runtime search path for the selected toolchain. If the port is busy, stop your own previous process or choose a free port and use it consistently in the browser.

A page that opens with resource errors needs a corrected resources path. A page that loads but shows the wrong result needs event and policy investigation. A stopped listener produces a transport failure, not a naming-rule refusal. This local lab is not a deployment recipe for an Internet-facing registration service.

[Learning Wt](../../../content/courses/learning-wt/index.html)

<!-- The previous security-wide build and source-directory document root are retained
for engineering review. The narrow policy target, explicit test layer and public
asset directory above replace those instructions while retaining the form workflow.
# Wt profile-name laboratory

A browser form calls Umicom Framework's C profile-name validator through a thin Wt C++ adapter. Each session owns its own input and output widgets. This is a local learning example; it neither registers users nor implements authentication.

## Prepare

Install CMake 3.26 or newer, Ninja, a C/C++ compiler, Wt 4 with its HTTP connector and an Umicom Framework SDK containing the security component. Use matching operating system, architecture, compiler and runtime libraries. A package prefix is the directory containing a package's lib/cmake directory. Find the real paths on your machine before using the examples.

## Run locally

In PowerShell, from this directory:

~~~powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug '-DCMAKE_PREFIX_PATH=C:/umicom/installed/applications;C:/libraries/wt'
cmake --build build --parallel 2
.\build\btb-wt-profile.exe --docroot . --http-address 127.0.0.1 --http-port 9090
~~~

For bash, choose matching Unix packages, use '-DCMAKE_PREFIX_PATH=/opt/umicom;/opt/wt', and launch ./build/btb-wt-profile with the same server options. Keep the terminal open. Visit http://127.0.0.1:9090 in a browser. Press Ctrl+C in the terminal to stop the server. The loopback address restricts this exercise to your computer; the example is not a production deployment recipe.

## Manual checks

1. Enter Alice_7 and select Check name. Expect Accepted name: alice_7.
2. Enter ../../other and press Enter. Expect a rejection instead of the previous accepted result.
3. Repeat with an empty value, a non-ASCII name and 49 letters. Each is rejected by Framework.
4. Open a separate private browser session. Enter Bob there. The first session's result must not change.
5. Use keyboard navigation to reach the input and button. Check the name label is announced by your assistive technology.
6. Stop the server. A browser connection failure now describes the stopped host, not a failed validation rule.

These are steps to execute, not recorded passes. The C validator's unit tests live in Framework tests/local_profile. Browser rendering, session separation and packaging need target-host checks as well.

## Troubleshoot

If CMake cannot find Wt::HTTP, install the Wt HTTP connector using the same toolchain as the SDK. If the server reports address in use, stop your earlier lab process or choose a free port and use that same port in the browser. Do not expose this exercise on a public network as a substitute for a reviewed deployment with TLS, access policy, request limits and operational monitoring.

[Learning Wt](../../../content/courses/learning-wt/index.html)

-->
