#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("%s", "wzip: file1 [file2 ...]\n");
        return 1;
    }
    
    int curr, prev;
    int numRow = 0;
    int first_char = 1;
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            return 1;
        }
        while ((curr = fgetc(file)) != EOF) {
            if (first_char) {
                prev = curr;
                numRow = 1;
                first_char = 0;
            } else if (curr == prev) {
                numRow++;
            } else {
                fwrite(&numRow, sizeof(int), 1, stdout);
                fwrite(&prev, sizeof(char), 1, stdout);
                prev = curr;
                numRow = 1;
            }
        }
        fclose(file);
    }
    // Output the last run if any input was processed
    if (!first_char) {
        fwrite(&numRow, sizeof(int), 1, stdout);
        fwrite(&prev, sizeof(char), 1, stdout);
    }
    return 0;
}