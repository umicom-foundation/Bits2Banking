<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/native-project-hidden-retired.md

PURPOSE:
Distinguish a hidden form from a retired host

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Distinguish a hidden form from a retired host

Read the focused native project guide first. Code fragments below explain the shared Framework implementation; they are not standalone applications or recorded execution results.

## Visibility is not lifetime

A hidden window can still belong to a live application. A destroyed native window can also remain as a GObject because another component retains a reference. A non-NULL pointer or retained widget therefore does not prove that its application context is available. Read DeveloperAlive and DeveloperVisible together: they answer different questions about the same controller.



~~~c
static int DeveloperVisible(const UmiGtk4DeveloperDialog *dialog)
{
    return DeveloperAlive(dialog) &&
        gtk_widget_get_visible(GTK_WIDGET(dialog->window));
}
~~~



## Keep a hidden result

When a write completes while its form is hidden, the owned result is still useful. The form retains the model/profile and offers Open Project when presented again. It does not invoke the host while hidden. When the form or parent has retired, completion only releases ownership; it must not update controls or use a borrowed application context.



## Prepare before adopting the handle

Prepare constructs a hidden form. Keep its output in local storage across construction, reacquire the live host, adopt the returned handle and then call Present. Construction and presentation can notify observers. If the host disappears before adoption, destroy the unadopted handle. The public callback context remains borrowed, so the host must destroy its owned handle before releasing that context.



## Compare native states

- hidden-completion retains a result, presents the form again and requires explicit adoption.
- parent-retired destroys the parent while retaining its object; completion must not adopt.
- form-retired destroys the native form while its controller remains owned; retained memory does not restore presentation authority.



## Keep recovery claims narrow

Destroy is not rollback. It cannot erase effects already performed, and forced process termination may prevent completion from draining. During normal shutdown, inspect pending activity while the handle is valid and keep the event loop alive. The expected tests separate memory lifetime from permission to act; neither source inspection nor an object reference proves runtime authority.



## Source and next steps

[Native project source and qualification guide](../../../docs/guides/native-project-forms.md) · [HTML edition](../../courses/umicom-development/lessons/native-project-hidden-retired.html)

[Previous lesson](native-project-result-publication.md) · [Next lesson](native-project-host-shutdown.md) · [Course index](index.md)
