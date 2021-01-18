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
#include <constants.h>
#include <student.h>

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

void file_db_ctor(file_db_t *db,
				  int _db_size,
				  char *_filename)
{
	db->db_size = db_size;
	strcpy(db->filename, _filename);
}

void file_db_dtor(file_db_t *db)
{
	for (int i = 0; i < db->db_size; i++)
	{
		free(db->students[i]);
	}
	free(db);
}

void *file_db_get_registers(file_db_t *db)
{
	return db->students;
}

void file_db_mkdb(file_db_t *db, int db_file_size)
{
	char db_file_path[100] = FILE_SERVICE_PATH;
	strcat(db_file_path, db->filename);

	FILE *file = fopen(db_file_path, "w");

	file_db_ctor(db, db->db_size, db_file_path);
	fprintf(file, "%d", db_file_size);
	fclose(file);

	puts("\nDb Created");
}

void file_loaddb(file_db_t *db, char *_db_name)
{
	db = fopen(_db_name, "r");
}

void file_db_savedb(file_db_t *db, char *regs)
{
	FILE *save_file = fopen(db->filename, "w");
	printf("\nSaving DB in: %s", db->filename);
	fprintf(save_file, db->db_size);
	fprintf(save_file, regs);

	fclose(save_file);
	puts("Db Saved :D");
}

void file_db_readall(file_db_t *db)
{
	printf("\n%20s %20s %20s", "Cedula", "Nombre", "Semestre");

	for (int i = 0; i < db->db_size; i++)
	{
		printf("\n%20d %20s %20d",
			   db->students[i]->id,
			   db->students[i]->name,
			   db->students[i]->semester);
	}
}

void file_db_readsize(file_db_t *db)
{
	printf("\nLa base de datos tiene %d registros", db->db_size);
}

void file_db_mkreg(file_db_t *db, int id, char name[], int semester)
{

	//Inicialización de la estructura
	struct student_t *student = student_new();
	student_ctor(student, id, name, semester);

	void *realloc_buffer = realloc(db->students, sizeof(student_t) * db_size);
	if (realloc_buffer == NULL)
	{
		perror("Error Reallocating Memory. MKREG");
	}
	else
	{
		db->db_size += 1;
		db->students = realloc_buffer;
		db->students[db_size] = student; //Push to end
										 //TODO make it a stack lol
	}
}

void file_db_readreg(file_db_t *db, int _id)
{
	//Search for id
	for (int i = 0; i < db->db_size; i++)
	{
		if (db->students[i]->id == _id)
		{
			printf("\n%20d %20s %20d",
				   db->students[i]->id,
				   db->students[i]->name,
				   db->students[i]->semester);
		}
	}
}
