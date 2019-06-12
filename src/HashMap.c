#include "Hashmap.h"
#include <stdio.h>

HashMap* newHashMap(unsigned int size){
	HashMap* map = malloc(sizeof(HashMap));
	HASHMAP_DATA** table = malloc(sizeof(HASHMAP_DATA*)*size);
	
	map->size = size;
	map->table = table;

	for (unsigned int i = 0; i < size; i++)
	{
		table[i] = NULL;
	}

	return map;
}

unsigned int fonctionDeHashage(HashMap* hashMap, char* cle)
{
	unsigned int k = 0;
	unsigned int length = strlen(cle);
	for (unsigned int i = 0; i < length; i++)
	{
		k += cle[i]*(10^i);
	}
	unsigned int hash = (k % (hashMap->size));
	//printf("%s : %d : %d\n", cle, k, hash);
	return hash;
}

void HASHMAP_inserer(HashMap *map, char* cle, int valeur)
{
	//printHashMap(map);
	//printf("insert '%s' : ", cle);
	int hash = fonctionDeHashage(map, cle);
	
	HASHMAP_DATA* newData=malloc(sizeof(HASHMAP_DATA));
	newData->cle = malloc(sizeof(char[16]));
	strcpy(newData->cle, cle);
	newData->valeur = valeur;
	newData->suivant = NULL;

	// S'il n'y a rien dans la table de hachage
	// à cet index, on crée une entrée
	if (map->table[hash] == NULL)
	{
		map->table[hash] = newData;
		//printf("new entry\n");
		return;
	}

	// On parcourt la liste chainée
	HASHMAP_DATA* list_ptr = map->table[hash];
	do
	{
		// On vérifie si l'entrée existe déjà
		if(strcmp(list_ptr->cle, cle) == 0)
		{
			list_ptr->valeur += valeur;
			//printf("entry++\n");
			return;
		}
		list_ptr = list_ptr->suivant;
	}
	while(list_ptr != NULL);

	// On a pas trouvé d'entrée attachée à la clé
	// On en crée une à la fin de la liste chainée
	list_ptr->suivant = newData;
	//printf("new entry chain\n");
}

HASHMAP_DATA* HASHMAP_rechercher(HashMap* map, char* cle)
{
	printHashMap(map);
	printf("scan %s\n", cle);

	int hash = fonctionDeHashage(map, cle);

	// On parcourt la liste chainée
	HASHMAP_DATA* list_ptr = map->table[hash];
	do
	{
		// On vérifie si l'entrée existe
		if(strcmp(list_ptr->cle, cle) == 0)
		{
			return list_ptr;
		}
		list_ptr = list_ptr->suivant;
	}
	while(list_ptr != NULL);
	return NULL;
}

void printHashMap(HashMap* map)
{
	for(unsigned int i = 0; i < map->size; i++)
	{
		if(map->table[i] != NULL)
		{
			// On parcourt la liste chainée
			HASHMAP_DATA* list_ptr = map->table[i];
			do
			{
				printf("[%d]%s:%d ", i, list_ptr->cle, list_ptr->valeur);
				list_ptr = list_ptr->suivant;
			}
			while(list_ptr != NULL);
		}
	}
	printf("\n");
}
