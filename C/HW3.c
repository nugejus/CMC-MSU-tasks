#define MAXSIZE 100
#define LENGTH 20 //максмальная длина слова

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info
{
    int count;   //кол-во повторений слова в данном тексте
    char *alias; //синоним данного слова
};
struct elem
{
    char *word;
    struct info data;
};
struct
{
    struct elem *tabl[MAXSIZE];
    int number; //кол-во слов в словаре
} dictionary;

struct elem *create_word(int size, int asize, char w[], char al[])
{
    struct elem *cr;
    cr = (struct elem *)malloc(sizeof(struct elem));
    cr->word = (char *)malloc(sizeof(char) * size);
    strcpy(cr->word, w);
    cr->data.count = 1;
    cr->data.alias = (char *)malloc(sizeof(char) * asize);
    strcpy(cr->data.alias, al);
    return cr;
}

void dict_print(struct elem *tabl[], int number)
{
    int i;
    for (i = 0; i < number; i++)
    {
        printf("%s ", tabl[i]->word);
        if (*(tabl[i]->data.alias) != '0')
            printf("%s", tabl[i]->data.alias);
        printf("\n");
    }
}

int main()
{
    char word[LENGTH], alias[LENGTH];
    int i = 0;
    printf("enter 'word' 'alias'(0, if no alias: 'word' 0)\n");
    printf("to end typing enter '.' twice\n");
    dictionary.number = 0;
    while ((word[0] != '.') && (word[1] != '\0'))
    {
        scanf("%s %s", &word, &alias);
        if ((word[0] == '.') && (word[1] == '\0'))
            break;
        dictionary.tabl[i] = create_word(strlen(word), strlen(alias), word, alias);
        i++;
        dictionary.number++;
    }

    dict_print(dictionary.tabl, dictionary.number);
}