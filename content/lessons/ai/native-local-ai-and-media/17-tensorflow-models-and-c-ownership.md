<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/17-tensorflow-models-and-c-ownership.md

PURPOSE:
Teach tensorFlow model export and C tensor ownership.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# TensorFlow model export and C tensor ownership

TensorFlow separates model authoring, saved model artifacts and inference runtimes. A tensor is a typed multidimensional array. A native application must agree with a model on element type, shape, ordering and preprocessing; a buffer with the right byte count can still represent the wrong input.

## Understand the deployment boundary

The [TensorFlow SavedModel guide](https://www.tensorflow.org/guide/saved_model) describes an artifact containing computation and trained parameters that can run without the original model-building source. The [TensorFlow C installation guide](https://www.tensorflow.org/install/lang_c) exposes the public c_api.h interface. This is a C-facing interface to an external runtime, not proof that TensorFlow itself is implemented entirely in C.

Select a reviewed runtime version and supported target before building. The C installation page includes platform-specific release limits; do not assume the latest Python wheel and a downloaded C library have matching versions or GPU support. Keep headers and binaries from the same reviewed distribution.

## Start with an allocation exercise

```c
#include <stdio.h>
#include <tensorflow/c/c_api.h>

int main(void)
{
    const int64_t shape[2] = {1, 4};
    TF_Tensor *input = TF_AllocateTensor(TF_FLOAT, shape, 2, 4 * sizeof(float));
    if (input == NULL) return 1;
    float *values = (float *)TF_TensorData(input);
    if (values == NULL) { TF_DeleteTensor(input); return 1; }
    for (int i = 0; i < 4; ++i) values[i] = (float)i;
    printf("runtime=%s, input-bytes=%zu\n", TF_Version(), TF_TensorByteSize(input));
    TF_DeleteTensor(input);
    return 0;
}
```

This complete C example checks tensor allocation and ownership only. It does not load a model or perform inference. Compile it against the reviewed TensorFlow C headers and library for your platform. On the conventional four-byte float ABI the expected byte count is 16; the runtime version is reported by the actual linked library. Keep the real output instead of substituting that expected value.

## Move from tensors to inference

1. Export a tiny model with an explicit input signature and retain reference input/output arrays.
2. Inspect the exported signature and actual graph operation names. A friendly signature alias is not automatically the operation name required by a low-level C API.
3. Load the model using the documented session API, check TF_Status after each fallible call, and bind the admitted input/output operations.
4. Compare native results with the reference using a stated numerical tolerance. Try a wrong shape and wrong type and record the actual refusal.
5. Destroy tensors, sessions, graphs and status objects according to their ownership contracts on every exit path.

## Framework extension exercise

Design a C adapter with an opaque model handle, a borrowed input view and a caller-visible output ownership rule. Admit dimension products before multiplying by element width so hostile dimensions cannot overflow allocation sizes. Put device selection and runtime lifetime in Framework; let Media choose a task and display results.

This lesson identifies an integration boundary. It does not add or qualify a TensorFlow provider in Umicom, redistribute the TensorFlow runtime or translate general Python source into C.

[Course contents](index.md) · [Previous lesson](16-langchain-retrieval-and-native-boundaries.md) · [Next lesson](18-pytorch-export-and-target-runtimes.md)
