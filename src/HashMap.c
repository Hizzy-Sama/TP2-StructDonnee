#include "Hashmap.h"
#include "stdafx.h"

Donnee* newHashTable(int size)
{
	Donnee *table = malloc(sizeof(Donnee)*size);
	for (int i = 0; i < size; i++)
	{
		table[i].cle = NULL;
		table[i].valeur = NULL;
		table[i].suivant = NULL;
	}
	return table;
}


int fonctionDeHashage(char* cle, int m)
{

	int k = 0;
	int length = strlen(cle);
	for (int i = 0; i < length; i++)
	{
		k += cle[i];
	}
	return k%m;
}

void inserer(Donnee *table, int m, char* cle)
{

	int hash = fonctionDeHashage(cle, m);
	Donnee *item=malloc(sizeof(Donnee));
	item->cle = cle;
	item->valeur = 1;
	item->suivant = NULL;
	if (table[hash].cle == NULL && table[hash].valeur == NULL)
	{
		table[hash] = (*item);
	}
	else
	{
		Donnee* trouve = recherche((*item), &table[hash]);
		if (strcmp(trouve->cle, item->cle) == 0)
		{
			trouve->valeur += 1;
		}
		else
		{
			trouve->suivant = item;
		}
		int a = 0;
	}
}

Donnee* recherche(Donnee cible, Donnee* noeud)
{
	int trouve = 0;

	do
	{
		if (strcmp(noeud->cle, cible.cle) == 0);
		{
			return noeud;
		}
		if (noeud->suivant == NULL)
		{
			return noeud;
		}
		noeud = noeud->suivant;
	} while (1);
}

Donnee* rechercheCle(char* cle, Donnee* noeud)
{
	do
	{
		if (strcmp(noeud->cle, cle) == 0);
		{
			return noeud;
		}
		noeud = noeud->suivant;
	} while (noeud != NULL);
	return NULL;
}

Donnee* get(Donnee *table, int m, char* cle)
{
	int hash = fonctionDeHashage(cle, m);
	Donnee* result = rechercheCle(cle, &table[hash]);
	return result;

}

