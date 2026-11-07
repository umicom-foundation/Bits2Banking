# Framework AI contracts lab

A token is a number used to represent input to a language model. A gradient is a collection of numbers describing how a model's error responds to its parameters. This lab uses small inputs to study these two independent contracts before attempting model training.

Framework owns both algorithms. This project compiles the original `byte_tokenizer.c` and `gradient_clipping.c` files from a checkout supplied by the learner. It does not copy their implementations, train a model, download weights or claim inference quality. This focused source consumer is separate from qualification of the full Framework SDK.

## Prepare the tools

1. Obtain the Bits2Banking and Umicom Framework source checkouts.
2. Install a C23 compiler, CMake and Ninja. On Windows, use the UCRT64 environment described in [the C setup guide](../../../content/lessons/learning-c/index.md). A terminal is the application in which you type commands.
3. Open the terminal. Run `cmake --version`, `ninja --version` and `gcc --version`. Each should print its version. If a command is not recognised, fix the tool installation or search path before continuing.
4. Locate Framework's `include/umicom/ai/training/byte_tokenizer.h`. The directory above `include` is the source directory needed below. The paths are examples; use your own checkout locations.

## Configure, compile and run in PowerShell

Run one command at a time and stop if it reports an error.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-ai-contracts"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=gcc -DBUILD_TESTING=ON -DUMICOM_FRAMEWORK_SOURCE="C:/umicom/Umicom-Applications/framework"
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure --no-tests=error
& ".\build\btb-ai-contracts.exe"
```

`-S .` selects the current source folder. `-B build` keeps generated files in a separate folder. The source option tells CMake where the shared implementation lives. `ctest` runs the ten named contract cases; it does not run every Framework test.

## The same lab in Bash

```bash
cd /path/to/Umicom-Bits2Banking/labs/native/framework-ai-contracts
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=gcc -DBUILD_TESTING=ON -DUMICOM_FRAMEWORK_SOURCE=/path/to/umicom-framework
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure --no-tests=error
./build/btb-ai-contracts
```

## Read the expected output

```text
byte 65 -> token 69 -> byte 65
byte 0 -> token 4 -> byte 0
byte 255 -> token 259 -> byte 255
norm=5.0 scale=0.4 elements=2 clipped=1
```

The byte zero is data here, not the end of a string. Each API receives an explicit count. IDs 0 through 3 are reserved; normal bytes map to IDs 4 through 259.

The values 3 and 4 have a combined Euclidean norm of 5 because the square root of 3×3 + 4×4 is 5. A limit of 2 gives a proposed scale of 2/5, or 0.4. The measurement function leaves the original values unchanged. An optimiser would apply a chosen policy in a later training operation.

## Follow the files

| File | Responsibility |
| --- | --- |
| `CMakeLists.txt` | Select canonical Framework source and register ten cases. |
| `main.c` | Call the APIs, check statuses and display the small result. |
| `test_contracts.c` | Exercise bytes, capacities, rejected IDs, global norms and failed-report preservation. |

Open the two Framework headers alongside the client. Find each argument at its declaration, then find the corresponding variable in `main.c`. Arrays remain owned by the caller. Use separate input, output and count storage as shown; this lab does not establish support for overlapping storage.

## Guided changes

1. Change byte 65 to 66. Predict token 70 before running.
2. Restore the input. Inspect the `encode-capacity` case. Its destination has three elements but advertises room for two. The expected result is refusal without any output or count change.
3. Inspect `reserved`. The invalid last token proves that decoding validates the whole input before writing the first output.
4. Compare `norm` and `split`. Splitting [3,4] into two arrays still measures one global norm.
5. Read `nonfinite`. It deliberately supplies NaN, meaning “not a number”. The report retains all its prior fields after rejection. The check avoids comparing unspecified structure padding.
6. Keep a record of the Framework Git revision, compiler version, exact command, exit status and test output.

## Troubleshooting

- A missing-source message means the source-directory option points to the wrong folder or an incomplete checkout.
- A missing header means the Framework include tree is incomplete. Do not copy an unrelated header into the lab to hide the problem.
- An unknown C23 option requires a compiler with C23 support. Use the documented toolchain.
- A failed contract is evidence to investigate. Keep its named case and diagnostic; do not remove the case or replace it with an unconditional pass.
- Expected output in this guide is a contract description, not a record of a test executed on your machine.

Continue with [byte token identities](../../../content/lessons/umicom-development/60-introduce-byte-token-identities.md) and [gradient measurement](../../../content/lessons/umicom-development/76-measure-a-gradient-vector.md). For the larger learning sequence, open [LLM from Scratch](../../../content/courses/llm-from-scratch/index.html).
