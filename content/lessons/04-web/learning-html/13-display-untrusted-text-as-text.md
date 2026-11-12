<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/13-display-untrusted-text-as-text.md

PURPOSE:
Keep record text out of executable markup

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Keep record text out of executable markup

## Before you begin
Read the table lesson. Work only with a scratch document containing synthetic notes. You will inspect bytes and escaped examples, not run an injected script.

## Separate data from the document
A note can contain characters that have meaning in HTML. If a server concatenates the note directly into its response, the browser may interpret it as markup. The display adapter must encode text for the destination context.

~~~text
Stored note:       Walk <outside> & rest
Text-node markup:  Walk &lt;outside&gt; &amp; rest
Visible text:      Walk <outside> & rest
~~~

1. Keep the original note in the model. Do not mutate stored text merely because one view uses HTML.
2. When producing an HTML text node, use the shared rendering service's escaping.
3. Avoid placing arbitrary notes in a URL, style or script. Those contexts need different admission rules.
4. Review the emitted page source and the resulting visible text separately.

## Follow the native adapter
Framework's umi_web_structured_form_render escapes its form data and does not emit a script. It requires a rooted local action path and a nonempty session-bound CSRF token supplied by the host. That renderer does not authenticate the visitor or grant record access.

~~~c
/* After the host establishes a session and authorizes the record: */
status = umi_web_structured_form_render(
    schema, form, "/observations/review", csrf_token,
    html_buffer, html_capacity, &html_length);
~~~

This fragment assumes declared buffers and an initialized form. Read the real header for limits and refused field types before adding it to a route. Do not copy a fixed demonstration token into a deployed service.

## Expected result
The synthetic note remains text when displayed. The caller can distinguish rendering refusal from a completed response. A correctly escaped page is not evidence of authentication, transport encryption or safe deployment.

## Exercise and recovery
Try the synthetic note A "quoted" label & <sample> with the existing Framework renderer in an owner-qualified test harness. Inspect both text and attribute contexts. If the output is truncated or the renderer refuses the buffer, allocate a permitted larger output buffer and repeat rendering from the original model; never publish a partial page as success.

For the exact native contract, read include/umicom/web/structured_form.h and the associated Framework tests. The [HTML forms specification](https://html.spec.whatwg.org/multipage/forms.html) provides browser background.


[Course contents](index.md) · [Previous lesson](12-read-an-observation-table.md) · [Next lesson](14-distinguish-a-draft-from-a-saved-record.md)
