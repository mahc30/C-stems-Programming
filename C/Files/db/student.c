#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
// Private definition

typedef struct
{
    int id;
    char name[30];
    int semester;
} student_t;

//Memory Allocator
student_t *estudiante_new()
{
    return (student_t *)malloc(sizeof(student_t));
}

//Constructor
void student_ctor(student_t *estudiante,
                     const int id,
                     const char *name,
                     const int semester)
{
    estudiante->id = id;
    strcpy(estudiante->name, name);
    estudiante->semester = semester;
}

//Destructor
void student_dtor(student_t* student){
    free(student);
}

int student_get_id(student_t *student){
	return student -> id;
}

char *student_get_name(student_t *student){
	return student -> name;
}

int student_get_semester(student_t *student){
	return student -> semester;
}

int db_size;
bool db_loaded = false;

//Behaviour functions
student_t *loaddb(char FILE_NAME[30]){
	char path[] = "./files/";
	char buffer[30];
	int size;
	student_t *strPointer;
	student_t newEst;
	int id;
	char name[30];
	int semester;
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
	strPointer = (student_t *)malloc(sizeof(student_t) * size);

	//Comprobar que si se haya creado la memoria;
	if(strPointer == 0){
		puts("\nError cargando base de datos");
		return NULL;
	}else{
		puts("\nCargando Base de Datos...");
	}


	//Cargo cada registro
	for(int i = 0; i < size; i++){
		fscanf(db, "%s %d", buffer, &id);
		fscanf(db, "%s %s", buffer, name);
		fscanf(db, "%s %d", buffer, &semester);

		newEst.id = id;
		strcpy(newEst.name, name);
		newEst.semester = semester;

		*(strPointer + i) = newEst;
	}

	fclose(db);
	puts("\nBase de datos Cargada");
	db_loaded = !db_loaded;

	return strPointer;
}

student_t *readreg(int id){
	for(int i = 0; i < db_size; i++){
		if((db + i) -> id == id){
			return db +i;
		}
	}

	return NULL;
}