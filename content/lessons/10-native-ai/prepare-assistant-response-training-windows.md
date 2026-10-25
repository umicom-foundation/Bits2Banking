# Prepare Assistant-Response Training Windows in Native C23

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Educational subject:** teacher forcing, token targets, loss masks and reviewed source boundaries

## Why this matters

A model trained to complete a conversation should learn from the intended **assistant answer**, not accidentally treat every instruction or right-padding token as a desired answer. That distinction is especially important for a coding assistant or financial-systems tutor: prompts provide context, while authorised completions are the training targets.

This lesson demonstrates the new Framework-owned `UmiAiTrainingSupervisedByteWindowBuild` operation. It uses the **existing byte tokenizer**; it is not a new language model, a document extractor or an automatic licensing decision. Real data must have passed the existing rights, privacy and source-integrity checks before the operation is called.

## 1. Start with one reviewed example

Suppose the prompt contains two bytes, `Hi`, and the approved completion contains three bytes, ` OK`. The Framework's reversible tokenizer maps an ordinary byte value `b` to token ID `b + 4`. It reserves `PAD=0`, `BOS=1`, `EOS=2` and `UNK=3`.

The complete conceptual sequence is:

`[BOS, H, i, SPACE, O, K, EOS]`

A next-token model receives the current token and predicts the following token. With context length eight, the **target** array is the input shifted left by one position; the unused slots are right-padded.

| Position | Decoder input | Target | Supervise loss? | Reason |
| ---: | --- | --- | --- | --- |
| 0 | BOS | H | No | Prompt begins here |
| 1 | H | i | No | Still prompt context |
| 2 | i | SPACE | **Yes** | First completion byte |
| 3 | SPACE | O | **Yes** | Completion |
| 4 | O | K | **Yes** | Completion |
| 5 | K | EOS | **Yes** | Teach reply termination |
| 6 | EOS | PAD | No | Padding |
| 7 | PAD | PAD | No | Padding |

The loss mask is `[0,0,1,1,1,1,0,0]`. **The first completion is the target associated with the final prompt token**; treating the mask as a mark on input tokens rather than target positions is a common off-by-one error.

## 2. Call the original Framework tokenizer through its new composition

```c
#include "umicom/ai/training/supervised_window.h"
#include <stdint.h>

const uint8_t prompt[] = {'H', 'i'};
const uint8_t reply[] = {' ', 'O', 'K'};
size_t inputs[8] = {0};
size_t targets[8] = {0};
uint8_t mask[8] = {0};
UmiAiTrainingSupervisedWindowInfo info = {0};

UmiStatus status = UmiAiTrainingSupervisedByteWindowBuild(
    prompt, sizeof(prompt), reply, sizeof(reply), 8U,
    inputs, 8U, targets, 8U, mask, 8U, &info);
/* On success, four target rows are supervised: three bytes and EOS. */
```

There is no new C23 tokenizer implementation in Bits2Banking. The reusable logic lives inside Umicom Framework, alongside `UmiAiByteEncode`.

## 3. Capacity and privacy are separate checks

The educational decoder accepts at most 32 context tokens. Both prompt and completion must fit *in full*. The builder rejects overflow rather than silently dropping the tail of the answer or the EOS target. Longer examples require a separately specified chunk/window policy that preserves answer boundaries and does not leak content across evaluation splits.

A successfully prepared training window is **not** an authorised training sample. It says nothing about copyright, training permission, personal information, extraction accuracy, near-duplicate contamination or an approved evaluation split. Review and verify those properties through the Framework's existing source-admission and reviewed-corpus components before training.

Raw byte tokenisation preserves all 256 possible values, including NUL; it is not Unicode-aware subword tokenisation. The reviewed-example layer validates UTF-8 text, whereas this lower-level byte window also accepts binary demonstration data.

## 4. Exercises with answers

**A.** A completion contains four bytes. How many selected targets are there when EOS is included? **Answer:** five, provided the complete example fits.

**B.** Why does the first completion target sit at the input position of the last prompt byte? **Answer:** autoregressive training predicts *the next token*; the model learns to begin responding after seeing the complete prompt.

**C.** What happens if prompt plus completion cannot fit the selected context? **Answer:** the entire preparation is rejected; no caller output array is partially filled.

**D.** Can a training manifest be approved just because it contains valid token IDs? **Answer:** no. Rights, provenance, privacy review, source integrity and split policy are independent admission decisions.

**Next:** [Compute response-only cross-entropy](selected-token-cross-entropy-in-c23.md).
