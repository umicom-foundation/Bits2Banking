# Lab: turn bytes into tokens and recover them

A language model processes numbers. A tokeniser converts input into those numbers using a defined vocabulary. Framework's byte tokeniser is deliberately simple: each possible byte has one token. This lab studies its exact input/output contract before attempting training.

## Setup recap

Install a C23 compiler, CMake and Ninja using [terminal setup](../learning-c/terminal-lab.md). Obtain Umicom Framework sources under `Umicom-Applications/framework`, or adapt the paths to a standalone checkout. The existing `learning/native-llm` project builds the real training service independently of application windows. No model download, account, GPU or market data is required for these checks.

If starting the course here, read [one next-token prediction](first-next-token-model.md) for the meaning of a prediction and [the first training run](first-training-run.md) for the broader experiment. Tokenisation prepares input; it does not train a model.

## 1. Read the vocabulary

Open `include/umicom/ai/training/byte_tokenizer.h`. Tokens 0–3 are reserved for padding, beginning, end and unknown markers. Ordinary bytes map to IDs 4–259. The encode function adds four to each byte value; it does not automatically insert beginning or end markers.

| Input byte | Token ID |
|---|---|
| zero | 4 |
| capital A, byte 65 | 69 |
| maximum byte, 255 | 259 |

A byte is not always a whole written character. UTF-8 can encode one character using several bytes. This tokeniser preserves those bytes; it does not claim to recognise words or language meaning.

## 2. Build only the contract target

PowerShell:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S 'C:/umicom/Umicom-Applications/framework/learning/native-llm' -B 'C:/umicom-learning/native-llm' -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build 'C:/umicom-learning/native-llm' --target umicom-ai-training-byte-tokenizer-test --parallel 2
ctest --test-dir 'C:/umicom-learning/native-llm' -R '^framework\.ai\.training\.byte_tokenizer$' --output-on-failure --no-tests=error
```

Bash:

```bash
cmake -S "$HOME/umicom/Umicom-Applications/framework/learning/native-llm" -B "$HOME/umicom-learning/native-llm" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build "$HOME/umicom-learning/native-llm" --target umicom-ai-training-byte-tokenizer-test --parallel 2
ctest --test-dir "$HOME/umicom-learning/native-llm" -R '^framework\.ai\.training\.byte_tokenizer$' --output-on-failure --no-tests=error
```

The expected selection is one test. Use `ctest -V` with the same directory and expression if you need the success text: `PASS: byte tokenizer round-trip and rejection`.

## 3. Explain the round trip

Read `tests/ai_training/test_training_byte_tokenizer.c`. It creates every possible byte value, encodes them and decodes the result. A round trip should reproduce the original bytes exactly, including zero. The test also supplies too little output space and an invalid token, then checks that failure preserves the specified outputs.

The output capacity is measured in elements. For an array of 256 `uint32_t` tokens, pass 256, not its storage size in bytes. [Length and capacity](../learning-c/19-length-capacity-and-terminators.md) explains this distinction.

## Exercise and recovery

Manually encode the three bytes A, zero and B. The answer is 69, 4 and 70. Would passing token 1 to this byte decoder represent an ordinary byte? No: it is a reserved marker, and the decoder refuses that input. Higher-level sequence logic must handle markers according to its own contract.

If the test name is absent, check `BUILD_TESTING` and the source directory. If a build fails, retain the first compiler diagnostic; changing the vocabulary to silence a test would change the data format. Continue with [training/evaluation partitions](sequence-split-contract-lab.md), then return to [LLM from Scratch](index.md).
