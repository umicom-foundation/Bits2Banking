<!--
Umicom Bits2Banking
File: labs/languages/rust-activity/README.md

PURPOSE:
Build a Rust caller of the existing C activity model.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Rust client for the shared activity model

Rust is used here to teach a language boundary. The counting rule remains in
`labs/native/framework-activity/activity.c`, reached through
`labs/native/activity-adapters/bridge.c`. No Rust copy of that rule is needed.

## Prepare the tools

Install Rust with support for edition 2024, a compatible C23 compiler, CMake and
Ninja. The C example needs an installed Framework SDK exposing the base component.
Read the [adapter build guide](../../native/activity-adapters/README.md) if the
SDK is not yet available. Check `rustc --version`, `cmake --version` and
`gcc --version` before building.

The commands below start in the Bits2Banking repository. Replace the SDK path
with the prefix containing `lib/cmake/UmicomFramework`. Stop on an error.

## PowerShell with the GNU Windows target

Install the Rust GNU Windows standard library through `rustup target add
x86_64-pc-windows-gnu`. Use a matching 64-bit GNU C compiler and linker.

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/activity-adapters -B build/activity-adapters -G Ninja -DCMAKE_C_COMPILER=gcc "-DCMAKE_PREFIX_PATH=C:/umicom/installed/framework"
cmake --build build/activity-adapters
rustc --edition=2024 --target x86_64-pc-windows-gnu -C linker=gcc labs/languages/rust-activity/main.rs -L native=build/activity-adapters -l static=btb-activity-adapters -o build/rust-activity.exe
& .\build\rust-activity.exe
rustc --edition=2024 --target x86_64-pc-windows-gnu -C linker=gcc --test labs/languages/rust-activity/activity.rs -L native=build/activity-adapters -l static=btb-activity-adapters -o build/rust-activity-tests.exe
& .\build\rust-activity-tests.exe
```

## Bash on a native Linux host

Use a native Rust toolchain and C compiler for the same architecture.

```bash
cmake -S labs/native/activity-adapters -B build/activity-adapters -G Ninja -DCMAKE_C_COMPILER=cc -DCMAKE_PREFIX_PATH="$HOME/umicom-sdk"
cmake --build build/activity-adapters
rustc --edition=2024 -C linker=cc labs/languages/rust-activity/main.rs -L native=build/activity-adapters -l static=btb-activity-adapters -o build/rust-activity
./build/rust-activity
rustc --edition=2024 -C linker=cc --test labs/languages/rust-activity/activity.rs -L native=build/activity-adapters -l static=btb-activity-adapters -o build/rust-activity-tests
./build/rust-activity-tests
```

Expected program output:

```text
0 -> 1
41 -> 42
999 -> 1000
1000 -> refused
```

The test executable checks ordinary values, the boundary, invalid values and
independent calls. These are expected results, not a claim that the commands
have already passed on a particular machine.

## Follow the files

1. `main.rs` selects values and presents results.
2. `activity.rs` declares the C function and maps its sentinel into a Rust Result.
3. The existing C bridge checks the signed input and calls the shared model.
4. The shared model returns a Framework status.

The unsafe declaration is an interface obligation. The small call site documents
why its specific argument and return types match; unsafe does not validate the
library automatically. Review bridge.h whenever the boundary changes.

## Troubleshooting

An unresolved BtbActivityNext usually means the C archive was not linked.
An incompatible-object error suggests mismatched target architectures or toolchains.
Do not switch a build directory between incompatible compilers; choose another
build directory. A missing SDK package needs the SDK prefix, not a copied header
with guessed status definitions.

See the [Rust edition guide](https://doc.rust-lang.org/edition-guide/rust-2024/unsafe-extern.html)
for the external-declaration syntax.

