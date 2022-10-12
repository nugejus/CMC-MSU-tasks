#include <stdio.h>
int main()
{
    FILE *f;
    int a, b, i = 0;
    i=0;
    f = fopen("test.f", "r");
    while (i++ < 11)
    {
        b=fread(&a, sizeof(int), 1, f);
        printf("%d:%d ", b,a);
    }
    fclose(f);
}