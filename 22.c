#include "main.h"

void run_shell(void)
{
	char *prompt = "simple_shell$ ";
	char *command = NULL;
	size_t command_size = 0;
	ssize_t nread_char;

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
		/* Parse command and arguments*/
		int argc = 0;
		char *args[nread_char + 1];
		char *arg = strtok(command, " ");

		while (arg != NULL)
		{
			args[argc++] = arg;
			arg = strtok(NULL, " ");
		}
		args[argc] = NULL;
		/* Fork a new process*/
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/* Child process*/
			if (execve(args[0], args, NULL) == -1)
			{
				/* If we get here, exec failed*/
				printf("%s: command not found\n", args[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
		/* Parent process*/
		int status;

		wait(&status);
		}
	}
	/* Free memory allocated by getline()*/
	free(command);
}
int main(int argc, char *argv[])
{
	run_shell();
	return (0);
}