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
#define path "/dev/input/mice"

/* defining the structure for timespec
* to check for the timming purpose
*/
struct timespec a;

/*signal handler to catch the signal 
 * generated and print the time remaining
*/
void handler(int signo)
{
	printf("Entered the handler | Time Remaining is : %d  sec\n",(int)a.tv_sec);
}

/* Main funcion */
int main()
{
	int ret;
	int fd;
	a.tv_sec=(time_t)10;// set the time in seconds
	a.tv_nsec=(time_t)10;// set the time in nanoseconds
	
	/* Register the signal for receiving the signal*/
	struct sigaction sa;
	memset(&sa,0,sizeof(sa));
	sa.sa_handler=&handler;
	sigaction(SIGIO,&sa,NULL);

	/*setting the file to generate SIGIO signal on getting the input */
	fd=open(path,O_RDWR | O_NONBLOCK);
	if (fd<0) 
	{
		printf("error in opening\n");
	}
	fcntl(fd,F_SETOWN,getpid());
	fcntl(fd,F_SETFL,FASYNC); // setting the file to be Asynchronous
	
	ret=1;
	printf("started nano sleep\n");
	printf("main function thread id : %lu\n",(unsigned long)pthread_self());

	while (ret!=0) 
	{
		ret=nanosleep(&a,&a);//the second variable of the function 'a' will hold the remaining time after interrupted by the signal
	}
	return 0;
}
