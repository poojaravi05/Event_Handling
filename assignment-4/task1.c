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
#include <math.h>
#include <limits.h>
#include <float.h>
#include <sys/time.h>
#define MOUSEFILE "/dev/input/event8"

jmp_buf jumper; //initialize the jump buffer to store the context

// Thread Function to check the mouse click //
void *mouse_check(void* arg)
{
	int fd,c,d;
	float l,r,mn;
	float la[2];
	struct input_event ie;

	if((fd=open(MOUSEFILE,O_RDONLY))==-1)
	{
		perror("opening device");
		exit(EXIT_FAILURE);
	}

	c=0;d=0;
	la[0]=0;la[1]=0;

	while((read(fd,&ie,sizeof(struct input_event))))
	{
		if(ie.code==273)
		{
			c++;
			if(c%2==0)
			{
				d=c/2;
				l=ie.time.tv_sec%100;
				r=ie.time.tv_usec/1000;
				l=l+r*0.001;
				d=d%2;
				if(d==0)la[d]=l;
				if(d==1) la[d]=l;
				mn=(la[0]-la[1]);

				if(mn<0.50 && mn >-0.5)
				{
					printf("Double click detected\n");kill(0,SIGUSR1);return 0;
				}
			}
		}

	}
	return 0;
}


/*handler function */
void handler(int signal_number)
{
	printf("Entered the handler\n" );
	longjmp(jumper,-1);// perform jump to the stored context with value -1
}

/*MAIN FUNCTION */
int main(int argc,char **argv)
{
	int i,j;
	int ret;
	int sum=0;

	// Create a thread to detect the mouse click //
	pthread_t thread_id;

	ret=pthread_create( &thread_id, NULL, mouse_check , NULL );    // Create the thread //
	signal(SIGUSR1,handler); // register the signal to reeive the signa //
	printf("Waiting for the signal !!!\n"); // the main function is waiting for the signal
	ret=0;
	ret=setjmp(jumper);// jumps back to this point on performing the long jump
	i=2;
	
	/* fuction performing the continuous computation*/
	if(ret==0)
	{
		while(1)
		{
			for(j=0;j<i;j++)
			{
				j++;
			}
			sum=sum+j;
			i++;
		}
	}
	printf(" Event has been detected & exiting the main function &  result of computation is %d  \n", sum); // Terminating the main 														    program on the 														          detection of mouse click //
	pthread_join( thread_id,  NULL );
	return 0;
}
