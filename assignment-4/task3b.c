#include "library.c" // Including the library function created by user

pthread_t thread_id[10]; // declaring the ten threads to be created 

/* Creating the Handler Function 
 * for all the threads.i.e, create ten handler functions
*/

void handler1()
{
	printf("Entered the handler-1\n");
}

void handler2()
{

	printf("Entered the handler-2\n");
}

void handler3()
{
	printf("Entered the handler-3\n");
}

void handler4()
{
	printf("Entered the handler-4\n");
}

void handler5()
{
	printf("Entered the handler-5\n");
}

void handler6()
{
	printf("Entered the handler-6\n");
}

void handler7()
{
	printf("Entered the handler-7\n");
}

void handler8()
{
	printf("Entered the handler-8\n");
}

void handler9()
{
	printf("Entered the handler-9\n");
}

void handler10()
{
	printf("Entered the handler-10\n");
}

/* Creating the thread Function 
 * for all the threads.i.e, create ten thread functions
 * signal being registered in each thread to receive the signal
*/
void *thread1(void *args)
{
	struct sigaction signal;
	memset(&signal, 0, sizeof(signal));
	signal.sa_handler = signal_handler;
	signal.sa_flags = SA_SIGINFO;
	sigaction(SIGIO, &signal, NULL);
	load_thread( handler1);
	pause();
	pthread_exit(0);
}

void *thread2 (void *args)
{
	struct sigaction signal;
	memset(&signal, 0, sizeof(signal));
	signal.sa_handler = signal_handler;
	signal.sa_flags = SA_SIGINFO;
	sigaction(SIGIO, &signal, NULL);
	load_thread(  handler2);
	pause();
	pthread_exit(0);
}

void *thread3 (void *args)
{
	struct sigaction signal;
	memset(&signal, 0, sizeof(signal));
	signal.sa_handler = signal_handler;
	signal.sa_flags = SA_SIGINFO;
	sigaction(SIGIO, &signal, NULL);
	load_thread(  handler3);
	pause();
	pthread_exit(0);
}

void *thread4 (void *args)
{
	struct sigaction signal;
	memset(&signal, 0, sizeof(signal));
	signal.sa_handler = signal_handler;
	signal.sa_flags = SA_SIGINFO;
	sigaction(SIGIO, &signal, NULL);
	load_thread(  handler4);
	pause();
	pthread_exit(0);
}

void *thread5 (void *args)
{
	struct sigaction signal;
	memset(&signal, 0, sizeof(signal));
	signal.sa_handler = signal_handler;
	signal.sa_flags = SA_SIGINFO;
	sigaction(SIGIO, &signal, NULL);
	load_thread(  handler5);
	pause();
	pthread_exit(0);
}

void *thread6 (void *args)
{
	struct sigaction signal;
	memset(&signal, 0, sizeof(signal));
	signal.sa_handler = signal_handler;
	signal.sa_flags = SA_SIGINFO;
	sigaction(SIGIO, &signal, NULL);
	load_thread(  handler6);
	pause();
	pthread_exit(0);
}

void *thread7 (void *args)
{
	struct sigaction signal;
	memset(&signal, 0, sizeof(signal));
	signal.sa_handler = handler7;
	signal.sa_flags = SA_SIGINFO;
	sigaction(SIGIO, &signal, NULL);
	load_thread(  handler7);
	pause();
	pthread_exit(0);
}

void *thread8 (void *args)
{
	struct sigaction signal;
	memset(&signal, 0, sizeof(signal));
	signal.sa_handler = handler8;
	signal.sa_flags = SA_SIGINFO;
	sigaction(SIGIO, &signal, NULL);
	load_thread(  handler8);
	pause();
	pthread_exit(0);
}

void *thread9 (void *args)
{
	struct sigaction signal;
	memset(&signal, 0, sizeof(signal));
	signal.sa_handler = signal_handler;
	signal.sa_flags = SA_SIGINFO;
	sigaction(SIGIO, &signal, NULL);
	load_thread(  handler9);
	pause();
	pthread_exit(0);
}

void *thread10 (void *args)
{
	struct sigaction signal;
	memset(&signal, 0, sizeof(signal));
	signal.sa_handler = signal_handler;
	signal.sa_flags = SA_SIGINFO;
	sigaction(SIGIO, &signal, NULL);
	load_thread(  handler10);
	pause();
	pthread_exit(0);
}

/* MAIN FUNCTION */
int main()
{
	/*Signal regestration*/
	struct sigaction act;
	sigset_t set;
	memset(&act,0,sizeof act);
	sigemptyset(&set);
	sigaddset(&set, SIGIO);
	act.sa_handler = signal_handler;
	sigaction(SIGIO, &act, NULL);

	/*CREATING TEN THREADS */
	pthread_create(&thread_id[0],NULL,thread1, NULL);
	pthread_create(&thread_id[1],NULL,thread2, NULL);
	pthread_create(&thread_id[2],NULL,thread3, NULL);
	pthread_create(&thread_id[3],NULL,thread4, NULL);
	pthread_create(&thread_id[4],NULL,thread5, NULL);
	pthread_create(&thread_id[5],NULL,thread6, NULL);
	pthread_create(&thread_id[6],NULL,thread7, NULL);
	pthread_create(&thread_id[7],NULL,thread8, NULL);
	pthread_create(&thread_id[8],NULL,thread9, NULL);
	pthread_create(&thread_id[9],NULL,thread10, NULL);
	
	printf("Waiting for signal!!!\n");

	pthread_sigmask(SIG_BLOCK,&set,NULL);// BLOCK THE SIGNAL IN THE MAIN FUNCTION

 	/* JOIN THE THREADS*/
	pthread_join(thread_id[0],NULL);
	pthread_join(thread_id[1],NULL);
	pthread_join(thread_id[2],NULL);
	pthread_join(thread_id[3],NULL);
	pthread_join(thread_id[4],NULL);
	pthread_join(thread_id[5],NULL);
	pthread_join(thread_id[6],NULL);
	pthread_join(thread_id[7],NULL);
	pthread_join(thread_id[8],NULL);
	pthread_join(thread_id[9],NULL);
	
	return 0;
}
