 /*
 ============================================================================
 Name        : yes.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>

typedef struct{
	int lineas;
}linea;

void* contarLineas(void* arg){
	 FILE *file = fopen(arg,"r");

	 char buffer[20];
	 intptr_t cont = 0;
	 while(fgets(buffer,20,file) != NULL){
		 cont++;
	 }

	 return (void*)cont;
}

 int main(int argc, char *argv[])
{
	pthread_t id_hilo[argc];
	linea lineas[argc];

	 for(int i = 1; i < argc; i++){
		pthread_create(id_hilo + i, NULL, &contarLineas, argv[i]);
	 }

	for(int i = 1; i < argc; i++){
		pthread_join(id_hilo[i], (void*)&lineas[i-1].lineas);
	}

	int total = 0;

	for(int i = 0; i < argc-1; i++){
		total += lineas[i];
		printf("\nArchivo %d: %d Lineas",i,lineas[i].lineas);
	}

	printf("\nTotal Lineas: %d",total);

	return 0;
}
