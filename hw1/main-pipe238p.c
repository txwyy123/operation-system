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
	int p1[2];
	int p2[2];
	pipe(p1);
	pipe(p2);

	if(fork() == 0){
      char *argv[2];
      argv[0] = "ls";
      argv[1] = 0;
      close(1);
      dup(p1[1]);
	  close(p1[0]);
      execv("/bin/ls", argv);
      printf("a\n");
	}else{
	  close(p1[1]);
        wait(NULL);
	}

	if(fork() == 0){
      char *argv[3];
      argv[0] = "grep";
      argv[1] = "echo.c";
      argv[2] = 0;
      close(0);
      dup(p1[0]);
      close(1);
      dup(p2[1]);
	  close(p1[1]);
	  close(p2[0]);
      execv("/usr/bin/grep", argv);
      printf("b\n");
	}else{
		close(p1[0]);
		close(p2[1]);
        wait(NULL);
	}

	if(fork() == 0){
      char *argv[2];
      argv[0] = "wc";
      argv[1] = 0;
      close(0);
      dup(p2[0]);
	close(p2[1]);
      execv("/usr/bin/wc", argv);
      printf("c\n");
	}else{
		close(p2[0]);
        wait(NULL);
	}
	exit(0);
}