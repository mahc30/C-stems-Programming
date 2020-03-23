/* Filename: msgq_send.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#define S_IRUSR 0400 //User Read
#define S_IWUSR 0200 //User Write
#define MESSAGE_SIZE 4
struct msgbuf {
	long mtype;
	char mtext[MESSAGE_SIZE];
};

int main(void) {

	key_t key1, key2;
	int id1, id2;
	struct msgbuf message1, message2;
	struct msgbuf received_message1, received_message2;
	system("touch msgq1.txt");
	system("touch msgq2.txt");

	//Creación de la clave/key
	if((key1 = ftok("msgq1.txt",'B')) == -1 || (key2 = ftok("msgq2.txt",'B')) == -1){
		perror("ftok");
		exit(1);
	}

	//Creación de la cola
	//id = msgget(key, IPC_CREAT | S_IRUSR | S_IMUSR);
	 if ((id1 = msgget(key1, IPC_CREAT | S_IRUSR | S_IWUSR)) == -1 || (id2 = msgget(key2, IPC_CREAT | S_IRUSR | S_IWUSR)) == -1) {
		perror("msgget");
		exit(1);
	}



	//int msgsnd(int msgid, const void *msgp, size_t msgsz, int msgflg)
	/*
	 * msgid: identificador de la cola
	 * msgp: puntero al mensaje
	 * msgsz: tamaño de mtext
	 * msgflag: 0 por defecto
	 *
	 * Formato del mensaje
	 *
	 * struct msgbuf{
	 * long mtype;
	 * char mtext[tamaño];
	 * }
	 */

	/*
	 * ELIMINAR UNA COLA
	 * if(msgctl(id, IPC_RMID, NULL) == -1) perror("msgctl");
	 */

	 switch(fork()){
	 case -1:
		 perror("Child bad");
		 break;

	 case 0:

		 printf("%s", "Ready to copy msgs");
		 while(1){

			 msgrcv(id1, &received_message1, sizeof(received_message1.mtext),0,0);
			 printf("\nUser2: %s", received_message1.mtext);
		 }

		 break;

	 default:
		 if(msgsnd(id1, "usr2", MESSAGE_SIZE, 0) == -1) perror("msgsend"); // +1 para contar el '\0'


		 //Creación del mensaje
		 while(fgets(message1.mtext, sizeof message1.mtext, stdin) != NULL){

			 int len = strlen(message1.mtext);
			 // Remove newline at end, if it exists
			 if(message1.mtext[len-1] == '\n') message1.mtext[len-1] = '\0';
			 //Enviar mensaje
			 if(msgsnd(id2, &message1, len + 1, 0) == -1){ // +1 para contar el '\0'
				 perror("msgsend");
			 }
		 }
		 break;
	 }



	wait(NULL);
	if(msgctl(id1, IPC_RMID, NULL) == -1) perror("msgctl");
	return 0;

}
	/*
	 *
	 * Client 1
	 *
	 switch(fork()){
	 case -1:
		 perror("Child bad");
		 break;

	 case 0:

		 printf("%s", "Ready to copy msgs");
		 while(1){

			 msgrcv(id2, &received_message2, sizeof(received_message2.mtext),0,0);
			 printf("\nreceivd: %s", received_message2.mtext);
		 }

		 break;

	 default:

		 if(msgsnd(id2, "hol\0", MESSAGE_SIZE, 0) == -1) perror("msgsend"); // +1 para contar el '\0'


		 //Creación del mensaje
		 while(fgets(message2.mtext, sizeof message2.mtext, stdin) != NULL){

			 int len = strlen(message2.mtext);
			 // Remove newline at end, if it exists
			 if(message2.mtext[len-1] == '\n') message2.mtext[len-1] = '\0';
			 //Enviar mensaje
			 if(msgsnd(id1, &message2, len + 1, 0) == -1){ // +1 para contar el '\0'
				 perror("msgsend");
			 }
		 }
		 break;
	 }


	 Client 2
	 switch(fork()){
	 case -1:
		 perror("Child bad");
		 break;

	 case 0:

		 printf("%s", "Ready to copy msgs");
		 while(1){

			 msgrcv(id1, &received_message1, sizeof(received_message1.mtext),0,0);
			 printf("\nUser2: %s", received_message1.mtext);
		 }

		 break;

	 default:
		 if(msgsnd(id1, "sen\0", MESSAGE_SIZE, 0) == -1) perror("msgsend"); // +1 para contar el '\0'


		 //Creación del mensaje
		 while(fgets(message1.mtext, sizeof message1.mtext, stdin) != NULL){

			 int len = strlen(message1.mtext);
			 // Remove newline at end, if it exists
			 if(message1.mtext[len-1] == '\n') message1.mtext[len-1] = '\0';
			 //Enviar mensaje
			 if(msgsnd(id2, &message1, len + 1, 0) == -1){ // +1 para contar el '\0'
				 perror("msgsend");
			 }
		 }
		 break;
	 }
	 */
