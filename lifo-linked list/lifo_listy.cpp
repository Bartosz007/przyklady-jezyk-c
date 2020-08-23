
#include <stdio.h>
#include <string.h>
#pragma warning (disable: 4996)

typedef struct MY_DATA {
	char *name;
	char *lastname;
	int year;
	struct MY_DATA *n;
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

MY_DATA *H;

void menu();
void push();
void pop();
void clear();
void wyswietl();
void find_lastname();

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

	if (H == (MY_DATA *)NULL)
	{
		H = B;
		B->n = NULL;
	}
	else
	{
		B->n = H;
		H = B;
	}

	printf("imie, nazwisko, rok\n");

	scanf("%s", bufor);
	len = (unsigned)strlen(bufor);
	bufor[len ] = '\0';
	B->name = (char*)malloc(len);
	strcpy(B->name, bufor);

	scanf("%s", bufor);
	len = (unsigned)strlen(bufor);
	bufor[len ] = '\0';
	B->lastname = (char*)malloc(len);
	strcpy(B->lastname, bufor);


	scanf("%d", &year);
	B->year = year;

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
	w = H->n;
	free(H);
	H = w;
	wyswietl();
}

void clear()
{
	MY_DATA *w = H;
	while ((MY_DATA *)w)
	{
		w = H->n;
		free(H);
		H = w;
	}
}

void wyswietl()
{
	MY_DATA *wsk = NULL;
	for (wsk = H; wsk != (MY_DATA *)NULL; wsk = wsk->n)
	{
		printf("%-12s \t %-12s \t %-10d \t %-10d \n", wsk->name, wsk->lastname, wsk->year, wsk->n);
	}
}

void find_lastname() {
	char bufor[512];
	char *nazwisko;

	scanf("%s", bufor);
	size_t len = (unsigned)strlen(bufor);
	bufor[len ] = '\0';
	nazwisko = (char*)malloc(len);
	strcpy(nazwisko, bufor);

	MY_DATA *wsk = NULL;
	for (wsk = H; wsk != (MY_DATA *)NULL; wsk = wsk->n)
	{
		if (!strcmp(wsk->lastname, nazwisko)) {
			printf("%-12s \t %-12s \t %-10d \t %-10d \n", wsk->name, wsk->lastname, wsk->year, wsk->n);
			return;
		}
	}
	printf("Nie ma takiego nazwiska w kolejce...\n");
	
}