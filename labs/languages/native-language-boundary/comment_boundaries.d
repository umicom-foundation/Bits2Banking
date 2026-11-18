/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/comment_boundaries.d
 *
 * PURPOSE:
 *   Compare escaped and raw D strings and nested comments without evaluating text as source.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module comment_boundaries;
import std.stdio : writeln;

/+ Comments may contain apparent "quotes" and an envelope closing token ?>.
   /+ This nested block must close before the outer block. +/
   No text in this comment is executed.
+/

enum string rawPath = r"C:\courses\umicom";
enum string escapedPath = "C:\\courses\\umicom";
enum string quotedData = `Show "quotes", ?> and /+ as text.`;
static assert(rawPath == escapedPath);
static assert(quotedData.length > 0);

void main()
{
    // A displayed delimiter remains data, not a request to run another language.
    if (rawPath != escapedPath)
        throw new Exception("The two string spellings must preserve the same bytes.");
    writeln("Raw and escaped paths contain the same bytes.");
    writeln(quotedData);
    writeln("Source text is data unless a separate compiler or evaluator is invoked.");
}
