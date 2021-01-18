#ifndef STUDENT_H
#define STUDENT_H

//Forward Declaration
struct student_t;

//Memory Allocator
struct student_t* student_new();

//Constructor
void student_ctor(struct student_t*, 
                            const int /*id*/,
                            const char* /*name*/,
                            const int /*semester*/);

//Destructor
void sutdent_dtor(struct student_t*);

//Behaviour functions
int student_get_id(struct student_t*);
char* student_get_name(struct student_t*);
int student_get_semester(struct student_t*);

student_t *loaddb(char FILE_NAME[30]);
student_t *readreg(int id);

int db_size;
bool db_loaded;

#endif