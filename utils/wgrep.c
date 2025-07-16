#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search_in_file(FILE *file, char *search_term) {
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, search_term) != NULL) {
            printf("%s", line);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("%s", "wgrep: searchterm [file ...]\n");
        return 1;
    }

    char *search_word = argv[1];

    if (argc == 2) {
        search_in_file(stdin, search_word);
    } else {
        FILE *file;
        file = fopen(argv[2], "r");
        if (file == NULL) {
            printf("%s", "wgrep: cannot open file\n");
            return 1;
        } else {
            search_in_file(file, search_word);
        }
        fclose(file);
    }
    
    return 0;
}