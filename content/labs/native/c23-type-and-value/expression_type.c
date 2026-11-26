/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/c23-type-and-value/expression_type.c
 *
 * PURPOSE:
 *   Show that a non-variably-modified typeof operand is not evaluated.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

static int samples;

/* Counting calls gives us an observable way to distinguish asking about a
 * function result type from calling the function. */
static int Sample(void)
{
    ++samples;
    return 42;
}

int main(void)
{
    /* The return type is int. No call happens in this declaration. */
    typeof(Sample()) cached = {};
    if (samples != 0 || cached != 0) return 1;
    cached = Sample();
    return cached != 42 || samples != 1;
}
