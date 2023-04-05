#include "pipex.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char *argv[], char *envp[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *command = "env";
    char *filename = argv[2];

    char *path = NULL;
    for (int i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], "PATH=", 5) == 0) {
            path = envp[i] + 5;
            break;
        }
    }

    if (path == NULL) {
        printf("PATH environment variable not found\n");
        return 1;
    }

    char *dir = strtok(path, ":");
    while (dir != NULL) {
        char fullpath[256];
        snprintf(fullpath, 256, "%s/%s", dir, command);
        if (access(fullpath, X_OK) == 0) {
            printf("path : %s\n", fullpath);
            char *args[] = {fullpath, filename, NULL};
            int ret = execve(args[0], args, envp);
            if (ret == -1) {
                perror("execve");
                return 1;
            }
            break;
        }

        dir = strtok(NULL, ":");
    }

    printf("Command not found: %s\n", command);
    return 1;
}


// int main(int argc, char *argv[]) {
//     char *args[] = {"cat", argv[1], NULL};
//     int ret = execve("/bin/cat", args, NULL);
//     if (ret == -1) {
//         perror("execve");
//         return 1;
//     }
//     return 0;
// }