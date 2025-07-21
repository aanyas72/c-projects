#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void interactive_mode() {
    while (1) {
        printf("%s", "wish> ");
        
        char *command = NULL;
        size_t len = 0;
        ssize_t state;
        
        state = getline(&command, &len, stdin);

        if (state != -1) {
            // handle command and free it
            free(command);
        } else {
            if (feof(stdin)) { // exit gracefully
                free(command);
                exit(0);
            } else { // handle error
                printf("An error has occurred.\n");
                free(command);
                exit(-1);
            }
        }
    }
}

void batch_mode() {

}

int main(int argc, char *argv[]) {
    if (argc > 2) {

    }
    if (argc == 1) { // interactive mode
        interactive_mode();
    } else { // batch mode, read from files
        batch_mode();
    }

    return 0;
}