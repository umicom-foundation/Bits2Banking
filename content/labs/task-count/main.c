#include <stdio.h>

static int CalculateRemaining(int total, int completed)
{
    return total - completed;
}

int main(void)
{
    printf("Remaining tasks: %d\n", CalculateRemaining(12, 5));
    return 0;
}
