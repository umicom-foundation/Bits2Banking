<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/index.md

PURPOSE:
Introduce native local AI application architecture and ordered lessons.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Native Local AI Chat and Media with Umicom Framework
## Build native AI application skills
Learn how to connect local text inference to Umicom Framework, select compatible runtimes, manage conversations, ground answers in sources and plan image/video generation. The course separates application orchestration, external engine integration and Umicom's own native model development.

## Before you begin
You should understand C functions, pointers, structures and resource ownership. Start with [Learning C](../../../courses/learning-c/index.html), then [Umicom development](../../../courses/umicom-development/index.html). The [LLM from scratch course](../../../courses/llm-from-scratch/index.html) explains model internals; it is useful background but is not required to run the routing exercises. Allow roughly eight to ten hours for reading and source exercises, plus optional environment setup.

Read without an account or installation. The native lab needs CMake, a C23-capable compiler and a matching installed Framework SDK. A live request additionally needs a separately started, trusted model server. The course does not install a Python environment or a model engine.

## Lessons
1. [Read a local AI project before designing your own](../../../courses/native-local-ai-and-media/lessons/01-read-a-local-ai-project.html)
2. [Map shared Framework services to AI applications](../../../courses/native-local-ai-and-media/lessons/02-map-framework-and-applications.html)
3. [Select capabilities and budget context](../../../courses/native-local-ai-and-media/lessons/03-select-capabilities-and-budget-context.html)
4. [Own providers and requests in C](../../../courses/native-local-ai-and-media/lessons/04-own-providers-and-requests-in-c.html)
5. [Call an existing local model through Framework](../../../courses/native-local-ai-and-media/lessons/05-call-an-existing-local-model.html)
6. [Stream cancel and display model text](../../../courses/native-local-ai-and-media/lessons/06-stream-cancel-and-display-text.html)
7. [Ground answers with reviewed sources](../../../courses/native-local-ai-and-media/lessons/07-ground-answers-with-reviewed-sources.html)
8. [Design a local image generation adapter](../../../courses/native-local-ai-and-media/lessons/08-design-local-image-generation.html)
9. [Plan video generation jobs and exports](../../../courses/native-local-ai-and-media/lessons/09-plan-video-jobs-and-exports.html)
10. [Manage personas and conversations explicitly](../../../courses/native-local-ai-and-media/lessons/10-manage-personas-and-conversations.html)
11. [Build native engines with measured kernels](../../../courses/native-local-ai-and-media/lessons/11-build-native-engines-with-measured-kernels.html)
12. [Qualify a complete AI workflow](../../../courses/native-local-ai-and-media/lessons/12-qualify-a-complete-ai-workflow.html)

## Native lab and capability limits
[Open the complete C23 lab](../../../../labs/native/local-ai-routing/README.md). Six deterministic scenarios exercise shared routing/policy contracts; a seventh check rejects an invalid port. A separate explicit command sends one prompt through Framework's existing loopback provider.

The lab and regression cases are authored and awaiting compiler/runtime qualification. It is a native learning client, not a finished chat GUI, diffusion engine or video model. Image/video lessons define the integration and qualification work needed to add those capabilities. No reference-project code, persona, logo or model list is copied.

## What to produce
Keep a component map, capability table, context budget, ownership diagram, source-evidence record and media-job acceptance matrix. For each exercised path, record the exact code/model identity and observed outcome. Expected examples are not measured results.

## Primary references
- [Reference text-chat project at the reviewed revision](https://github.com/MaokunZhang/local-nsfw-model-router/tree/76c0420ed60e8a83c00cbbfc26b1d7c38a742dbe): learn from its user workflows while implementing original native contracts.
- [llama.cpp](https://github.com/ggml-org/llama.cpp): an external C/C++ text-inference engine, not an all-C Umicom implementation.
- [stable-diffusion.cpp](https://github.com/leejet/stable-diffusion.cpp): an external C/C++ diffusion-engine reference, not a dependency installed or qualified by this course.

These links support the identified projects' roles. Model compatibility and external APIs must be reviewed at the exact version selected for an integration. The practical C examples use inspected Umicom Framework APIs.
