# Video script — Publish native LLM HTML alongside Markdown

**Bits to Banking · Umicom Foundation · Sammy Hegab**

**Learning goal:** Show contributors the two course representations and their distinct purposes.

## Opening · Repository tree

Show `content/lessons/10-native-ai` for editable Markdown manuscripts, and `content/courses/llm-from-scratch/lessons` for directly readable HTML companions. Both are educational content; reusable website and AI operations belong to Umicom Framework.

## Scene 1 · Open a written manuscript

Show headings, an inline formula, a fenced C23 API example and a `<details>` answer. Narration: “Review the manuscript's facts and relative links before preparing its browser companion.”

## Scene 2 · Open the browser version

Show the same headings, syntax-preserved code, keyboard-expandable answer and previous/next links. Use the continuation catalogue to discover new lessons. The original Lesson 1–94 course and shared artwork remain unchanged.

## Scene 3 · Verify the course

Run the Framework-owned native catalogue regression. Check that an unsafe path is rejected, that HTML-sensitive headings are escaped, and that a failed short-buffer render leaves the output untouched. Then check the static lesson hyperlinks.

## Closing · Practical exercise

Ask learners to identify the difference between “the HTML file exists”, “the link resolves” and “the source content has been technically verified”. All three checks are different.

**Production note:** A static lesson page is not permission to use its text for model training, and C23 examples must not be executed automatically by the browser.
