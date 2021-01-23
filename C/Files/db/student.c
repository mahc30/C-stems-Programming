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
void student_ctor(student_t *_student,
                  int _id,
                  char *_name,
                  int _semester)
{

    _student -> id = _id;
    _student -> name = (char *)malloc(strlen((_name) + 1) * sizeof(char));
    strcpy(_student -> name, _name);
    _student ->semester = _semester;
}

//Destructor
void student_dtor(student_t *student)
{
    free(student);
}

int student_get_id(student_t *student)
{
    return student->id;
}

char *student_get_name(student_t *student)
{
    return student->name;
}

int student_get_semester(student_t *student)
{
    return student->semester;
}

void student_to_string(student_t *student)
{
    printf("%20d %20s %20d\n",
           student->id,
           student->name,
           student->semester);
}

student_t *student_parse_reg(char *reg)
{
    int id;
    char name[MAX_STUDENT_NAME_SIZE];
    int semester;
	student_t *new_student = student_new();

    sscanf(reg, "%d %s %d", &id, name, &semester);
    student_ctor(new_student, id, name, semester);
    return new_student;
}
