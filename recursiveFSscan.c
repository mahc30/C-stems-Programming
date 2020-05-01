#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#define PATH_SIZE 1024
char filepath[PATH_SIZE];

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void printDir(DIR *streamp){
	struct dirent *dep;
	struct stat stat_str;

	//puts("PrintDir called");
	while ((dep = readdir(streamp)) != NULL) {

		//puts("Determine fileType");
		stat(dep->d_name, &stat_str); //Determine FileType

		if (!S_ISDIR(stat_str.st_mode)) //Si es directorio
		{
			if(strcmp(dep-> d_name, ".") || strcmp(dep-> d_name, "..")) //Si no es el mismo directorio o el anterior
			{
				printf("Found Dir: %s\n", dep->d_name);
				sprintf(filepath, "%s/%s", filepath, dep->d_name);
				//printf("Scanning: %s\n", filepath);
				DIR *streamp2 = opendir(filepath);

				if (streamp2 == NULL )
				{
					perror("Unable to open folder");
					return;
				}

				printDir(streamp2);
			}

		}
		else
		{
			printf("	Found file: %s\n", dep->d_name);
		}

	}
	//Trim path
	//puts("Trimming path");
	for(int i = PATH_SIZE - 1; filepath[i] != '/' && i >= 0; i--) filepath[i] = 0;
	filepath[strlen(filepath) - 1] = 0;

	if(strlen(filepath) != 0){
		printf("\nCurrently In: %s\n", filepath);
		closedir(streamp);
	}

}

int main(int argc, char **argv)
{
    DIR *streamp;

    if (argc != 2) {
        printf("usage: %s <pathname>\n", argv[0]);
        exit(1);
    }
    strcpy(filepath, argv[1]);
    streamp = opendir(argv[1]);

    printf("Scanning: %s\n", argv[1]);
    printDir(streamp);

    errno = 0;
    if (errno != 0)
        unix_error("readdir error");

    closedir(streamp);
    exit(0);
}
