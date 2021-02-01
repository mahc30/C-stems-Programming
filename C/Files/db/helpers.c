#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"

int helpers_sanitize_string(char *string)
{
    //Check is not empty
    if (strlen(string) == 0)
    {
        puts("Empty String");
        return 0;
    }

    //Whitelist characters
    const char *whitelist = CHAR_WHITELIST;
    short char_found;

    //C doesnt have a String.contains() sooo iterate over it it is
    int string_size = strlen(string);

    for (int i = 0; i <  string_size - 1; i++)
    {
        char_found = 0;
        for (int j = 0; j < strlen(CHAR_WHITELIST); j++)
        {
            if (string[i] == whitelist[j])
            {
                char_found = 1;
                break;
            }
        }

        if (char_found == 0)
        {
            return 0;
        }
    }

    return 1;
}

//Función auxiliar para castear strings a enteros
void *itoa(int *num, char *str)
{
	if (str == NULL)
	{
		return NULL;
	}
	sprintf(str, "%d", *num);
}