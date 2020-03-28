/*
 * ---------------------------------------------------
 * PROGRAMA 1
 * ---------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h> //Para semaforos
#include <fcntl.h>   //For 0__* constants
#include <sys/stat.h> //Constantes de modo
#include <unistd.h>

#define BUFFER_SIZE 64

typedef struct {
	char nombre[64];
	int edad;
}Registro;

int main(int argc, char *argv[]){

	FILE *in,*out1,*out2;
	//P1 debe crear los semáforos
	mode_t perms = 0666;
	int flags = O_CREAT;

	//Crear el semáforo
	sem_t *sem1 = sem_open("sem1", flags, perms, 0);
	sem_t *sem2 = sem_open("sem2", flags, perms, 0);

	if(sem1 == SEM_FAILED || sem2 == SEM_FAILED){
		perror("pSemCreate sem_open fails: ");
		return -1;
	}

	// Si el semáforo debe seguir disponible para otros procesos solo hago
	// close.
	// Si se quiere destruir el semáforo se hace sem_unlink


	Registro regs[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	in = fopen(argv[1],"r");

	int cont = 0;
	for(int i = 0; fgets(buffer, BUFFER_SIZE -1, in) != NULL; i++){
		sscanf(buffer, "%63s %d", regs[i].nombre, &regs[i].edad);
		printf("%s %d\n", regs[i].nombre, regs[i].edad);
		cont++;
	}

	fclose(in);
	//sort
	Registro temp;
	for(int i = 0; i < cont; i++){
		for(int j = 0; j < cont ; j++){
			if(strcmp(regs[i].nombre, regs[j].nombre) < 0){
				temp = regs[i];
				regs[i] = regs[j];
				regs[j] = temp;
			}
		}
	}

	//Print
	out1 = fopen(argv[2],"w");

	for(int i = 0; i < cont; i++){
		fprintf(out1, "%s %d\n", regs[i].nombre, regs[i].edad);
	}

	fclose(out1);

	puts("Archivo de entrada leído");
	//Post en semáforo para que el proceso 2 pueda leer datos
	puts("Unlocking semaphore 1");
	if(sem_post(sem1) == - 1){
		perror("pSemWait sem_post error: ");
		exit(EXIT_FAILURE);
	}
	puts("Semaphore 1 unlocked");

	printf("P1. SemWait %d sem_wait() ...\n", getpid());
	if(sem_wait(sem2) == - 1){
		perror("pSemWait sem_wait error: ");
		exit(EXIT_FAILURE);
	}

	puts("P1. Continuando");

	out2 = fopen(argv[3], "r");
	for(int i = 0; fgets(buffer, BUFFER_SIZE -1, out2) != NULL; i++){
		printf("%s",buffer);
	}
	return 0;
}

/*
 * ---------------------------------------------------
 * PROGRAMA 2
 * ---------------------------------------------------
 *
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h> //Para semaforos
#include <fcntl.h>   //For 0__* constants
#include <sys/stat.h> //Constantes de modo
#include <unistd.h>

#define BUFFER_SIZE 64

typedef struct {
	char nombre[64];
	int edad;
}Registro;

int main(int argc, char *argv[]){

	FILE *out1,*out2;
	Registro regs[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];

	//Abrir semáforos
	sem_t *sem1 = sem_open("sem1", 0);
	sem_t *sem2 = sem_open("sem2", 0);

	if(sem1 == SEM_FAILED || sem2 == SEM_FAILED){
		perror("P2. sem_open fails: ");
		return -1;
	}

	puts("P2. Waiting semaforo 1");
	if(sem_wait(sem1) == -1){
		perror("P2. psem_wait error: ");
		return -1;
	}

	if(sem_unlink("sem1") == -1){
		perror("Error eliminando semaforo 1: ");
		return -1;
	}

	puts("P2. Semaforo 1 eliminado");
	puts("P2. Continuando...");

	printf("P2. Abriendo %s\n: ", argv[1]);
	out1 = fopen(argv[1], "r");

	if(out1 == NULL){
		perror("P2. Error abriendo archivo");
	}

	puts("P2. Leyendo out1");
	int cont = 0;
	for(int i = 0; fgets(buffer, BUFFER_SIZE -1, out1) != NULL; i++){
		sscanf(buffer, "%63s %d", regs[i].nombre, &regs[i].edad);
		printf("%s %d\n", regs[i].nombre, regs[i].edad);
		cont++;
	}

	fclose(out1);
	//sort
	Registro temp;
	for(int i = 0; i < cont; i++){
		for(int j = 0; j < cont; j++){
			if(regs[i].edad > regs[j].edad){
				temp = regs[i];
				regs[i] = regs[j];
				regs[j] = temp;
			}
		}
	}

	printf("%s leido, creando %s...\n", argv[1],argv[2]);
	//Print
	out2 = fopen(argv[2],"w");

	for(int i = 0; i < cont; i++){
		fprintf(out2, "%s %d\n", regs[i].nombre, regs[i].edad);
	}

	fclose(out2);

	printf("%s creado\n", argv[2]);

	//Post en semáforo para que el proceso 1 pueda leer datos
	int status;
	sem_getvalue(sem2, &status);
	puts("Unlocking semaphore 2");

	printf("Estado del semáforo 2: %d", status );

	if(sem_post(sem2) == - 1){
		perror("pSemWait sem_post error: ");
		exit(EXIT_FAILURE);
	}
	puts("Semaphore 2 unlocked");

	puts("P2. Cerrando semáforo 2");
	if(sem_close(sem2) == -1){
				perror("pSemCreate sem_close fails: ");
				return -1;
	}

	puts("P2. Eliminando semáforo 2...");
	if(sem_unlink("sem2") == -1){
		perror("Error eliminando semaforo 2: ");
		return -1;
	}
	return 0;
}
*/
