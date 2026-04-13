
struct csubexec{
	char cmd[512];
	int (*on_nline)( char *line );
	int (*on_done)( int exitCode );
	int pipefd[2];
	pid_t pid;
	char buffer[1024];
	int linesC;
	int status;
	int exitCode;
};


