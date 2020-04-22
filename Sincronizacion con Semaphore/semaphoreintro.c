#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h> //Para semaforos
#include <fcntl.h>   //For 0__* constants
#include <sys/stat.h> //Constantes de modo
#include <unistd.h>

int main(int argc, char *argv[]){

	mode_t perms = 0666;
	int flags = O_CREAT;

	//Valor inicial del semáforo
	unsigned int value = 0;

	//Crear el semáforo
	sem_t *sem = sem_open("semExample", flags, perms, value);

	if(sem == SEM_FAILED){
		perror("pSemCreate sem_open fails: ");
		return -1;
	}

	// Si el semáforo debe seguir disponible para otros procesos solo hago
	// close.
	// Si se quiere destruir el semáforo se hace sem_unlink
	//


	if(sem_close(sem) == -1){
		perror("pSemCreate sem_close fails: ");
		return -1;
	}
	return 0;
}

//pSemCreate.c
/*

 int main(int argc, char *argv[]){

	mode_t perms = 0666;
	int flags = O_CREAT;

	//Valor inicial del semáforo
	unsigned int value = 0;

	//Crear el semáforo
	sem_t *sem = sem_open("semExample", flags, perms, value);

	if(sem == SEM_FAILED){
		perror("pSemCreate sem_open fails: ");
		return -1;
	}

	// Si el semáforo debe seguir disponible para otros procesos solo hago
	// close.
	// Si se quiere destruir el semáforo se hace sem_unlink
	//


	if(sem_close(sem) == -1){
		perror("pSemCreate sem_close fails: ");
		return -1;
	}
	return 0;
}

 */

//pSemWait.c
/*
 *
 int main(int argc, char *argv[]){

	//Para utilizar el semaforo ya no se especifica el modo ni el valor
	sem_t *sem = sem_open("semExample",0);

	if(sem == SEM_FAILED){
		perror("pSemWait sem Open: ");
		exit(EXIT_FAILURE);
	}

	printf("pSemWait %d sem_wait() ...\n", getpid());

	if(sem_wait(sem) == - 1){
		perror("pSemWait sem_wait error: ");
		exit(EXIT_FAILURE);
	}

	printf("pSemWait %d succeeded\n", getpid());

	if(sem_close(sem) == -1){
		perror("pSemWait sem_close fails: ");
		exit(EXIT_FAILURE);
	}

	if(sem_unlink("semExample") == -1){
		perror("pSemWait sem_unlink fails: ");
		exit(EXIT_FAILURE);
	}

	return 0;
}
 *
 */

//pSemPost.c
/*
 *
 int main(int argc, char *argv[]){

	//Para utilizar el semaforo ya no se especifica el modo ni el valor
	sem_t *sem = sem_open("semExample",0);

	if(sem == SEM_FAILED){
		perror("pSemWait sem Open: ");
		exit(EXIT_FAILURE);
	}

	printf("pSemWait %d sem_wait() ...\n", getpid());

	if(sem_post(sem) == - 1){
		perror("pSemWait sem_post error: ");
		exit(EXIT_FAILURE);
	}

	printf("pSemWait %d succeeded\n", getpid());

	if(sem_close(sem) == -1){
		perror("pSemWait sem_close fails: ");
		exit(EXIT_FAILURE);
	}

	return 0;
}

 */
