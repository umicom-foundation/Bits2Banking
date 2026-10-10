# 25. Build an application with Umicom Framework

We have already built small programs in Python, C and C++. Now we will use a **real Framework learning application** to see how shared capabilities make a project easier to extend. Instead of inventing new API names, we will use examples already present in the Umicom Framework repository.

## Step 1 — find the existing learning projects

Open your Umicom Applications checkout and locate:

```text
framework/
└── examples/
    └── learning/
        ├── projects/
        │   ├── notes_model.c
        │   ├── notes_model.h
        │   ├── notes_session.c
        │   ├── notes_window.c
        │   └── test_notes_model.c
        └── CMakeLists.txt
```

These files demonstrate a model, a session application, a graphical window and a focused test. The `notes` examples use shared Framework document and UI contracts rather than embedding an unrelated application framework.

## Step 2 — configure the learning examples

On Windows, start in PowerShell at the Umicom Applications root:

```powershell
Set-Location "C:\umicom\umicom-applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake --preset windows-ucrt64-all-debug `
    -DUMICOM_BUILD_LEARNING_EXAMPLES=ON `
    -DUMICOM_LEARNING_BUILD_GUI=ON
```

This selects the complete Windows configuration and enables the optional learning examples. It does not create another Framework copy. If you only need terminal examples, set `UMICOM_LEARNING_BUILD_GUI=OFF`.

## Step 3 — build the notes model and session

```powershell
cmake --build --preset windows-ucrt64-all-debug `
    --target umicom-learning-notes-session --parallel 2
```

This target is defined in the Framework's learning project CMake files and links its notes model through the relevant Framework library. Ninja compiles the files needed for that target rather than requiring you to name each source file yourself.

Try running the built executable from the parent repository:

```powershell
& ".\build\windows-ucrt64-all-debug\bin\umicom-learning-notes-session.exe"
```

If the path differs in a particular build, locate it using:

```powershell
Get-ChildItem ".\build\windows-ucrt64-all-debug" `
    -Recurse -Filter "umicom-learning-notes-session.exe"
```

## Step 4 — inspect the actual program flow

Open `framework/examples/learning/projects/notes_session.c`. Find `main` and follow the calls that create or work with the notes model. Then open `notes_model.h`, which declares the model's public-facing contract, and `notes_model.c`, which implements it.

Notice the separation:

1. The session program chooses what the user is trying to do.
2. The notes model owns operations on note data.
3. Framework document services provide reusable underlying capabilities.
4. The application can report an error without requiring a graphical window.

The same model can be used by a graphical window without duplicating the storage rules.

## Step 5 — run the focused test

Build the test executable before running CTest, so the test is not accidentally reported as *not run*:

```powershell
cmake --build --preset windows-ucrt64-all-debug `
    --target umicom-learning-notes-model-test --parallel 2

ctest --preset windows-ucrt64-all-debug `
    -R "^framework\.learning\.projects\.notes-model$" `
    --output-on-failure
```

CTest reports whether the test passed and prints details when it fails. The test executable is registered through the learning project only when the learning examples and testing are enabled. If no tests are found, verify those configuration options rather than assuming the test passed.

## Step 6 — open the graphical Notes window

If GTK4 is installed and the GUI option is enabled:

```powershell
cmake --build --preset windows-ucrt64-all-debug `
    --target umicom-learning-notes-window --parallel 2

& ".\build\windows-ucrt64-all-debug\bin\umicom-learning-notes-window.exe"
```

The window is a thin frontend to the shared notes model. When you edit a note and save it, ask which layer owns the displayed text, which layer owns the persistent state and which component is allowed to decide whether a save succeeded.

## Step 7 — make a small, reviewable improvement

Start with a documentation or test-only change in your fork. For example, add a test for an empty or invalid note only after reading the existing test file and verifying whether that case is already covered. Run the focused test, inspect your diff and follow the [pull-request steps](../05-engineering/17-first-pull-request.md).

Do not remove existing logic because a different implementation looks shorter. Preserve public contracts, authorship and behaviour; explain any intentional replacement. When a capability is useful to multiple applications, implement it in Framework and let the applications consume it rather than copying it into each product.

**Next:** [Explore Umicom Kernel](26-umicom-kernel.md).
