struct Node
{
    struct Node *prev, *next;
    char *elem;
};
struct List
{
    struct Node *first, *last;
};