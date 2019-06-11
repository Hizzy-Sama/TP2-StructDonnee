#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <HashMap.h>

#define MAXCHAR 1024

struct donnee {
	char* mot;
	int compte;
	struct donnee* suivant;
};

typedef struct donnee donnee;

int parent(int pos) {
	return (pos - 1) / 2;
}

int leftChild(int pos) {
	return 2 * pos + 1;
}

int rightChild(int pos) {
	return 2 * pos + 2;
}

struct MaxHeap {
	int size;
	int count;
	donnee *heap;
};

typedef struct MaxHeap MaxHeap;

void initialiser(MaxHeap *h, int s) {
	h->count = 0;
	h->size = s;
	h->heap = (donnee *)malloc(sizeof(donnee) * s);
}

void inserer(MaxHeap *h, donnee v) {
	if (h->count == h->size) {
		h->size += 1;
		h->heap = realloc(h->heap, sizeof(donnee) * h->size);
	}

    // une seule position possible : à la fin
	int index = h->count;
	h->heap[index] = v;

    // percolage
	while (index != 0) {
		if (h->heap[index].compte > h->heap[parent(index)].compte) {

            // si le parent a un nombre d'occurence plus faible
            // que la nouvelle donnée, on les échange
			donnee tmp = h->heap[index];
			h->heap[index] = h->heap[parent(index)];
			h->heap[parent(index)] = tmp;

			index = parent(index);
		}
		else break;
	}
	h->count++;
}

void construire(MaxHeap *h, donnee * data, int data_length){
	h->count = 0;
	h->size = data_length;
	h->heap = (donnee *)malloc(sizeof(donnee) * data_length);
    for (int i = 0; i < data_length; i++)
    {
        inserer(h, data[i]);
    }
}

void pop(MaxHeap *h) {
	if (h->count == 0)
		return;

    // on inverse la racine
    // et la plus éloignée des feuilles
	h->heap[0] = h->heap[--(h->count)];

	int index = 0;

    // tamisage
	while (index < h->count) {
		int max = index;

		if (leftChild(index) < h->count && h->heap[leftChild(index)].compte > h->heap[max].compte)
		{
			max = leftChild(index);
		}

		if (rightChild(index) < h->count && h->heap[rightChild(index)].compte > h->heap[max].compte)
		{
			max = rightChild(index);
		}

		if (max != index) {
			donnee tmp = h->heap[index];
			h->heap[index] = h->heap[max];
			h->heap[max] = tmp;
			index = max;
		}
		else break;
	}
}

donnee top(MaxHeap *h) {
	return h->heap[0];
}

void printWordOccur(char* word, unsigned int occurence)
{
	//max len = 16 caractères
	int word_len = strlen(word);
	printf("%s", word);
	if (word_len < 8) printf("\t");
	if (word_len < 16) printf("\t");
	printf(": %i\n", occurence);
}

void afficherDonnees(MaxHeap *h) {
    int previous_count = h->count;
	while (h->count != 1)
	{
		donnee d = top(h); pop(h);
		printWordOccur(d.mot, d.compte);
	}
    h->count = previous_count;
}

void printInfo(unsigned int taille, double remplissage, unsigned int longueurMax, double execTime)
{
	printf("\n");
	printf("============== Infos ==============\n");
	printf("Taille de la table de hachage : %i\n", taille);
	printf("Facteur de remplissage : %f\n", remplissage);
	printf("Plus longue liste : %i\n", longueurMax);
	printf("Temps d'exécution : %f\n", execTime);
	printf("===================================\n");
	printf("| %i | %f | %i | %f |\n", taille, remplissage, longueurMax, execTime);
	printf("\n");
}

// test du monceau
/*
int main() {
	const int heap_size = 100;
	MaxHeap h;
    donnee data[100];
	for (int i = 0; i <= 100; ++i)
	{
		donnee d;
		d.compte = rand() % 10000;
		d.mot = "a";
		data[i] = d;
	}
	construire(&h, data, heap_size);
	afficherDonnees(&h);
	return 0;
}
*/

int main(int argc, const char* argv[])
{
	// INPUT CHECK
	if (argc < 2)
	{
		printf("wrong usage,\n use : %s <input file>\n", argv[0]);
	}
	const char* filename = argv[1];

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Could not open file %s", filename);
		return 1;
	}

	// INIT
	time_t start = clock();

	char str[MAXCHAR];
	char *word;
	//unsigned int max = 0;

	// DATA GATHERING -> HASHTABLE
	while (fgets(str, MAXCHAR, fp) != NULL)
	{
		//printf("%s", str);

		//découpe en mots
		char delimiters[] = " \n,.';!:";
		word = strtok(str, delimiters);
		while (word != NULL)
		{
			//if(strlen(word) > max) { max = strlen(word); }

			//=========================================================/
			//insérer dans la table de hashage, clé = word, valeur += 1
			//=========================================================/

			printf("'%s'\n", word);
			word = strtok(NULL, delimiters);
		}
	}
	//printf("%i", max);
	fclose(fp);

	// HEAP-MAX
	//MaxHeap h;
	//initialiser(&h, 100);

	// DISPLAY WORD-OCCURENCE (most used first)
	//afficherDonnees(&h);

	time_t end = clock();
	printInfo(
		42, //Taille
		1.0, //remplissage
		42, // longueur max
		(end - start) / CLOCKS_PER_SEC // Temps d'éxec
	);

	return 0;
}
