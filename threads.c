 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>

void* contarLineas(void* arg){
	 FILE *file = fopen(arg,"r");

	 char buffer[20];
	 intptr_t cont = 1;
	 while(fgets(buffer,20,file) != NULL){
		 cont++;
	 }

	 return (void*)cont;
}

 int main(int argc, char *argv[])
{
	pthread_t id_hilo[argc];
	int lineas[argc];

	 for(int i = 1; i < argc; i++){
		pthread_create(id_hilo + i, NULL, &contarLineas, argv[i]);
	 }

	for(int i = 1; i < argc; i++){
		pthread_join(id_hilo[i], (void*)&lineas[i-1]);
	}

	int total = 0;

	for(int i = 0; i < argc-1; i++){
		total += lineas[i];
		printf("\nArchivo %d: %d Lineas",i,lineas[i]);
	}

	printf("\nTotal Lineas: %d",total);

	return 0;
}
