#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 10

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
      //printf("pid0");
      close(fd[1]); //zamkniecie zapisu do bufora
      while((read(fd[0], &bufor, BUF_SIZE)) > 0)
	printf(" #%s# ",bufor);
    }
  else //kod rodzica
    {
      //printf("pidrodzica");
      char c;
      close(fd[0]); //zamkniecie odczytu z bufora
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
      close(fd[1]); //zamkniecie zapisu do bufora	
      fclose (fp); /* zamknij plik */
    }
}
