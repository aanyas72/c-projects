#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *builtin_str[] = {
  "cd",
  "path",
  "exit"
};

int num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int cd_cmd(char **commands) {
    int argc = 0;
    while (commands[argc] != NULL) {
        argc++;
    }

    if (argc != 2) {
        fprintf(stderr, "Usage: cd <directory>\n");
        return 1;
    }

    if (chdir(commands[1]) != 0) {
        perror("cd");
        return 1;
    }

    return 0;
}

int path_cmd(char **commands) {
    return 1;
}

int exit_cmd(char **commands) {
    exit(0);
    return 1;
}

int (*builtin_func[]) (char **) = {
  &cd_cmd,
  &cd_cmd,
  &exit_cmd
};

char **parse_command(char *command) {
    int cap = 10; // initial array size
    int filled = 0;
    char **arr = malloc(cap * sizeof(char *)); // hold pointers to all strings in the command
    
    // handle command and free it
    char *tok;

    if (arr == NULL) {
        printf("%s", "malloc error :(");
    }

    while ((tok = strsep(&command, " ")) != NULL) {
        if (*tok == '\0') continue; // skip empty tokens from multiple spaces
            
        if (filled == cap) {
            cap *= 2;
            arr = realloc(arr, cap * sizeof(char *));

            if (!arr) {
                printf("%s", "realloc error");
                exit(1);
            }
        }

        arr[filled] = strdup(tok);
        filled++;
    }
    
    arr[filled] = NULL; // null terminate the array
    return arr;
}

int execute_commands(char **commands) {

    for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(commands[0], builtin_str[i]) == 0) {
            return builtin_func[i](commands);
        }
    }
    
    // fork duplicates the current process and returns the process id
    // execv replaces the current process with a new one
    pid_t pid;
    int status = 0;

    pid = fork();
    
    if (pid < 0) {
        // Error occurred
        printf("%s", "fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        if (execvp(commands[0], commands) == -1) {
            perror("lsh");
        }
        exit(1);
    } else {
        // Parent Process
        waitpid(pid, &status, WUNTRACED);
    }

    return 0;
}

void interactive_mode() {
    while (1) {
        printf("%s", "wish> ");

        char *command = NULL;
        size_t len = 0;
        ssize_t state;

        state = getline(&command, &len, stdin);

        if (state == -1) {
            free(command);
            printf("%s", "Error reading line");
            exit(1);
        }

        if (command[state - 1] == '\n') {
            command[state - 1] = '\0';
        }

        char **commands = parse_command(command);
        if (execute_commands(commands) != 0) break;

        for (int i = 0; commands[i] != NULL; i++) {
            free(commands[i]);  // free each string
        }

        free(command);
        free(commands);
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