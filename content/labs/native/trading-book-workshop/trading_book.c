/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/trading-book-workshop/trading_book.c
 *
 * PURPOSE:
 *   Teach one deterministic synthetic order fill and its cash and position checks.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

enum { ASK_CAPACITY = 4 };

typedef struct {
    uint64_t sequence;
    int64_t price_cents;
    int64_t units;
} Ask;

typedef struct {
    int64_t cash_cents;
    int64_t owned_units;
    Ask offers[ASK_CAPACITY];
    size_t count;
} Book;

typedef struct {
    uint64_t ask_sequence;
    int64_t units;
    int64_t unit_price_cents;
} Fill;

typedef enum { BOOK_FILLED, BOOK_NO_TRADE, BOOK_CASH_LIMIT, BOOK_INVALID } BookStatus;

static BookStatus buy_once(Book *book, int64_t limit_cents, int64_t wanted, Fill *fill)
{
    /* This helper handles one buyer and a checked local snapshot. Output
       remains caller-owned and untouched on every refusal. */
    if (book == NULL || fill == NULL || book->count > ASK_CAPACITY ||
        book->cash_cents < 0 || book->owned_units < 0 ||
        limit_cents <= 0 || wanted <= 0) {
        return BOOK_INVALID;
    }

    size_t best = ASK_CAPACITY;
    for (size_t index = 0; index < book->count; ++index) {
        const Ask ask = book->offers[index];
        if (ask.sequence == 0 || ask.price_cents <= 0 || ask.units < 0) {
            return BOOK_INVALID;
        }
        /* Check identity even for depleted rows so a replay stays deterministic. */
        for (size_t prior = 0; prior < index; ++prior) {
            if (ask.sequence == book->offers[prior].sequence) {
                return BOOK_INVALID;
            }
        }
        if (ask.units == 0 || ask.price_cents > limit_cents) {
            continue;
        }
        /* Use the lower price first, then the earlier accepted sequence. This
           is the rule of the exercise and needs no timestamp tie-breaker. */
        if (best == ASK_CAPACITY ||
            ask.price_cents < book->offers[best].price_cents ||
            (ask.price_cents == book->offers[best].price_cents &&
             ask.sequence < book->offers[best].sequence)) {
            best = index;
        }
    }
    if (best == ASK_CAPACITY) {
        return BOOK_NO_TRADE;
    }

    Ask *ask = &book->offers[best];
    const int64_t units = wanted < ask->units ? wanted : ask->units;
    /* Bounds are checked before multiplying or adding signed units. The
       lesson chooses a no-fill refusal when the fixture cash cannot pay. */
    if (units > INT64_MAX / ask->price_cents || book->owned_units > INT64_MAX - units) {
        return BOOK_INVALID;
    }
    const int64_t cost = units * ask->price_cents;
    if (cost > book->cash_cents) {
        return BOOK_CASH_LIMIT;
    }

    /* Publish the proven result only after every fallible check has finished. */
    ask->units -= units;
    book->owned_units += units;
    book->cash_cents -= cost;
    *fill = (Fill){ ask->sequence, units, ask->price_cents };
    return BOOK_FILLED;
}

int main(void)
{
    Book book = { .cash_cents = 1000, .offers = {{13, 160, 3}, {11, 150, 2}, {12, 150, 4}},
                  .count = 3 };
    Fill result = {0};
    const BookStatus status = buy_once(&book, 155, 3, &result);
    const BookStatus no_trade = buy_once(&book, 140, 1, &result);
    if (status != BOOK_FILLED || no_trade != BOOK_NO_TRADE ||
        result.ask_sequence != 11 || result.units != 2 ||
        result.unit_price_cents != 150 || book.cash_cents != 700 ||
        book.owned_units != 2 || book.offers[1].units != 0) {
        fputs("The training order book failed its expected checks.\n", stderr);
        return 1;
    }
    printf("Filled %" PRId64 " at %" PRId64 " cents on ask %" PRIu64 "\n",
           result.units, result.unit_price_cents, result.ask_sequence);
    printf("Cash: %" PRId64 " cents; units: %" PRId64 "\n", book.cash_cents, book.owned_units);
    return 0;
}
