#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
int main()
{
  char n_pliku[50];
  int plik_map;
  int fd, pid;
  FILE* fd_r;
  size_t rozmiar;
  char* obszar_pamieci;
  struct stat buf;
  plik_map = open("plik_map", O_RDWR | O_CREAT);

  if(plik_map==-1)
    {
    printf(" %s\n", strerror(errno));
    return -1;
    }
  
  pid=fork();

  if(pid<0)  //blad
    return 1;

  if(pid==0)
    {
        sleep(10);
	execlp("display", "display", "-update", "1", "-delay", "2", "plik_map", NULL);
    }
  
  while(1)
 {
      printf("Podaj nazwe pliku\n");
      scanf("%s",n_pliku);
      if(n_pliku[0]=='.')
	break;
      fd=open(n_pliku,O_RDONLY);
      fstat(fd, &buf);

      //printf("%ld\n",buf.st_size);
      
      ftruncate(plik_map, buf.st_size);
      
      //fstat(plik_map, &buf);
      //printf("%ld\n",buf.st_size);
	
      obszar_pamieci=mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, plik_map, 0);
      if (obszar_pamieci == MAP_FAILED)
	printf("blad");
      printf(" %s\n", strerror(errno));

      /*
      close(fd);
      fd_r=fopen(n_pliku,"r");
      
      while(!feof(fd_r))
	{
	  obszar_pamieci[i++]=getc(fd_r);
   	}
      fclose(fd_r);
      */
      read(fd, obszar_pamieci,buf.st_size);
      msync(obszar_pamieci, buf.st_size, MS_SYNC);
      munmap(obszar_pamieci, buf.st_size);
 }
  close(plik_map);
}
