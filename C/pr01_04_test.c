//#include <windows.h>
#include "pr01_04.c"

void printstr(struct List *Ls, int i)
{
    struct Node *unit = Ls->first,*lastn = Ls->last;
    int j;

    if(unit==NULL) return;
    while(unit!=lastn)
    {
        printf("%s ", unit->elem);
        unit = unit->next;
    }
    printf("%s ", unit->elem);
    printf("\n");
    return;
}
int main()
{
    char s[20];
    struct Node *unit;
    struct List *Ls; 
    int i = 0;

    Ls = (struct List *)malloc(sizeof(struct List));
    scanf("%s", &s);
    unit = (struct Node *)malloc(sizeof(struct Node));
    unit->elem = (char *)malloc(sizeof(char) * strlen(s));
    strcpy(unit->elem, s);
    Ls->first = unit;
    Ls->last = unit;
    do
    {
        scanf("%s", &s);
        if (s[0] == '.')
            break;
        i++;
        unit = (struct Node *)malloc(sizeof(struct Node));
        unit->elem = (char *)malloc(sizeof(char) * strlen(s));
        strcpy(unit->elem, s);
        unit->prev = Ls->last;
        Ls->last->next = unit;
        Ls->last = unit;
    } while (s[0] != '.');

    printstr(Ls, i + 1);

    printf("enter testing string:\n");
    scanf("%s", &s);

    process(Ls, s);
    printf("\nprocess done\n");
    printstr(Ls, i + 1);
    printf("\nno inturrupt\n");
}