#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t encXorFunction(uint8_t data) { return data ^ 0xFF; }

int main(int argc, char *argv[]) {
	char input[50];
	uint8_t (*encFuntion)(uint8_t) = NULL;

	FILE *fin = fopen((*(argv+1)), "r");
	if (fin == NULL) {
		perror("Error: ");
		return EXIT_FAILURE;
	}

	if (strncmp("xor", (*(argv+3)), 3) == 0) {
		encFuntion = &encXorFunction;
	}

	FILE *fout = fopen((*(argv+2)), "w");
	if (fout == NULL) {
		perror("Error: ");
		return EXIT_FAILURE;
	}

	while ( fgets(input, sizeof(input), fin) != NULL) {

		int n = strlen(input);

		for (int i = 0; i < n; i++) {
		input[i] = (*encFuntion)(input[i]);
		}
		fputs(input, fout);
	}

	fclose(fin);
	fclose(fout);
	return EXIT_SUCCESS;
}
