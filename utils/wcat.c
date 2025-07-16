#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        FILE *filePointer;
        filePointer = fopen(argv[i], "r");

        if (filePointer == NULL) {
            printf("wcat: cannot open file\n");
            return 1;
        } else {
            char lineBuffer[1024];
            while (fgets(lineBuffer, sizeof(lineBuffer), filePointer) != NULL) {
                printf("%s", lineBuffer);
            }
        }
        fclose(filePointer);
    }

    return 0;
}