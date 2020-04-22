/*
 ============================================================================
 Name        : parcial4.c
 Author      : Miguel Hincapié
 Version     :
 Copyright   : ID 000148441
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
 #include <stdlib.h>
 #include <sys/mman.h>
 #include <sys/stat.h>        /* For mode constants */
 #include <fcntl.h>           /* For O_* constants */
 #include <string.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/wait.h>
 #include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>

 #define SH_SIZE 256

sem_t* semaphore1, *semaphore2, *connectCounter_sem, *disconnectCounter_sem, *close_sem;
pthread_t id_hilos[4];

int shared_fd1,shared_fd2;
int n_connected = 0;
bool shouldRun = true;
char *ptr1, *ptr2;

//Semaphore functions
void init_control_mechanism() {
     semaphore1 = sem_open("sem0", O_CREAT, 0600, 0);
     semaphore2 = sem_open("sem1", O_CREAT, 0600, 0);
     connectCounter_sem = sem_open("connect_sem", O_CREAT, 0600,0);
     disconnectCounter_sem = sem_open("disconnect_sem", O_CREAT, 0600,0);
     close_sem = sem_open("close_sem", O_CREAT, 0600,0);

     if (semaphore1 == SEM_FAILED || semaphore2 == SEM_FAILED
    || connectCounter_sem == SEM_FAILED || disconnectCounter_sem == SEM_FAILED
	|| close_sem == SEM_FAILED) {
         perror("Opening the semaphore  failed: ");
         exit(EXIT_FAILURE);
     }

     puts("Semaforos creados");
 }

 void shutdown_control_mechanism() {
     if (sem_close(semaphore1) < 0 || sem_close(semaphore2) < 0 || sem_close(connectCounter_sem) < 0 || sem_close(disconnectCounter_sem) < 0 || sem_close(close_sem) < 0) {
         perror("Closing the semaphore1 failed: ");
         exit(EXIT_FAILURE);
     }

     if(sem_unlink("sem0") < 0 || sem_unlink("sem1") < 0 || sem_unlink("connect_sem") < 0 || sem_unlink("disconnect_sem") < 0 || sem_unlink("close_sem") < 0){
    	 perror("Error eliminando semaforos");

     }
 }

 //Memory functions
 void init_shared_resource() {
     shared_fd1 = shm_open("shm0", O_CREAT | O_RDWR, 0600);
     shared_fd2 = shm_open("shm1", O_CREAT | O_RDWR, 0600);
     if (shared_fd2 < 0) {
         perror("Failed to create shared memory: ");
         exit(EXIT_FAILURE);
     }
     fprintf(stdout, "Shared memory are created with fd: %d and %d\n", shared_fd1, shared_fd2);
 }

 void shutdown_shared_resource() {
      if (shm_unlink("/shm0") < 0 || shm_unlink("/shm1") < 0) {
          perror("Unlinking shared memory failed: ");
          exit(EXIT_FAILURE);
      }
  }

void *handleConnection(void *args){
	puts("Handling Connections...");

	while(shouldRun){
		sem_wait(connectCounter_sem);
		puts("\nUsuario Conectado");
		strcpy(ptr2, "\nUn usuario se ha conectado\n\0");

		n_connected++;

		for(int i = 0; i < n_connected; i++){
			sem_post(semaphore2); //Tell all clients to read
		}
	}

	puts("Handle Connections Closed");
	return NULL;
}

void *handleDisconnection(void *args){
	puts("Handling Disconnections");
	while(shouldRun){
		sem_wait(disconnectCounter_sem);
		puts("\nUsuario desconectado");
		strcpy(ptr2, "\nUn usuario se ha desconectado\n\0");

		n_connected--;
		for(int i = 0; i < n_connected; i++){
					sem_post(semaphore2); //Tell all clients to read
		}
	}

	puts("Handle Disconnections Closed");
	return NULL;
}

void *handleExit(void *args){
	char b[2];
	puts("Handling Exit... Ctrl+D to close Group");
	while(fgets(b ,2 ,stdin) != NULL) puts(">");

	puts("Closing Group");
	strcpy(ptr2, "\nGrupo Cerrado Byeee :)\n\0");


	shouldRun = false;

	//Desbloquear demás Hilos para que terminen
	sem_post(connectCounter_sem);
	sem_post(disconnectCounter_sem);
	sem_post(semaphore1);


	for(int i = 0; i < n_connected; i++){
		sem_post(semaphore2); //Tell all clients to read
		sem_post(close_sem);
	}

	//Esperar Hilos
	for(int i = 0; i < 4; i++){
		pthread_cancel(id_hilos[i]);
	}

	return NULL;
}

 void *memoryWritten(void* args){
	 puts("Handling memory write");

	while(shouldRun){
		sem_wait(semaphore1); //When Memory is Written
		strcpy(ptr2, ptr1);

		for(int i = 0; i < n_connected; i++){
			sem_post(semaphore2); //Tell all clients to read
		}
	}

	puts("Handle Memory Written Closed");
	return NULL;
}

 int main(int argc, char * argv[]){
	 //Iniciar Memoria Compartida
	 init_shared_resource();

	 //Iniciar Semáforos
	 init_control_mechanism();



     if (ftruncate(shared_fd1, SH_SIZE * sizeof(char)) < 0 || ftruncate(shared_fd2, SH_SIZE * sizeof(char)) < 0) {
         perror("Truncation failed: ");
         exit(EXIT_FAILURE);
     }
     //fprintf(stdout, "The memory region is truncated.\n");

     //Mapear memoria
     void* map1 = mmap(NULL, SH_SIZE, PROT_READ, MAP_SHARED, shared_fd1, 0);
     void* map2 = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shared_fd2, 0);
     ptr1 = (char *)map1;
     ptr2 = (char *)map2;

     if (map1 == MAP_FAILED || map2 == MAP_FAILED) {
         perror("Mapping failed: ");
         exit(EXIT_FAILURE);
     }

     //Crear thread de enviar mensajes
     pthread_create(&id_hilos[0], NULL, &memoryWritten,NULL);
     pthread_create(&id_hilos[1], NULL, &handleConnection, NULL);
     pthread_create(&id_hilos[2], NULL, &handleDisconnection, NULL);
     pthread_create(&id_hilos[3], NULL, &handleExit, NULL);

     //Esperar Hilos
     for(int i = 0; i < 4; i++){
    	 pthread_join(id_hilos[i], NULL);
     }

     shutdown_shared_resource();
     shutdown_control_mechanism();
     exit(EXIT_SUCCESS);
 }

