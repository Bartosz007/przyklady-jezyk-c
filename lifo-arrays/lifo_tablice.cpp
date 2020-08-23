#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning (disable: 4996)

typedef struct MY_DATA {
	char *name;
	char *lastname;
	int year;
}MY_DATA;

enum MY_INTERF_EN
{
	INTERF_PUSH = 1,
	INTERF_POP,
	INTERF_CLEAR,
	INTERF_FIND_LASTNAME,
	INTERF_STOP,
	INTERF_TOT
};

void menu();
void push();
void pop();
void clear();
void wyswietl();
void find_lastname();

MY_DATA *H;
size_t n;

int main()
{
	size_t op = 1; //bez znaku int, więc %d - to samo co unsigned int

	while (op >= INTERF_PUSH && op <= INTERF_STOP)
	{
		menu();
		scanf("%d", &op);

		switch (op)
		{
		case INTERF_PUSH:
			push();
			break;
		case INTERF_POP:
			pop();
			break;
		case INTERF_CLEAR:
			clear();
			break;
		case INTERF_FIND_LASTNAME:
			find_lastname();
			break;
		case INTERF_STOP:
			clear();
			return 0;
		default:
			printf("nieuznawalny kod operacji\n");
		}
	}

}

void menu()
{
	printf("Wybierz opcje 1-dodaj, 2-usun, 3-wyczysc, 4-szukaj nazwiska, 5-zatrzymaj:\n");
}

void push()
{
	unsigned int len;
	size_t year;
	char bufor[512];
	MY_DATA *B = (MY_DATA *)NULL;
	B = (MY_DATA *)malloc(sizeof(MY_DATA));

	printf("imie, nazwisko, rok\n");

	scanf("%s", bufor);
	len = (unsigned)strlen(bufor);
	bufor[len] = '\0';
	B->name = (char*)malloc(len);
	strcpy(B->name, bufor);

	scanf("%s", bufor);
	len = (unsigned)strlen(bufor);
	bufor[len] = '\0';
	B->lastname = (char*)malloc(len);
	strcpy(B->lastname, bufor);

	scanf("%d", &year);
	B->year = year;

	if (H == (MY_DATA *)NULL)
	{
		H = B;
		n = 1;
	}
	else
	{

		n++;
		H = (MY_DATA *)realloc(H, n * sizeof(MY_DATA));
		H[n - 1].name = B->name;
		H[n - 1].lastname = B->lastname;
		H[n - 1].year = B->year;
	}

	wyswietl();
}

void pop()
{
	MY_DATA *w = NULL;
	if (H == (MY_DATA *)NULL)
	{
		printf("Stos pusty!\n");
		return;
	}
	else if (n == 1) {
		free(H);
		n = 0;
		H = (MY_DATA *)NULL;
	}
	else {
		
		n--;
		H = (MY_DATA *)realloc(H, n * sizeof(MY_DATA));
	}

	wyswietl();
}

void clear()
{
	if (H != (MY_DATA *)NULL) {
		free(H);
		H = (MY_DATA *)NULL;
		n = 0;
	}

}

void wyswietl()
{
	for (int i = n-1; i >=0; i--)
	{
		printf("%-12s \t %-12s \t %-10d \n", H[i].name, H[i].lastname, H[i].year);
	}
}

void find_lastname() {
	char bufor[512];
	char *nazwisko;

	scanf("%s", bufor);
	size_t len = (unsigned)strlen(bufor);
	bufor[len] = '\0';
	nazwisko = (char*)malloc(len);
	strcpy(nazwisko, bufor);

	for (int i = 0; i < n; i++)
	{
		if (!strcmp(H[i].lastname, nazwisko)) {
			printf("%-12s \t %-12s \t %-10d  \n", H[i].name, H[i].lastname, H[i].year);
			return;
		}
	}
	printf("Nie ma takiego nazwiska w kolejce...\n");

}