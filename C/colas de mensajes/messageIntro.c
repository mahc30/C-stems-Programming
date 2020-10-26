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
#define MESSAGE_SIZE 5
struct msgbuf {
	long mtype;
	char mtext[MESSAGE_SIZE];
};

int main(void) {

	key_t key;
	int id;
	struct msgbuf message;


	//Creación de la clave/key
	if((key = ftok("msgq.txt",'B')) == -1){
		perror("ftok");
		exit(1);
	}

	//Creación de la cola
	//id = msgget(key, IPC_CREAT | S_IRUSR | S_IMUSR);
	 if ((id = msgget(key, IPC_CREAT | S_IRUSR | S_IWUSR)) == -1) {
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

	 struct msgbuf received_message;
	 switch(fork()){
	 case -1:
		 perror("Child bad");
		 break;

	 case 0:

		 printf("%s", "Ready to copy msgs");
		 while(1){

			 msgrcv(id, &received_message, sizeof(received_message.mtext),0,0);
			 printf("\nreceivd: %s", received_message.mtext);
		 }

		 break;

	 default:

		 //Creación del mensaje


		 while(fgets(message.mtext, sizeof message.mtext, stdin) != NULL){

			 int len = strlen(message.mtext);
			 // Remove newline at end, if it exists
			 if(message.mtext[len-1] == '\n') message.mtext[len-1] = '\0';
			 //Enviar mensaje
			 if(msgsnd(id, &message, len + 1, 0) == -1){ // +1 para contar el '\0'
				 perror("msgsend");
			 }
		 }
		 break;
	 }

	 wait(NULL);
	if(msgctl(id, IPC_RMID, NULL) == -1) perror("msgctl");
	return 0;
}
