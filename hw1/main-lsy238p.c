#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc,char *argv[],char *envp[])
{  
	char *args[2];
	args[0] = "ls";
	args[1] = NULL;

	close(1);
  	open("y", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
  	execv("/bin/ls", args);
	exit(0);
}