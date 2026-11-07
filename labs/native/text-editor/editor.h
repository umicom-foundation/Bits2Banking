/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/text-editor/editor.h
 *
 * PURPOSE:
 *   Define an ASCII editor model with bounded storage and one-level undo.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BTB_EDITOR_H
#define BTB_EDITOR_H
#include <stddef.h>
#define BTB_EDITOR_CAPACITY 1024U
/* The original result set is retained for review. Existing numeric values stay
   stable; the appended result distinguishes unsaved work from invalid input. */
#if 0
typedef enum { BTB_EDIT_OK, BTB_EDIT_INVALID, BTB_EDIT_FULL, BTB_EDIT_NO_UNDO,
               BTB_EDIT_IO } BtbEditResult;
#endif
typedef enum { BTB_EDIT_OK, BTB_EDIT_INVALID, BTB_EDIT_FULL, BTB_EDIT_NO_UNDO,
               BTB_EDIT_IO, BTB_EDIT_DIRTY } BtbEditResult;
typedef struct {
    char text[BTB_EDITOR_CAPACITY + 1U];
    char previous[BTB_EDITOR_CAPACITY + 1U];
    size_t length;
    size_t previous_length;
    int can_undo;
    int dirty;
} BtbEditor;
/* Initialise with = {0}. Positions count ASCII bytes, starting at zero.
   Valid input is printable ASCII, newline or tab. Failed edits preserve state.
   The caller owns the model and must keep all input spans readable. */
BtbEditResult BtbEditorInsert(BtbEditor *editor, size_t position,
                              const char *text, size_t length);
BtbEditResult BtbEditorErase(BtbEditor *editor, size_t position, size_t length);
BtbEditResult BtbEditorUndo(BtbEditor *editor);
/* Explicit caller path; exclusive creation refuses existing files.
   A failed write may leave a partial new file. Inspect it before retrying.
   This is an I/O lesson, not crash-safe or durable production persistence. */
BtbEditResult BtbEditorSaveNew(BtbEditor *editor, const char *path);
/* Open an existing ASCII file only when the current document is clean.
   CRLF becomes LF; a lone CR, embedded NUL, non-ASCII byte or oversized text
   is refused. The complete old state survives every failure. Successful load
   starts a clean document with no undo step. This bounded teaching model is
   separate from Framework's production document and Unicode services. */
BtbEditResult BtbEditorLoadFile(BtbEditor *editor, const char *path);
#endif
