#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

pid_t find_command(char *command);

void run_shell() {
char *prompt = "simple_shell$ ";
char *command = NULL;
size_t command_size = 0;
ssize_t nread_char;

while (1) { 
    // Display prompt and read command from user 
    printf("%s", prompt); 
    nread_char = getline(&command, &command_size, stdin); 

    // Handle end of file (Ctrl+D) 
    if (nread_char == -1) { 
        printf("\n"); 
        break; 
    } 

    // Remove newline character from input 
    if (command[nread_char - 1] == '\n') { 
        command[nread_char - 1] = '\0'; 
    } 

    // Check if command is "exit" 
    if (strcmp(command, "exit") == 0) { 
        break; 
    } 

    // Check if command is "env" 
    if (strcmp(command, "env") == 0) { 
        for (char **env = environ; *env != 0; env++) { 
            printf("%s\n", *env); 
        } 
        continue; 
    } 

    // Check if command exists in PATH 
    pid_t result = find_command(command); 
    if (result == -1) { 
        printf("%s: command not found\n", command); 
    } else { 
        // Fork a new process 
        pid_t pid = fork(); 
        if (pid == -1) { 
            perror("fork"); 
            exit(EXIT_FAILURE); 
        } else if (pid == 0) { 
            // Child process 
            execlp(command, command, (char *) NULL); 

            // If we get here, exec failed 
            printf("%s: command not found\n", command); 
            exit(EXIT_FAILURE); 
        } else { 
            // Parent process 
            wait(NULL); 
        } 
    } 
} 

// Free memory allocated by getline() 
free(command); 

}

pid_t find_command(char *command) {
// Rest of code...
}

int main(int argc, char *argv[]) {
run_shell();
return 0;
}
