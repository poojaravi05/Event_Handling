#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <poll.h>
#include <stdint.h>
#include <linux/input.h>
#include <signal.h>
#include <setjmp.h>
#include <sched.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <float.h>
#include <semaphore.h>
#include <sys/time.h>
pthread_t x;
/* Initializing the global variables
 * flag : used to indicate that signal has arrived and handler has been called.
 * params : used to set the priority of the thread.
*/
int flag=0;
struct sched_param params;

/* Handler function which is initiated when the signal
 * arrives, and sets the flag variable to 1
*/
void handler(int signum)
{
	printf("\n============================================================================\n");
	printf("Entered the handler !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	flag=1;
	printf("\n============================================================================\n");
}

/*Lower priority thread function
 *The SIGUSR1 signal is registered in this thread,using the sigaction structure.
 *Once the signal arrives the flag is set to 1,the print statement gets initiated within the while loop
 *and starts printing the statements
*/
void *fun_low(void *agrv)
{
	int i;
	struct sigaction usr_action;
	memset(&usr_action, 0, sizeof(usr_action));
	usr_action.sa_handler = handler;
	sigaction(SIGUSR1, &usr_action, NULL); //registration of the signal
	x=pthread_self();
	printf("\nLower priority thread running...\n");

	while(1)
	{	/*print the statements only after the handler is called*/
		if(flag==1)
		{
			for(i=0;i<35;i++) 
				printf("Lower priority thread running and count is : %d \n",i);
		  	break;
		}
		else
			sleep(1);
	}
	return 0;
}

/* Higher priority thread
 * here we just printing the statements to keep the thread running
 * The signal is killed or raised in this thread, thus invoking the
 * HANDLER function.
*/
void *fun_high(void *(agrv))
{
	int j=0;
	int ret;

	pthread_t this_thread=pthread_self();
	ret=pthread_setschedparam(this_thread,SCHED_RR,&params); //set the scheduling parameters of the higher priority thread
	if(ret!=0)
	{	printf("Error in setting the priority!!!\n");// check for the corectness
		return 0;
	}

	/*print the statements to keep the thread running*/
	for(j=0;j<100;j++)
	{
		printf("Higher priority thread running and count is : %d\n",j);
		if(j==50)
		{
		    pthread_kill(x,SIGUSR1); // deliver the signal .i.e, generating the signal
		}
	}
	printf("\n============================================================================\n");
	printf("Finished executing higher priority thread...\n");
	printf("\n============================================================================\n");
	return 0;
}

/*main function*/
int main()
{
	pthread_t thread_low,thread_high;// initialize two threads

	/* creating threads*/
	pthread_create(&thread_low,NULL,&fun_low,NULL);
	sleep(1);
	params.sched_priority=sched_get_priority_max(SCHED_RR);
	pthread_create(&thread_high,NULL,&fun_high,NULL);

	/*join the threads after the completion of execution */
	pthread_join(thread_high,NULL);
	pthread_join(thread_low,NULL);
	return 0;
}
