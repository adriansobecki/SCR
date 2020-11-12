#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int i=0;


void nazwa(int sig, siginfo_t *sip, ucontext_t *uap)
{
  switch(sig)
    {
    case 14:  //sigalrm
      printf("Dostalem signal numer %d\n", sig);
      exit(0);
      break;
    case 15:  //sigterm
      printf("Dostalem signal numer %d\n", sig);
      break;
    case 16:  //sigusr1
      printf("Dostalem signal numer %d\n", sig);
      if(i==0)
	i++;
      break;
    case 17:  //sigusr2
      break;
    }
  
      
}



void main()
{
  int k=0;
  sigset_t signal_set,signal_set2;
  sigemptyset(&signal_set);
  //sigaddset(&signal_set,17);  //blokowanie sygnalu nr. 17
  sigprocmask(SIG_BLOCK, &signal_set, NULL);

  
  struct sigaction act;
  act.sa_handler = nazwa;
  act.sa_flags = SA_SIGINFO;
  //sigaction(2, &act, 0);
  sigaction(14, &act, 0);
  sigaction(15, &act, 0);
  sigaction(16, &act, 0);
  sigaction(17, NULL, 0);
  
  while(1)
    {
      if(i==1)
	{
	k++;
	sigaddset(&signal_set,16);
	sigprocmask(SIG_SETMASK, &signal_set, NULL);
	//sigprocmask(SIG_BLOCK, &signal_set, NULL);
	}
      if(k>10)
	{
	i=0;
	k=0;
	sigdelset(&signal_set,16);
	sigprocmask(SIG_SETMASK, &signal_set, NULL);
	//sigprocmask(SIG_UNBLOCK, &signal_set, NULL);
	}
      
      printf("Hello World!\n");
      sleep(1);
    }
}
