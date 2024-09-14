#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include  <string.h>
#include <stddef.h>
#define path "/dev/input/mice"
#define no_of_threads 10  // defining the number of threads to be created in the function

/* Handler function to catch the signal generated */
void handler(int signum)
{
	printf("The signal handler is serving the thread_id : %lu \n",(unsigned long)pthread_self());// print the thread_id to which the 														signal hadler is serving//
}

/* thread function
* register the signal in each thread
* being created 
*/
void* thread_func(void * argv)
{	
	/*registering the signal*/
	struct sigaction usr_action;
	memset(&usr_action, 0, sizeof(usr_action));
	usr_action.sa_handler = handler;
	sigaction(SIGIO, &usr_action, NULL);// signal IO registered
	printf("The thread_id Waiting for the signal is:%lu \n",(unsigned long)pthread_self());// printing the thread_id waiting for the signal
	pause();// wait for the signal
	pthread_exit(0);

}

/*Main function*/
int main()
{
	int i;	
	int fd;
	pthread_t thread[no_of_threads];// declare the threads
	printf(" Main thread_id : %lu !!!\n",(unsigned long)pthread_self());// print the main thread_id

	/*blocking the signal in the main thread*/
	struct sigaction act;
	sigset_t set;
	memset(&act,0,sizeof act);
	sigemptyset(&set);
	sigaddset(&set, SIGIO);
	act.sa_handler = handler;
	sigaction(SIGIO, &act, NULL);

	/*setting the signal to generate the SIGIO signal*/
	fd=open(path,O_RDWR | O_NONBLOCK);
	if (fd<0) 
	{
		printf("error in opening\n");
	}
	fcntl(fd,F_SETOWN,getpid());
	fcntl(fd,F_SETFL,FASYNC);

	/*creating the threads*/
	for(i=0;i<no_of_threads;i++)
	{	
		pthread_create(&thread[i],NULL,&thread_func,NULL);
	}

	pthread_sigmask(SIG_BLOCK,&set,NULL);// block the signal in the main thread

	/* join the threads*/	
	for(i=0;i<no_of_threads;i++)
		pthread_join(thread[i],NULL);

	return 0;
}
