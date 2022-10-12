#include <stdio.h>
int main(int argc, char **argv)
{
    FILE *f;
    int m, n = 1, br2 = 0, x, y;

    while (n < argc)
    {
        while (1)
        {
            f = fopen(argv[n], "r+");
            br2 = 0;
            fread(&x, sizeof(int), 1, f);
            while (fread(&y, sizeof(int), 1, f) != 0)
            {
                m = ftell(f) - sizeof(int);
                if (x > y)
                {
                    br2 = 1;
                    fseek(f, m - sizeof(int), SEEK_SET);
                    fwrite(&y, sizeof(int), 1, f);
                    fwrite(&x, sizeof(int), 1, f);
                }
                fseek(f, m + sizeof(int), SEEK_SET);
                x = y;
            }
            if (br2 == 0)
                break;
            fclose(f);
        }
        n++;
    }

    for (n = 1; n < argc; n++)
    {
        f = fopen(argv[n], "r");
        while (fread(&x, sizeof(int), 1, f) != 0)
            printf("%d ", x);
            
        fclose(f);
        printf("\n");
    }
}