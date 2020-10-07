#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

// you can change the prototype of existing
// functions, add new routines and global variables
// cheatmode, car1, car2, report are different threads
// they communicate with each other via shared memory

volatile int shutdown = 0; // exit all thread
volatile int car_1 = 0; // position of car1
volatile int car_2 = 0; // position of car2

volatile int car1_user = 0; // position of car1 given by user
volatile int car2_user = 0; // position of car2 given by user

volatile int cheat1 = 0; // it ensures that car1 modified only once coresspondence to user input
volatile int cheat2 = 0; // it ensures that car2 modified only once coresspondence to user input

// create pthread
pthread_t cheatmode_thread;
pthread_t car1_thread;
pthread_t car2_thread;

// create locks
pthread_mutex_t car1_user_lock;
pthread_mutex_t car2_user_lock;

pthread_mutex_t car1_lock;
pthread_mutex_t car2_lock;


// the cheatmode thread
void *cheatmode(void *arg)
{
	char flag;
	int type;
	int pos;
	while(!shutdown){
		printf("\nDo you want cheat(y/n) :");
		int res1 =scanf("%c", &flag); 
		
		if (flag == 'y'){
			printf("\nwhich car do you want to relocate car1 or car2(1/2) :");
			int res2 =scanf("%d", &type);
			if(type == 1){
				printf("\nEnter new position :");
				int res3 = scanf("%d" , &pos);
				pthread_mutex_lock(&car1_user_lock);
				car1_user = pos;
				cheat1 = 1;
				pthread_mutex_unlock(&car1_user_lock);
				
			}
			else if(type == 2){
				printf("\nEnter new position :");
				int res3 = scanf("%d" , &pos);
				pthread_mutex_lock(&car2_user_lock);
				car2_user = pos;
				cheat2 = 1;
				pthread_mutex_unlock(&car2_user_lock);
			}
			sleep(1); // due to prevent some lagging which is mentioned in key point in design doc

			

		}
		else{
			continue;
		}
	}
	return NULL;
}

// the car1 thread
void *car1(void *arg)
{
	int pos = 0;
	while(!shutdown){
		pos = rand() % 10;
		pthread_mutex_lock(&car1_lock);

		car_1 = car_1 + pos;

		pthread_mutex_lock(&car1_user_lock);

		if (cheat1 == 1 ){
			car_1 = car1_user;
			cheat1 = 0;
		}

		pthread_mutex_unlock(&car1_user_lock);

		pthread_mutex_unlock(&car1_lock);
		sleep(1); // one second elapse 

	}
	return NULL;
}

// the car2 thread
void *car2(void *arg)
{
	int pos = 0;
	while(!shutdown){
		pos = rand() % 10;
		pthread_mutex_lock(&car2_lock);

		car_2 += pos;

		pthread_mutex_lock(&car2_user_lock);

		if (cheat2 == 1 ){
			car_2 = car2_user;
			cheat2 = 0;
		}
		
		pthread_mutex_unlock(&car2_user_lock);

		pthread_mutex_unlock(&car2_lock);
		sleep(1); // one second elapse

	}
	return NULL;
}

// the report thread
void *report(void *arg)
{
	int pos1 = 0;
	int pos2 = 0;
	while(!shutdown){
		pthread_mutex_lock(&car1_lock);
		pos1 = car_1;
		pthread_mutex_unlock(&car1_lock);
		pthread_mutex_lock(&car2_lock);
		pos2 = car_2;
		pthread_mutex_unlock(&car2_lock);

		printf("\ncar1_position %d , car2_position %d \n", pos1 , pos2);
		if(pos1 >= 100 && pos1 > pos2){
			printf("\ncar1 is winner\n");
			printf("\nGame end\n");
			shutdown = 1;
		}
		else if(pos2 >= 100 && pos2 > pos1){
			printf("\ncar2 is winner\n");
			printf("\nGame end\n");
			shutdown = 1;
		}
		else if(pos1==pos2 && pos1 >=100 ){
			printf("\nmatch tie\n");
			printf("\nGame end\n");
			shutdown = 1;
		}
		else{
			sleep(1); // one second elapse
		}

	}
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
	pthread_create(&car2_…
