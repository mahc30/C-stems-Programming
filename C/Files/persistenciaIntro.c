#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>


void unix_error(char msg)
{
    fprintf(stderr, "%d: %s\n", msg, strerror(errno));
    exit(0);
}

int main(int argc, char **argv)
{

	struct stat stat_str;
	char *type;
	char *readok;

	if (argc != 2) {
	fprintf(stderr, "usage: %s <filename>\n", argv[0]);
	exit(0);
	}
    /* $begin statcheck */
	stat(argv[1], &stat_str);

	if (S_ISREG(stat_str.st_mode))     /* Determine file type */
	type = "regular";
	else if (S_ISDIR(stat_str.st_mode))
		type = "directory";
	else
    type = "other";

	if ((stat_str.st_mode & S_IRUSR)) /* Check read access */
		readok = "yes";
	else
		readok = "no";

	printf("type: %s, read: %s\n", type, readok);
	exit(0);

    exit(0);
}
