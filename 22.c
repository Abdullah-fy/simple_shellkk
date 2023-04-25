#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void run_shell(void)
{
        char *prompt = "simple_shell$ ";
        char *command = NULL;
        size_t command_size = 0;
        ssize_t nread_char;
        pid_t pid;
        int argc;
        char *arg;

    char **args = malloc(100 * sizeof(char*));

    while (1)
    {
            /* Display prompt and read command from user*/
            printf("%s", prompt);
            nread_char = getline(&command, &command_size, stdin);

            if (nread_char == -1)
            {
                    printf("\n");
                    break;
            }

            if (command[nread_char - 1] == '\n')
            {
                    command[nread_char - 1] = '\0';
            }


            argc = 0;
            arg = strtok(command, " ");

            while (arg != NULL)
            {
                    args[argc++] = strdup(arg);
                    arg = strtok(NULL, " ");
            }
            args[argc] = NULL;

            pid = fork();
           if (pid == -1)
            {
                    perror("fork");
                    exit(EXIT_FAILURE);
            }
            else if (pid == 0)
            {
                    execve(args[0],  args + 1, NULL);

                    printf("%s: command not found\n", args[0]);
                    exit(EXIT_FAILURE);
            }
            else
            {
                int status;
                wait(&status);
            }

    free(args);
    free(command);
    command = NULL;

    }

}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    run_shell();
    return (0);

}
