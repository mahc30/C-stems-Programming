#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "constants.h"
#include "student.h"
#include "file_db.h"

int main(void)
{
	struct file_db_t *file_db = file_db_new();
	short files_open = 0;
	bool db_loaded = true;
	char instruction_buffer[MAX_INSTRUCTION_SIZE];
	char command[MAX_COMMAND_SIZE];
	char arg1[MAX_FILENAME_SIZE];
	char arg2[MAX_FILENAME_SIZE];
	char arg3[MAX_SEMESTER_ARG_SIZE];
	bool exit_flag = false;

	//Scan for Instructions
	puts("¡Wilkommen!");
	
	while (!exit_flag)
	{
		printf("\n%c", '>');
		strcpy(command, "");
		fgets(instruction_buffer, MAX_INSTRUCTION_SIZE, stdin);
		sscanf(instruction_buffer, "%9s %30s %30s %2s", command, arg1, arg2, arg3);

		if (strcmp(command, "mkdb") == 0)
		{
			int db_size;
			db_size = atoi(arg2);
			file_db_ctor(file_db, arg1, db_size);
			file_db_mkdb(file_db);
		}
		else if (strcmp(command, "loaddb") == 0)
		{
			printf("TODO IMPLEMENT LOADDB running %s %s", command, arg1);
			
			file_db_ctor(file_db, arg1, 0); //Initialize with 0 regs
			file_db_loaddb(file_db);

			printf("\nDatabase loaded in: %p", file_db );
			file_db_readsize(file_db);
			file_db_readall(file_db);
			// Para verificar que el puntero está bien o los datos whatever u want
			/*
			  for(int i = 0; i < 2; i++){
				printf("\nCedula: %dNombre: %sSemestre: %d", (file_db+i)->cedula,(file_db+i)->nombre,(file_db+i)->semestre);
				}
			 */
		}
		else if (strcmp(command, "savedb") == 0 && db_loaded)
		{
			printf("\nrunning %s %s", command, arg1);
			file_db_savedb(file_db, arg1);
		}
		else if (strcmp(command, "readall") == 0 && db_loaded)
		{
			puts("\nrunning readall");
			file_db_readall(file_db);
		}
		else if (strcmp(command, "readsize") == 0 && db_loaded)
		{
			puts("\nrunning readsize");
			file_db_readsize(file_db);
		}
		else if (strcmp(command, "mkreg") == 0 && db_loaded)
		{
			printf("\nrunning %s %s %s %s", command, arg1, arg2, arg3);
			int db_size;
			int s_reg;
			db_size = atoi(arg1);
			s_reg = atoi(arg3);

			file_db_mkreg(file_db, db_size, arg2, s_reg);
		}
		else if (strcmp(command, "readreg") == 0 && db_loaded)
		{
			printf("\nrunning %s %s", command, arg1);
			file_db_readreg(file_db, atoi(arg1));
		}
		else if (strcmp(command, "exit") == 0)
		{
			strcpy(command, "");
			salir(&exit_flag);
			if (exit_flag)
			{
				return (0);
			}
		}
		else
		{
			printf("%s", "Comando no reconocido");
		}
	}

	return (0);
}

//Función auxiliar para castear strings a enteros
char *itoa(int num, char *str)
{
	if (str == NULL)
	{
		return NULL;
	}
	sprintf(str, "%d", num);
	return str;
}

void salir(bool *exit);
void salir(bool *exit)
{
	int confirmation;

	puts("?Seguro que desea salir¿ SI: 1 NO: 0");
	scanf("%d", &confirmation);

	if (confirmation)
	{
		/*
		puts("?Desea guardar la Base de Datos¿ SI: 1 NO: 0");

		scanf("%d", &confirmation);
		if (confirmation)
		{
			char ruta[30];
			puts("\nIngrese el nombre del nuevo archivo: ");
			scanf("%s", ruta);
			file_db_savedb(fil);
			puts("\nBase de datos guardada, bye :)");
			*exit = !(*exit);
		}
		else
		{
			*/
			puts("\nbye :)");
			*exit = !(*exit);
		//}
	}
	else
	{
		puts("\nTan indeciso :v");
	}
}