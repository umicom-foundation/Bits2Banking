# Lesson 148 — Build and qualify the native stacked inference laboratory

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Run CMake, CTest and a small demonstration while accurately recording what was tested.

## 1. Understand the engineering problem

The optional native laboratory is a focused test of the real stacked decoder, its existing checkpoint codec and its new inference/evaluation services. All runtime logic is C23 and lives in Umicom Framework; CMake merely describes how those native targets are built. You do not need a separate Python, PowerShell or JavaScript implementation of sampling to complete this exercise.

## 2. Follow a concrete example

From a configured Framework source tree, select the `learning/native-ai-stacked-inference` CMake project. A standard development invocation is shown below. Adjust the source and build paths for your own checkout and compiler; the lesson does not assume the application repository is the current working directory. The CTest suite covers ten independent cases, including canonical replay, binary bytes, model identity, masked evaluation, quality selection and invalid requests.

## 3. Implement through the Framework

Use these commands after merging the new Framework files: `cmake -S framework/learning/native-ai-stacked-inference -B build/native-stacked-inference -G Ninja -DBUILD_TESTING=ON`; then `cmake --build build/native-stacked-inference --parallel 2`; then `ctest --test-dir build/native-stacked-inference -R '^framework\.ai\.stacked_inference\.' --output-on-failure`. The educational demonstration is the executable `umicom-native-stacked-inference-demo`; it reports aggregate counters and held-out metrics for synthetic token IDs.

## 4. Check the boundaries

Read each failure rather than simply suppressing it. The package's structural validation against isolated test doubles is not a successful production-linked decoder test. Execute the complete native tests in the actual checkout, then run the wider stacked decoder regressions and the consolidated application build separately. A clean archive and a successful CMake configure do not establish correct training gradients or a secure LLM.

## Practice

**Question:** Why is a successful compile not equivalent to a successful model-evaluation regression?

<details>
<summary>Reveal the worked answer</summary>

Compilation verifies types and syntax. The numerical regression must also execute actual model operations and compare their results against declared invariants and independently calculated expectations.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
