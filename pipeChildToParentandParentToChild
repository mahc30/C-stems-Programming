#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    int pfd[2],pfd2[2]; /* Pipe file descriptors */
    //pf2 -> hijo escribe al padre
    //pfd -> padre escribe al hijo

    char buf[BUF_SIZE],buf2[BUF_SIZE];
    char *cadena ="";
    ssize_t numRead,numRead2;

    if (argc != 3 || strcmp(argv[1], "--help") == 0){
        printf("usage error: %s string\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    if (pipe(pfd) == -1){ /* Create the pipe */
        perror("pipe");
        exit(EXIT_FAILURE);
    }

      if (pipe(pfd2) == -1){ /* Create the pipe */
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    switch (fork())
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    case 0:
        //Cierra lado de lectura de lo que el hijo escribe al padre, porque pfd2 es para escribir al padre
    	if (close(pfd2[0]) == -1)
        {
            perror("close - child");
            exit(EXIT_FAILURE);
        }

    	//Cierra lado de escritura de lo que el padre le escribe al hijo porque esta tubería, porque el hijo va a escribir
        if (close(pfd[1]) == -1)
        {
            perror("close - child");
            exit(EXIT_FAILURE);
        }


        //Envía mensaje al padre (argv[2])
         if (write(pfd2[1], argv[2], strlen(argv[2])) != strlen(argv[2]))
        {
            perror("parent - partial/failed write");
            exit(EXIT_FAILURE);
        }

         //Se queda escuchando lo que le escribe el padre
        for(;;) {
            numRead2 = read(pfd[0], buf2, BUF_SIZE);
            strcat(buf2,"\0");
            if (numRead2 == -1)
            {
                perror("child read error");
                exit(EXIT_FAILURE);
            }

            //Si se cierra la tubería deja de escuchar
            if (numRead2 == 0){
               break;
            }

            printf("\n%s\n","MENSAJE DEL PADRE:");

            //Print pero más feo el mensaje del padre
            if (write(STDOUT_FILENO, buf2, numRead2) != numRead2)
            {
                perror("child - partial/failed write");
                exit(EXIT_FAILURE);
            }
        }

        //Si el padre dejó de mandar mensajes el hijo puede morirse
        //Cierra las tubería de escritura al padre y la de lectura del padre
        if (close(pfd2[1]) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }

        if (close(pfd[0]) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }


        exit(EXIT_SUCCESS);




        //Parent
    default:

    	//Padre cierra lado de lectura porque pfd es para escribir al hijo
        if (close(pfd[0]) == -1)
        {
            perror("close - parent");
            exit(EXIT_FAILURE);
        }

        //Padre cierra lado de escritura del hijo, porque pfd va a escribir al hijo
        if (close(pfd2[1]) == -1)
        {
            perror("close - parent");
            exit(EXIT_FAILURE);
        }

        int tamano = strlen(argv[1]);

        //Escribe mensaje al hijo
        if (write(pfd[1], argv[1],tamano) != tamano)
        {
            perror("parent - partial/failed write");
            exit(EXIT_FAILURE);
        }

        //Se queda escuchando la tubería por la que escucha al hijo pfd2
        for(;;){
          numRead = read(pfd2[0],buf,BUF_SIZE);

          //Error al leer
          if (numRead == -1)
            {
                perror("Paretn read error");
                exit(EXIT_FAILURE);
            }

          	//Si se cierra la tubería del hijo es que terminó
            if (numRead == 0){
              break;
            }

            puts("");
            printf("%s\n","MENSAJE DEL HIJO:");

            //Print pero más feo de lo que envía el hijo
            if (write(STDOUT_FILENO, buf, numRead) != numRead)
            {
                perror("child - partial/failed write");
                exit(EXIT_FAILURE);
            }
        }


        //Si la tubería del hijo se cierra el padre se puede morir
        if (close(pfd[1]) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }

        //Cierra la lectura de lo que escribe el hijo
         if (close(pfd2[0]) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}
