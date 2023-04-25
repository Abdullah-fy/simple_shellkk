#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * run_shell - excute the fiel
 */
void run_shell(void)
{
char *prompt = "simple_shell$ ";
char *command = NULL;
size_t command_size = 0;
ssize_t nread_char;
pid_t pid;

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
{
command[nread_char - 1] = '\0';
}
pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
char *args[] = {"command", NULL};

execve(command, args, NULL);
printf("%s: command not found\n", command);
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}
free(command);
}
/**
 * main - the main shell code
 * @argc: number of arguments passed
 * @argv: program arguments to be parsed
 *
 * applies the functions in utils and helpers
 * implements EOF
 * Prints error on Failure
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
(void)argc;
(void)argv;
run_shell();
return (0);
}
