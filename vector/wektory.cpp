#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning (disable: 4996)

struct MY_VECTOR
{
	int dim;
	char str[64];
	double *buff;
};
int main()
{
	struct MY_VECTOR tab[2];	//x i y
	int n, len;
	double s = 0;
	char bufor[64];

	printf("Podaj n: \n");
	scanf("%d", &n);
	//getchar();	//łap enter;
	tab[0].dim = n;
	tab[1].dim = n;

	printf("Podaj nazwe wekt x\n");
	fgets(bufor, 64, stdin);
	len = (unsigned)strlen(bufor);
	bufor[len - 1] = '\0';
	strcpy(tab[0].str, bufor);

	scanf("%s", tab[0].str); 
	getchar();

	tab[0].buff = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		tab[0].buff[i] = 1. / (i + 1);

	printf("Podaj nazwe wekt y\n");
	fgets(bufor, 64, stdin);
	len = (unsigned)strlen(bufor);
	bufor[len - 1] = '\0';
	strcpy(tab[1].str, bufor);

	tab[1].buff = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		tab[1].buff[i] = (double)i + 1;

	for (int i = 0; i < n; i++) 
		s = s + tab[0].buff[i] * tab[1].buff[i];


	printf("s=%lf \n", s);
	printf("%d - %s - %lf", tab[1].dim, tab[1].str, tab[1].buff[0]);

	return 0;
}
