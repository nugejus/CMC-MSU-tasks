#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "pr01_04struct.c"

void process(struct List *pl, const char *str)
{
    struct Node *sw, *p = pl->first, *lastn = pl->last;
    while (p != NULL)
    {
        printf("%s ", p->elem);
        Sleep(1000);
        if (p == pl->first) //if its head
        {
            if (pl->first == pl->last) //if only one structure
            {
                if (!strcmp(p->elem, str)) //if str==elem
                {
                    free(pl->first->elem);
                    free(pl);
                    p = pl->first = pl->last = NULL;
                }
                return;
            }
            if (!strcmp(p->elem, str)) //if str==elem
            {
                pl->first = pl->first->next;
                pl->first->prev = NULL;
                free(p->elem);
                free(p);
                p = pl->first;
            }
            else if (strcmp(p->elem, str) > 0) //str<elem
            {
                pl->last->next = pl->first;
                pl->first->prev = pl->last;
                pl->first = pl->first->next;
                pl->last = pl->last->next;
                pl->first->prev = NULL;
                pl->last->next = NULL;
                p = pl->first;
            }
            else
                p = p->next;
        }
        else //if its not head
        {
            if (p != lastn) //if not last structure
            {
                if (!strcmp(p->elem, str)) //if str==elem
                {
                    p->prev->next = p->next;
                    p->next->prev = p->prev;
                    sw = p;
                    p = p->next;
                    free(sw->elem);
                    free(sw);
                }
                else if (strcmp(p->elem, str) > 0) //str<elem
                {
                    p->prev->next = p->next;
                    p->next->prev = p->prev;
                    p->prev = pl->last;
                    pl->last->next = p;
                    p = p->next;
                    pl->last = pl->last->next;
                    pl->last->next = NULL;
                }
                else
                    p = p->next;
            }
            else
            {
                if (!strcmp(p->elem, str)) //if str==elem
                {
                    if (lastn == pl->last)
                    {
                        pl->last = pl->last->prev;
                        pl->last->next = NULL;
                    }
                    if (pl->first == lastn)
                        pl->first = pl->first->next;
                    free(p->elem);
                    free(p);
                }
                else if (strcmp(p->elem, str) > 0) //str<elem
                {
                    p->prev->next = p->next;
                    p->next->prev = p->prev;
                    p->prev = pl->last;
                    pl->last->next = p;
                    p = p->next;
                    pl->last = pl->last->next;
                    pl->last->next = NULL;
                }
                return;
            }
        }
    }
}