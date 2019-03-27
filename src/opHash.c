#include "opHash.h"
#include "hash.h"

int add(TD *atd, char *cuv)
{
	unsigned int i;
	ALista aL;

	i = atd->fd(cuv, atd->hash_length);
	aL = atd->v + i;

	return InserareL(aL, cuv, strlen(cuv) + 1);
}

ALista find(TD *atd, char *cuv)
{
	unsigned int i;
	ALista aL;

	i = atd->fd(cuv, atd->hash_length);
	aL = atd->v + i;
	while (*aL) {
		if (memcmp(cuv, (*aL)->info, strlen(cuv)) == 0)
			return aL;
		aL = &(*aL)->urm;
	}

	return NULL;
}

void clear(TD **atd)
{
	unsigned int i;

	for (i = 0; i < (*atd)->hash_length; i++)
		DistrugeL((*atd)->v + i);
}

void remove_cuv(TD *atd, char *cuv)
{
	TLista aux;
	ALista aL = find(atd, cuv);

	if (aL != NULL) {
		aux = *aL;
		*aL = aux->urm;
		free(aux->info);
		free(aux);
	}
}

void print(TD *atd, FILE *f)
{
	ALista aL;
	unsigned int i;

	for (i = 0; i < atd->hash_length; i++) {
		aL = atd->v + i;
		if (*aL)
			AfisareL(aL, f);
	}
}

void print_bucket(TD *atd, unsigned int index_bucket, FILE *f)
{
	ALista aL;

	aL = atd->v + index_bucket;
	if (*aL)
		AfisareL(aL, f);
}

TD *resize(TD *atd, unsigned int newtd_length)
{
	unsigned int i;
	ALista aL;
	TD *new_td;

	new_td = AlocTD(newtd_length, atd->fd);
	if (!new_td)
		return NULL;
	for (i = 0; i < atd->hash_length; i++) {
		aL = atd->v + i;
		for (; *aL; aL = &(*aL)->urm)
			add(new_td, (*aL)->info);
	}

	DistrugeTD(&atd);
	return new_td;
}

TD *resize_double(TD *atd)
{
	return resize(atd, atd->hash_length * 2);
}

TD *resize_halve(TD *atd)
{
	return resize(atd, atd->hash_length / 2);
}
