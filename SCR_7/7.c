#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#define NUM_THREADS 15
#define AMOUNT 5000000

bool check(double x, double y);

void* thread_fun(void *arg)
{
  long int* counter;
  counter=(long int*)arg;
  for(int i=0;i<AMOUNT;i++)
    {
      double x=drand48();
      double y=drand48();
      if(check(x,y))
	(*counter)++;
    }
  pthread_exit(NULL);
}

int main()
{
   pthread_t threads[NUM_THREADS];
   long int results[NUM_THREADS]={0};
   
   for(long int t=0;t<NUM_THREADS;t++)
     {
     printf("poczatek watku numer: %ld\n", t);
     if((pthread_create(&threads[t], NULL, thread_fun,(void *) &results[t])))
       {
       printf("blad");
       exit(-1);
       }
     }

   double pi=0;
   for(int t = 0; t < NUM_THREADS; t++)
   {
     pthread_join(threads[t],NULL);
     printf("watek nr %d,value: %ld\n",t, results[t]);
	pi=pi+results[t];
   }
   pi=pi/(AMOUNT*NUM_THREADS)*4;
   
   printf("PI: %f\n", pi);
   pthread_exit(NULL);
}

bool check(double x, double y)
{
  if((x*x+y*y)<1.0)
    return true;
  return false;
}
