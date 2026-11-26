/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/data/daily-cash-practice/check_totals.c
 *
 * PURPOSE:
 *   Cross-check the exact integer-cent totals of the daily cash practice.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { LastDay = 4, DeskCount = 2 };

typedef struct CashDay {
    bool seen[DeskCount];
    long cents;
} CashDay;

/* Admit only the published three-column practice format. Keep a repeated
 * observation out of the total even when its amount matches the first row. */
static bool record(char *line, CashDay days[LastDay + 1])
{
    char *end = NULL;
    const long day = strtol(line, &end, 10);
    if (day < 1L || day > LastDay || *end != ',') {
        return false;
    }
    const char *desk = end + 1;
    const char *amount = strchr(desk, ',');
    if (amount == NULL) {
        return false;
    }
    const size_t desk_size = (size_t)(amount - desk);
    const bool reserve = desk_size == 7U && strncmp(desk, "reserve", desk_size) == 0;
    const bool operations = desk_size == 10U && strncmp(desk, "operations", desk_size) == 0;
    if (!reserve && !operations) {
        return false;
    }

    ++amount;
    const long cents = strtol(amount, &end, 10);
    if (end == amount || *end != '\0' || cents < -1000000L || cents > 1000000L) {
        return false;
    }

    const size_t slot = reserve ? 0U : 1U;
    CashDay *const total = &days[day];
    if (total->seen[slot]) {
        return false;
    }
    total->seen[slot] = true;
    /* Two admitted rows of at most one million cents fit in a long. */
    total->cents += cents;
    return true;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("Supply the path to daily_cash.csv.\n", stderr);
        return EXIT_FAILURE;
    }
    FILE *const input = fopen(argv[1], "r");
    if (input == NULL) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    char line[96];
    CashDay days[LastDay + 1] = {0};
    bool valid = fgets(line, sizeof line, input) != NULL &&
        (strcmp(line, "day,desk,change_cents\n") == 0 ||
         strcmp(line, "day,desk,change_cents\r\n") == 0);
    size_t rows = 0U;
    while (valid && fgets(line, sizeof line, input) != NULL) {
        size_t length = strlen(line);
        if (length == 0U || line[length - 1U] != '\n') {
            valid = false;
            break;
        }
        line[--length] = '\0';
        if (length != 0U && line[length - 1U] == '\r') {
            line[length - 1U] = '\0';
        }
        valid = record(line, days);
        ++rows;
    }
    const bool read_failed = ferror(input) != 0;
    const int closed = fclose(input);
    if (!valid || rows == 0U || read_failed || closed != 0) {
        fputs("The practice table could not be read as one row per day and desk.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Only report days supplied by the data. Two canceling entries still
     * count as an observed zero because at least one desk was seen. */
    for (size_t day = 1U; day <= LastDay; ++day) {
        if (days[day].seen[0] || days[day].seen[1]) {
            printf("day %zu: %ld cents\n", day, days[day].cents);
        }
    }
    return EXIT_SUCCESS;
}
