#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

struct csubexec{
	char cmd[512];
	int pipefd[2];
	pid_t pid;
	char buffer[1024];
	int linesC;
	int status;
};


int csubstream( struct csubexec csube ) {
    printf("csubstream ... with ... cmd[%s]\n", csube.cmd );
    //int pipefd[2];
    //pid_t pid;
    //char buffer[1024];

    // 1. Create the pipe: csube.pipefd[0] is read, csube.pipefd[1] is write
    if(pipe(csube.pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    csube.pid = fork();

    if(csube.pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(csube.pid == 0) {
        // --- CHILD PROCESS ---
        // Close the read end of the pipe (not needed by child)
        close(csube.pipefd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(csube.pipefd[1], STDOUT_FILENO);
        // Optional: Redirect stderr to stdout to capture errors too
        dup2(csube.pipefd[1], STDERR_FILENO);

        close(csube.pipefd[1]);

        // Execute bash command
        execlp("sh", "sh", "-c", csube.cmd, NULL);
        //execlp("sh", "sh", "-c", "termux-sensor -s orientation -d 1000", NULL);
        //execlp("sh", "sh", "-c", "./test_csubstream.sh", NULL);
        //execlp("sh", "sh", "-c", "ls -l /etc | head -n 5", NULL);
        
        // If exec fails
        perror("execlp");
        exit(EXIT_FAILURE);

    } else {
        // --- PARENT PROCESS ---
        //int status;

        // Close the write end of the pipe (not needed by parent)
        close(csube.pipefd[1]);

        // Convert the file descriptor to a FILE stream for easy line reading
        FILE *stream = fdopen(csube.pipefd[0], "r");
        if(stream == NULL) {
            perror("fdopen");
            exit(EXIT_FAILURE);
        }

        printf("--- Capturing Output ---\n");
        while (fgets(csube.buffer, sizeof(csube.buffer), stream) != NULL) {
            // Process the line in the buffer
            printf("[%03i] Buffer: %s", csube.linesC++, csube.buffer );
        }

        fclose(stream);
        close(csube.pipefd[0]);

        // 2. Handle Exit Code
        waitpid(csube.pid, &csube.status, 0);

        if(WIFEXITED(csube.status)) {
            int exit_code = WEXITSTATUS(csube.status);
            printf("--- Child exited with code: %d ---\n", exit_code);
        } else if(WIFSIGNALED(csube.status)) {
            printf("--- Child terminated by signal: %d ---\n", WTERMSIG(csube.status));
        }
    }

    return 0;
}


int main(){

	printf("#* ... csubstream ... START\n");

	struct csubexec cse0 = {
		.cmd = "whoami",
	};
	csubstream( cse0 );	
	

	struct csubexec cse1 = {
		.cmd = "./test_csubstream.sh"
	};
	csubstream( cse1 );	
	printf("#* ... csubstream ... DONE\n");
	return 0;
}

