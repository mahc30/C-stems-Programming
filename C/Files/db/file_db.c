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
#include "stack.h"

//private definition
typedef struct
{
	unsigned int db_size;
	char *filename;
	struct stack_t *students;
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
	struct stack_t *stack_node = stack_new();
	_db->students = stack_node;
}

void file_db_dtor(file_db_t *_db)
{
	for (int i = 0; i < _db->db_size; i++)
	{
		free(_db->students);
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
	char reg[1024];
	char path[MAX_FILENAME_SIZE + 16];
	strcpy(path, FILE_SERVICE_PATH);
	strcat(path, _db->filename);

	FILE *file = fopen(path, "r");
	if (file == NULL)
	{
		perror("LOADDB, ERROR READING FILE");
		return;
	}

	//Read File db_size, Because of format is always the first line
	if (fgets(reg, 1024, file) == NULL)
	{
		puts("Error reading the file");
		return;
	}

	if (sscanf(reg, "%u", &(_db->db_size)) != 1)
	{
		perror("LOADDB, ERROR READING FILE");
	}

	struct student_t *new_student;

	//Scan the rest of the file
	for (int i = 0; i < _db->db_size; i++)
	{
		//TODO refactor this into a function hehe
		fgets(reg, sizeof(reg), file);
		reg[sizeof(reg) - 1] = '\n';

		new_student = student_parse_reg(reg);
		stack_push(&(_db->students), new_student);
	}

	puts("DB loaded");
}

void file_db_savedb(file_db_t *_db)
{

	int db_size = _db->db_size;
	char path[MAX_FILENAME_SIZE + 24];
	strcpy(path, FILE_SERVICE_PATH);
	strcat(path, _db->filename);
	strcat(path, "saved");

	FILE *save_file = fopen(path, "w");

	printf("\nSaving DB in: %s", path);

	//Obligatory first line size of db
	fprintf(save_file, "%d\n", _db->db_size);

	struct stack_t *students = _db->students;

	struct stack_t *copy = stack_new();
	char *student_reg;

	struct student_t *student;

	for (int i = 0; i < _db->db_size; i++)
	{
		student = (struct student_t *)stack_pop(&students, student_get_struct_size());
		stack_push(&copy, student);

		student_reg = student_to_string(student);
		fprintf(save_file, "%s\n", student_reg);
		free(student_reg);
	}

	_db->students = copy;

	fclose(save_file);
	puts("Db Saved :D");
}

void file_db_readall(file_db_t *_db)
{

	//TODO Apparently i should have made a deque as i need to iterate over it
	//And stacks / queues are not really made for iteration (Who would have thought...)
	//So we are doing the just download more ram way
	//btw solo funciona una vez PORQUE NO ES LA ESTRUCTURA ADECUADA PLS FIX IT
	//The Actual Solution:
	//I'm freeing the other stack node with each pop so
	//im creating a copy of that stack to keep integrity
	//it's a temporal fix pls dont hate

	struct stack_t *students = _db->students;
	struct stack_t *copy = stack_new();

	struct student_t *student;
	char *student_reg;

	for (int i = 0; i < _db->db_size; i++)
	{
		student = (struct student_t *)stack_pop(&students, student_get_struct_size());
		stack_push(&copy, student);
		student_reg = student_to_string(student);
		printf("%s\n", student_reg);
	}

	_db->students = copy;
	//Podría hacer un save_db y luego un load_db... así le tiro más duro a procesador y memoria pero funciona uwu
}

void file_db_readsize(file_db_t *_db)
{
	printf("\nLa base de datos tiene %d registros\n", _db->db_size);
}

void file_db_readfilename(file_db_t *_db)
{
	printf("\nDB filename is: %s\n", _db->filename);
}

void file_db_mkreg(file_db_t *_db, int id, char name[], int semester)
{
	struct student_t *student = student_new();
	char *student_reg;

	student_ctor(student, id, name, semester);
	puts("Adding student: ");
	student_reg = student_to_string(student);
	printf("%s", student_reg);

	stack_push(&(_db->students), student);
}

struct student_t *file_db_readreg(file_db_t *_db, int _id)
{

	//Same solution as in file_db_readall
	struct stack_t *students = _db->students;
	struct stack_t *copy;
	copy = stack_new();

	struct student_t *student;
	char *student_reg;

	bool found = false;
	for (int i = 0; i < _db->db_size; i++)
	{
		student = (struct student_t *)stack_pop(&students, student_get_struct_size());
		stack_push(&copy, student);

		if (student_get_id(student) == _id)
		{
			student_reg = student_to_string(student);
			printf("%s\n", student_reg);
			found = true;
			break;
		}
	}

	if (!found)
		puts("Student not found");
	
	_db->students = copy;
}

void file_db_inc_size(file_db_t *_db)
{
	_db->db_size = _db->db_size + 1;
}