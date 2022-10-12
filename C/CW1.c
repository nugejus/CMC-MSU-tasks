#include <stdio.h>
#include <stdlib.h>

struct lnode
{
    char *str;
    struct lnode *next;
}

struct lnode *IN(struct lnode *l, char *w)
{
    struct lnode *p = l, *head = l, *t;

    while (l != null)
    {
        if (!strcmp(l->str, w))
        {
            if (p == l) //the node is head
            {
                t = (struct lnode *)malloc(sizeof(struct lnode));
                t->str = (char *)malloc(strlen(w) * 2 + 1);
                strcpy(t->str, w);
                strcpy(t->str + strlen(w), w);
                t->next=l;
                head=t;
                l=p->next;
            }
            else
            {
                t = (struct lnode *)malloc(sizeof(struct lnode));
                t->str = (char *)malloc(strlen(w) * 2 + 1);
                strcpy(t->str, w);
                strcpy(t->str + strlen(w), w);
                t->next=l;
                p->next=t;
                p=l;
                l=l->next;
            }
        }
        else
        {
            p = l;
            l = l->next;
        }
    }
    return head;
}

void IN2(struct lnode **l,char *w)
{
    struct lnode *p = *l, *head = *l, *t;
    while(l!=null)
    {
        if (!strcmp((*l)->str, w))
        {
            if (p == *l) //the node is head
            {
                t = (struct lnode *)malloc(sizeof(struct lnode));
                t->str = (char *)malloc(strlen(w) * 2 + 1);
                strcpy(t->str, w);
                strcpy(t->str + strlen(w), w);
                t->next=*l;
                head=t;
                *l=p->next;
            }
            else
            {
                t = (struct lnode *)malloc(sizeof(struct lnode));
                t->str = (char *)malloc(strlen(w) * 2 + 1);
                strcpy(t->str, w);
                strcpy(t->str + strlen(w), w);
                t->next=*l;
                p->next=t;
                p=*l;
                *l=(*l)->next;
            }
        }
        else
        {
            p = *l;
            *l = *(l)->next;
        }
    }
}