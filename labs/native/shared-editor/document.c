/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/shared-editor/document.c
 *
 * PURPOSE:
 *   Demonstrate named-document editing, bounded history and stale-plan refusal with shared services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
#include "umicom/document/edit.h"
#include <stdio.h>
#include <string.h>

/* Comparison helpers borrow their service arguments. Every returned text copy
 * is released with its matching Framework function, including error paths. */
static int HasText(UmiUiDocumentViewModel *views, const char *view_id, const char *expected)
{
    char *text = NULL;
    size_t bytes = 0U;
    UmiStatus status = UmiUiDocumentViewModelCopyText(views, view_id, &text, &bytes);
    int matches = status == UMI_STATUS_OK && bytes == strlen(expected) &&
                  memcmp(text, expected, bytes) == 0;
    UmiUiDocumentViewModelFreeText(text);
    return matches;
}

/* This thin client selects the intended document and asks Framework to prepare
 * and apply one edit. It owns no buffer, replacement algorithm or undo stack. */
static UmiStatus ReplaceAll(UmiDocumentCoordinator *documents, UmiDocumentId id, const char *text)
{
    UmiDocumentEditPlan *plan = NULL;
    UmiStatus status = UmiDocumentCoordinatorSelectAll(documents, id);
    if (status == UMI_STATUS_OK)
        status = UmiDocumentCoordinatorPrepareEdit(documents, id, &plan);
    if (status == UMI_STATUS_OK)
        status = UmiDocumentCoordinatorApplyEdit(documents, plan, text, strlen(text));
    UmiDocumentEditPlanDestroy(plan);
    return status;
}

static int SameWorkingState(const UmiDocumentWorkingCopySnapshot *a,
                            const UmiDocumentWorkingCopySnapshot *b)
{
    return a->document_id == b->document_id && a->revision == b->revision &&
           a->text_length == b->text_length && a->undo_count == b->undo_count &&
           a->redo_count == b->redo_count && a->dirty == b->dirty &&
           a->has_path == b->has_path && strcmp(a->view_id, b->view_id) == 0;
}

