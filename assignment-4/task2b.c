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
#include <limits.h>
#include <float.h>
#include <semaphore.h>
#include <sys/time.h>

/*Intitializnig the global variables
 * jumper to jump back to the saved context
 * xyz is the semaphore declared
*/

jmp_buf jumper;
sem_t xyz;
unsigned long x;
int i=0;

/*Handler funnction to catch the signal genearated
 *signo being the number of the signal received
*/
void handler(int signo)
{
	printf("Entered the handler\n" );
}

/* Thread function 
 * here the signal is installed using sigaction struct
 * semaphore is initialized and is made to wait initially
*/
void *fn1(void *arg)
{
    struct sigaction sa;
	memset(&sa,0,sizeof(sa));
	sa.sa_handler=&handler;
	sigaction(SIGUSR1,&sa,NULL);// signal registered ...i.e, signal SUIGUSR1
	x=pthread_self(); // thread id of this thread
	printf("Entered the thread & its id is : %lu\n",x);
	sem_init(&xyz,0,0); //initialize the semaphore 
	printf("Waiting to acquire semaphore\n");
	sem_wait(&xyz); // wait for acquiring the semaphore
	printf("released the semaphore\n");
	pthread_exit(0);
}

/* Main funciton */
int main()
{	
	int iret;
	pthread_t thread_high; //declare the thread 
	iret = pthread_create(&thread_high, NULL , &fn1, NULL);// create the thread
	if(iret!=0)printf("Error in thread creation\n");
	sleep(3);
	pthread_kill(x,SIGUSR1); // generate the signal i.e, SIGUSR1 signal
	pthread_join(thread_high, NULL);// join the threads created 
	printf("the created thread was joined\n");
	return 0;
}
