#include "main.h"
void run_shell(void)
{
	char *prompt = "simple_shell$ ";
	char *command = NULL;
	size_t command_size = 0;
	ssize_t nread_char;
	pid_t pid;
	char *args[];

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
		/* Remove newline character from input*/
		if (command[nread_char - 1] == '\n')
		{
			command[nread_char - 1] = '\0';
		}
		/* Fork a new process*/
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/*Child process*/
			*args[] = {command, NULL};
			execve(command, args, NULL);

			/* If we get here, exec failed*/
			printf("%s: command not found\n", command);
			exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process*/
		wait(NULL);
	}
	/* Free memory allocated by getline()*/
	free(command);
}
int main(int argc, char *argv[])
{
	run_shell();
	return (0);
}