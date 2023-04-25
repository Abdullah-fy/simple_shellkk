#include "main.h"

#define MAX_ARGS 100

void run_shell()
{
        char *prompt = "simple_shell$ ";
        char *command = NULL;
        char *dir;
        char *path;
        size_t command_size = 0;
        ssize_t nread_char;
        pid_t pid;
        int argc = 0;
        char cmd_path[1024];
        char *args[MAX_ARGS];
        char path_copy[1024];

        while (1)
        {
                printf("%s", prompt);
                nread_char = getline(&command, &command_size, stdin);

                if (nread_char == -1)
                {
                        printf("\n");
                        break;
                }

                if (command[nread_char - 1] == '\n')
                        command[nread_char - 1] = '\0';

                argc = 0;
                char *arg = strtok(command, " ");

                while (arg != NULL)
                {
                        args[argc++] = arg;
                        arg = strtok(NULL, " ");
                }
                args[argc] = NULL;
                path = getenv("PATH");
                strcpy(path_copy, path);
                dir = strtok(path_copy, ":");

                while (dir != NULL)
                {
                        snprintf(cmd_path, sizeof(cmd_path), "%s/%s", dir, args[0]);
                        if (access(cmd_path, X_OK) == 0)
                        {
                                args[0] = cmd_path;
                                break;
                        }
                        dir = strtok(NULL, ":");
                }
                pid = fork();

                if (pid == -1)
                {
                        perror("fork");
                        exit(EXIT_FAILURE);
                }
                else if (pid == 0)
                {
                        if (execve(args[0], args, NULL) == -1)
                        {
                                printf("%s: command not found\n", args[0]);
                                exit(EXIT_FAILURE);
                        }
                }
                else
                {
                        int status;

                        wait(&status);
                }
        }
        free(command);
}
int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        run_shell();
        return (0);
}
