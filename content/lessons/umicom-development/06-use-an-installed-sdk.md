# Use an installed Framework SDK

## What an SDK contains

An application does not need to contain a separate copy of every reusable function. An SDK, or software development kit, supplies the files another project needs to use those functions. Umicom Framework's SDK contains headers, compiled libraries, and CMake package files. These are different kinds of files with different jobs.

| File | Its job | When it is used |
| --- | --- | --- |
| Header (.h) | Declares names, types and function interfaces. | The compiler reads it while translating your C source. |
| Library (.a or .lib) | Contains compiled implementations. | The linker combines the required implementations with your program. |
| Package configuration (.cmake) | Describes library targets and dependencies. | CMake reads it when configuring the project. |

A declaration is a promise about how a function can be called. The implementation is the code that performs the work. Finding a header does not prove that the corresponding implementation is installed. That is why a program can compile successfully and still fail while linking.

## Follow one real consumer

Read [the independent component consumer](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/component_integration/client/CMakeLists.txt) and [its complete C source](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/component_integration/main.c). It uses a fictional market tape, a historical replay, and broker connection settings. It opens no broker connection and submits no real order.

~~~cmake
target_link_libraries(umicom-components-client PRIVATE
    Umicom::market_tape Umicom::research_replay Umicom::ibkr_connection)
~~~

The first name identifies the program being linked. The three Umicom names identify Framework components. PRIVATE means these are dependencies of this program; it is not publishing a library interface for another program to inherit. A target is a named build item, not a folder and not a command to run immediately.

~~~text
your main.c
    | compiler reads public headers
    v
compiled main object
    | linker resolves Framework functions
    v
program + required Framework libraries
~~~

## Choose one installation deliberately

An installation prefix is the root folder selected when installing an SDK. A package folder lies below it, often under lib/cmake/UmicomFramework. A computer may have several installations. Supplying CMAKE_PREFIX_PATH normally guides the search; it does not by itself prove which package was selected.

1. Complete the Windows tools and SDK installation steps in the setup guide. Use an installation compatible with the compiler and target architecture of your consumer.
2. Open the consumer's CMakeLists.txt. Find find_package and its requested components. A required component must be available before configuration can finish.
3. For the integration laboratory, set UMICOM_EXPECTED_SDK_PREFIX to the exact installation being checked. The laboratory's installed case supplies this automatically.
4. After configuration, inspect sdk-origin.txt in that consumer's build folder. It records the selected prefix and package configuration. It does not claim a successful build or execution.
5. Build the consumer, then run its registered test. If configuration or linking fails, fix that stage before interpreting any old executable as the new result.

The full SDK also offers umicom_require_installed_sdk. Its layout check follows transitive Framework dependencies: libraries needed by other libraries. If the broker component needs platform storage services, those services must also come from the selected SDK. The full contract additionally checks the public-header identity. The smaller component laboratory deliberately checks a subset and reports that limit.

## Recognise a mixed installation

An ABI, or application binary interface, describes how compiled code exchanges arguments, values and data layouts. Two headers can look similar while describing incompatible binary layouts. Matching file names, or a package version string alone, is not enough to prove compatibility.

If an archive is missing, inspect the installation log. If a Framework dependency points into a source build, inspect the exported target metadata. If the header identity differs, use a fresh complete installation from the matching build. Do not copy a random archive into the folder merely to make the error disappear.

<details>
<summary>Check your understanding</summary>
<p>The compiler finds a declaration for UmiMarketTapeCreate, but the linker cannot find its implementation. Which SDK part should you investigate?</p>
<p><strong>Answer:</strong> Investigate the compiled library and its link dependencies. Rewriting the header does not supply the missing implementation. Check the requested package, installed archive, target linkage and matching build configuration.</p>
</details>

Continue with [the Framework SDK inspection guide](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/guides/inspecting-an-installed-sdk.html). Reading this lesson and inspecting paths do not qualify an SDK for production use.

[Previous lesson](05-introduction-to-gtk4.md) · [Course contents](index.md) · [Next lesson](07-build-only-what-changed.md)

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
