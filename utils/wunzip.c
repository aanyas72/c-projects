#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("%s", "wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *file;
        file = fopen(argv[i], "rb");

        if (file == NULL) {
            printf("%s", "Cannot open file");
            return 1;
        } else {
            while (1) {
                int num;
                char currChar;
                if (fread(&num, sizeof(int), 1, file) != 1) break; // fread outputs 0 if unsuccessful (aka EOF detected)
                if (fread(&currChar, sizeof(char), 1, file) != 1) break;
                
                for (int j = 0; j < num; j++) {
                    fputc(currChar, stdout); // output function for standard text
                }
            }
        }
        fclose(file);
    }
    return 0;
}