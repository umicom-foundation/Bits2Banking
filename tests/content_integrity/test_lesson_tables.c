/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: tests/content_integrity/test_lesson_tables.c
 *
 * PURPOSE:
 *   Check the semantic table shape of authored comparison lessons without executing a browser.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This is a contract for the course author's canonical table markup, not an
 * HTML parser. Exact lowercase tags and scoped column headers are intentional.
 * Comments are ignored so preserved previous output cannot satisfy the check. */
static int hide_comments(char *text)
{
    char *start = text;
    while ((start = strstr(start, "<!--")) != NULL) {
        char *end = strstr(start + 4, "-->");
        if (end == NULL) return 0;
        end += 3;
        memset(start, ' ', (size_t)(end - start));
        start = end;
    }
    return 1;
}
static size_t occurrences(const char *start, const char *end, const char *tag)
{
    size_t count = 0U;
    const size_t length = strlen(tag);
    const char *found = start;
    while ((found = strstr(found, tag)) != NULL && found < end) {
        if ((size_t)(end - found) < length) break;
        ++count;
        found += length;
    }
    return count;
}
static int rows_match(const char *start, const char *end, size_t rows,
                      size_t columns, const char *open_cell, const char *close_cell)
{
    size_t found_rows = 0U;
    const char *row = start;
    while ((row = strstr(row, "<tr>")) != NULL && row < end) {
        const char *close_row = strstr(row + 4, "</tr>");
        if (close_row == NULL || close_row >= end ||
            occurrences(row + 4, close_row, "<tr>") != 0U ||
            occurrences(row + 4, close_row, open_cell) != columns ||
            occurrences(row + 4, close_row, close_cell) != columns) return 0;
        const char *cell = row + 4;
        for (size_t i = 0U; i < columns; ++i) {
            cell = strstr(cell, open_cell);
            if (cell == NULL || cell >= close_row) return 0;
            cell += strlen(open_cell);
            const char *close = strstr(cell, close_cell);
            if (close == NULL || close >= close_row ||
                occurrences(cell, close, open_cell) != 0U) return 0;
            while (cell < close && isspace((unsigned char)*cell)) ++cell;
            if (cell == close) return 0;
            cell = close + strlen(close_cell);
        }
        ++found_rows;
        row = close_row + 5;
    }
    return found_rows == rows && occurrences(start, end, "</tr>") == rows;
}
static int table_matches(char *text, size_t columns, size_t rows)
{
    if (!hide_comments(text)) return 0;
    const char *end = text + strlen(text);
    const char *table = strstr(text, "<table>");
    if (table == NULL || occurrences(text, end, "<table>") != 1U ||
        occurrences(text, end, "</table>") != 1U) return 0;
    const char *table_end = strstr(table, "</table>");
    const char *head = strstr(table, "<thead>");
    const char *head_end = head == NULL ? NULL : strstr(head, "</thead>");
    const char *body = head_end == NULL ? NULL : strstr(head_end, "<tbody>");
    const char *body_end = body == NULL ? NULL : strstr(body, "</tbody>");
    if (head == NULL || head_end == NULL || body == NULL || body_end == NULL ||
        table_end == NULL || body_end >= table_end ||
        occurrences(table, table_end, "<thead>") != 1U ||
        occurrences(table, table_end, "<tbody>") != 1U ||
        occurrences(table, table_end, "<tr>") != rows + 1U ||
        occurrences(table, table_end, "</tr>") != rows + 1U) return 0;
    return rows_match(head + 7, head_end, 1U, columns, "<th scope=\"col\">", "</th>") &&
        rows_match(body + 7, body_end, rows, columns, "<td>", "</td>");
}
static int self_test(void)
{
    static const struct {const char *html; int accepted;} cases[] = {
        {"<table><thead><tr><th scope=\"col\">A</th></tr></thead><tbody><tr><td>B</td></tr></tbody></table>", 1},
        {"<!-- <p>| A | | --- | | B |</p> --><table><thead><tr><th scope=\"col\">A</th></tr></thead><tbody><tr><td>B</td></tr></tbody></table>", 1},
        {"<p>| A | | --- | | B |</p>", 0},
        {"<!-- <table><thead><tr><th scope=\"col\">A</th></tr></thead><tbody><tr><td>B</td></tr></tbody></table> -->", 0},
        {"<table><thead><tr><th>A</th></tr></thead><tbody><tr><td>B</td></tr></tbody></table>", 0},
        {"<table><thead><tr><th scope=\"col\">A</th></tr></thead><tbody><tr><td>B</td><td>C</td></tr></tbody></table>", 0},
        {"<table><thead><tr><th scope=\"col\">A</th></tr></thead><tbody><tr><td>B</td></tr></tbody>", 0},
        {"<table><thead><tr><th scope=\"col\">A</th></tr></thead><tbody><tr><td> </td></tr></tbody></table>", 0},
        {"<!-- incomplete <table>", 0}
    };
    for (size_t i = 0U; i < sizeof cases / sizeof cases[0]; ++i) {
        char copy[512];
        const size_t length = strlen(cases[i].html);
        if (length >= sizeof copy) return 2;
        memcpy(copy, cases[i].html, length + 1U);
        if (table_matches(copy, 1U, 1U) != cases[i].accepted) {
            fprintf(stderr, "table fixture %zu disagrees\n", i);
            return 1;
        }
    }
    return 0;
}
static int dimension(const char *text, size_t *value)
{
    char *end = NULL;
    errno = 0;
    const unsigned long parsed = strtoul(text, &end, 10);
    if (errno != 0 || end == text || *end != '\0' || parsed == 0UL || parsed > 1024UL) return 0;
    *value = (size_t)parsed;
    return 1;
}
int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--self-test") == 0) return self_test();
    size_t columns = 0U, rows = 0U;
    if (argc != 4 || !dimension(argv[2], &columns) || !dimension(argv[3], &rows)) return 2;
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {perror(argv[1]); return 2;}
    /* Bound memory independently of filesystem metadata. A full buffer is
     * refused, and embedded NUL cannot hide an unreviewed suffix. */
    const size_t limit = 1024U * 1024U;
    char *text = malloc(limit + 1U);
    if (text == NULL) {fclose(file); return 2;}
    const size_t length = fread(text, 1U, limit, file);
    const int read_failed = ferror(file);
    const int close_failed = fclose(file);
    if (read_failed || close_failed != 0 || length == limit || memchr(text, 0, length) != NULL) {
        free(text); return 2;
    }
    text[length] = '\0';
    const int accepted = table_matches(text, columns, rows);
    free(text);
    if (!accepted) fprintf(stderr, "%s: expected one scoped %zu-column table with %zu data rows\n", argv[1], columns, rows);
    return accepted ? 0 : 1;
}
