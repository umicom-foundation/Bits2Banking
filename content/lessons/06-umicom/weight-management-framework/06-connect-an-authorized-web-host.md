<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/weight-management-framework/06-connect-an-authorized-web-host.md

PURPOSE:
Connect the shared form to a web host

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Connect the shared form to a web host

## Before you begin
Complete the HTML forms and request lessons. Read include/umicom/web/structured_form.h and structured_form_edit.h. This chapter describes a host integration; the native console example is not an HTTP server.

## Render the current revision
The Framework renderer produces controls from the schema and current form. It escapes data for the page and requires the host to supply a local action and a session-bound CSRF token.

~~~c
status = umi_web_structured_form_render(
    umi_weight_log_schema(), form, "/observations/review",
    csrf_token, html, html_capacity, &html_length);
~~~

1. Authenticate the request and authorize access to this record before rendering.
2. Generate and bind the CSRF token through the host's session service.
3. Emit the complete page only after rendering succeeds.
4. Keep personal observations and tokens out of ordinary access diagnostics.

## Review a submission
umi_web_structured_form_prepare checks the complete submitted control contract against the current form and prepares an edit. Applying that edit remains a separate shared operation. Serialize prepare and apply with competing writes; an HTML hidden revision is not a lock.

Do not replace the generated field names with a hand-written three-field exercise and assume the adapter will accept it. The adapter also binds form identity, schema version, revision and intent.

## Exercise and expected result
Draw two browser tabs showing the same initial revision. Submit a change from the first tab. Then submit the older second tab. The old submission must be reviewed against the actual current form and refused when its revision no longer matches. The older screen must not overwrite the accepted change.

## Recovery
On refusal, preserve the submitted draft separately from accepted storage. A refreshed page should explain the conflict and offer an explicit review path. Do not echo unescaped request bytes into an error page or mark a form saved because HTML rendering succeeded.

This renderer does not supply authentication, network transport, TLS, hosting or a deployment policy. Use the existing Framework web services and separately qualify the actual host. Read the [HTML forms specification](https://html.spec.whatwg.org/multipage/forms.html) for the browser side of this boundary.


[Course contents](index.md) · [Previous lesson](05-compose-the-existing-desktop-editor.md) · [Next lesson](07-plan-a-mobile-native-boundary.md)
