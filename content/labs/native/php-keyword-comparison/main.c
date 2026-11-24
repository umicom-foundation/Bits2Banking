/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/php-keyword-comparison/main.c
 *
 * PURPOSE:
 *   Compare nine PHP language exercises with equivalent C23 data and control flow.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct Amount {
    bool present;
    int pennies;
} Amount;

typedef int (*Operation)(int amount, int context);

typedef struct Reader {
    int (*read_total)(const void *context);
    const void *context;
} Reader;

typedef enum LabelChoice {
    LABEL_STABLE,
    LABEL_DRAFT
} LabelChoice;

typedef struct Request {
    int pennies;
    bool released;
} Request;

typedef struct AmountIterator {
    const int *items;
    size_t count;
    size_t next;
} AmountIterator;

/* The route classifier consumes a validated integer at the caller boundary. */
static const char *payment_state(int pennies)
{
    if (pennies == 0) return "unpaid";
    if (pennies < 4200) return "partial";
    return "complete";
}

/* This exercise models a small bounded collection of whole pennies. */
static int total_admitted(const int *amounts, size_t count)
{
    int total = 0;
    for (size_t index = 0U; index < count; ++index) {
        if (amounts[index] < 0) continue;
        total += amounts[index];
    }
    return total;
}

/* The presence field stays meaningful when the contained integer is zero. */
static Amount fill_total(Amount input)
{
    if (input.present) input.pennies = 15 + 27;
    return input;
}

/* Native function pointers take the operation's extra data explicitly. */
static int add(int amount, int surcharge)
{
    return amount + surcharge;
}

static int apply(Operation operation, int amount, int context)
{
    return operation(amount, context);
}

/* An interface-like operation can read private data supplied by its owner. */
static int read_integer(const void *context)
{
    return *(const int *)context;
}

/* This enum chooses between two already compiled labels with stable names. */
static const char *label_for(LabelChoice choice)
{
    return choice == LABEL_STABLE ? "stable" : "draft";
}

/* Model both control paths and record the release after determining status. */
static int finish_request(Request *request)
{
    const int status = request->pennies < 0 ? 1 : 0;
    request->released = true;
    return status;
}

/* A returned Boolean carries completion, leaving zero as an ordinary item. */
static bool next_amount(AmountIterator *iterator, int *pennies)
{
    if (iterator->next == iterator->count) return false;
    *pennies = iterator->items[iterator->next++];
    return true;
}

static const char *amount_label(Amount amount)
{
    if (!amount.present) return "missing";
    return amount.pennies == 0 ? "zero" : "present";
}

int main(void)
{
    /* Use a positive and negative control where the exercise distinguishes them. */
    if (strcmp(payment_state(0), "unpaid") != 0 ||
        strcmp(payment_state(2100), "partial") != 0 ||
        strcmp(payment_state(4200), "complete") != 0) return 1;
    puts("choices: unpaid/partial/complete");

    const int amounts[] = {100, -8, 40};
    if (total_admitted(amounts, sizeof amounts / sizeof amounts[0]) != 140 ||
        total_admitted(amounts, 0U) != 0) return 2;
    puts("loops: 140");

    const Amount filled = fill_total((Amount){true, 0});
    const Amount missing = fill_total((Amount){false, 0});
    if (!filled.present || filled.pennies != 42 || missing.present || missing.pennies != 0) return 3;
    puts("values: 42");

    if (apply(add, 40, 2) != 42 || apply(add, 40, 0) != 40) return 4;
    puts("functions: 42");

    const int fixed = 42;
    const Reader reader = {read_integer, &fixed};
    if (reader.read_total(reader.context) != 42) return 5;
    puts("objects: 42");

    if (strcmp(label_for(LABEL_STABLE), "stable") != 0 ||
        strcmp(label_for(LABEL_DRAFT), "draft") != 0) return 6;
    puts("composition: stable/draft");

    Request invalid = {-1, false};
    Request valid = {42, false};
    if (finish_request(&invalid) != 1 || !invalid.released ||
        finish_request(&valid) != 0 || !valid.released) return 7;
    puts("cleanup: negative/checked");

    const int streamed[] = {12, 15, 15};
    AmountIterator iterator = {streamed, sizeof streamed / sizeof streamed[0], 0U};
    int total = 0;
    int pennies = 0;
    while (next_amount(&iterator, &pennies)) total += pennies;
    if (total != 42 || pennies != 15) return 8;
    puts("generators: 42");

    if (strcmp(amount_label((Amount){false, 0}), "missing") != 0 ||
        strcmp(amount_label((Amount){true, 0}), "zero") != 0 ||
        strcmp(amount_label((Amount){true, 42}), "present") != 0) return 9;
    puts("types: missing/zero/present");
    return 0;
}
