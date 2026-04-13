#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "csubstreamNode.h"

int csubstream( struct csubexec csube ){
    printf("\n\n#* ... cmd[ %s ] ... \n\t"
	"on_nline:[%p] | "
	"on_done:[%p] | "
	"... START\n", csube.cmd, csube.on_nline, csube.on_done );
    csube.exitCode = -1;
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
	    if( csube.on_nline == 0 ){
		    // Process the line in the buffer
		    printf("[%03i] Buffer: %s", csube.linesC++, csube.buffer );
	    }else{
		    csube.on_nline( csube.buffer );	
	    }
        }

        fclose(stream);
        close(csube.pipefd[0]);

        // 2. Handle Exit Code
        waitpid(csube.pid, &csube.status, 0);

        if(WIFEXITED(csube.status)) {
            csube.exitCode = WEXITSTATUS(csube.status);
            printf("--- Child exited with code: %d ---\n", csube.exitCode);
        } else if(WIFSIGNALED(csube.status)) {
            printf("--- Child terminated by signal: %d ---\n", WTERMSIG(csube.status));
        }

	if( csube.on_done != 0 )
		csube.on_done( csube.exitCode );
    	printf("#* ... cmd[ %s ] DONE\n\n", csube.cmd );
    
    }

    return 0;
}

#ifdef CSUBSTREAMTEST

// -------------- TEST FUNCTIONS FOR TEST -------- START 
int onNewLine( char *nl ){
	int slen = strlen( nl );
	if( nl[ slen - 1 ] == '\n' ){
		nl[ slen - 1 ] = 0;
	}
	printf("* on new line [%s] (%i)\n", nl, slen);
	return 0;
}

int onDone( int exitCode ){
	printf("* on done ... got exit code [%i]", exitCode );
}
// -------------- TEST FUNCTIONS FOR TEST ------- END 

int main(){

	printf("#* ... csubstream ... START\n");

	struct csubexec cse0 = { .cmd = "whoami" };
	csubstream( cse0 );	

	struct csubexec cse1 = { .cmd = "./test_csubstream.sh", .on_nline = onNewLine, .on_done = onDone };
	csubstream( cse1 );	

	struct csubexec cse2 = { .cmd = "termux-sensor -s orientation -d 500 -n 5" };
	csubstream( cse2 );	

	printf("#* ... csubstream ... DONE\n");
	return 0;
}

#endif

