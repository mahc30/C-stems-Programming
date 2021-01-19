#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "constants.h"

// Private definition

typedef struct
{
    int id;
    char *name;
    int semester;
} student_t;

//Memory Allocator
student_t *student_new()
{
    return (student_t *)malloc(sizeof(student_t));
}

//Constructor
void student_ctor(student_t *estudiante,
                     int id,
                     char *name,
                     int semester)
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

void student_parse_reg(student_t *student, char *reg){
    int id;
	char name[MAX_STUDENT_NAME_SIZE];
	int semester;
		
    sscanf(reg, "%d %s %d", &id, name, &semester);
    student -> id = id;
    strcmp(student -> name, name);
    student -> semester = semester;
}

void student_calloc_n(student_t * student, int n){
    student = calloc(n, sizeof(student_t));
}

