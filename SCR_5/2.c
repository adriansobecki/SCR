#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> 
#define BUF_SIZE 256

int main(int argc, char *argv[])
{
  char bufor[BUF_SIZE];
  int fd[2];
  if(pipe(fd)==-1)
    return 1;

  int pid;
  pid=fork();

  if(pid<0)  //blad
    return 1;
  else if(pid==0) //kod dziecka
    {
      close(fd[1]); //zamkniecie zapisu do pipe
      close(0);
      dup(fd[0]);
      close(fd[0]);
      execlp("display", "display", "-", NULL);

    }
  else //kod rodzica
    {
      char c;
      close(fd[0]); //zamkniecie odczytu z pipe
      FILE *fp;
      if ((fp=fopen(argv[1], "r"))==NULL)
	{
	  exit(1);
	}
      
      while((fread(bufor, sizeof(char),BUF_SIZE, fp)) > 0)
	{
	if(write(fd[1], &bufor, BUF_SIZE) < 0)
	  return 1;
	}
      sleep(5);
      close(fd[1]); //zamkniecie zapisu do pipe
      sleep(5);	
      fclose (fp);  // zamknij plik 
    }
}
