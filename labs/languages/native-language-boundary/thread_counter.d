/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/thread_counter.d
 *
 * PURPOSE:
 *   Separate D shared atomic access from worker lifetime and explicit joins.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module thread_counter;
import core.atomic : atomicLoad, atomicOp, atomicStore;
import core.thread : Thread;
import std.stdio : stderr, writeln;

private enum uint iterations = 10_000;
private shared uint completed;

private void countWorker() nothrow @nogc
{
    foreach (uint stepIndex; 0U .. iterations)
        atomicOp!"+="(completed, 1U);
}

/* This teaching owner is called serially. Its single module counter is not a
 * reentrant job API. Register a join only after that worker starts; if creating
 * the second worker fails, the first guard still waits for the first worker. */
private void runPair()
{
    atomicStore(completed, 0U);
    auto first = new Thread(&countWorker);
    first.start();
    scope(exit) first.join();

    auto second = new Thread(&countWorker);
    second.start();
    scope(exit) second.join();
    /* Scope guards run in reverse order on exit. No result is published here
       before those waits have completed. Garbage collection is not a join. */
}

unittest
{
    runPair();
    assert(atomicLoad(completed) == 2U * iterations);
}

int main()
{
    try {
        runPair();
        const observed = atomicLoad(completed);
        if (observed != 2U * iterations) {
            stderr.writeln("Unexpected completed count: ", observed);
            return 1;
        }
        writeln("Completed increments: ", observed);
        writeln("Both workers joined before observing the final result.");
        return 0;
    } catch (Exception error) {
        stderr.writeln("Thread exercise failed: ", error.msg);
        return 1;
    }
}
