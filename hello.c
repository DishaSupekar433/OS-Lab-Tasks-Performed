#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    // Create a variable to store the process ID
    pid_t pid;

    // Fork a new process
    pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // This code will be executed by the child process

        // Define the command and arguments for execv
        char *command = "/bin/ls"; // Example: list files in the /bin directory
        char *args[] = {command, NULL};

        // Execute the specified program
        if (execv(command, args) == -1)
        {
            perror("Execv failed");
            exit(1);
        }
    }
    else
    {
        // This code will be executed by the parent process

        // Wait for the child process to complete
        int status;
        wait(&status);

        if (WIFEXITED(status))
        {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("Child process did not exit normally\n");
        }
    }

    return 0;
}
