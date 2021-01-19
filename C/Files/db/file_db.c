/*
 ============================================================================
 Name        : sistemasOperativos.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================

Realice un programa que permita crear un base de datos de estudiantes.
Cada registro de la base de datos estará dado por: número de cédula, name y semester.
Cada registro corresponde a un student_t.

Implemente los siguientes comandos:

mkdb name tamaño : crea una base de datos especificando el name y la cantidad de registros.

loaddb name : carga la base de datos en memoria desde el archivo especificado.
El comando debe indicar si la base de datos se cargó correctamente o no existe.
La base de datos debe cargarse en memoria dinámica antes de poder aplicar los siguientes comandos.

savedb name : este comando salva la base de datos en el archivo especificado.

readall : lee todos los registros de la base de datos.

readsize : lee la cantidad de registros de la base datos.

mkreg id name semester : crea un nuevo registro en la base de datos.

readreg cédula : busca en la base de datos por número de cédula. En caso de encontrar la cédula imprime el registro completo.

exit : salir del programa. Antes de terminar debe preguntar si se desea salvar la base de datos en el archivo especificado con el comando loaddb.

Cada comando deberá implementarse como una función.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "constants.h"
#include "student.h"

//private definition
typedef struct
{
	int db_size;
	char *filename;
	struct student_t *students[];
} file_db_t;

file_db_t *file_db_new()
{
	return (file_db_t *)malloc(sizeof(file_db_t));
}

void file_db_ctor(file_db_t *_db,
				  char *_filename,
				  int _db_size)
{
	_db->filename = (char *)malloc(strlen((_filename) + 1) * sizeof(char));
	strcpy(_db->filename, _filename);
	_db->db_size = _db_size;
}

void file_db_dtor(file_db_t *_db)
{
	for (int i = 0; i < _db->db_size; i++)
	{
		free(_db->students[i]);
	}
	free(_db);
}

void *file_db_get_registers(file_db_t *_db)
{
	return _db->students;
}

void file_db_mkdb(file_db_t *_db)
{
	char db_file_path[100];
	strcpy(db_file_path, FILE_SERVICE_PATH);
	strcat(db_file_path, _db->filename);

	FILE *file = fopen(db_file_path, "w");
	if (file == NULL)
	{
		perror("MKDB, ERROR CREATING FILE");
	}

	file_db_ctor(_db, db_file_path, _db->db_size);
	fprintf(file, "%d", _db->db_size);
	fclose(file);

	puts("\nDb Created");
}

void file_db_loaddb(file_db_t *_db)
{
	char path[MAX_FILENAME_SIZE + 16];
	strcmp(path, FILE_SERVICE_PATH);
	strcat(path, _db -> filename);

printf("%s", path);
	FILE *file = fopen(path, "r");
	if (file == NULL)
	{
		perror("LOADDB, ERROR CREATING FILE");
	}


	//Read File db_size, Because of format is always the first line
	fscanf(file, "%d", &(_db -> db_size));
	printf("DB size: %d", _db -> db_size);

	//Allocate memory for students
	student_calloc_n( *(_db -> students) ,_db -> db_size);

	char reg[1024];
	//Scan all registers
	for(int i = 0; i < _db -> db_size; i++){
		fscanf(file, "%s", reg);
		student_parse_reg(_db -> students[i], reg);
	}

	//TOdo _db ctor
}

void file_db_savedb(file_db_t *_db, char *regs)
{
	FILE *save_file = fopen(_db->filename, "w");
	printf("\nSaving DB in: %s", _db->filename);
	fprintf(save_file, "%d", _db->db_size);
	fprintf(save_file, "%s", regs);

	fclose(save_file);
	puts("Db Saved :D");
}

void file_db_readall(file_db_t *_db)
{
	printf("\n%20s %20s %20s", "Cedula", "Nombre", "Semestre");

	for (int i = 0; i < _db->db_size; i++)
	{
		printf("\n%20d %20s %20d",
			   student_get_id(_db->students[i]),
			   student_get_name(_db->students[i]),
			   student_get_semester(_db->students[i]));
	}
}

void file_db_readsize(file_db_t *_db)
{
	printf("\nLa base de datos tiene %d registros", _db->db_size);
}

void file_db_mkreg(file_db_t *_db, int id, char name[], int semester)
{
	struct student_t *student = student_new();
	student_ctor(student, id, name, semester);

	printf("\nTODO STACK FOR MKREG\n Tried Adding new student:\n %20d %20s %20d",
		   student_get_id(student),
		   student_get_name(student),
		   student_get_semester(student));

	_db->db_size += 1;
	//TODO stack for students in file_db
}

void file_db_readreg(file_db_t *_db, int _id)
{
	//Search for id
	for (int i = 0; i < _db->db_size; i++)
	{
		if (student_get_id(_db->students[i]) == _id)
		{
			printf("\n%20d %20s %20d",
				   student_get_id(_db->students[i]),
				   student_get_name(_db->students[i]),
				   student_get_semester(_db->students[i]));
		}
	}
}
