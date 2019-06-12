#include <stdlib.h>
#include <string.h>
#include <tchar.h>

typedef struct donnee
{
	char* cle;
	int valeur;
	struct donnee* suivant;
} HASHMAP_DATA;

typedef struct hashMap
{
	unsigned size;
	HASHMAP_DATA** table;
} HashMap;

HashMap* newHashMap(unsigned size);
unsigned int fonctionDeHashage(HashMap* hashMap, char* cle);
void HASHMAP_inserer(HashMap *map, char* cle, int valeur);
HASHMAP_DATA* HASHMAP_rechercher(HashMap* map, char* cle);
void analyseHashMap(HashMap* map);
