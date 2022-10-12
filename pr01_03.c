#include <stdio.h>
#include <stdlib.h>
void SpaceLoop(int i, int j, int n)
{
    int k, l;
    long long m;
    //행*열의 자릿수 구하기
    for (l = 0, m = 1; abs((((long long)i * j) / m)) > 0; l++, m *= 10)
        ;
        if(l>n) return;
    //공백 출력, {요구공백수}-{자릿수}-{1:음수,0:양수}-{1:0,0:1}
    for (k = 0; k < n - l - ((long long)i * j < 0) - ((long long)i * j == 0); k++, printf(" "))
        ;
    return;
}

int main()
{
    int a, b, n; //입력 변수
    int i, j;    //루프 변수

    scanf("%d %d %d", &a, &b, &n);

    SpaceLoop(0,0,n+1);
    for(i=a;i<b;i++){SpaceLoop(i,1,n);printf(" %d",i);}
    printf("\n");
    for (i = a; i < b; i++) //행
    {
        SpaceLoop(i, 1, n);
        printf("%d", i);
        for (j = a; j < b; j++) //열
        {
            SpaceLoop(i, j, n);
            printf(" %lld", (long long)i * j);
        }

        printf("\n");
    }
    return 0;
}