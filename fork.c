#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    // Fork a new process
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    {
        // This code is executed by the child process
        printf("Child process ID: %d\n", getpid());
        printf("Executing 'ls' command...\n");

        // Execute the 'ls' command using exec
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);

        // If execvp returns, it means an error occurred
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        // This code is executed by the parent process
        printf("Parent process ID: %d\n", getpid());

        // Wait for the child process to complete
        int status;
        pid_t terminated_child_pid = wait(&status);

        if (terminated_child_pid == -1)
        {
            perror("wait");
            exit(EXIT_FAILURE);
        }

        printf("Child process with ID %d has terminated with status %d\n", terminated_child_pid, status);
    }

    return 0;
}
