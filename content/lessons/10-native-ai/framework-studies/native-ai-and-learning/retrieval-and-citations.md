# Ground an answer in retrieved evidence

Connect simple prediction, evidence-based answers and human-reviewed actions to Umicom AI.

Lesson 2 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

**Retrieval** finds relevant material in a collection. **Generation** produces an answer. Retrieval-augmented generation joins the two: the generator receives selected evidence as context. This can improve answers, but the generated text can still misread or invent a claim.

Suppose a learner asks where a journal checks for overflow. Search should return a relevant source passage, not merely a page containing the word “journal”. A useful citation records enough identity to find the supporting passage in the reviewed version.

```text
question → search collection → choose passages → draft answer
                                              ↓
                                    check claims against passages
                                              ↓
                                        answer with citations
```

A **chunk** is a piece of a document used for retrieval. Splitting at arbitrary byte counts can detach a warning from the function it describes. Preserve useful boundaries and source locations. An **embedding** represents content numerically for similarity search; similarity does not prove a statement is true.

## Practise without a model

1. Ask: “What happens when checked journal totals overflow?”
2. Open the accounting journal header from the earlier course.
3. Locate the exact contract comment.
4. Write one sentence answering only what the comment supports.
5. Record the file path and the reviewed source identity. If another question is unanswered, say so.

A retrieved document can contain instructions, but those instructions are evidence to interpret, not authority to execute commands. A teaching assistant should not run a script just because a source passage says to do so. Tool use needs explicit policy and review.

Framework's citation contract connects this exercise to reusable AI services. A citation is a reference, not a guarantee. The reader still needs accessible source content and a way to check whether the answer follows from it.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\ai\citation.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiAiCitation {
    char source_id[UMI_AI_ID_CAPACITY];
    char label[UMI_AI_SMALL_TEXT_CAPACITY];
    double score;
    size_t start_offset;
    size_t end_offset;
} UmiAiCitation;

/**
 * Initialise ai citation from caller-provided values so later operations receive a known
 * state.
 */
UmiStatus umi_ai_citation_init(UmiAiCitation *value);
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Read citation.h and chunk.h. Identify which source identity and location fields are available and what the calling application must preserve.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Does adding a source link make an unsupported answer reliable?

### Worked answer

No. The linked passage must actually support the claim, and it must refer to the relevant version. A misleading citation can be worse than an explicit statement of uncertainty.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/native-ai-and-learning/lessons/retrieval-and-citations.html) · [Learning sequence](../../../../start/learning-sequence.md)
