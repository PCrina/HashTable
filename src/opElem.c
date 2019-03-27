#include "opHash.h"
#include "hash.h"

TLista AlocCel(char *ae, unsigned int dim_cuv)
{
	TLista aux;

	aux = (TLista)malloc(sizeof(TCelula));
	if (!aux)
		return NULL;
	aux->info = malloc(dim_cuv);
	if (!aux->info) {
		free(aux);
		return NULL;
	}

	memcpy(aux->info, ae, dim_cuv);
	aux->urm = NULL;

	return aux;
}

TD *AlocTD(unsigned int hash_length, TFHASH fct_d)
{
	TD *atd;

	atd = (TD *)malloc(sizeof(TD));
	if (!atd)
		return NULL;
	atd->v = (TLista *)calloc(hash_length, sizeof(TLista));
	if (!atd->v) {
		free(atd);
		return NULL;
	}

	atd->hash_length = hash_length;
	atd->fd = fct_d;

	return atd;
}

void DistrugeL(ALista aL)
{
	TLista aux, L;

	L = *aL;
	while (L) {
		aux = L;
		L = L->urm;
		free(aux->info);
		free(aux);
	}

	*aL = NULL;
}

void DistrugeTD(TD **atd)
{
	unsigned int i;

	for (i = 0; i < (*atd)->hash_length; i++)
		DistrugeL((*atd)->v + i);

	free((*atd)->v);
	free(*atd);

	*atd = NULL;
}

int InserareL(ALista aL, char *cuv, unsigned int dim_cuv)
{
	TLista aux;

	while (*aL) {
		if (strcmp((*aL)->info, cuv) == 0)
			return 0;
		aL = &(*aL)->urm;
	}

	aux = AlocCel(cuv, dim_cuv);
	if (!aux)
		return -1;
	*aL = aux;

	return 1;
}

void AfisareL(ALista aL, FILE *f)
{
	for (; *aL; aL = &(*aL)->urm)
		fprintf(f, "%s ", (*aL)->info);
	fprintf(f, "\n");
}
