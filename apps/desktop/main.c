/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: apps/desktop/main.c
 *
 * PURPOSE:
 *   Host the existing Framework learning catalogue as a standalone desktop app.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/base/version.h"
#include "umicom/platform/rooted_files.h"
#include "umicom/ui/gtk4/learning_catalogue.h"

#include <stdlib.h>

typedef struct DesktopLaunch {
    char *root;
    char *manifest;
    gboolean failed;
} DesktopLaunch;

/* GApplication parses platform arguments before GUI registration. Arrays let
 * the local handler refuse repeated selectors instead of silently changing
 * the requested library. Values must be copied before the option dict dies. */
static const GOptionEntry options[] = {
    {"root", 0, 0, G_OPTION_ARG_STRING_ARRAY, NULL, "Bits2Banking library directory", "DIRECTORY"},
    {"manifest", 0, 0, G_OPTION_ARG_STRING_ARRAY, NULL, "Course manifest relative to the library", "PATH"},
    {G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_STRING_ARRAY, NULL, NULL, NULL},
    {NULL, 0, 0, 0, NULL, NULL, NULL}
};

static gint ReadLaunch(GApplication *application, GVariantDict *values, gpointer data)
{
    (void)application;
    DesktopLaunch *launch = data;
    const char **roots = NULL;
    const char **manifests = NULL;
    const char **remaining = NULL;
    const gboolean has_root = g_variant_dict_lookup(values, "root", "^a&s", &roots);
    const gboolean has_manifest = g_variant_dict_lookup(values, "manifest", "^a&s", &manifests);
    const gboolean has_remaining = g_variant_dict_lookup(values, G_OPTION_REMAINING, "^a&s", &remaining);
    gint result = -1;

    /* A no-option launch opens the stock catalogue. Explicit input must be a
     * single pair and meet the same rooted path contract used by Framework. */
    if ((has_remaining && remaining[0] != NULL) || has_root != has_manifest ||
        (has_root && (roots[0] == NULL || roots[1] != NULL ||
                      manifests[0] == NULL || manifests[1] != NULL))) {
        g_printerr("Supply both --root and --manifest once, or open without arguments.\n");
        result = EXIT_FAILURE;
    } else if (has_root) {
        const UmiStatus status = UmiRootedFileValidatePath(roots[0], manifests[0]);
        if (status != UMI_STATUS_OK) {
            g_printerr("Choose an absolute library and a portable relative manifest path.\n");
            result = EXIT_FAILURE;
        } else {
            launch->root = g_strdup(roots[0]);
            launch->manifest = g_strdup(manifests[0]);
        }
    }
    g_free(remaining);
    g_free(manifests);
    g_free(roots);
    return result;
}

/* Retire the Framework panel before the shell releases its reference. Worker
 * completions still run on GTK and release their Framework-owned app holds. */
static gboolean CloseCatalogue(GtkWindow *window, gpointer panel)
{
    (void)window;
    UmiLearningCatalogueGtk4Retire(GTK_WIDGET(panel));
    return FALSE;
}

static void RetireCatalogue(GtkWidget *window, gpointer panel)
{
    (void)window;
    UmiLearningCatalogueGtk4Retire(GTK_WIDGET(panel));
}

static void Activate(GtkApplication *application, gpointer data)
{
    DesktopLaunch *launch = data;
    GtkWindow *existing = gtk_application_get_active_window(application);
    if (existing != NULL) {
        gtk_window_present(existing);
        return;
    }

    /* The existing Framework panel owns every control and the library, search
     * and reader state. The standalone host supplies identity and a window. */
    const UmiVersion version = {UMICOM_FRAMEWORK_VERSION_MAJOR,
        UMICOM_FRAMEWORK_VERSION_MINOR, UMICOM_FRAMEWORK_VERSION_PATCH};
    GtkWidget *panel = UmiLearningCatalogueGtk4Create(version);
    if (panel == NULL) {
        g_printerr("Could not create the learning catalogue.\n");
        launch->failed = TRUE;
        return;
    }

    GtkWindow *window = GTK_WINDOW(gtk_application_window_new(application));
    gtk_window_set_title(window, "Umicom Bits2Banking");
    gtk_window_set_default_size(window, 900, 720);
    gtk_window_set_icon_name(window, "org.umicom.bits2banking");
    gtk_window_set_child(window, panel);
    g_signal_connect_object(window, "close-request", G_CALLBACK(CloseCatalogue), panel, 0);
    g_signal_connect_object(window, "unrealize", G_CALLBACK(RetireCatalogue), panel, 0);
    g_signal_connect_object(window, "destroy", G_CALLBACK(RetireCatalogue), panel, 0);

    /* Attach the panel before dispatch so Framework can hold the application
     * until the asynchronous read retires. The panel reports completion. */
    if (launch->root != NULL) {
        const UmiStatus status = UmiLearningCatalogueGtk4LoadManifest(panel, launch->root, launch->manifest);
        if (status != UMI_STATUS_OK)
            g_printerr("Could not dispatch course loading: %s\n", umi_status_text(status));
    }
    gtk_window_present(window);
}

int main(int argc, char **argv)
{
    /* Each process owns its explicitly chosen pack and cannot forward it to a
     * previously running window or make an implicit working-folder choice. */
    DesktopLaunch launch = {0};
    GtkApplication *application = gtk_application_new("org.umicom.bits2banking", G_APPLICATION_NON_UNIQUE);
    g_application_add_main_option_entries(G_APPLICATION(application), options);
    g_signal_connect(application, "handle-local-options", G_CALLBACK(ReadLaunch), &launch);
    g_signal_connect(application, "activate", G_CALLBACK(Activate), &launch);
    int result = g_application_run(G_APPLICATION(application), argc, argv);
    if (UmiLearningCatalogueGtk4PendingReads() != 0U || launch.failed)
        result = EXIT_FAILURE;
    g_object_unref(application);
    g_free(launch.manifest);
    g_free(launch.root);
    return result;
}
