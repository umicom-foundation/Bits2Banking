# Explore collection workflows

These four programs use the existing collection model. They do not introduce an application container library. The examples make ownership and failure visible before following larger Framework services.

## Prepare the lab

Install a C23 compiler, CMake and Ninja. Open a terminal in this directory. On Windows, put your compiler's bin directory on Path first. Then run each command separately and stop if it fails.

```powershell
cmake -S . -B build -G Ninja -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
```

The same commands work in Bash. CMake records compiler selection in build; use a new build directory when changing compiler families.

## Follow the programs

| Program | What to predict |
| --- | --- |
| btb-queue_pipeline | Twenty jobs arrive in order, even when the producer encounters a full queue. |
| btb-undo_trace | Eight successful edits can be undone; a ninth is rejected before changing the value. |
| btb-search_trace | Search reports the first zero at index one; missing items leave the index unchanged. |
| btb-sort_records | Negative values and duplicates survive sorting; repeating the operation preserves the sequence. |

Run an executable from build, adding .exe on Windows. A nonzero exit code indicates a failed expectation. The registered CTest checks invoke these programs automatically, alongside the existing boundary suite.

## Investigate a result

Write down inputs, expected state, actual state and the first failed operation. Inspect the model before changing an expectation. A program that prints some correct lines and then exits nonzero has not completed successfully.

The queue example is a single-threaded schedule. It teaches backpressure, not synchronization between CPU cores. The undo example has fixed storage and deliberately refuses a change when history is full. A real editor may choose another explicit policy.

These checks are authored examples; the delivery does not claim they have been compiled or executed.
