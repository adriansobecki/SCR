#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUF_SIZE 10
#define FIFO "/tmp/potok"

int main(int argc, char *argv[]){
  int fd;
  char bufor[BUF_SIZE];		
			       
  		
  mkfifo(FIFO, 0666);
  fd = open(FIFO, O_WRONLY);
  

  
  for(int i=1;i<argc;i++)
    {
      //FILE *fp;
      int fp;
      if ((fp=open(argv[i], O_RDONLY))==0)
	  exit(1);
      
      while((read(fp, bufor, BUF_SIZE)) >0)
	{
	if(write(fd, bufor, BUF_SIZE) < 0)
	  return 1;
	}
      close(fp);
      sleep(5);
    }

  close(fd);
  return 0;
}
