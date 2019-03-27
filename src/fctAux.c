#include "opHash.h"
#include "hash.h"

#define MAX 20000

int read_data(FILE *f, TD **td)
{
	char cmd[MAX];
	char *p;

	while (fgets(cmd, MAX, f)) {
		if (cmd[strlen(cmd) - 1] == '\n')
			cmd[strlen(cmd) - 1] = '\0';
		p = strtok(cmd, " ");
		if (p != NULL) {
			if (strcmp(p, "add") == 0) {
				if (exec_add(p, *td) == -1)
					goto exit_1;
			} else if (strcmp(p, "remove") == 0) {
				if (exec_remove(p, *td) == -1)
					goto exit_1;
			} else if (strcmp(p, "find") == 0) {
				if (exec_find(p, *td) == -1)
					goto exit_1;
			} else if (strcmp(p, "clear") == 0)
				clear(td);
			else if (strcmp(p, "print_bucket") == 0) {
				if (exec_print_bucket(p, *td) == -1)
					goto exit_1;
			} else if (strcmp(p, "print") == 0) {
				if (exec_print(p, *td) == -1)
					goto exit_1;
			} else if (strcmp(p, "resize") == 0) {
				if (exec_resize(p, td) == -1)
					goto exit_1;
			} else {
				perror("comanda invalida!");
				goto exit_1;
			}
		}
	}

	return 1;

exit_1:
	DistrugeTD(td);
	return -1;
}

int exec_add(char *p, TD *td)
{
	p = strtok(NULL, " ");
	if (p != NULL) {
		if (add(td, p) == -1) {
			perror("inserare element nereusita!");
			return -1;
		}
	} else {
		perror("add: lipsa parametru obligatoriu!");
		return -1;
	}

	return 1;
}

int exec_remove(char *p, TD *td)
{
	p = strtok(NULL, " ");
	if (p != NULL)
		remove_cuv(td, p);
	else {
		perror("remove: lipsa parametru obligatoriu!");
		return -1;
	}
	return 1;
}

int exec_print_bucket(char *p, TD *td)
{
	unsigned int index;
	FILE *f;
	char *test;

	p = strtok(NULL, " ");
	if (p != NULL) {
		index = strtoul(p, &test, 10);
		if (*test != '\0') {
			perror("index bucket invalid!");
			return -1;
		}
		p = strtok(NULL, " ");
		if (p != NULL) {
			f = fopen(p, "a");
			if (f == NULL) {
				perror("deschidere f_out nereusita!");
				return -1;
			}
			print_bucket(td, index, f);
			fclose(f);
		} else
			print_bucket(td, index, stdout);
	} else {
		perror("print_bucket: lipsa parametru obligatoriu!");
		return -1;
	}

	return 1;
}

int exec_print(char *p, TD *td)
{
	FILE *f;

	p = strtok(NULL, " ");
	if (p != NULL) {
		f = fopen(p, "a");
		if (f == NULL) {
			perror("deschidere f_out nereusita!");
			return -1;
		}
		print(td, f);
		fclose(f);
	} else {
		print(td, stdout);
	}
	return 1;
}

int exec_resize(char *p, TD **td)
{
	p = strtok(NULL, " ");
	if (p != NULL) {
		if (strcmp(p, "double") == 0)
			*td = resize_double(*td);
		else if (strcmp(p, "halve") == 0)
			*td = resize_halve(*td);
		else {
			perror("argumente invalide resize!");
			return -1;
		}
	} else {
		perror("resize: lipsa parametru obligatoriu!");
		return -1;
	}

	if (!(*td)) {
		perror("redimensionare tabela nereusita!");
		return -1;
	}

	return 1;
}

int exec_find(char *p, TD *td)
{
	FILE *f;
	char *cuv;

	p = strtok(NULL, " ");
	if (p != NULL) {
		cuv = malloc(strlen(p) + 1);
		memcpy(cuv, p, strlen(p) + 1);
		p = strtok(NULL, " ");
		if (p != NULL) {
			f = fopen(p, "a");
			if (f == NULL) {
				perror("deschidere f_out nereusita!");
				free(cuv);
				return -1;
			}
			if (find(td, cuv))
				fprintf(f, "True\n");
			else
				fprintf(f, "False\n");
			fclose(f);
		} else {
			if (find(td, cuv))
				fprintf(stdout, "True\n");
			else
				fprintf(stdout, "False\n");
		}
		free(cuv);
	} else {
		perror("find: lipsa parametru obligatoriu!");
		return -1;
	}

	return 1;
}
