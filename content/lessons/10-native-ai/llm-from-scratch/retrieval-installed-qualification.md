<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/retrieval-installed-qualification.md

PURPOSE:
Qualify the installed retrieval client and state its limits

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Qualify the installed retrieval client and state its limits

## Test the same boundary an application consumes

The laboratory includes public Framework headers and links the installed Umicom::ai target. It does not compile private copies of the ranking implementation. This checks a different boundary from a source-tree unit test: exported headers, component discovery, linked symbols and the client together. Both forms of qualification are useful, and neither should be inferred from the other.


First qualify and install the matching Framework revision through your normal workflow. Confirm that the installation includes the chunk, embedding, vector-store and retrieval validators used by the client. Combining new headers with an old library can produce missing symbols or behavior mismatches. Preserve the exact source and installation identities in your observation record.


## Build one client, then inspect named scenarios

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-retrieval-ownership"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
ctest --test-dir build --output-on-failure
.\build\btb-framework-retrieval-ownership.exe rerank
~~~


Run commands individually and stop on errors. The seven CTest cases compare complete standard output, exit zero and an empty error stream. Each client scenario checks its contract before printing the expected observation. An error message is therefore a reason to investigate the named assertion, not to edit the output checker until the test turns green.


## Include branding in visible qualification

CMake calls the installed application-branding helper. It stages the approved SVG assets and uses the approved ICO through the Windows resource compiler. NO_RUNTIME_DEPLOYMENT keeps this console client from requesting GTK deployment. The lessons use the shared stylesheet with Segoe UI and Cascadia Code fallbacks. Static asset identities do not prove how a particular shell, browser or native reader renders them.


These commands and cases are authored but have not been executed for this laboratory. Record actual pass, failure and skipped results separately when you run them. If configuration fails, check the installation prefix and component exports first. If execution fails before reaching main, check that the runtime libraries match the linked installation.


## Write a bounded conclusion

A useful report says which seven local contracts were exercised, on which revision and toolchain, with which actual results. It also states that no model was trained, no network provider was contacted and no retrieval-quality benchmark was performed. Continue developing those capabilities with separate evidence rather than expanding the meaning of a successful small client.


## Read and run the client

[Setup, expected output and troubleshooting](../../../../labs/native/framework-retrieval-ownership/README.md) · [C23 example source](../../../../labs/native/framework-retrieval-ownership/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Keep callback failures from publishing partial scores](retrieval-callback-ownership.md)
