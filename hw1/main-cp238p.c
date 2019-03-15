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
  /* Insert your code here */
  if(argc != 3){
    printf("arguments error\n");
    exit(1); 
  }

  char *src = argv[1];
  char *des = argv[2];

  close(0);
  open(src, O_RDONLY);
  close(1);
  open(des, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);

  char buf[512];
  int n;
  do{
    n = read(0, buf, sizeof buf);
    if(n == 0)
      break;
     if(n < 0){
        printf("read error\n");
        exit(1); 
      }
     if(write(1, buf, n) != n){
         printf("write error\n");
         exit(1);
      }
  }while(1);
  exit(0);
}