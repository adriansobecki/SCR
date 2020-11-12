#include <stdio.h>
#include <time.h>

int main()
{
  struct timespec tv;
  tv.tv_sec=0;
  tv.tv_nsec=100;
  int i=0;
  while(1)
    {
      printf ("%d", ++i);
      nanosleep(&tv,(struct timespec*) NULL);
    }
}
