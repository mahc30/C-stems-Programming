#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

//Forward Declarations
struct file_db_t;

//Memory Allocator
struct file_db_t *file_db_new();

//Constructor
void file_db_ctor(struct file_db_t * /*obj*/,
                  char *, /*filename*/
                  int     /* db_size */
);

//Destructor
void file_db_dtor(struct file_db_t *);

void *file_db_get_registers(struct file_db_t *);

//Behaviour functions
void file_db_mkdb(struct file_db_t *);
void file_db_loaddb(struct file_db_t *);
void file_db_savedb(struct file_db_t *, char *);
void file_db_readall(struct file_db_t *);
void file_db_readsize(struct file_db_t *);
void file_db_readfilename(struct file_db_t *);
void file_db_mkreg(struct file_db_t **, int, char *, int);
void file_db_readreg(struct file_db_t *, int);
void file_db_inc_size(struct file_db_t *_db);

#endif

/*
Implemente los siguientes comandos:

mkdb nombre tamaño : crea una base de datos especificando el nombre y la cantidad de registros.

loaddb nombre : carga la base de datos en memoria desde el archivo especificado.
El comando debe indicar si la base de datos se cargó correctamente o no existe.
La base de datos debe cargarse en memoria dinámica antes de poder aplicar los siguientes comandos.

savedb nombre : este comando salva la base de datos en el archivo especificado.
readall : lee todos los registros de la base de datos.
readsize : lee la cantidad de registros de la base datos.
mkreg cedula nombre semestre : crea un nuevo registro en la base de datos.
readreg cédula : busca en la base de datos por número de cédula. En caso de encontrar la cédula imprime el registro completo.
exit : salir del programa. Antes de terminar debe preguntar si se desea salvar la base de datos en el archivo especificado con el comando loaddb.
*/