int RunDocumentLesson(const char *scenario)
{
    UmiCommandRegistry *commands = NULL;
    UmiUiWorkbench *workbench = NULL;
    UmiDocumentStore *store = NULL;
    UmiDocumentCoordinator *documents = NULL;
    UmiDocumentEditPlan *plan = NULL;
    UmiDocumentWorkingCopySnapshot target = {0}, before = {0}, after = {0};
    UmiUiDocumentViewSnapshot view = {0};
    char source_view[UMI_UI_ID_CAPACITY], other_view[UMI_UI_ID_CAPACITY];
    int result = 1;
#define REQUIRE(condition) do { if (!(condition)) { \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); goto cleanup; \
} } while (0)
#define OK(call) REQUIRE((call) == UMI_STATUS_OK)
    /* All operations use this thread. Destroy dependent owners first below. */
    OK(umi_command_registry_create(&commands));
    OK(umi_ui_workbench_create("umicom.learning.shared-editor", commands, &workbench));
    OK(umi_document_store_create(&store));
    OK(umi_document_coordinator_create(store, workbench, NULL, &documents));
    OK(umi_document_coordinator_new(documents, "lesson.txt", source_view, sizeof source_view));
    OK(umi_document_coordinator_active_snapshot(documents, &target));
    UmiUiDocumentViewModel *views = umi_ui_workbench_documents(workbench);
    REQUIRE(HasText(views, source_view, ""));
    REQUIRE(target.undo_count == 0U && !target.has_path);

    if (strcmp(scenario, "history") == 0 || strcmp(scenario, "redo-branch") == 0) {
        OK(ReplaceAll(documents, target.document_id, "one"));
        OK(ReplaceAll(documents, target.document_id, "two"));
        OK(ReplaceAll(documents, target.document_id, "caf\xc3\xa9"));
        OK(umi_document_coordinator_active_snapshot(documents, &after));
        REQUIRE(after.undo_count == 3U && after.redo_count == 0U);
        OK(UmiDocumentCoordinatorUndo(documents, target.document_id));
        REQUIRE(HasText(views, source_view, "two"));
        if (strcmp(scenario, "redo-branch") == 0) {
            OK(ReplaceAll(documents, target.document_id, "different"));
            OK(umi_document_coordinator_active_snapshot(documents, &before));
            REQUIRE(before.redo_count == 0U);
            REQUIRE(UmiDocumentCoordinatorRedo(documents, target.document_id) == UMI_STATUS_NOT_FOUND);
            OK(umi_document_coordinator_active_snapshot(documents, &after));
            REQUIRE(SameWorkingState(&before, &after) && HasText(views, source_view, "different"));
        } else {
            OK(UmiDocumentCoordinatorUndo(documents, target.document_id));
            REQUIRE(HasText(views, source_view, "one"));
            OK(UmiDocumentCoordinatorUndo(documents, target.document_id));
            REQUIRE(HasText(views, source_view, ""));
            OK(UmiDocumentCoordinatorRedo(documents, target.document_id));
            REQUIRE(HasText(views, source_view, "one"));
            OK(UmiDocumentCoordinatorRedo(documents, target.document_id));
            REQUIRE(HasText(views, source_view, "two"));
            OK(UmiDocumentCoordinatorRedo(documents, target.document_id));
            REQUIRE(HasText(views, source_view, "caf\xc3\xa9"));
        }
    } else {
        OK(ReplaceAll(documents, target.document_id, "original"));
        OK(UmiDocumentCoordinatorSelectAll(documents, target.document_id));
        if (strcmp(scenario, "read-only") == 0) {
            OK(umi_ui_document_view_model_find(views, source_view, &view));
            view.read_only = 1;
            OK(umi_ui_document_view_model_upsert(views, &view));
        }
        OK(UmiDocumentCoordinatorPrepareEdit(documents, target.document_id, &plan));
        const char *selected = NULL;
        size_t selected_bytes = 0U;
        OK(UmiDocumentEditPlanSelection(plan, &selected, &selected_bytes));
        REQUIRE(selected_bytes == 8U && memcmp(selected, "original", 8U) == 0);
        /* selected is borrowed from plan, so it must not outlive that owner. */

        if (strcmp(scenario, "other-tab") == 0) {
            OK(umi_document_coordinator_new(documents, "other.txt", other_view, sizeof other_view));
            OK(umi_document_coordinator_active_snapshot(documents, &before));
            OK(ReplaceAll(documents, before.document_id, "second"));
            OK(UmiDocumentCoordinatorApplyEdit(documents, plan, "updated", 7U));
            REQUIRE(HasText(views, source_view, "updated") && HasText(views, other_view, "second"));
            OK(umi_document_coordinator_active_snapshot(documents, &after));
            REQUIRE(after.document_id == before.document_id);
            OK(UmiDocumentCoordinatorUndo(documents, target.document_id));
            REQUIRE(HasText(views, source_view, "original"));
            OK(UmiDocumentCoordinatorRedo(documents, target.document_id));
            REQUIRE(HasText(views, source_view, "updated") && HasText(views, other_view, "second"));
            OK(umi_document_coordinator_active_snapshot(documents, &after));
            REQUIRE(after.document_id == before.document_id);
        } else {
            const char *expected = "original";
            if (strcmp(scenario, "stale-plan") == 0) {
                OK(ReplaceAll(documents, target.document_id, "newer"));
                expected = "newer";
            } else if (strcmp(scenario, "consumed-plan") == 0) {
                OK(UmiDocumentCoordinatorApplyEdit(documents, plan, "updated", 7U));
                expected = "updated";
            }
            OK(umi_document_coordinator_active_snapshot(documents, &before));
            if (strcmp(scenario, "invalid-replacement") == 0) {
                static const char malformed[] = {(char)0xc0, (char)0xaf};
                static const char embedded_zero[] = {'a', '\0', 'b'};
                REQUIRE(UmiDocumentCoordinatorApplyEdit(documents, plan, malformed,
                        sizeof malformed) == UMI_STATUS_INVALID_ARGUMENT);
                REQUIRE(UmiDocumentCoordinatorApplyEdit(documents, plan, embedded_zero,
                        sizeof embedded_zero) == UMI_STATUS_INVALID_ARGUMENT);
            } else if (strcmp(scenario, "read-only") == 0) {
                REQUIRE(UmiDocumentCoordinatorApplyEdit(documents, plan, "updated", 7U) ==
                        UMI_STATUS_PERMISSION_DENIED);
            } else if (strcmp(scenario, "stale-plan") == 0 ||
                       strcmp(scenario, "consumed-plan") == 0) {
                REQUIRE(UmiDocumentCoordinatorApplyEdit(documents, plan, "updated", 7U) ==
                        UMI_STATUS_INVALID_STATE);
            } else {
                goto cleanup;
            }
            OK(umi_document_coordinator_active_snapshot(documents, &after));
            REQUIRE(SameWorkingState(&before, &after) && HasText(views, source_view, expected));
            if (strcmp(scenario, "invalid-replacement") == 0) {
                /* Refusal leaves this capture usable while its document is unchanged. */
                OK(UmiDocumentCoordinatorApplyEdit(documents, plan, "corrected", 9U));
                REQUIRE(HasText(views, source_view, "corrected"));
            }
        }
    }
    printf("shared-editor %s: checks completed\n", scenario);
    result = 0;
cleanup:
    /* A plan borrows documents; documents borrow the store and workbench. */
    UmiDocumentEditPlanDestroy(plan);
    umi_document_coordinator_destroy(documents);
    umi_document_store_destroy(store);
    umi_ui_workbench_destroy(workbench);
    umi_command_registry_destroy(commands);
    return result;
#undef OK
#undef REQUIRE
}
