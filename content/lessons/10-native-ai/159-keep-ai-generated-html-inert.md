# Lesson 159 — Display generated HTML as text, not executable markup

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation language:** C23

## Learning objectives

Understand the encoding and ownership invariant, follow a concrete example, identify the reusable Framework service and explain a safe failure outcome.

## 1. The engineering problem

A language model might generate `<script>`, event handler attributes or other HTML-like strings. Such output is untrusted content, even if it was produced from a verified checkpoint. A chat viewer must distinguish text display from interpreting markup.

Suppose the generated answer includes `2 < 5 & 7 > 4`. If the application inserts that string as raw HTML, the symbols may be parsed as markup. For a safe HTML text node, encode `&` as `&amp;`, `<` as `&lt;` and `>` as `&gt;`. For HTML attribute values, quotes also need escaping. A validated Unicode sequence is still not trusted application code.

A checkpoint digest proves which model bytes were used; it cannot certify that model output is true, safe or suitable for executing instructions.

## 2. Use the existing Framework boundaries

In Umicom Studio, the presentation adapter should display escaped plain text using Framework-owned UI/text facilities. The AI runtime supplies length-delimited bytes or validated Unicode text; the user interface handles authorised rendering. Do not pass model output to a shell, C compiler, trade-order service or payment API merely because the bytes are well formed.

The native educational HTML catalogue renderer `UmiEducationCourseCatalogueRender` explicitly escapes lesson headings; that principle also applies to user-visible model output, although production chat escaping and authorisation belong to their own Framework services.

## Practice

**Question:** Is valid UTF-8 sufficient to permit an AI response to be used as an HTML fragment?

<details><summary>Reveal the worked answer</summary>

No. UTF-8 validity checks encoding only. HTML must be escaped for its insertion context and any executable action requires separate authorisation.

</details>

## Continue

Return to [tokenisation and context planning](155-plan-tokenisation-before-model-scaling.md), or use [Mathematics Unit 69](../11-maths-for-ai/69-utf8-byte-sequences-and-character-counts.md) for the byte-level arithmetic. Code examples are educational and not automatically executed.

*Service to Many Leads to Greatness.*
