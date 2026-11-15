<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/14-comfyui-workflows-and-local-jobs.md

PURPOSE:
Teach comfyUI workflows and local generation jobs.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# ComfyUI workflows and local generation jobs

ComfyUI is useful for learning how a media workflow connects operations: loading a model, encoding a prompt, sampling and saving an output. Start with a reviewed workflow that already runs in your selected ComfyUI installation. Record its node types, model files and custom-node versions before trying to automate it. A graph that opens in an editor may still depend on missing models or nodes.

## Separate a graph from a request

The [ComfyUI server API](https://docs.comfy.org/development/comfyui-server/comms_routes) documents POST /prompt for queue submission, GET /history/{prompt_id} for a particular history record, /object_info for node descriptions and /ws for execution messages. Submission returns either a prompt identity or validation errors. These are transport concepts; they are not evidence that a generated image exists.

1. Export the workflow in the API format supported by the installed ComfyUI version. Keep an unchanged copy and a digest.
2. Identify the exact input node and field you intend to change. Avoid replacing arbitrary text throughout the JSON file.
3. Wrap that graph in the documented request envelope. Assign a client identifier and store the returned prompt identity with your local operation.
4. Read validation errors before declaring the job queued. Observe progress and obtain the matching history entry before collecting output metadata.
5. Retrieve only reviewed output assets into a bounded destination and verify their format, dimensions and size. Import them into the media project through shared services.

```text
local operation: media-demo-001
workflow identity: SHA256 of reviewed API graph
model identity: selected checkpoint digest
provider receipt: prompt_id after accepted submission
result: absent until verified output has been retrieved
```

## A native Framework boundary

An original C adapter can prepare a bounded JSON request, own HTTP/WebSocket state and normalize observations into application-visible progress. It should reuse Framework cancellation, filesystem, media and secret-policy facilities. The Python runtime used by ComfyUI stays behind that protocol boundary; no part of this lesson claims to translate its Python implementation into C.

Do not expose a cancel button as if it always cancels only this job. The documented /interrupt operation stops the current workflow execution. A shared server needs ownership checks and a precise adapter contract before an application can safely use a global operation. Disconnection also does not prove cancellation.

## Practical exercise

Make a four-row observation sheet: rejected graph, accepted job, lost connection after submission, completed history with an unavailable output file. For each row record the local state, provider identity and next permitted action. In the lost-connection row, retain uncertainty and reconcile by identity; do not automatically resubmit.

Expected learning result: you can explain why node progress, completed execution, retrieved bytes and a branded media export are four different observations. This lesson does not install ComfyUI, download weights or provide a qualified Umicom ComfyUI adapter.

[Course contents](index.md) · [Previous lesson](13-use-an-installed-framework-sdk.md) · [Next lesson](15-runway-video-task-lifecycles.md)
