/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/framework-control-inspection/main.c
 *
 * PURPOSE:
 *   Demonstrate checked Framework control lookup, explicit reveal and window-owned callbacks.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <gtk/gtk.h>
#include <umicom/ui/gtk4/automation.h>

typedef struct LabWindow {
    GtkWidget *root;
    GtkWidget *status;
    GtkWidget *expander;
    GtkWidget *duplicate;
    unsigned confirmations;
} LabWindow;

static LabWindow *window_state(GtkWindow *window)
{
    return g_object_get_data(G_OBJECT(window), "lab-state");
}

static const char *status_text(UmiStatus status)
{
    switch (status) {
    case UMI_STATUS_OK: return "Unique control found";
    case UMI_STATUS_NOT_FOUND: return "No matching control";
    case UMI_STATUS_ALREADY_EXISTS: return "More than one matching control";
    case UMI_STATUS_INVALID_ARGUMENT: return "Invalid lookup argument";
    case UMI_STATUS_CAPACITY_EXCEEDED: return "Tree exceeds the inspection limit";
    case UMI_STATUS_CANCELLED: return "The view changed during reveal";
    default: return "Operation did not complete";
    }
}

static void inspect_clicked(GtkButton *button, GtkWindow *window)
{
    (void)button;
    LabWindow *state = window_state(window);
    void *control = NULL;
    UmiStatus status = umi_gtk4_automation_find_named_widget_checked(
        state->root, "lab-confirm", &control);
    /* A result is borrowed from this window's tree. Observe it immediately;
     * never save it across a callback, event-loop iteration or view replacement. */
    gboolean expanded = gtk_expander_get_expanded(GTK_EXPANDER(state->expander));
    char *message = g_strdup_printf("%s. Section: %s. Confirmations: %u.",
        status_text(status), expanded ? "expanded" : "collapsed", state->confirmations);
    gtk_label_set_text(GTK_LABEL(state->status), message);
    g_free(message);
}

static void reveal_clicked(GtkButton *button, GtkWindow *window)
{
    (void)button;
    LabWindow *state = window_state(window);
    UmiStatus status = umi_gtk4_automation_reveal_tagged_widget(
        state->root, "lesson.review.confirm");
    /* Reveal can notify application code. A fresh lookup after it succeeds
     * avoids keeping a borrowed child pointer through those notifications. */
    void *control = NULL;
    if (status == UMI_STATUS_OK)
        status = umi_gtk4_automation_find_tagged_widget_checked(
            state->root, "lesson.review.confirm", &control);
    gtk_label_set_text(GTK_LABEL(state->status), status == UMI_STATUS_OK
        ? "Review section selected. Click Confirm yourself; reveal does not click it."
        : status_text(status));
}

static void confirm_clicked(GtkButton *button, GtkWindow *window)
{
    (void)button;
    LabWindow *state = window_state(window);
    if (state->confirmations == G_MAXUINT) {
        gtk_label_set_text(GTK_LABEL(state->status), "Confirmation counter is full.");
        return;
    }
    ++state->confirmations;
    char *message = g_strdup_printf("Confirm callback ran. Confirmations: %u.", state->confirmations);
    gtk_label_set_text(GTK_LABEL(state->status), message);
    g_free(message);
}

static void duplicate_toggled(GtkCheckButton *button, GtkWindow *window)
{
    LabWindow *state = window_state(window);
    gtk_widget_set_name(state->duplicate,
        gtk_check_button_get_active(button) ? "lab-confirm" : "lab-other");
    gtk_label_set_text(GTK_LABEL(state->status), "Name changed. Inspect again to observe the result.");
}

static void collapse_clicked(GtkButton *button, GtkWindow *window)
{
    (void)button;
    LabWindow *state = window_state(window);
    gtk_expander_set_expanded(GTK_EXPANDER(state->expander), FALSE);
    gtk_label_set_text(GTK_LABEL(state->status), "Section collapsed; its control still belongs to the window.");
}

static void activate(GtkApplication *application, gpointer user_data)
{
    (void)user_data;
    GtkWidget *window = gtk_application_window_new(application);
    LabWindow *state = g_new0(LabWindow, 1);
    /* The window owns state. Object-bound signals disconnect when the window
     * dies and hold it alive during each callback. No global state is shared. */
    g_object_set_data_full(G_OBJECT(window), "lab-state", state, g_free);
    gtk_window_set_title(GTK_WINDOW(window), "Framework control inspection lab");
    gtk_window_set_default_size(GTK_WINDOW(window), 680, 360);
    state->root = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
    gtk_widget_set_margin_start(state->root, 18);
    gtk_widget_set_margin_end(state->root, 18);
    gtk_widget_set_margin_top(state->root, 18);
    gtk_widget_set_margin_bottom(state->root, 18);
    gtk_window_set_child(GTK_WINDOW(window), state->root);
    GtkWidget *intro = gtk_label_new("Inspect finds a control. Reveal opens its section. Confirm runs its action.");
    gtk_label_set_wrap(GTK_LABEL(intro), TRUE);
    gtk_box_append(GTK_BOX(state->root), intro);
    GtkWidget *inspect = gtk_button_new_with_label("Inspect by name");
    GtkWidget *reveal = gtk_button_new_with_label("Reveal review section");
    GtkWidget *collapse = gtk_button_new_with_label("Collapse review section");
    GtkWidget *duplicate = gtk_check_button_new_with_label("Give a second control the same GTK name");
    state->duplicate = gtk_label_new("Second named control");
    gtk_widget_set_name(state->duplicate, "lab-other");
    state->expander = gtk_expander_new("Review");
    GtkWidget *confirm = gtk_button_new_with_label("Confirm");
    gtk_widget_set_name(confirm, "lab-confirm");
    UmiStatus tagged = umi_gtk4_automation_tag_widget(confirm, "lesson.review.confirm");
    if (tagged != UMI_STATUS_OK) {
        g_warning("Cannot identify the review control: %d", (int)tagged);
        gtk_widget_set_sensitive(reveal, FALSE);
    }
    gtk_expander_set_child(GTK_EXPANDER(state->expander), confirm);
    state->status = gtk_label_new("The Review section starts collapsed. Choose Inspect by name.");
    gtk_label_set_wrap(GTK_LABEL(state->status), TRUE);
    gtk_label_set_selectable(GTK_LABEL(state->status), TRUE);
    GtkWidget *controls[] = {inspect, reveal, collapse, duplicate, state->duplicate,
        state->expander, state->status};
    for (size_t i = 0; i < G_N_ELEMENTS(controls); ++i)
        gtk_box_append(GTK_BOX(state->root), controls[i]);
    g_signal_connect_object(inspect, "clicked", G_CALLBACK(inspect_clicked), window, 0);
    g_signal_connect_object(reveal, "clicked", G_CALLBACK(reveal_clicked), window, 0);
    g_signal_connect_object(collapse, "clicked", G_CALLBACK(collapse_clicked), window, 0);
    g_signal_connect_object(confirm, "clicked", G_CALLBACK(confirm_clicked), window, 0);
    g_signal_connect_object(duplicate, "toggled", G_CALLBACK(duplicate_toggled), window, 0);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    GtkApplication *application = gtk_application_new(
        "org.umicom.learning.control-inspection", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(application, "activate", G_CALLBACK(activate), NULL);
    int result = g_application_run(G_APPLICATION(application), argc, argv);
    g_object_unref(application);
    return result;
}
