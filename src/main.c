#include "opHash.h"
#include "hash.h"

int main(int argc, char **argv)
{

	unsigned int hash_length;
	int i;
	TD *td;
	FILE *f;

	if (argc < 2) {
		perror("nu a fost introdusa lungime hash!");
		return -1;
	}

	hash_length = strtoul(argv[1], NULL, 10);
	td = AlocTD(hash_length, hash);
	if (!td) {
		perror("alocare tabela nereusita!");
		return -1;
	}

	if (argc > 2) {
		for (i = 2; i < argc; i++)  {
			f = fopen(argv[i], "r");
			if (f == NULL) {
				perror("deschidere f_out nereusita!");
				DistrugeTD(&td);
				return -1;
			}
			if (read_data(f, &td) == -1) {
				fclose(f);
				return -1;
			}
			fclose(f);
		}
	} else {
		if (read_data(stdin, &td) == -1)
			return -1;
	}

	DistrugeTD(&td);
	return 0;
}
