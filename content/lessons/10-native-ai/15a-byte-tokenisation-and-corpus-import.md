# Supplement 15A — Reversible Byte Tokenisation in C23

**Bits to Banking · Native AI laboratory · Sammy Hegab · Umicom Foundation**

## Learning objective

Understand how a model turns source text into token IDs **without importing a pretrained tokenizer or installing a scripting environment**. This supplement precedes the planned Lesson 16 training run and uses real native Umicom Framework sources.

A tokenizer converts a sequence of input bytes into integer identifiers. The model works with identifiers; it does not read a C source file as text directly. In this first reproducible baseline, tokenisation is deliberately simple and lossless: every byte has its own ID.

## Vocabulary and special tokens

IDs `0` through `3` are reserved for padding, begin-of-sequence, end-of-sequence and unknown tokens. Byte values `0` through `255` map to IDs `4` through `259`. Thus the vocabulary contains **260 IDs**, and an input byte `0x00` maps to token `4` even when it occurs inside a string. This is byte-based encoding, not a Unicode character tokenizer or a learned BPE model.

For a source fragment such as `int`, ASCII bytes have decimal values 105, 110 and 116; the resulting token IDs are `109`, `114`, `120`. Decoding subtracts four and reconstructs the exact input bytes, including UTF-8 multibyte encodings. The inverse deliberately rejects reserved special IDs instead of silently discarding them.

## Read the actual Framework API

The public contract is `framework/include/umicom/ai/training/byte_tokenizer.h`, and the implementation is `framework/src/ai/training/byte_tokenizer.c`. The functions `UmiAiByteEncode` and `UmiAiByteDecode` accept caller-owned buffers with explicit capacities and a writable output count. If an output buffer is too short or a token ID is invalid, the function returns a status and leaves output data unchanged.

This design matters in C23. If the tokenizer wrote the first 100 tokens before noticing that the destination held only 99, the caller would receive a partially changed buffer. Instead, Umicom validates capacity and all token IDs before writing.

## Build and test on Windows

From PowerShell in `C:\umicom\Umicom-Applications`:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\learning\native-llm" -B ".\build\windows-ucrt64-native-llm-debug" -G Ninja -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2
ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" -R "framework.ai.training.byte_tokenizer" --output-on-failure
```

The test checks all 256 possible bytes (including zero and 255), round-trip identity, insufficient output capacity and invalid reserved IDs.

## Why not start with BPE?

Byte Pair Encoding compresses repeated byte sequences into vocabulary tokens and is useful for large models. However, it introduces vocabulary learning, merge ranks, normalisation policies and versioned tokenizer files. The reversible byte baseline gives us a trustworthy reference against which to test those later improvements. It is inefficient for some languages and long contexts, so we should not describe it as an optimised production tokenizer.

## Questions

What is the token ID for byte 10? Why do we validate every decoded ID before modifying the output? Why must a checkpoint record which tokenizer created its training tokens? What is the difference between a byte and a Unicode character?

**Next:** [Supplement 15B — Importing source files and generating training windows](15b-native-corpus-and-next-token-windows.md).
