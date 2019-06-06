#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXCHAR 1024

void printWordOccur(char* word, unsigned int occurence)
{
    //max len = 16 caractères
    int word_len = strlen(word);
    printf("%s", word);
    if(word_len < 8) printf("\t");
    if(word_len < 16) printf("\t");
    printf(": %i\n", occurence);
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
    printf("| %i | %f | %i | %f |\n", taille, remplissage ,longueurMax, execTime);
    printf("\n");
}

int main(int argc, const char* argv[])
{
    // INPUT CHECK
    if(argc < 2)
    {
        printf("wrong usage,\n use : %s <input file>\n", argv[0]);
    }
    const char* filename = argv[1];
 
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
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

            //printf("'%s'\n", word);
            word = strtok(NULL, delimiters);
        }    
    }
    //printf("%i", max);
    fclose(fp);

    // HEAP-MAX
    //...
    
    // DISPLAY WORD-OCCURENCE (most used first)
    //printf("===== Word ===== | ===== Occurence =====\n");
    //printWordOccur(word, occur);
    
    time_t end = clock();
    printInfo(
        42, //Taille
        1.0, //remplissage
        42, // longueur max
        (end - start) / CLOCKS_PER_SEC // Temps d'éxec
    );

    return 0;
}

