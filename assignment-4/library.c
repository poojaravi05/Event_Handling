#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#define path "/dev/input/mice"

/* DEACLARING THE GLOBAL VARIABLES
*/
int fd;
int flag=0;

/*declare funtions */
void (*store_function[20])();
pthread_mutex_t hold = PTHREAD_MUTEX_INITIALIZER;// mutex to achieve synchrionization
static int count = 0;

/* load the received function in the array of function*/
void load_thread( void *func)
{	
	/*we need to set the file for generating the SIGIO signal*/	
	if(flag==0)
	{
		fd = open(path, O_RDONLY);
		if(fd < 0)
		{
			printf("Failed to Open Mice Device\n");
			exit (0);
		}
		fcntl(fd, F_SETOWN, getpid());
		flag=fcntl(fd, F_GETFL);
		fcntl(fd, F_SETFL, flag | FASYNC);
		flag=1;
	}
	/*Loadig all the handler functions into the function array declared*/
	pthread_mutex_lock(&hold);// lock the global variable
	if(count < 20)
	{
		store_function[count] = func;
		count++;// keep the count of the functions being loaded
	}
	pthread_mutex_unlock(&hold);//unlock the global variable
}

/* the final signal_handler function which when initiated 
* serves all the threads with their respective handlers
*/
void signal_handler(int signo)
{
	int i;
	/* call all the handler functions*/
	for(i=0;i<count;i++)
	{
		store_function[i]();

	}
	exit(0);
}
