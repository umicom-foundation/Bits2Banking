<!--
Umicom Bits2Banking
File: labs/native/creative-draft-recovery/README.md

PURPOSE:
Build and study a small creative recovery client against an identified Framework SDK.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Creative draft recovery with Umicom Framework

This C23 application composes the shared storyboard, creation-brief and editable-document services. It prepares local text and recovers it without making a model request. Start after the Framework course lessons on ownership and task lifetimes.

The executable uses the installed Framework branding helper. On Windows the helper embeds the approved Umicom ICO; it does not replace a console application's terminal font. Course pages use the shared Segoe UI font stack and Cascadia Code/Consolas code stack with local fallbacks.

## Prepare one matching SDK

1. Install the Framework revision that supplies media_brief_document.h and storyboard draft persistence into C:/umicom/installed/framework using the Framework build guide.
2. Confirm that the installed package, headers, archive and runtime libraries come from that same qualified build. A newer source checkout alone does not update an SDK.
3. Keep practice files in a disposable directory. The optional save command can replace its selected file.
4. Run each command separately and stop on an unexpected error.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\creative-draft-recovery -B .\build\creative-draft-recovery -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\creative-draft-recovery --parallel 2
ctest --test-dir .\build\creative-draft-recovery --output-on-failure --no-tests=error
~~~

CMake selects the explicitly supplied SDK prefix and checks the package origin and installed layout. An error at this boundary should be investigated rather than bypassed with a source-tree include path. The build contains eight named CTest scenarios, each with a ten-second timeout.

## Follow the scenarios

| Scenario | Observation required for a successful exit |
| --- | --- |
| pipeline | One scene's prepared text survives export and import with all document fields preserved. |
| unfinished | Prompt-only work recovers while preparation refuses empty title and source. |
| owned-bytes | Editing the original value does not change an already captured asset. |
| source-change | An edited prompt remains recoverable independently of a changed source and fresh preparation. |
| refused | A future format version is refused without changing any destination byte. |
| cancel | A pre-requested cancellation produces no asset and preserves the destination. |
| unresolved | An unresolved storyboard tag recovers as text; preparation needs an explicit matching inventory. |
| bounds | Invalid string storage and an oversized composition are refused without silent truncation. |

~~~powershell
& .\build\creative-draft-recovery\creative-draft-recovery.exe pipeline
& .\build\creative-draft-recovery\creative-draft-recovery.exe unfinished
& .\build\creative-draft-recovery\creative-draft-recovery.exe owned-bytes
& .\build\creative-draft-recovery\creative-draft-recovery.exe source-change
& .\build\creative-draft-recovery\creative-draft-recovery.exe refused
& .\build\creative-draft-recovery\creative-draft-recovery.exe cancel
& .\build\creative-draft-recovery\creative-draft-recovery.exe unresolved
& .\build\creative-draft-recovery\creative-draft-recovery.exe bounds
~~~

The messages describe expected local outcomes after the corresponding checks. They do not establish GUI behavior, remote provider capability or successful video rendering.

## Save and open a disposable document

The path must be an ordinary absolute path in trusted parent directories. Save uses Framework's atomic replacement and can create missing parents. The explicit --replace argument is the teaching client's replacement decision, not an option accepted by the C API.

~~~powershell
& .\build\creative-draft-recovery\creative-draft-recovery.exe save "C:\umicom\_local\practice\creative-draft.json" --replace
& .\build\creative-draft-recovery\creative-draft-recovery.exe open "C:\umicom\_local\practice\creative-draft.json" --replace-current
~~~

A restored document contains editable words, not provider permission. Save is not a conflict-detection protocol: concurrent successful writers replace in completion order. A cancellation request after publication starts does not erase a real successful write.

## Read and extend the code

1. Follow BuildStory into BuildDocument. Identify the boundary between a mutable draft and an immutable prepared plan.
2. Locate CopyText. Explain why the client chooses a scene instead of truncating full storyboard instructions to fit a smaller field.
3. Trace RoundTrip and the owner of each borrowed pointer.
4. Read Refused and Cancelled. Both must check preservation as well as status.
5. Extend a practice copy with a different scene. Keep serialization and file policy in Framework.

All input literals are synthetic. The unresolved scenario supplies only reference metadata; it does not load or upload an image. A final media production workflow must apply the canonical Umicom SVG watermark and verify the rendered output separately.

## Diagnose a failure

A missing header or undefined symbol usually requires checking the selected SDK and its installation before changing the client. A refusal status requires inspecting the specific contract: byte capacity, termination, UTF-8, version, reference identity or explicit path. Preserve the first failure and the exact command.

If a CTest selection reports no tests, inspect its generated listing and build configuration. If a native test skips because the host is unavailable, record skipped coverage separately. See [qualification](QUALIFICATION.md) and the [course contents](../../../content/courses/umicom-development/index.html).
