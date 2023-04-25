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

    char **args = malloc(100 * sizeof(char*)); 

    while (1) 
    { 
            /* Display prompt and read command from user*/ 
            printf("%s", prompt); 
            nread_char = getline(&command, &command_size, stdin); 

            /* Handle end of file (Ctrl+D)*/ 
            if (nread_char == -1) 
            { 
                    printf("\n"); 
                    break; 
            } 

            /*Remove newline character from input*/ 
            if (command[nread_char - 1] == '\n') 
            { 
                    command[nread_char - 1] = '\0'; 
            } 

             char *arg = strtok(command, " ");  // Move this to before the while loop 

            /* Parse command and arguments*/ 
            argc = 0; 

            while (arg != NULL) 
            { 
                    args[argc++] = strdup(arg); 
                    arg = strtok(NULL, " "); 
            } 
            args[argc] = NULL; 

            /* Fork a new process*/ 
            pid = fork(); 
           if (pid == -1) 
            { 
                    perror("fork"); 
                    exit(EXIT_FAILURE); 
            } 
            else if (pid == 0) 
            { 
                    /* Child process*/ 
                    execve(args[0],  args + 1, NULL);   

                    /* If we get here, exec failed*/ 
                    printf("%s: command not found\n", args[0]); 
                    exit(EXIT_FAILURE); 
            } 
            else 
            { 
            /* Parent process*/ 
            int status; 
            wait(&status); 
            } 

    /* Free allocated memory */ 

    free(args); 
    free(command); 
    } 

}

int main(int argc, char *argv[]) {
run_shell();
return (0); }

