# From text to a next-token prediction

Connect simple prediction, evidence-based answers and human-reviewed actions to Umicom AI.

Lesson 1 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **language model** estimates likely continuations of text. A **token** is a unit in the model's representation: it might be a byte, character, word or word fragment. Tokenisation turns text into a sequence of identifiers. The model's numbers refer to those identifiers, so the vocabulary must stay consistent.

Begin with three tiny sentences: “open file”, “open folder” and “open file”. After the word “open”, the observed next word is “file” twice and “folder” once. A simple counting model estimates probabilities of two thirds and one third. This small model teaches the prediction idea; it is not a transformer or a competitive general-purpose assistant.

```text
text → tokens → integer IDs → model → scores → selected next token
"open file" → ["open", "file"] → [0, 1]
```

## Build a model on paper

1. Assign an identifier to each word.
2. Count transitions from “open”.
3. Divide each count by the total number of transitions.
4. Add “open folder” once more and recalculate.
5. Keep a separate sentence for evaluation rather than including every example in the counts.

**Training** changes model parameters using examples. **Inference** uses a fixed model to calculate outputs. **Evaluation** measures behaviour on defined inputs. An attractive response is not a complete evaluation; record the model, vocabulary, input and expected property.

A **tensor** is a multidimensional array of numbers. Shape describes its dimensions. Two arrays can contain the same number of values while having incompatible shapes for an operation. Later lessons in the existing LLM course develop these ideas into larger computations.

Framework's AI model contract is the source-reading bridge between educational models and application-facing metadata. Inspect what it represents; do not assume a model descriptor implements training or proves quality.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\ai\model.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiAiModel {
    char model_id[UMI_AI_ID_CAPACITY];
    char display_name[UMI_AI_SMALL_TEXT_CAPACITY];
    uint32_t context_tokens;
    uint32_t max_output_tokens;
    int supports_tools;
    int supports_embeddings;
} UmiAiModel;

/**
 * Initialise ai model from caller-provided values so later operations receive a known
 * state.
 */
UmiStatus umi_ai_model_init(UmiAiModel *value);
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Read model.h, dataset.h and evaluation.h. Separate model description, training data and evaluation evidence. Continue through the existing LLM course in the browser library.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Why must the vocabulary be saved with the trained parameters?

### Worked answer

The parameters refer to token identifiers. If identifier 1 means a different token later, the same numbers represent different text and the model's behaviour is corrupted.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/native-ai-and-learning/lessons/tokens-and-prediction.html) · [Learning sequence](../../../../start/learning-sequence.md)
