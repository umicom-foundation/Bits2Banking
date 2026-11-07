/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: main.c
 *
 * PURPOSE:
 *   Host Framework banking operations with user-selected storage and GTK-owned windows.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <gtk/gtk.h>
#include "umicom/ui/gtk4/bank_operations.h"

/* This application owns only the top-level window. The Framework launcher
 * owns its operational child and delegates all financial state to its service. */
static void Activate(GtkApplication *application, gpointer data)
{
    (void)data;
    GtkWindow *existing = gtk_application_get_active_window(application);
    if (existing != NULL) { gtk_window_present(existing); return; }
    GtkWidget *window = gtk_application_window_new(application);
    gtk_window_set_title(GTK_WINDOW(window), "Banking workspace lab");
    gtk_window_set_default_size(GTK_WINDOW(window), 880, 180);
    GtkWidget *launcher = UmiGtk4BankOperationsLauncherCreate();
    gtk_window_set_child(GTK_WINDOW(window), launcher);
    gtk_window_present(GTK_WINDOW(window));
}
int main(int argc, char **argv)
{
    GtkApplication *application = gtk_application_new(
        "org.umicom.learning.bankworkspace", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(application, "activate", G_CALLBACK(Activate), NULL);
    int result = g_application_run(G_APPLICATION(application), argc, argv);
    g_object_unref(application);
    return result;
}
