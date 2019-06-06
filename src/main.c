#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1024

void printWordOccur(char* word, unsigned int occurence)
{
    //max len = 16 caractères
    int word_len = strlen(word);
    //printf("===== Word ===== | ===== Occurence =====\n");
    printf("%s", word);
    if(word_len < 8) printf("\t");
    if(word_len < 16) printf("\t");
    printf(": %i\n", occurence);
}

int main(int argc, const char* argv[]) {
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

    char str[MAXCHAR];
    char *word;

    unsigned int max = 0;

    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        //printf("%s", str);

        //découpe en mots
        char delimiters[] = " \n,.';!:";
        word = strtok(str, delimiters);
        while (word != NULL)
        {
            if(strlen(word) > max) { max = strlen(word); }
            //=========================================================/
            //insérer dans la table de hashage, clé = word, valeur += 1
            //=========================================================/

            //printf("'%s'\n", word);
            word = strtok(NULL, delimiters);
        }    
    }

    printf("%i", max);

    fclose(fp);

    return 0;
}

