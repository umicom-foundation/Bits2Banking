/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/classroom-chain/check_target.d
 *
 * PURPOSE:
 *   Teach a small D-to-C ABI call against the shared classroom proof rule.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

extern(C) int classroom_meets_target(const(ubyte)* digest) nothrow @nogc;

int main()
{
    // Keep ownership of the fixed-size array in D. The borrowed pointer is
    // valid until the synchronous C call returns and is never stored there.
    ubyte[32] digest;
    digest[31] = 3;
    if (classroom_meets_target(digest.ptr) != 1) {
        return 1;
    }
    digest[0] = 1;
    return classroom_meets_target(digest.ptr) == 0 ? 0 : 1;
}
