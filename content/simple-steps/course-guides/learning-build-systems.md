<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-build-systems.md

PURPOSE:
Provide practical first steps and a result to check for Learning Build Systems.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning Build Systems

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. From the Bits2Banking checkout with the build tools ready, type `cmake -S labs/native/build-dependency-graph -B build/dependency-graph -G Ninja -DBUILD_TESTING=ON`. [Meet the tools and the files they produce](../../lessons/05-engineering/learning-build-systems/01-tools-and-artifacts.md)
2. Type `cmake --build build/dependency-graph`. Run the same command again without editing any input. [Observe incremental work before changing the build](../../lessons/05-engineering/learning-build-systems/03-observe-incremental-work.md)
3. Type `ninja -C build/dependency-graph -n -d explain` to inspect what Ninja would rebuild. [Observe incremental work before changing the build](../../lessons/05-engineering/learning-build-systems/03-observe-incremental-work.md)

**Check your result.** The first build creates the practice program. The unchanged repeat and the dry run report no work.

[Continue in the full course](../../courses/learning-build-systems/index.html) · [All course guides](index.md)
