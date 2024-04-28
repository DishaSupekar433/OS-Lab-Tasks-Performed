#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t child_pid;
    int status;

    // Fork a child process
    child_pid = fork();

    if (child_pid == -1)
    {
        perror("Fork failed");
        exit(1);
    }

    if (child_pid == 0)
    {
        // This code runs in the child process

        // Define the command and arguments for execve
        char *program = "/bin/ls";
        char *args[] = {"ls", "-l", NULL};

        // Execute the ls command using execve
        execve(program, args, NULL);

        // If execve fails, it will reach here
        perror("Execve failed");
        exit(1);
    }

    else
    {
        // This code runs in the parent process

        printf("Parent process: Child process ID is %d\n", child_pid);

        // Wait for the child process to complete
        wait(&status);

        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            printf("Parent process: Child exited with status %d\n", exit_status);
        }
        else
        {
            printf("Parent process: Child process did not exit normally\n");
        }
    }

    return 0;
}
