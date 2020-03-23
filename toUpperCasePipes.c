// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE 30

int main(int argc, char *argv[]) {

	int parent_pipe[2], child_pipe[2];

	char buffer1[BUFFER_SIZE], buffer2[BUFFER_SIZE];

	ssize_t read1,read2;

	//create pipes
	//1 for write
	//0 for read

	if (pipe(parent_pipe) == -1 || pipe(child_pipe) == -1){ /* Create the pipe */
	        perror("pipe creation error");
	        return -1;
	}

	//Create child process
	switch(fork())
	{
	case -1:
		perror("child machine broke");
		break;
	case 0:
		//Child
		//Close parent write and child read
		if(close(parent_pipe[1]) == -1 || close(child_pipe[0]) == -1){
			perror("Error in child pipes");
		}

		//Listen to parent
		for(;;){
			read2 = read(parent_pipe[0], buffer2, BUFFER_SIZE);
			strcat(buffer2,"\0");
			if (read2 == -1)
			{
				perror("child read error");
				return -1;
			}

			//Se acabó :C
			if(read2 == 0){
				if(close(parent_pipe[0]) == -1 || close(child_pipe[1]) == -1){
					perror("Error in child pipes");
				}
				break;
			}

			//Modifico el mensaje, lo pongo en mayusculas
			for(int i = 0; i < strlen(buffer2); i++){
				buffer2[i] = toupper(buffer2[i]);
			}

			//Envío mensaje modificado
			if (write(child_pipe[1], buffer2, strlen(buffer2)) != strlen(buffer2)) {
				perror("parent - partial/failed write");
			}

			for(int i = 0; i < BUFFER_SIZE; i++){
				buffer2[i] = '\0';
			}
		}

		break;
	default:
		//Parent
		//Cierro write del hijo y read del padre
		if(close(parent_pipe[0]) == -1){
			perror("Error in child pipes");
		}

		if(close(child_pipe[1]) == -1){
			perror("Error in child pipes");
		}

		//Enviar mensaje al hijo
		int size;
		char message[BUFFER_SIZE];


		puts("Escribir lo que se quiere convertir a mayusculas. Escriba 1 para salir");
		//Scan and send message
		while(1){

			//Get message
			write(STDOUT_FILENO, "\n>", 2);
			fgets(message, BUFFER_SIZE, stdin);

			if(atoi(message) == 1){
				if(close(parent_pipe[1]) == -1 || close(child_pipe[0]) == -1){
					perror("Error in child pipes");
				}
				puts("Saliendo");
				break;
			}

			//Send message
			size = strlen(message);
			if (write(parent_pipe[1], message, size) != size) {
				perror("parent - partial/failed write");
			}

			//Reads message
			read1 = read(child_pipe[0], buffer1, BUFFER_SIZE);

			strcat(buffer1,"\0");

			if (read1 == -1)
			{
				perror("parent read error");
				return -1;
			}


			if (write(STDOUT_FILENO, buffer1, read1) != read1) {
						perror("parent - partial/failed write");
			}

			//reset message buffer
		}

		break;
	}

	//Send message
	return 0;
}
