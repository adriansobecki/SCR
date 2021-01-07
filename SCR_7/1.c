#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5

void* thread_fun(void *arg)
{
   long int id;
   id=(long int) arg;
   printf("Hello SCR. Written by thread ID %ld\n",id);
   pthread_exit(NULL);
}

int main()
{
   pthread_t threads[NUM_THREADS];

   for(long int t=0;t<NUM_THREADS;t++)
     {
     printf("poczatek wateku numer: %ld\n", t);
     if((pthread_create(&threads[t], NULL, thread_fun,(void *) t)))
       {
       printf("blad");
       exit(-1);
       }
     }

   for(int t = 0; t < NUM_THREADS; t++)
   {
      	pthread_join(threads[t], NULL);
	printf("koniec wateku nr: %d\n", t);
   }

   pthread_exit(NULL);
}
