#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void interactive_mode() {
    while (1) {
        printf("%s", "wish> ");
        
        char *command = NULL;
        char *exit_command = "exit";
        size_t len = 0;
        ssize_t state;
        
        state = getline(&command, &len, stdin);

        if (state != -1) { // state is valid
            if (command[state - 1] == '\n') {
                command[state - 1] = '\0';
            }
            
            if (strcmp(command, exit_command) == 0) {
                free(command);
                exit(0);
            } else { // handle command and free it

                const char *delim = " ";
                // char *command_toks = strsep(&command, delim);
                char *command_toks;
                while ((command_toks = strsep(&command, delim)) != NULL) {
                    printf("%s\n", command_toks);
                }
                free(command);
            }
        } else { // state is invalid
            free(command);
            
            if (feof(stdin)) { // exit gracefully
                printf("Exiting\n");
                exit(0);
            } else { // handle error
                printf("An error has occurred.\n");
                exit(1);
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