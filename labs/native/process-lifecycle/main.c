/* Bits2Banking | Sammy Hegab | Umicom Foundation | MIT */
#include "process.h"
#include <stdio.h>
int main(void)
{
    BtbProcess lesson;
    if (BtbProcessInit(&lesson, 101U) != BTB_PROCESS_OK) return 1;
    puts("Fictional lesson-renderer process:");
    printf("  revision %u: %s\n", lesson.revision, BtbProcessStateName(lesson.state));
    static const BtbProcessEvent sequence[] = {
        BTB_EVENT_ADMIT, BTB_EVENT_DISPATCH, BTB_EVENT_WAIT,
        BTB_EVENT_WAKE, BTB_EVENT_DISPATCH, BTB_EVENT_EXIT
    };
    for (size_t i = 0U; i < sizeof(sequence) / sizeof(sequence[0]); ++i) {
        if (BtbProcessApply(&lesson, sequence[i], 0) != BTB_PROCESS_OK) return 1;
        printf("  revision %u: %s\n", lesson.revision, BtbProcessStateName(lesson.state));
    }
    puts("No real operating-system process was created.");
    return lesson.state == BTB_PROCESS_TERMINATED ? 0 : 1;
}
