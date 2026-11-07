/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/text-editor/editor.c
 *
 * PURPOSE:
 *   Teach safe text movement, undo ownership and explicit save destinations.
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

static int Valid(const BtbEditor *editor)
{
    return editor != NULL && editor->length <= BTB_EDITOR_CAPACITY &&
           editor->text[editor->length] == '\0';
}

static void Remember(BtbEditor *editor)
{
    memcpy(editor->previous, editor->text, editor->length + 1U);
    editor->previous_length = editor->length;
    editor->can_undo = 1;
}

BtbEditResult BtbEditorInsert(BtbEditor *editor, size_t position,
                              const char *text, size_t length)
{
    if (!Valid(editor) || position > editor->length ||
        (text == NULL && length != 0)) return BTB_EDIT_INVALID;
    /* Subtract after validating the model, so the capacity check itself
       cannot overflow. Copy input before moving the buffer: it may alias it. */
    if (length > BTB_EDITOR_CAPACITY - editor->length) return BTB_EDIT_FULL;
    if (length == 0) return BTB_EDIT_OK;
    char incoming[BTB_EDITOR_CAPACITY];
    for (size_t i = 0; i < length; ++i) {
        const unsigned char byte = (unsigned char)text[i];
        if (byte != '\n' && byte != '\t' && (byte < 32U || byte > 126U))
            return BTB_EDIT_INVALID;
        incoming[i] = text[i];
    }
    Remember(editor);
    memmove(editor->text + position + length, editor->text + position,
            editor->length - position + 1U);
    memcpy(editor->text + position, incoming, length);
    editor->length += length;
    editor->dirty = 1;
    return BTB_EDIT_OK;
}

BtbEditResult BtbEditorErase(BtbEditor *editor, size_t position, size_t length)
{
    if (!Valid(editor) || position > editor->length ||
        length > editor->length - position) return BTB_EDIT_INVALID;
    if (length == 0) return BTB_EDIT_OK;
    Remember(editor);
    memmove(editor->text + position, editor->text + position + length,
            editor->length - position - length + 1U);
    editor->length -= length;
    editor->dirty = 1;
    return BTB_EDIT_OK;
}

BtbEditResult BtbEditorUndo(BtbEditor *editor)
{
    if (!Valid(editor)) return BTB_EDIT_INVALID;
    if (!editor->can_undo) return BTB_EDIT_NO_UNDO;
    if (editor->previous_length > BTB_EDITOR_CAPACITY ||
        editor->previous[editor->previous_length] != '\0') return BTB_EDIT_INVALID;
    memcpy(editor->text, editor->previous, editor->previous_length + 1U);
    editor->length = editor->previous_length;
    editor->can_undo = 0;
    /* Conservative: undo marks the document changed even when its contents
       happen to equal a previously saved file. There is no saved-file hash. */
    editor->dirty = 1;
    return BTB_EDIT_OK;
}

BtbEditResult BtbEditorSaveNew(BtbEditor *editor, const char *path)
{
    if (!Valid(editor) || path == NULL || path[0] == '\0') return BTB_EDIT_INVALID;
    FILE *stream = fopen(path, "wbx");
    if (stream == NULL) return BTB_EDIT_IO;
    int failed = fwrite(editor->text, 1, editor->length, stream) != editor->length;
    if (fflush(stream) != 0) failed = 1;
    if (fclose(stream) != 0) failed = 1;
    if (failed) return BTB_EDIT_IO;
    editor->dirty = 0;
    return BTB_EDIT_OK;
}

BtbEditResult BtbEditorLoadFile(BtbEditor *editor, const char *path)
{
    if (!Valid(editor) || path == NULL || path[0] == '\0') return BTB_EDIT_INVALID;
    if (editor->dirty) return BTB_EDIT_DIRTY;
    FILE *stream = fopen(path, "rb");
    if (stream == NULL) return BTB_EDIT_IO;

    /* Build a private candidate with the same insertion validator used by
       editing. No caller-visible fields change before reading and closing
       both succeed. The caller, rather than the model, chooses the path. */
    BtbEditor candidate = {0};
    BtbEditResult result = BTB_EDIT_OK;
    int byte;
    while ((byte = fgetc(stream)) != EOF) {
        if (byte == '\r') {
            byte = fgetc(stream);
            if (byte != '\n') {
                result = ferror(stream) ? BTB_EDIT_IO : BTB_EDIT_INVALID;
                break;
            }
        }
        const char character = (char)(unsigned char)byte;
        result = BtbEditorInsert(&candidate, candidate.length, &character, 1U);
        if (result != BTB_EDIT_OK) break;
    }
    if (ferror(stream)) result = BTB_EDIT_IO;
    if (fclose(stream) != 0) result = BTB_EDIT_IO;
    if (result != BTB_EDIT_OK) return result;

    /* Loading begins a new editing history. The intermediate insertion
       snapshots were validation details, not user-visible undo commands. */
    memset(candidate.previous, 0, sizeof candidate.previous);
    candidate.previous_length = 0;
    candidate.can_undo = 0;
    candidate.dirty = 0;
    *editor = candidate;
    return BTB_EDIT_OK;
}
