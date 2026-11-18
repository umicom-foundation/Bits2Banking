<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/plan-context-from-a-cache-budget.md

PURPOSE:
Plan context capacity from a cache budget

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Plan context capacity from a cache budget

[Course contents](../../../courses/llm-from-scratch/index.html)
After calculating bytes per token, we can ask the reverse question: how many tokens fit within a chosen cache budget? Framework divides the budget by the checked per-token payload and limits the result to the requested capacity. Integer division rounds down. The service does not load a model, reserve memory or silently change its configuration.


## 1. Solve a boundary case

The previous lesson's geometry requires 192 bytes per token. A 1,919-byte budget fits nine tokens because ten would require 1,920 bytes. Nine tokens consume 1,728 bytes and leave 191 bytes unused. A budget of 191 bytes fits zero tokens. Zero is a valid planning answer, but it is not a useful context configuration to launch.

~~~text
affordable = min(requested_tokens, budget_bytes / bytes_per_token)
cache_bytes = affordable * bytes_per_token
unused = budget_bytes - cache_bytes
~~~


## 2. Run the shared native command

After building the updated Framework model console, open PowerShell in the Framework repository. The ten numeric arguments are cache bytes, requested tokens, sequences, layers, key heads, value heads, key dimensions, value dimensions, key element bytes and value element bytes. Their order matters.

~~~powershell
& ./build/windows-ucrt64-debug/bin/umicom-models.exe cache-plan 1919 10 2 3 2 2 4 4 2 2
~~~

The same operation is exposed by umicom models cache-plan with the same numbers. Use the actual runtime output directory reported by your configured build if it differs. The report should contain affordable_tokens=9, bytes_per_token=192, cache_bytes=1728, unused_budget_bytes=191 and request_fits=no. A fitting cache still excludes every other model cost.


## 3. Use the LLM product consumer

The optional umicom-llm-cache-plan console delegates to the same Framework command. Enable UMICOM_LLM_BUILD_CACHE_PLANNER when configuring Applications or the LLM module with a matching SDK. Its arguments omit cache-plan because the executable already selects that operation. It does not introduce a second planner or an inference engine.

~~~powershell
umicom-llm-cache-plan 1919 10 2 3 2 2 4 4 2 2
~~~


## 4. Interpret refusals

Arguments must be unsigned decimal text. Signs, spaces inside a value, hexadecimal notation, excessive length and overflow are refused. Geometry dimensions must be positive and element widths must be supported. A malformed request returns an unsuccessful exit code without printing a successful plan. A too-small but valid budget prints a plan with zero affordable tokens.


## 5. Verify a recommendation before using it

1. Check that the geometry matches the actual backend.
2. Reserve separate budgets for weights, workspace, runtime and host activity.
3. Choose a token capacity no larger than both the model's supported context and the planned capacity.
4. Recheck current system conditions before loading.
5. Measure the real operation and retain failure diagnostics; planning arithmetic is not a guarantee.

Exercise: request six tokens with a budget that could hold ten. The answer remains six. The planner treats the request as an upper bound, not an instruction to consume every available byte.


[Previous lesson](dense-kv-cache-geometry.md)

[Next lesson](separate-memory-plans-from-launch-admission.md)
