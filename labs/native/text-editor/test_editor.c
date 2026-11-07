/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/text-editor/test_editor.c
 *
 * PURPOSE:
 *   Exercise insertion, overlap, deletion, undo and rejected-edit preservation.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "editor.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define CHECK(expression) do { if (!(expression)) { \
    fprintf(stderr, "Line %d: %s\n", __LINE__, #expression); return 1; } } while (0)
int main(void)
{
    BtbEditor editor = {0};
    CHECK(BtbEditorUndo(&editor) == BTB_EDIT_NO_UNDO);
    CHECK(BtbEditorInsert(&editor, 0, "ac", 2) == BTB_EDIT_OK);
    CHECK(BtbEditorInsert(&editor, 1, "b", 1) == BTB_EDIT_OK);
    CHECK(strcmp(editor.text, "abc") == 0 && editor.length == 3);
    CHECK(BtbEditorInsert(&editor, 1, editor.text, 3) == BTB_EDIT_OK);
    CHECK(strcmp(editor.text, "aabcbc") == 0);
    CHECK(BtbEditorUndo(&editor) == BTB_EDIT_OK && strcmp(editor.text, "abc") == 0);
    CHECK(BtbEditorErase(&editor, 1, 1) == BTB_EDIT_OK);
    CHECK(strcmp(editor.text, "ac") == 0);
    /* Compare fields, not struct padding: C need not copy padding bytes. */
    const size_t before_length = editor.length;
    const size_t before_previous = editor.previous_length;
    CHECK(BtbEditorErase(&editor, SIZE_MAX, 1) == BTB_EDIT_INVALID);
    CHECK(BtbEditorErase(&editor, 1, SIZE_MAX) == BTB_EDIT_INVALID);
    CHECK(BtbEditorInsert(&editor, 0, "x", SIZE_MAX) == BTB_EDIT_FULL);
    CHECK(BtbEditorInsert(&editor, 0, "\x01", 1) == BTB_EDIT_INVALID);
    CHECK(BtbEditorInsert(&editor, 0, NULL, 1) == BTB_EDIT_INVALID);
    CHECK(editor.length == before_length && editor.previous_length == before_previous);
    CHECK(strcmp(editor.text, "ac") == 0 && strcmp(editor.previous, "abc") == 0);
    CHECK(editor.can_undo == 1 && editor.dirty == 1);
    CHECK(BtbEditorInsert(&editor, 2, NULL, 0) == BTB_EDIT_OK);
    CHECK(BtbEditorErase(&editor, 2, 0) == BTB_EDIT_OK);
    CHECK(BtbEditorUndo(&editor) == BTB_EDIT_OK && strcmp(editor.text, "abc") == 0);
    CHECK(BtbEditorUndo(&editor) == BTB_EDIT_NO_UNDO);
    editor = (BtbEditor){0};
    char full[BTB_EDITOR_CAPACITY];
    memset(full, 'a', sizeof full);
    CHECK(BtbEditorInsert(&editor, 0, full, sizeof full) == BTB_EDIT_OK);
    CHECK(editor.length == BTB_EDITOR_CAPACITY && editor.text[editor.length] == '\0');
    CHECK(BtbEditorInsert(&editor, 0, "b", 1) == BTB_EDIT_FULL);
    CHECK(BtbEditorErase(&editor, 0, editor.length) == BTB_EDIT_OK);
    CHECK(editor.length == 0 && editor.text[0] == '\0');
    CHECK(BtbEditorUndo(&editor) == BTB_EDIT_OK && editor.length == BTB_EDITOR_CAPACITY);
    CHECK(BtbEditorSaveNew(&editor, "") == BTB_EDIT_INVALID);
    CHECK(BtbEditorInsert(NULL, 0, "x", 1) == BTB_EDIT_INVALID);
    CHECK(BtbEditorErase(NULL, 0, 1) == BTB_EDIT_INVALID);
    CHECK(BtbEditorUndo(NULL) == BTB_EDIT_INVALID);
    return 0;
}
