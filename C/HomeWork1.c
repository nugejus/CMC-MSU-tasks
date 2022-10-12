#include<stdio.h>
#define Nums case '0' : NumberM[0]++; Numbers++; break;\
			 case '1' : NumberM[1]++; Numbers++; break;\
			 case '2' : NumberM[2]++; Numbers++; break;\
			 case '3' : NumberM[3]++; Numbers++; break;\
			 case '4' : NumberM[4]++; Numbers++; break;\
			 case '5' : NumberM[5]++; Numbers++; break;\
			 case '6' : NumberM[6]++; Numbers++; break;\
			 case '7' : NumberM[7]++; Numbers++; break;\
			 case '8' : NumberM[8]++; Numbers++; break;\
			 case '9' : NumberM[9]++; Numbers++; break

int Numbers=0,AlphabetS=0,AlphabetB=0,Others=0,Space=0;
int NumberM[11]={0,0,0,0,0,0,0,0,0,0};

void Count(int c);

int main()
{
	int c,i;
	while((c=getchar())!=EOF){
		Count(c);
	}
	printf("Numbers:%d AlphabetS:%d AlphabetB: %d\n Others: %d Space: %d\n",Numbers,AlphabetS,AlphabetB,Others,Space);

	for(i=0;i<=9;i++) printf("%d : %d\n",i,NumberM[i]);
	return 0;
}

void Count(int c)
{
	extern int Numbers,AlphabetS,AlphabetB,Others,Space;
		switch(c)
	{
		Nums;
		case 'a' ... 'z': AlphabetS++; break;
		case 'A' ... 'Z': AlphabetB++; break;
		case ' ' : Space++; break;
		default: Others++; break;
	}
}