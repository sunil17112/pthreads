#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>

// you can change the prototype of existing
// functions, add new routines and global variables
// cheatmode, car1, car2, report are different threads
// they communicate with each other via shared memory


// the cheatmode thread
void *cheatmode(void *arg)
{
	return NULL;
}

// the car1 thread
void *car1(void *arg)
{
	return NULL;
}

// the car2 thread
void *car2(void *arg)
{
	return NULL;
}

// the report thread
void *report(void *arg)
{
	return NULL;
}
// it create all threads and initialize all locks
void create_all_thread(){

	pthread_mutex_init(&car1_lock , NULL);
	pthread_mutex_init(&car2_lock , NULL);
	pthread_mutex_init(&car1_user_lock , NULL);
	pthread_mutex_init(&car2_user_lock , NULL);


	pthread_create(&cheatmode_thread , NULL , &cheatmode , NULL);
	pthread_create(&car1_thread , NULL , &car1 , NULL);
	pthread_create(&car2_thread , NULL , &car2 , NULL);
	
}

// it join all threads and destroy all locks
void join_all_thread(){
	pthread_join(cheatmode_thread , NULL);
	pthread_join(car1_thread , NULL);
	pthread_join(car2_thread , NULL);
	

	pthread_mutex_destroy(&car1_lock );
	pthread_mutex_destroy(&car2_lock);
	pthread_mutex_destroy(&car1_user_lock);
	pthread_mutex_destroy(&car2_user_lock);

}

// create all threads
int main()
{

	create_all_thread(); // create all pthreads
	report(0); // using master / main thread for report component as a fourth thread

	join_all_thread(); // join all pthreads

	return 0;
}
