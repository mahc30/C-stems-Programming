#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void mkdb(char n_base[30], int c_reg);
char loaddb(char *FILE_NAME);
void savedb(FILE db, char path[]);
void readall(FILE db);
int readsize(FILE db);
void mkreg(int cedula, char nombre[], int semestre);
struct estudiante readreg(int cedula);
void salir(bool *exit);

struct{
	int cedula;
	char nombre[30];
	int semestre;
}estudiante;

int main(void) {
	bool exit = false;
	bool db_loaded = false;
	char instruccion[33];
	char comando[10];
	char arg1[31];
	char arg2[31];
	char arg3[3];

	//Scan for Instructions
	while(!exit){
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
			puts("running loaddb");
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
			salir(&exit);
		}else{
			puts("Comando no reconocido");
		}
	}

	return(0);
}

void mkdb(char n_base[30],int c_reg){
	char PATH[64];
	char *dir = "./files/";

	strcat(PATH,dir);
	strcat(PATH,n_base);
	char reg[] = "Cedula:xxxxxxxxxx\nNombre:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\nSemestre:xx";

	FILE *db = fopen(PATH,"w");
	for(int i = 0; i < c_reg; i++){
		fprintf(db, "Número de Registros: %d\n", c_reg);
		fprintf(db, reg);
	}

	puts("Db Created");
	fclose(db);
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
	}
}
