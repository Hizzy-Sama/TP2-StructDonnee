#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#define Donnee struct donnee

struct donnee
{
	struct donnee* suivant;
	char* cle;
	int valeur;
};

Donnee* newHashTable(int size);
int fonctionDeHashage(char* cle, int m);
void inserer(Donnee *table, int m, char* cle);
Donnee* recherche(Donnee cible, Donnee* noeud);
Donnee* rechercheCle(char* cle, Donnee* noeud);
Donnee* get(Donnee *table, int m, char* cle);