#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 10
#define LOOPS 1000000
long sum = 0;
pthread_mutex_t mymutex;

void *doWork(void *pdata){
	long i;

	for(i = 0; i < LOOPS; i++){
		pthread_mutex_lock (&mymutex);
		sum += 1;
		pthread_mutex_unlock (&mymutex);
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	pthread_t threads[NTHREADS];
	pthread_mutex_init(&mymutex, NULL);

	for(int i = 0; i < NTHREADS; i++){
		pthread_create(&threads[i], NULL, doWork, NULL);
	}

	for(int i = 0; i < NTHREADS; i++){
			pthread_join(threads[i], NULL);
	}

	printf("Thread sum: %ld\n", sum);
	sum = 0;

	for(int i = 0; i < NTHREADS*LOOPS; i++){
			sum += 1;
	}

	printf("Check sum: %ld\n", sum);
	pthread_exit(NULL);
	return 0;
}
