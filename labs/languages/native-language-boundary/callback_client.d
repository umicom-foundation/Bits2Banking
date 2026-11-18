/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/callback_client.d
 *
 * PURPOSE:
 *   Use a noncapturing C-linkage D callback with bounded explicit context.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


import std.stdio : writeln;
extern(C) {
    alias ProgressVisitor = int function(int, int, void*) nothrow @nogc;
    int bounded_progress_visit(const(int)* completed, const(int)* totals,
        int count, ProgressVisitor visitor, void* context, int* accepted) nothrow @nogc;
}
struct CallbackState { int calls; int stopAt; int[3] observed; }
extern(C) int onProgress(int index, int percent, void* context) nothrow @nogc
{
    if (context is null) return 99;
    auto state = cast(CallbackState*) context;
    if (index != state.calls || index < 0 || index >= 3) return 99;
    state.observed[index] = percent;
    ++state.calls;
    return index == state.stopAt ? 17 : 0;
}
int main()
{
    static assert(int.sizeof == 4);
    int[3] completed = [1, 2, 3], totals = [4, 4, 4];
    CallbackState state;
    state.stopAt = 1;
    int accepted = -1;
    int status = bounded_progress_visit(completed.ptr, totals.ptr, 3,
        &onProgress, &state, &accepted);
    if (status != 2 || accepted != 1 || state.calls != 2 ||
        state.observed[0] != 25 || state.observed[1] != 50) return 1;
    writeln("D callback checks passed: two attempted, one accepted");
    return 0;
}
