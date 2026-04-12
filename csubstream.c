#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[1024];

    // 1. Create the pipe: pipefd[0] is read, pipefd[1] is write
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // --- CHILD PROCESS ---
        // Close the read end of the pipe (not needed by child)
        close(pipefd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        // Optional: Redirect stderr to stdout to capture errors too
        dup2(pipefd[1], STDERR_FILENO);

        close(pipefd[1]);

        // Execute bash command
        execlp("sh", "sh", "-c", "./test_csubstream.sh", NULL);
        //execlp("sh", "sh", "-c", "ls -l /etc | head -n 5", NULL);
        
        // If exec fails
        perror("execlp");
        exit(EXIT_FAILURE);

    } else {
        // --- PARENT PROCESS ---
        int status;

        // Close the write end of the pipe (not needed by parent)
        close(pipefd[1]);

        // Convert the file descriptor to a FILE stream for easy line reading
        FILE *stream = fdopen(pipefd[0], "r");
        if (stream == NULL) {
            perror("fdopen");
            exit(EXIT_FAILURE);
        }

        printf("--- Capturing Output ---\n");
        while (fgets(buffer, sizeof(buffer), stream) != NULL) {
            // Process the line in the buffer
            printf("Buffer: %s", buffer);
        }

        fclose(stream);
        close(pipefd[0]);

        // 2. Handle Exit Code
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("--- Child exited with code: %d ---\n", exit_code);
        } else if (WIFSIGNALED(status)) {
            printf("--- Child terminated by signal: %d ---\n", WTERMSIG(status));
        }
    }

    return 0;
}
