#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>

// Declarare lista simpla inlantuita
typedef struct cellista {
	char *info;		// informatie
	struct cellista *urm;	// adresa campul urmator
} TCelula, *TLista, **ALista;	// tipurile Celula, Lista si Adresa_Lista

// Declarare functie de dispersie
typedef unsigned int (*TFHASH)(const char *str, unsigned int hash_length);

// Declarare tabela de dispersie
typedef struct {
	unsigned int hash_length;	// dimensiune hash
	TFHASH fd;			// functia de dispersie
	TLista *v;			// vector de bucket-uri
} TD;

// OPERATII ELEMENTARE

// alocare spatiu celula, testare, copiere informatie
TLista AlocCel(char *ae, unsigned int dim_cuv);

// initializarea tabelei de dispersie
TD *AlocTD(unsigned int hash_length, TFHASH fct_d);

// eliberare spatiu ocupat de lista simpla inlantuita
void DistrugeL(ALista aL);

// eliberare spatiu ocupat de tabela de dispersie
void DistrugeTD(TD **atd);

// inserare la sf listei
int InserareL(ALista aL, char *cuv, unsigned int dim_cuv);

// afisare lista in fisierul dat ca parametru
void AfisareL(ALista aL, FILE *f);

// OPERATII IN TABELA DE DISPERSIE

// adauga cuvant la hashtable
int add(TD *atd, char *cuv);

// cauta cuvant in hashtable
ALista find(TD *atd, char *cuv);

// sterge cuvant din hashtable
void remove_cuv(TD *atd, char *cuv);

// printeaza toate bucket-urile
void print(TD *atd, FILE *f);

// printeaza cuvintele din bucket-ul indicat
void print_bucket(TD *atd, unsigned int index_bucket, FILE *f);

// goleste tabela
void clear(TD **atd);

// modifica dimensiunea hash-ului
TD *resize(TD *atd, unsigned int newtd_length);

// dubleaza dimensiunea hash-ului
TD *resize_double(TD *atd);

// injumatateste dimensiunea hash-ului
TD *resize_halve(TD *atd);

// FUNCTII AUXILIARE MAIN

// parsare si executie comenzi
int read_data(FILE *f, TD **td);

// executa comanda add
int exec_add(char *p, TD *td);

// executa comanda remove
int exec_remove(char *p, TD *td);

// executa comanda print_bucket
int exec_print_bucket(char *p, TD *td);

// executa comanda print
int exec_print(char *p, TD *td);

// executa comanda resize
int exec_resize(char *p, TD **td);

// executa comanda find
int exec_find(char *p, TD *td);
