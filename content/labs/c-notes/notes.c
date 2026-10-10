#include <stdio.h>
#include <string.h>

int main(void)
{
    char note[256];

    printf("Write a note: ");
    if (fgets(note, sizeof note, stdin) == NULL) {
        fprintf(stderr, "Unable to read input.\n");
        return 1;
    }

    note[strcspn(note, "\n")] = '\0';
    if (note[0] == '\0') {
        fprintf(stderr, "A note cannot be empty.\n");
        return 1;
    }

    FILE *output = fopen("notes.txt", "a");
    if (output == NULL) {
        perror("Unable to open notes.txt");
        return 1;
    }

    if (fprintf(output, "%s\n", note) < 0) {
        fprintf(stderr, "Unable to write the note.\n");
        fclose(output);
        return 1;
    }
    if (fclose(output) != 0) {
        perror("Unable to finish saving notes.txt");
        return 1;
    }

    printf("Saved.\n");
    return 0;
}
