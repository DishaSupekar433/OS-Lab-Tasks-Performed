#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipefd[2]; // File descriptors for the pipe
    pid_t child_pid;

    // Create a pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    {
        // Child process (Reader)
        close(pipefd[1]); // Close the write end of the pipe

        char buffer[50];

        // Read the first message
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received 1st message: %s\n", buffer);

        // Read the second message
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received 2nd message: %s\n", buffer);

        close(pipefd[0]); // Close the read end of the pipe
    }
    else
    {
        // Parent process (Writer)
        close(pipefd[0]); // Close the read end of the pipe

        char message1[] = "Message 1 from parent";
        char message2[] = "Message 2 from parent";

        // Write the first message
        write(pipefd[1], message1, strlen(message1) + 1);

        // Write the second message
        write(pipefd[1], message2, strlen(message2) + 1);

        close(pipefd[1]); // Close the write end of the pipe
    }

    return 0;
}