//PROCESO 1
//Escribe en shared1 y lee shared2
//Espera a sem1 y postea a sem2

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

 #define SH_SIZE 16

sem_t* semaphore1, *semaphore2;
int shared_fd1,shared_fd2;

void *sendMessage(void* mem){

	char message[SH_SIZE];
	char *ptr = (char *)mem;

	puts("Proceso 2: Escriba su mensaje");

	while(1){
		printf(">");
		fgets(message,15,stdin);
		message[SH_SIZE - 1] = '\0';

		strcpy(ptr, message);
		sem_post(semaphore1);
	}

	return NULL;
}

//Semaphore functions
void init_control_mechanism() {
     semaphore1 = sem_open("sem0", O_CREAT, 0600, 1);
     semaphore2 = sem_open("sem1", O_CREAT, 0600, 0);
     if (semaphore1 == SEM_FAILED || semaphore2 == SEM_FAILED) {
         perror("Opening the semaphore1 failed: ");
         exit(EXIT_FAILURE);
     }
 }

 void shutdown_control_mechanism() {
     if (sem_close(semaphore1) < 0 || sem_close(semaphore2) < 0) {
         perror("Closing the semaphore1 failed: ");
         exit(EXIT_FAILURE);
     }

     if (sem_unlink("sem0") < 0 || sem_unlink("sem1") < 0) {
         perror("Unlinking failed: ");
         exit(EXIT_FAILURE);
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

 int main(int argc, char * argv[]){

	 //Iniciar Memoria Compartida
	 init_shared_resource();

	 //Iniciar Semáforos
	 init_control_mechanism();

	 pthread_t id_hilo;

     if (ftruncate(shared_fd1, SH_SIZE * sizeof(char)) < 0 || ftruncate(shared_fd2, SH_SIZE * sizeof(char)) < 0) {
         perror("Truncation failed: ");
         exit(EXIT_FAILURE);
     }

     fprintf(stdout, "The memory region is truncated.\n");

     //Mapear memoria
     void* map = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shared_fd2, 0);

     if (map == MAP_FAILED) {
         perror("Mapping failed: ");
         exit(EXIT_FAILURE);
     }

     //Crear thread de enviar mensajes aquí
     pthread_create(&id_hilo, NULL, &sendMessage, map);

     //Mapeo memoria a leer
     void* map2 = mmap(NULL, SH_SIZE, PROT_READ, MAP_SHARED, shared_fd1, 0);
     char *ptr = (char *)map2;

     while(1){
    	 sem_wait(semaphore2);
    	 printf("Proceso 1 Dice: %s", ptr);
     }

     //Cerrar hilo de escritura
     pthread_join(id_hilo, NULL);



     shutdown_shared_resource();
     shutdown_control_mechanism();
     exit(EXIT_SUCCESS);
 }

/*
 * Proceso 1

 void *sendMessage(void* mem){

	char message[SH_SIZE];
	char *ptr = (char *)mem;

	puts("Proceso 1: Escriba su mensaje");

	while(1){
		printf(">");
		fgets(message,15,stdin);
		message[SH_SIZE - 1] = '\0';

		strcpy(ptr, message);
		sem_post(semaphore2);
	}

	return NULL;
}

//Semaphore functions
void init_control_mechanism() {
     semaphore1 = sem_open("sem0", O_CREAT, 0600, 1);
     semaphore2 = sem_open("sem1", O_CREAT, 0600, 0);
     if (semaphore1 == SEM_FAILED || semaphore2 == SEM_FAILED) {
         perror("Opening the semaphore1 failed: ");
         exit(EXIT_FAILURE);
     }
 }

 void shutdown_control_mechanism() {
     if (sem_close(semaphore1) < 0 || sem_close(semaphore2) < 0) {
         perror("Closing the semaphore1 failed: ");
         exit(EXIT_FAILURE);
     }

     if (sem_unlink("sem0") < 0 || sem_unlink("sem1") < 0) {
         perror("Unlinking failed: ");
         exit(EXIT_FAILURE);
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

 int main(int argc, char * argv[]){

	 //Iniciar Memoria Compartida
	 init_shared_resource();

	 //Iniciar Semáforos
	 init_control_mechanism();

	 pthread_t id_hilo;

     if (ftruncate(shared_fd1, SH_SIZE * sizeof(char)) < 0 || ftruncate(shared_fd2, SH_SIZE * sizeof(char)) < 0) {
         perror("Truncation failed: ");
         exit(EXIT_FAILURE);
     }

     fprintf(stdout, "The memory region is truncated.\n");

     //Mapear memoria
     void* map = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shared_fd1, 0);

     if (map == MAP_FAILED) {
         perror("Mapping failed: ");
         exit(EXIT_FAILURE);
     }

     //Crear thread de enviar mensajes aquí
     pthread_create(&id_hilo, NULL, &sendMessage, map);

     //Mapeo memoria a leer
     void* map2 = mmap(NULL, SH_SIZE, PROT_READ, MAP_SHARED, shared_fd2, 0);
     char *ptr = (char *)map2;

     while(1){
    	 sem_wait(semaphore1);
    	 printf("Proceso 2 Dice: %s", ptr);
     }

     //Cerrar hilo de escritura
     pthread_join(id_hilo, NULL);



     shutdown_shared_resource();
     shutdown_control_mechanism();
     exit(EXIT_SUCCESS);
 }


=====================================================================
						PROCESO 2
====================================================================

 void *sendMessage(void* mem){

	char message[SH_SIZE];
	char *ptr = (char *)mem;

	puts("Proceso 2: Escriba su mensaje");

	while(1){
		printf(">");
		fgets(message,15,stdin);
		message[SH_SIZE - 1] = '\0';

		strcpy(ptr, message);
		sem_post(semaphore1);
	}

	return NULL;
}

//Semaphore functions
void init_control_mechanism() {
     semaphore1 = sem_open("sem0", O_CREAT, 0600, 1);
     semaphore2 = sem_open("sem1", O_CREAT, 0600, 0);
     if (semaphore1 == SEM_FAILED || semaphore2 == SEM_FAILED) {
         perror("Opening the semaphore1 failed: ");
         exit(EXIT_FAILURE);
     }
 }

 void shutdown_control_mechanism() {
     if (sem_close(semaphore1) < 0 || sem_close(semaphore2) < 0) {
         perror("Closing the semaphore1 failed: ");
         exit(EXIT_FAILURE);
     }

     if (sem_unlink("sem0") < 0 || sem_unlink("sem1") < 0) {
         perror("Unlinking failed: ");
         exit(EXIT_FAILURE);
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

 int main(int argc, char * argv[]){

	 //Iniciar Memoria Compartida
	 init_shared_resource();

	 //Iniciar Semáforos
	 init_control_mechanism();

	 pthread_t id_hilo;

     if (ftruncate(shared_fd1, SH_SIZE * sizeof(char)) < 0 || ftruncate(shared_fd2, SH_SIZE * sizeof(char)) < 0) {
         perror("Truncation failed: ");
         exit(EXIT_FAILURE);
     }

     fprintf(stdout, "The memory region is truncated.\n");

     //Mapear memoria
     void* map = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shared_fd2, 0);

     if (map == MAP_FAILED) {
         perror("Mapping failed: ");
         exit(EXIT_FAILURE);
     }

     //Crear thread de enviar mensajes aquí
     pthread_create(&id_hilo, NULL, &sendMessage, map);

     //Mapeo memoria a leer
     void* map2 = mmap(NULL, SH_SIZE, PROT_READ, MAP_SHARED, shared_fd1, 0);
     char *ptr = (char *)map2;

     while(1){
    	 sem_wait(semaphore2);
    	 printf("Proceso 1 Dice: %s", ptr);
     }

     //Cerrar hilo de escritura
     pthread_join(id_hilo, NULL);



     shutdown_shared_resource();
     shutdown_control_mechanism();
     exit(EXIT_SUCCESS);
 }
 */
