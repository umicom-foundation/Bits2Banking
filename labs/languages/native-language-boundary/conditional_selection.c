/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/conditional_selection.c
 *
 * PURPOSE:
 *   Compare C conditional selection and ordinary function arguments without depending on argument order.
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
static int probe(int value,unsigned *calls) {++*calls;return value;}
static bool condition(bool choice,unsigned *calls) {++*calls;return choice;}
static int choose_values(bool choice,int left,int right) {return choice?left:right;}
static int check(bool choice)
{
    unsigned left=0,right=0,conditions=0;
    const int expected=choice?11:22;
    int selected=condition(choice,&conditions)?probe(11,&left):probe(22,&right);
    if(selected!=expected || conditions!=1 || left!=(choice?1U:0U) || right!=(choice?0U:1U))return 1;
    left=0;right=0;conditions=0;
    /* Each argument changes a different object; the test makes no assumption
     * about C argument evaluation order. Both value arguments are evaluated. */
    selected=choose_values(condition(choice,&conditions),probe(11,&left),probe(22,&right));
    return selected!=expected || left!=1 || right!=1 || conditions!=1;
}
int main(void)
{
    if(check(true) || check(false))return 1;
    puts("Umicom C selective expression and eager argument checks passed.");
    return ferror(stdout)?1:0;
}
