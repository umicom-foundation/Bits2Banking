/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/framework-activity/window.c
 *
 * PURPOSE:
 *   Compose a GTK4 window around the same checked application logic.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "activity.h"
#include <gtk/gtk.h>

typedef struct ActivityWindow {
    unsigned completed;
    GtkWidget *label;
} ActivityWindow;
static void Completed(GtkButton *button, gpointer data)
{
    (void)button;
    GtkWindow *window = g_object_ref(GTK_WINDOW(data));
    ActivityWindow *state = g_object_get_data(G_OBJECT(window), "activity");
    UmiStatus status = BtbActivityAdvance(state->completed, &state->completed);
    char text[96];
    if (status == UMI_STATUS_OK)
        g_snprintf(text, sizeof text, "Completed exercises: %u", state->completed);
    else
        g_snprintf(text, sizeof text, "Could not record exercise: %s", umi_status_text(status));
    /* GTK owns the label and window data. Hold the window while notifications
     * run so a callback cannot release state halfway through this operation. */
    gtk_label_set_text(GTK_LABEL(state->label), text);
    g_object_unref(window);
}
static void Activate(GtkApplication *application, gpointer unused)
{
    (void)unused;
    GtkWidget *window = gtk_application_window_new(application);
    gtk_window_set_title(GTK_WINDOW(window), "Learning with Umicom Framework");
    gtk_window_set_default_size(GTK_WINDOW(window), 440, 180);
    ActivityWindow *state = g_new0(ActivityWindow, 1);
    g_object_set_data_full(G_OBJECT(window), "activity", state, g_free);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_bottom(box, 20);
    state->label = gtk_label_new("Completed exercises: 0");
    GtkWidget *button = gtk_button_new_with_label("Record one exercise");
    g_signal_connect_object(button, "clicked", G_CALLBACK(Completed), window, 0);
    gtk_box_append(GTK_BOX(box), state->label);
    gtk_box_append(GTK_BOX(box), button);
    gtk_window_set_child(GTK_WINDOW(window), box);
    gtk_window_present(GTK_WINDOW(window));
}
int main(int argc, char **argv)
{
    GtkApplication *application = gtk_application_new("org.umicom.LearningActivity",
        G_APPLICATION_NON_UNIQUE);
    g_signal_connect(application, "activate", G_CALLBACK(Activate), NULL);
    int result = g_application_run(G_APPLICATION(application), argc, argv);
    g_object_unref(application);
    return result;
}
