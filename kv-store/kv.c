#include <stdio.h>
#include <string.h>

static char *cmd_options[] = {"a", "c", "d", "g", "p"};

// get all k-v pairs stored
void a_cmd(char **command) {

}

// clear all entries
void c_cmd(char **command) {

}

// delete an entry
void d_cmd(char **command) {

}

// get an entry
void g_cmd(char **command) {

}

// add/update an entry
void p_cmd(char **command) {

}


void (*cmd_function[]) (char **) = {
  &a_cmd,
  &c_cmd,
  &d_cmd,
  &g_cmd,
  &p_cmd
};

void execute_command(char **command) {
    for (int i = 0; i < 5; i++) {
        if (strcmp(command[0], cmd_options[i])) {
            cmd_function[i](command);
        }
    }
}

char **parse_command(char *command) {
    int cap = 4;
    int filled = 0;
    char **arr = malloc(cap * sizeof(char *));

    char *tok;
    if (arr == NULL) {
        printf("%s", "malloc error");
    }

    while ((tok = strsep(&command, ",")) != NULL) {
        if (*tok == '\0') continue; // skip empty tokens from multiple spaces

        arr[filled] = strdup(tok);
        filled++;
    }
    
    arr[filled] = NULL;
    return arr;
}

// Get K/V pairs from database file and load into hashmap
int get_from_db() {
    FILE *file;
    file = fopen("database.txt", "a+");

    if (file == NULL) {
        printf("Error opening or creating file!\n");
        return 1;
    }

    int buffer_size = 100;
    char buffer[buffer_size];



    fclose(file);
    return 0;
}


int main(int argc, char *argv[]) {
    if (argc == 1) return 0;

    // populate hashmap
    if (get_from_db() == 1) {
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        char **command = parse_command(argv[i]);


        free(command);
    }
}