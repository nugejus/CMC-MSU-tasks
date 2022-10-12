#include <stdio.h>
void MoveAndPut(FILE *f, int a, int location)
{
    int b;
    fseek(f, location, SEEK_SET);

    while (fread(&b, sizeof(int), 1, f) != NULL)
    {
        fwrite(&a, sizeof(int), 1, f);
        a = b;
    }
    fwrite(&a, sizeof(int), 1, f);
    return 0;
}

int main(int argc, char **argv)
{
    int i, a, b;
    FILE *f1, *f2;

    f1 = fopen(argv[1], "r+");
    i = 2;
    while (i < argc)
    {
        f2 = fopen(argv[i], "r");
        fread(&a, sizeof(int), 1, f2);
        while (fread(&b, sizeof(int), 1, f1) != NULL)
        {
            if (b > a)
                MoveAndPut(f1,a,ftell(f1));
        }
    }
}