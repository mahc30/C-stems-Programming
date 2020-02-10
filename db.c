/*
 ============================================================================
 Name        : sistemasOperativos.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================

Realice un programa que permita crear un base de datos de estudiantes.
Cada registro de la base de datos estará dado por: número de cédula, nombre y semestre.
Cada registro corresponde a un estudiante.

Implemente los siguientes comandos:

mkdb nombre tamaño : crea una base de datos especificando el nombre y la cantidad de registros.

loaddb nombre : carga la base de datos en memoria desde el archivo especificado.
El comando debe indicar si la base de datos se cargó correctamente o no existe.
La base de datos debe cargarse en memoria dinámica antes de poder aplicar los siguientes comandos.

savedb nombre : este comando salva la base de datos en el archivo especificado.

readall : lee todos los registros de la base de datos.

readsize : lee la cantidad de registros de la base datos.

mkreg cedula nombre semestre : crea un nuevo registro en la base de datos.

readreg cédula : busca en la base de datos por número de cédula. En caso de encontrar la cédula imprime el registro completo.

exit : salir del programa. Antes de terminar debe preguntar si se desea salvar la base de datos en el archivo especificado con el comando loaddb.

Cada comando deberá implementarse como una función.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Estudiante{
		int cedula;
		char nombre[30];
		int semestre;
} estudiante;


void mkdb(char n_base[30], int c_reg);
estudiante *loaddb(char FILE_NAME[30]);
void savedb(FILE db, char path[]);
void readall(FILE db);
int readsize(FILE db);
void mkreg(int cedula, char nombre[], int semestre);
struct estudiante readreg(int cedula);
void salir(bool *exit);


int main(void) {


	bool exit = false;
	bool db_loaded = false;
	char instruccion[33];
	char comando[10];
	char arg1[31];
	char arg2[31];
	char arg3[3];

	struct estudiante * db;
	//Scan for Instructions
	while(!exit){
		strcpy(comando, "");
		printf("\n%c",'>');
		//mkdb
		fgets(instruccion, 32, stdin);
		sscanf(instruccion, "%32s %30s %30s %2s", comando, arg1, arg2, arg3);

		if(strcmp(comando, "mkdb") == 0){
			int c_reg;
			printf("running %s %s %s",comando, arg1, arg2);
			c_reg = atoi(arg2);
			mkdb(arg1, c_reg);
		}
		else if(strcmp(comando, "loaddb") == 0){
			printf("running %s %s", comando, arg1);
			db = loaddb(arg1);
		}
		else if(strcmp(comando, "savedb") == 0 && db_loaded){
			puts("running savedb");
		}else if(strcmp(comando, "readall") == 0 && db_loaded){
			puts("running readall");
		}else if(strcmp(comando, "readsize") == 0 && db_loaded){
			puts("running readsize");
		}else if(strcmp(comando, "mkreg") == 0 && db_loaded){
			puts("running mkreg");
		}
		else if(strcmp(comando, "exit") == 0){
			strcpy(comando, "");
			salir(&exit);
			if(exit){
				break;
			}
		}else{
			printf("%s","Comando no reconocido");
		}
	}

	return(0);
}

void mkdb(char n_base[30],int c_reg){
	char PATH[64];
	char *dir = "./files/";

	strcat(PATH,dir);
	strcat(PATH,n_base);
	char reg[] = "\nCedula:xxxxxxxxxx\nNombre:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\nSemestre:xx";

	FILE *db = fopen(PATH,"w");
	fprintf(db, "Número_de_Registros: %d", c_reg);
	for(int i = 0; i < c_reg; i++){
		fprintf(db, "%s",reg);
	}

	puts("\nDb Created");
	fclose(db);
}

estudiante *loaddb(char FILE_NAME[30]){
	char path[] = "./files/";
	char buffer[30];
	int size;
	estudiante *dynPtr;
	estudiante newEst;
	int cedula;
	char nombre[30];
	int semestre;
	strcat(path, FILE_NAME);

	//Abrir Archivo
	FILE *db = fopen(path,"r");

	//Que si se lea el archivo
	if(db == NULL){
			printf("\nCannot open %s", path);
			return NULL;
	}
	//Leo la primera linea para saber la cantidad de registros
	*buffer = fscanf(db, "%s %d", buffer, &size);
	printf("Se cargarán %d Registros", size);
	//Asigno un puntero a donde se crea el espacio para la base de datos
	dynPtr = (estudiante *)malloc(sizeof(struct Estudiante) * size);

	//Comprobar que si se haya creado la memoria;
	if(dynPtr == 0){
		puts("\nError cargando base de datos");
		return NULL;
	}else{
		puts("\nCargando Base de Datos...");
	}


	//Cargo cada registro
	for(int i = 0; fscanf(db, "%s %d", buffer, cedula) == 2; i++){
		fscanf(db, "%s %s", buffer, nombre);
		fscanf(db, "%s %d", buffer, semestre);

		newEst.cedula = cedula;
		strcpy(newEst.nombre, nombre);
		newEst.semestre = semestre;

		*(dynPtr + i) = newEst;
	}
	//TODO Comprobar que si se guarden los datos en memoria
	puts("\nBase de datos Cargada");
	return dynPtr;
}

void salir(bool *exit){
	int confirmation;

	puts("?Seguro que desea salir¿ SI: 1 NO: 0");
	scanf("%d", &confirmation);

	if(confirmation){
		puts("?Desea guardar la Base de Datos¿ SI: 1 NO: 0");
		//TODO Guardar base de datos
		scanf("%d", &confirmation);
		if(confirmation){
			puts("Base de datos guardada, bye :)");
			*exit = !(*exit);
		}else{
			puts("bye :)");
			*exit = !(*exit);
		}
	}else{
		puts("\nTan indeciso :v");
	}
}
