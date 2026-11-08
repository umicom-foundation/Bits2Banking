<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/37-distinguish-digest-claims-from-provenance.md

PURPOSE:
Distinguish digest claims from provenance

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish digest claims from provenance

## Prepare the exercise

Install a matching native Framework SDK with the recipe API, then build this C23 consumer using the same compiler and architecture. Run each command separately and stop on unexpected errors. The recipe stages themselves are never executed by this exercise.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-recipes -B .\build\framework-recipes -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-recipes --parallel 2
ctest --test-dir .\build\framework-recipes --output-on-failure --no-tests=error
& .\build\framework-recipes\btb-framework-recipes.exe inspect C:/umicom/Umicom-Bits2Banking/labs/native/framework-recipes/recipe.json
```

The inspect scenario should report recipe-lab with one input and one stage. CTest registers inspect, owned, identity and refuse. These are expected observations; the commands must be run to establish results in your environment.

## Understand exact-byte identity

SHA-256 is a digest of bytes. The recipe digest covers the exact JSON file, including whitespace, so semantically equivalent JSON can have different identities. Run identity mode: the exercise appends one space in memory, parses again and requires the same recipe ID but a different digest. This is useful when a qualification record must identify the actual reviewed input. It is not a canonical semantic hash.

## Read every claim at its own level

The root source entry contains a claimed byte count and digest. The toolchain entry contains a claimed digest for a provenance manifest. Parsing checks their shape and numeric range; it does not read those files and compare their content. The exercise uses the authored main.c identity and an all-zero illustrative manifest digest. A malicious or stale document can contain well-formed claims, so accepted syntax cannot establish authenticity.

## Design a verification step

For real work, capture source and toolchain bytes through the existing file-observation service, compare them to the intended record, and retain the observed identities with the environment. Decide who is trusted to approve a provenance manifest and how that approval is authenticated; an unkeyed digest alone cannot identify an author. If main.c changes, regenerate or explicitly review the expected claim. Never silently relabel stale evidence as current merely because its JSON still parses.

## Review and recover

Keep the selected JSON, diagnostic and executable identity when a check fails. Reconcile SDK headers and libraries before changing source. Correct malformed metadata without weakening the validator, and preserve unexecuted build, target and provenance checks separately from inspection results.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/source-build-recipes.md)

[Course contents](index.md) · [Previous lesson](36-use-native-recipe-inspection-and-exit-status.md) · [Next lesson](38-plan-reproducible-build-and-resume-evidence.md)
