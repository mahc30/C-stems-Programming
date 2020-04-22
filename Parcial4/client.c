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

sem_t* semaphore1, *semaphore2, *file_sem, *connectCounter_sem, *disconnectCounter_sem, *close_sem;
int shared_fd1,shared_fd2;
bool shouldRun = true;
bool readingFile = false;
pthread_t id_hilo1, id_hilo2;

typedef struct {
	 void* shm_pointer1;
	 void* shm_pointer2;
	 char user_name[32];
}User;


//Semaphore functions
void init_control_mechanism() {
     semaphore1 = sem_open("sem0", 0);
     semaphore2 = sem_open("sem1", 0);
     connectCounter_sem = sem_open("connect_sem",0);
     disconnectCounter_sem = sem_open("disconnect_sem",0);
     close_sem = sem_open("close_sem",0);

     file_sem = sem_open("file_sem", O_CREAT, 0600,0);


     if (semaphore1 == SEM_FAILED || semaphore2 == SEM_FAILED || connectCounter_sem == SEM_FAILED || disconnectCounter_sem == SEM_FAILED || close_sem == SEM_FAILED) {
         perror("Opening the semaphore1 failed: ");
         exit(EXIT_FAILURE);
     }
 }

 void shutdown_control_mechanism() {
     if (sem_close(semaphore1) < 0 || sem_close(semaphore2) < 0 || sem_close(file_sem) < 0 || sem_close(connectCounter_sem) < 0 || sem_close(disconnectCounter_sem) < 0 || sem_close(close_sem) < 0) {
         perror("Closing the semaphore1 failed: ");
         exit(EXIT_FAILURE);
     }

     if(sem_unlink("file_sem") < 0){
    	 //perror("Error cerrando file_sem");
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
     //fprintf(stdout, "Shared memory are created with fd: %d and %d\n", shared_fd1, shared_fd2);
 }

 void shutdown_shared_resource(void* ptr1, void* ptr2) {
	 if (munmap(ptr1, SH_SIZE) < 0 || munmap(ptr2, SH_SIZE) < 0) {
	          perror("Unmapping failed: ");
	          exit(EXIT_FAILURE);
	 }
  }

 //================================================================
 //============================ My Functions ======================
 //================================================================
void salir(void* map1, void* map2){
	puts("Desconectando...");

	//Cancelo los Threads
	pthread_cancel(id_hilo1);
	pthread_cancel(id_hilo2);

	//Solo para estar un poquito más seguro
	shouldRun = false;

	//Avisar al server
	sem_post(disconnectCounter_sem);

    shutdown_shared_resource(map1, map2);
    shutdown_control_mechanism();

    exit(EXIT_SUCCESS);
}

void *sendFile(void *args){
	readingFile = true;
	char fileName[SH_SIZE];

	User *arg = (User *)args;
	char *ptr = (char *)(arg -> shm_pointer1);

	sscanf(arg -> user_name, "%*s %255s", fileName);
	strcat(fileName,"\0");

	fprintf(stdout, "\nEnviando Archivo '%s ...'\n", fileName);

	FILE *file = fopen(fileName, "r");
	if(file == NULL){
			printf("Cannot open %s\n", fileName);
			readingFile = false;
			return NULL;
	}


	while(fgets(ptr, SH_SIZE, file) != NULL){
		sem_post(semaphore1);
		sleep(1);
		//sem_wait(file_sem);
	}

	fclose(file);


	puts("Archivo cerrad");
	readingFile = false;
	return NULL;
}

 void *sendMessage(void* args){
	char buffer[SH_SIZE - 33];
	char message[SH_SIZE];

	//Config Thread
	User *arg = (User *)args;
	char *ptr = arg->shm_pointer1;
	char *user_name = arg->user_name;
	strcat(user_name, ": ");

	puts("Conectado al grupo :D\nCtrl+D para salir\nPara enviar archivo: /file <path>\n>");
	//Enviar Mensaje de Conectado
	strcpy(message, user_name);
	strcat(message, "ha entrado al grupo");
	sem_post(semaphore1);

	//Entro en ciclo para enviar mensajes
	while(fgets(buffer,SH_SIZE - 33 ,stdin) != NULL){

		//Detectar comando para enviar archivos
		if(strstr(buffer, "/file") != NULL){
			pthread_t id;

			 //Inicio Estructura
			User args = {.shm_pointer1 = arg -> shm_pointer1};
			strcpy(args.user_name, buffer);

			pthread_create(&id, NULL, &sendFile, &args);

			strcpy(buffer, ""); //Limpiar buffer
			pthread_join(id, NULL);
		}

		printf("\n>");

		//Formatear mensaje (Agregar nombre de usuario al comienzo y concatenar buffer/mensaje)
		strcpy(message, user_name);
		strcat(message, buffer);

		//Copiar a memoria compartida
		strcpy(ptr, message);

		//Avisar al servidor
		sem_post(semaphore1);
	}

	salir(arg ->shm_pointer1, arg -> shm_pointer2);
	return NULL;
}

void *readMessage(void* arg){
	User *args = (User *)arg;
	char *ptr = (char *)(args -> shm_pointer2);

	while(1){

		sem_wait(semaphore2);
		if(!shouldRun) break;
		//if(readingFile) sem_post(file_sem);
		printf("%s", ptr);
		sleep(1);
	}

	return NULL;
}

 int main(int argc, char * argv[]){

	 //Conectarse
	 char buffer[3];
	 while(atoi(buffer)!= 1){
		 printf("Escriba 1 para conectarse\n");
		 fgets(buffer,3,stdin);
	 }

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
     void* map1 = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shared_fd1, 0);
     void* map2 = mmap(NULL, SH_SIZE, PROT_READ, MAP_SHARED, shared_fd2, 0);

     if (map1 == MAP_FAILED || map2 == MAP_FAILED) {
         perror("Mapping failed: ");
         exit(EXIT_FAILURE);
     }

     //Inicio Estructura
     User args = {.shm_pointer1 = map1, .shm_pointer2 = map2};
     strcpy(args.user_name, argv[1]);

     //Crear threads de enviar mensajes
     pthread_create(&id_hilo1, NULL, &sendMessage, (void *)(&args));
     pthread_create(&id_hilo2, NULL, &readMessage, (void *)(&args));

     //Indicar que se conectó
     sem_post(connectCounter_sem);

     while(1){
    	 sem_wait(close_sem);
    	 puts("El grupo se ha cerrado. Desconectando...");
    	 salir(map1, map2);
     }

     //Esperar Hilos
     pthread_join(id_hilo1, NULL);
     pthread_join(id_hilo2, NULL);

     //Indicar a server que se desconectó
     sem_post(disconnectCounter_sem);


     exit(EXIT_SUCCESS);
 }


