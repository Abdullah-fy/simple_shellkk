#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void run_shell() {
char *prompt = "simple_shell$ ";
char *command = NULL;
size_t command_size = 0;
ssize_t nread_char;

while (1) 
{ 
	/*Display prompt and read command from user*/ 
	printf("%s", prompt); 
	nread_char = getline(&command, &command_size, stdin); 

	/*Handle end of file (Ctrl+D)*/ 
	if (nread_char == -1) 
	{ 
		printf("\n"); 
		break; 
	} 

	/*Split input into command name and arguments*/ 
	char *command_name = strtok(command, " "); 
	char *arguments = strtok(NULL, "\n"); 

	/*Check for and handle redirection*/ 
	if (strchr(command, '>') != NULL) 
	{ 
		perform_output_redirection(command); 
	} 
	else if (strchr(command, '<') != NULL) 
	{ 
		perform_input_redirection(command); 
	} 
	else 
	{ 
		/*Execute command normally */ 
		char *full_path = command_name;
		if (command_name[0] != '/') 
		{ 
			full_path = find_command(command_name); 
		} 

		/*Fork a new process*/ 
		pid_t pid = fork(); 
		if (pid == -1) 
		{ 
			perror("fork"); 
			exit(EXIT_FAILURE); 
		} 
		else if (pid == 0) 
		{ 
			/*Child process*/ 
			execlp(full_path, command_name, arguments, NULL); 

			/*If we get here, execlp failed*/ 
			printf("%s: command not found\n", full_path); 
			exit(EXIT_FAILURE); 
		} 
		else 
		{ 
			/* Parent process*/ 
			wait(NULL); 
		} 
	} 
} 

/*Free memory allocated by getline()*/ 
free(command); 

}

int main(int argc, char *argv[]) {
run_shell();
return 0;
}