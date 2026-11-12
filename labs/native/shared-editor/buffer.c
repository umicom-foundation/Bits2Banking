/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/shared-editor/buffer.c
 *
 * PURPOSE:
 *   Exercise owned text, exact Unicode positions and source selections through Framework.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
#include "umicom/editor/text_buffer.h"
#include "umicom/editor/text_position.h"
#include "umicom/editor/source_selection.h"
#include <stdio.h>
#include <string.h>

/* The fixture is A, e-acute, grinning face, CRLF, note, LF. Hexadecimal UTF-8
 * keeps its bytes independent of a compiler's source-file encoding setting. */
static const char sample[] = "A\xc3\xa9\xf0\x9f\x98\x80\r\nnote\n";

int RunBufferLesson(const char *scenario)
{
    UmiEditorTextBuffer *buffer = NULL;
    UmiEditorTextBufferView view = {0};
    int result = 1;
#define REQUIRE(condition) do { if (!(condition)) { \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); goto cleanup; \
} } while (0)
#define OK(call) REQUIRE((call) == UMI_STATUS_OK)
    OK(umi_editor_text_buffer_create(32U, &buffer));
    OK(umi_editor_text_buffer_set(buffer, sample, sizeof sample - 1U));
    OK(umi_editor_text_buffer_view(buffer, &view));
    REQUIRE(view.byte_count == 14U);

    if (strcmp(scenario, "ownership") == 0) {
        char caller[] = "draft";
        char copy[6] = {0};
        size_t copied = 0U;
        OK(umi_editor_text_buffer_set(buffer, caller, sizeof caller - 1U));
        caller[0] = 'X';
        OK(umi_editor_text_buffer_copy(buffer, 0U, 5U, copy, sizeof copy, &copied));
        REQUIRE(copied == 5U && strcmp(copy, "draft") == 0);
        /* A saved mark is model metadata. This exercise does not save a file. */
        OK(umi_editor_text_buffer_mark_saved(buffer));
        REQUIRE(!umi_editor_text_buffer_is_dirty(buffer));
        OK(umi_editor_text_buffer_insert(buffer, 5U, "!", 1U));
        REQUIRE(umi_editor_text_buffer_is_dirty(buffer));
        /* Reacquire after mutation; never dereference an earlier borrowed view. */
        OK(umi_editor_text_buffer_view(buffer, &view));
        REQUIRE(view.byte_count == 6U && memcmp(view.bytes, "draft!", 6U) == 0);
        REQUIRE(strcmp(copy, "draft") == 0);
    } else if (strcmp(scenario, "positions") == 0) {
        static const struct { size_t offset; uint64_t line, column; } rows[] = {
            {0U, 0U, 0U}, {1U, 0U, 1U}, {3U, 0U, 2U}, {7U, 0U, 4U},
            {9U, 1U, 0U}, {13U, 1U, 4U}, {14U, 2U, 0U}
        };
        for (size_t i = 0U; i < sizeof rows / sizeof rows[0]; ++i) {
            UmiEditorTextPosition position = {99U, 99U};
            size_t offset = SIZE_MAX;
            OK(UmiEditorTextViewPositionAt(&view, rows[i].offset, &position));
            REQUIRE(position.line == rows[i].line && position.utf16_column == rows[i].column);
            OK(UmiEditorTextViewResolvePosition(&view, position, &offset));
            REQUIRE(offset == rows[i].offset);
        }
    } else if (strcmp(scenario, "position-refusals") == 0) {
        static const size_t invalid_offsets[] = {2U, 4U, 5U, 6U, 8U, 15U};
        for (size_t i = 0U; i < sizeof invalid_offsets / sizeof invalid_offsets[0]; ++i) {
            UmiEditorTextPosition position = {99U, 98U};
            REQUIRE(UmiEditorTextViewPositionAt(&view, invalid_offsets[i], &position) ==
                    UMI_STATUS_INVALID_ARGUMENT);
            REQUIRE(position.line == 99U && position.utf16_column == 98U);
        }
        size_t offset = 77U;
        REQUIRE(UmiEditorTextViewResolvePosition(&view, (UmiEditorTextPosition){0U, 3U},
                &offset) == UMI_STATUS_INVALID_ARGUMENT);
        REQUIRE(offset == 77U);
    } else if (strcmp(scenario, "selection") == 0) {
        UmiEditorSourceSelection selected = {0};
        OK(UmiEditorSourceSelectionAt(&view, 11U, UMI_EDITOR_SELECT_SOURCE_WORD, &selected));
        REQUIRE(selected.offset == 9U && selected.byte_count == 4U);
        REQUIRE(memcmp(view.bytes + selected.offset, "note", selected.byte_count) == 0);
        OK(UmiEditorSourceSelectionAt(&view, 3U, UMI_EDITOR_SELECT_LINE_CONTENT, &selected));
        REQUIRE(selected.offset == 0U && selected.byte_count == 7U);
        OK(UmiEditorSourceSelectionAt(&view, 3U, UMI_EDITOR_SELECT_LINE_WITH_ENDING, &selected));
        REQUIRE(selected.offset == 0U && selected.byte_count == 9U);
        OK(UmiEditorSourceSelectionAt(&view, 14U, UMI_EDITOR_SELECT_LINE_CONTENT, &selected));
        REQUIRE(selected.offset == 14U && selected.byte_count == 0U);
    } else if (strcmp(scenario, "selection-refusals") == 0) {
        UmiEditorSourceSelection selected = {71U, 72U};
        REQUIRE(UmiEditorSourceSelectionAt(&view, 8U, UMI_EDITOR_SELECT_LINE_CONTENT,
                &selected) == UMI_STATUS_INVALID_ARGUMENT);
        REQUIRE(selected.offset == 71U && selected.byte_count == 72U);
        /* The byte buffer can own arbitrary bytes; source selection validates text.
         * A valid start position alone would not certify a malformed suffix. */
        static const char malformed[] = {'o', 'k', ' ', (char)0xc0, (char)0xaf};
        OK(umi_editor_text_buffer_set(buffer, malformed, sizeof malformed));
        OK(umi_editor_text_buffer_view(buffer, &view));
        /* Invalid caret coordinates report INVALID_ARGUMENT; malformed encoding
         * reaches the position scanner and reports PARSE_ERROR. Retain the first
         * authored expectation to explain why status contracts need source review. */
#if 0
        REQUIRE(UmiEditorSourceSelectionAt(&view, 0U, UMI_EDITOR_SELECT_SOURCE_WORD,
                &selected) == UMI_STATUS_INVALID_ARGUMENT);
#endif
        REQUIRE(UmiEditorSourceSelectionAt(&view, 0U, UMI_EDITOR_SELECT_SOURCE_WORD,
                &selected) == UMI_STATUS_PARSE_ERROR);
        REQUIRE(selected.offset == 71U && selected.byte_count == 72U);
    } else {
        goto cleanup;
    }
    printf("shared-editor %s: checks completed\n", scenario);
    result = 0;
cleanup:
    umi_editor_text_buffer_destroy(buffer);
    return result;
#undef OK
#undef REQUIRE
}
