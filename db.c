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
void savedb(char ruta[31]);
void readall();
void readsize();
void mkreg(int cedula, char nombre[], int semestre);
estudiante *readreg(int cedula);

void salir(bool *exit);

//Función auxiliar para castear strings a enteros
char *itoa(int num, char *str)
{
        if(str == NULL)
        {
                return NULL;
        }
        sprintf(str, "%d", num);
        return str;
}

//Global Variables for easier code purposes

int db_size;
bool db_loaded = false;
estudiante *db; //Acá se almacena la base de datos

int main(void) {

	bool exit = false;
	char instruccion[33];
	char comando[10];
	char arg1[31];
	char arg2[31];
	char arg3[3];

	//Scan for Instructions
	while(!exit){
		strcpy(comando, "");
		printf("\n%c",'>');
		//mkdb
		fgets(instruccion, 32, stdin);
		sscanf(instruccion, "%9s %30s %30s %2s", comando, arg1, arg2, arg3);

		if(strcmp(comando, "mkdb") == 0){
			int c_reg;
			printf("running %s %s %s",comando, arg1, arg2);
			c_reg = atoi(arg2);
			mkdb(arg1, c_reg);
		}
		else if(strcmp(comando, "loaddb") == 0){
			printf("running %s %s", comando, arg1);
			db = loaddb(arg1);

			printf("\nDatabase loaded in: %p",db);
			// Para verificar que el puntero está bien o los datos whatever u want
			/*
			  for(int i = 0; i < 2; i++){
				printf("\nCedula: %dNombre: %sSemestre: %d", (db+i)->cedula,(db+i)->nombre,(db+i)->semestre);
				}
			 */

		}
		else if(strcmp(comando, "savedb") == 0 && db_loaded){
			printf("\nrunning %s %s", comando, arg1);

			savedb(arg1);
		}else if(strcmp(comando, "readall") == 0 && db_loaded){
			puts("\nrunning readall");
			readall();
		}else if(strcmp(comando, "readsize") == 0 && db_loaded){
			puts("\nrunning readsize");
			readsize();
		}else if(strcmp(comando, "mkreg") == 0 && db_loaded){
			printf("\nrunning %s %s %s %s",comando, arg1, arg2, arg3);
			int c_reg;
			int s_reg;
			c_reg = atoi(arg1);
			s_reg = atoi(arg3);

			mkreg(c_reg, arg2, s_reg);
		}
		else if(strcmp(comando, "readreg") == 0 && db_loaded){
			printf("\nrunning %s %s", comando, arg1);
			estudiante *current_reg;
			int c_num = atoi(arg1);
			current_reg = readreg(c_num);

			printf("\nCedula %d Nombre %s Semestre %d", current_reg ->cedula, current_reg -> nombre, current_reg ->semestre);
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
	char reg[] = "\nCedula: xxxxxxxxxx\nNombre: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\nSemestre: xx";

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
	estudiante *strPointer;
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
	printf("\nSe cargarán %d Registros", size);
	db_size = size;
	//Asigno un puntero a donde se crea el espacio para la base de datos
	strPointer = (estudiante *)malloc(sizeof(struct Estudiante) * size);

	//Comprobar que si se haya creado la memoria;
	if(strPointer == 0){
		puts("\nError cargando base de datos");
		return NULL;
	}else{
		puts("\nCargando Base de Datos...");
	}


	//Cargo cada registro
	for(int i = 0; i < size; i++){
		fscanf(db, "%s %d", buffer, &cedula);
		fscanf(db, "%s %s", buffer, nombre);
		fscanf(db, "%s %d", buffer, &semestre);

		newEst.cedula = cedula;
		strcpy(newEst.nombre, nombre);
		newEst.semestre = semestre;

		*(strPointer + i) = newEst;
	}

	fclose(db);
	puts("\nBase de datos Cargada");
	db_loaded = !db_loaded;

	return strPointer;
}

void savedb(char ruta[30]){
	char PATH[64];
	char *dir = "./files/";
	char snum[32];

	strcpy(PATH, dir);
	strcat(PATH, ruta);
	printf("\nSaving DB in: %s", PATH);

	estudiante *ldb = db;
	FILE *newDb;
	char regs[2048];

	newDb = fopen(PATH, "w");

	strcpy(regs, "Numero_de_Registros: ");
	itoa(db_size, snum);
	strcat(regs, snum);

	for(int i = 0; i < db_size; i++){
		strcat(regs, "\nCedula: ");

		itoa((db + i) -> cedula, snum);
		strcat(regs, snum);

		strcat(regs, "\nNombre: ");
		strcat(regs, (db + i) -> nombre);

		strcat(regs, "\nSemestre: ");
		itoa((db + i) -> semestre, snum);
		strcat(regs, snum);
	}

	fprintf(newDb, regs);

	printf("\n%s", "Db Saved :D");
	fclose(newDb);
}

void readall(){
	printf("\n%20s %20s %20s", "Cedula","Nombre","Semestre");
	char cedula[11];
	char semestre[3];

	for(int i = 0; i < db_size; i++){

		itoa((db + i) -> cedula, cedula);
		itoa((db + i) -> semestre, semestre);
		printf("\n%20s %20s %20s",cedula, (db + i) ->nombre, semestre);
	}
}

void readsize(){
	printf("\nLa base de datos tiene %d registros", db_size);
}

void mkreg(int cedula, char nombre[], int semestre){

	//Inicialización de la estructura
	estudiante newEst;
	estudiante *ptr = &newEst;

	ptr -> cedula = cedula;
	strcpy(ptr ->nombre, nombre);
	ptr -> semestre = semestre;

	//printf("\n %d %s %d", newEst.cedula, newEst.nombre, newEst.semestre);
	*(db + db_size) = *ptr;
	db_size ++;
}

estudiante *readreg(int cedula){
	for(int i = 0; i < db_size; i++){
		if((db + i) -> cedula == cedula){
			return db +i;
		}
	}

	return NULL;
}

void salir(bool *exit){
	int confirmation;

	puts("?Seguro que desea salir¿ SI: 1 NO: 0");
	scanf("%d", &confirmation);

	if(confirmation){
		puts("?Desea guardar la Base de Datos¿ SI: 1 NO: 0");

		scanf("%d", &confirmation);
		if(confirmation && db_loaded){
			char ruta[30];
			puts("\nIngrese el nombre del nuevo archivo: ");
			scanf("%s", ruta);
			savedb(ruta);
			puts("\nBase de datos guardada, bye :)");
			*exit = !(*exit);
		}else{
			puts("\nbye :)");
			*exit = !(*exit);
		}
	}else{
		puts("\nTan indeciso :v");
	}
}
