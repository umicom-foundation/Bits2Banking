/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/reading_component_report.c
 *
 * PURPOSE:
 *   Read two known C23 structure members through an explicit descriptor table.
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

typedef struct {
    int minute;
    int value;
} Reading;

typedef struct {
    const char *name;
    size_t offset_bytes;
} ReadingComponent;

int main(void)
{
    const Reading reading = { .minute = 15, .value = 42 };

    /* Keep the printable names and compiler-computed offsets beside their owner.
       Each entry intentionally describes a member of type int. */
    const ReadingComponent components[] = {
        { "minute", offsetof(Reading, minute) },
        { "value", offsetof(Reading, value) }
    };
    const unsigned char *record_bytes = (const unsigned char *)&reading;

    /* Copy the native int representation from a known member before printing it.
       This works independently of padding between the two members. */
    for (size_t index = 0; index < sizeof components / sizeof components[0]; ++index) {
        int value;
        memcpy(&value, record_bytes + components[index].offset_bytes, sizeof value);
        if (printf("%s = %d\n", components[index].name, value) < 0) {
            return 1;
        }
    }
    return fflush(stdout) == 0 ? 0 : 1;
}
