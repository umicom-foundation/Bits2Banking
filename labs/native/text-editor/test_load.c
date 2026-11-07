/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/text-editor/test_load.c
 *
 * PURPOSE:
 *   Verify transactional file loading, line endings, capacity and unsaved-work protection.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "editor.h"
#include <stdio.h>
#include <string.h>

#define CHECK(expression) do { if (!(expression)) { \
    fprintf(stderr, "Line %d: %s\n", __LINE__, #expression); return 1; } } while (0)

static int WriteFixture(const char *path, const void *bytes, size_t length)
{
    FILE *file = fopen(path, "wb");
    if (file == NULL) return 0;
    int ok = fwrite(bytes, 1, length, file) == length;
    if (fclose(file) != 0) ok = 0;
    return ok;
}

static int SameState(const BtbEditor *left, const BtbEditor *right)
{
    /* Compare members, never padding bytes that a C assignment may ignore. */
    return left->length == right->length &&
        left->previous_length == right->previous_length &&
        left->can_undo == right->can_undo && left->dirty == right->dirty &&
        memcmp(left->text, right->text, sizeof left->text) == 0 &&
        memcmp(left->previous, right->previous, sizeof left->previous) == 0;
}

int main(int argc, char **argv)
{
    CHECK(argc == 2);
    /* CTest supplies a dedicated binary-tree directory. Only this test's
       fixed fixture file is overwritten; user documents are never inputs. */
    char path[4096];
    const int count = snprintf(path, sizeof path, "%s/load-fixture.txt", argv[1]);
    CHECK(count > 0 && (size_t)count < sizeof path);

    BtbEditor editor = {0};
    CHECK(WriteFixture(path, "alpha\r\nbeta\tend\n", 16));
    CHECK(BtbEditorLoadFile(&editor, path) == BTB_EDIT_OK);
    CHECK(strcmp(editor.text, "alpha\nbeta\tend\n") == 0);
    CHECK(editor.length == 15 && editor.dirty == 0 && editor.can_undo == 0);
    CHECK(editor.previous_length == 0);

    CHECK(BtbEditorInsert(&editor, editor.length, "!", 1) == BTB_EDIT_OK);
    const BtbEditor dirty = editor;
    CHECK(BtbEditorLoadFile(&editor, path) == BTB_EDIT_DIRTY);
    CHECK(SameState(&editor, &dirty));

    /* Prepare a known clean model with a prior undo snapshot. Failed loads
       must retain that snapshot as well as the visible text. */
    editor.dirty = 0;
    const BtbEditor before = editor;
    const unsigned char nul[] = {'a', 0, 'b'};
    const unsigned char high[] = {'a', 0xc3, 0xa9};
    const char *invalid[] = {"lone\r", "middle\rx", "control\x01"};
    for (size_t i = 0; i < sizeof invalid / sizeof invalid[0]; ++i) {
        CHECK(WriteFixture(path, invalid[i], strlen(invalid[i])));
        CHECK(BtbEditorLoadFile(&editor, path) == BTB_EDIT_INVALID);
        CHECK(SameState(&editor, &before));
    }
    CHECK(WriteFixture(path, nul, sizeof nul));
    CHECK(BtbEditorLoadFile(&editor, path) == BTB_EDIT_INVALID);
    CHECK(SameState(&editor, &before));
    CHECK(WriteFixture(path, high, sizeof high));
    CHECK(BtbEditorLoadFile(&editor, path) == BTB_EDIT_INVALID);
    CHECK(SameState(&editor, &before));

    char large[BTB_EDITOR_CAPACITY + 1U];
    memset(large, 'z', sizeof large);
    CHECK(WriteFixture(path, large, sizeof large));
    CHECK(BtbEditorLoadFile(&editor, path) == BTB_EDIT_FULL);
    CHECK(SameState(&editor, &before));
    CHECK(BtbEditorLoadFile(&editor, "") == BTB_EDIT_INVALID);
    CHECK(BtbEditorLoadFile(&editor, NULL) == BTB_EDIT_INVALID);
    CHECK(SameState(&editor, &before));
    CHECK(BtbEditorLoadFile(NULL, path) == BTB_EDIT_INVALID);

    CHECK(WriteFixture(path, large, BTB_EDITOR_CAPACITY));
    CHECK(BtbEditorLoadFile(&editor, path) == BTB_EDIT_OK);
    CHECK(editor.length == BTB_EDITOR_CAPACITY && editor.text[editor.length] == '\0');
    CHECK(editor.can_undo == 0 && editor.dirty == 0);
    CHECK(WriteFixture(path, "", 0));
    CHECK(BtbEditorLoadFile(&editor, path) == BTB_EDIT_OK);
    CHECK(editor.length == 0 && editor.text[0] == '\0');
    CHECK(editor.previous_length == 0 && editor.can_undo == 0 && editor.dirty == 0);

    /* A directory plus a child cannot resolve through this ordinary file.
       This provides a missing-path case without relying on a global name. */
    char absent[4112];
    const int absent_count = snprintf(absent, sizeof absent, "%s/child", path);
    CHECK(absent_count > 0 && (size_t)absent_count < sizeof absent);
    const BtbEditor empty = editor;
    CHECK(BtbEditorLoadFile(&editor, absent) == BTB_EDIT_IO);
    CHECK(SameState(&editor, &empty));
    puts("Existing-file load checks passed");
    return 0;
}

