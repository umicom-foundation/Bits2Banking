/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/web-statement-contract/statement-report.c
 *
 * PURPOSE:
 *   Produce one validated synthetic statement as JSON or accessible HTML.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef enum RowStatus {
    ROW_POSTED,
    ROW_PENDING
} RowStatus;

typedef struct StatementRow {
    int32_t id;
    int32_t cents;
    RowStatus status;
} StatementRow;

typedef struct StatementSummary {
    int32_t posted_cents;
    size_t posted_count;
} StatementSummary;

/* This teaching fixture never reads a live account. A separate native owner
 * would authenticate and admit real statement records before this boundary. */
static const StatementRow receipt[] = {
    {101, 2600, ROW_POSTED},
    {102, -850, ROW_POSTED},
    {103, 500, ROW_PENDING},
};

static bool Summarise(const StatementRow *rows, size_t count, StatementSummary *result)
{
    StatementSummary next = {0};
    int32_t previous_id = 0;

    /* Ascending positive IDs also give the presentation a stable row identity.
     * Finish validation before exposing any partial total to either writer. */
    for (size_t row = 0; row < count; ++row) {
        const StatementRow item = rows[row];
        if (item.id <= previous_id)
            return false;
        previous_id = item.id;

        switch (item.status) {
        case ROW_PENDING:
            continue;
        case ROW_POSTED: {
            const int64_t wide = (int64_t)next.posted_cents + item.cents;
            if (wide < INT32_MIN || wide > INT32_MAX)
                return false;
            next.posted_cents = (int32_t)wide;
            ++next.posted_count;
            break;
        }
        default:
            return false;
        }
    }
    *result = next;
    return true;
}

/* Only validated enum values reach this conversion. Each arrives as an
 * application-owned literal, so no arbitrary text is inserted into output. */
static const char *StatusLabel(RowStatus status)
{
    return status == ROW_POSTED ? "posted" : "pending";
}

static bool WriteJson(const StatementRow *rows, size_t count, StatementSummary summary)
{
    /* Keep integer arithmetic and admission in C. The version and explicit
     * cents unit let browser and Node clients reject incompatible snapshots. */
    if (printf("{\n  \"version\": 1,\n  \"postedCount\": %zu,\n"
               "  \"postedCents\": %" PRId32 ",\n  \"rows\": [\n",
               summary.posted_count, summary.posted_cents) < 0)
        return false;
    for (size_t row = 0; row < count; ++row) {
        const StatementRow item = rows[row];
        if (printf("    { \"id\": %" PRId32 ", \"cents\": %" PRId32
                   ", \"status\": \"%s\" }%s\n",
                   item.id, item.cents, StatusLabel(item.status),
                   row + 1 < count ? "," : "") < 0)
            return false;
    }
    return puts("  ]\n}") >= 0;
}

static bool WriteHtml(const StatementRow *rows, size_t count, StatementSummary summary)
{
    /* A caption, row headings and explicit state text remain readable with
     * styles disabled. Bootstrap owns spacing and scroll presentation. */
    if (puts("<!doctype html>\n"
             "<html lang=\"en-GB\">\n"
             "<head><meta charset=\"utf-8\">\n"
             "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
             "<title>Synthetic statement | Bits2Banking</title>\n"
             "<link rel=\"icon\" href=\"assets/umicom.ico\">\n"
             "<link rel=\"stylesheet\" href=\"assets/bootstrap.min.css\">\n"
             "<link rel=\"stylesheet\" href=\"assets/umicom-brand.css\">\n"
             "</head><body><main class=\"container py-3\">\n"
             "<img src=\"assets/umicom-wordmark.svg\" alt=\"Umicom Foundation\" width=\"176\">\n"
             "<h1>Synthetic statement</h1>") < 0)
        return false;
    if (printf("<p>Posted total: %" PRId32 " cents in %zu entries.</p>\n",
               summary.posted_cents, summary.posted_count) < 0)
        return false;
    if (puts("<div class=\"table-responsive\" tabindex=\"0\" role=\"region\" aria-label=\"Statement rows\">\n"
             "<table class=\"table table-striped\"><caption>Fictional statement entries</caption>\n"
             "<thead><tr><th scope=\"col\">Entry</th><th scope=\"col\">Amount in cents</th>"
             "<th scope=\"col\">State</th></tr></thead><tbody>") < 0)
        return false;
    for (size_t row = 0; row < count; ++row) {
        const StatementRow item = rows[row];
        if (printf("<tr><th scope=\"row\">%" PRId32 "</th>"
                   "<td class=\"text-end\">%" PRId32 "</td><td>%s</td></tr>\n",
                   item.id, item.cents, StatusLabel(item.status)) < 0)
            return false;
    }
    return puts("</tbody></table></div></main></body></html>") >= 0;
}

int main(int argc, char **argv)
{
    /* Both presentations read the same admitted native snapshot. Keep invalid
     * options and diagnostics off stdout so it remains machine-readable. */
    const bool html = argc == 2 && strcmp(argv[1], "--html") == 0;
    if (argc != 1 && !html) {
        fputs("Usage: statement-report [--html]\n", stderr);
        return 2;
    }

    const size_t count = sizeof(receipt) / sizeof(receipt[0]);
    StatementSummary summary;
    if (!Summarise(receipt, count, &summary)) {
        fputs("Statement rows were rejected.\n", stderr);
        return 1;
    }

    const bool written = html
        ? WriteHtml(receipt, count, summary)
        : WriteJson(receipt, count, summary);
    if (!written || fflush(stdout) != 0) {
        fputs("Statement output could not be completed.\n", stderr);
        return 1;
    }
    return 0;
}
