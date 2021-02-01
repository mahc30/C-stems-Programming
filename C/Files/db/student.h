#ifndef STUDENT_H
#define STUDENT_H

//Forward Declaration
struct student_t;

//Memory Allocator
struct student_t *student_new();

//Constructor
void student_ctor(struct student_t *,
                  const int /*id*/,
                  const char * /*name*/,
                  const int /*semester*/);

//Destructor
void student_dtor(struct student_t *);

//Behaviour functions
int student_get_id(struct student_t *);
char *student_get_name(struct student_t *);
int student_get_semester(struct student_t *);
char *student_to_string(struct student_t *);
struct student_t *student_parse_reg(char *);
char *student_create_register(struct student_t *);
void student_calloc_n(struct student_t *, unsigned int);
size_t student_get_struct_size();

#endif