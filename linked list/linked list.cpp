
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#pragma warning (disable: 4996)
#define MAX_BUFOR 100

typedef struct stud {
	char *imie;
	char *nazwisko;
	int rok;
	char *adres;
	double stypendium;
	struct stud *n;
}STUDENT;

STUDENT *H;
FILE *fd = NULL;
void list1(FILE *);
STUDENT *najwiekszeStypendium();
STUDENT *DodajDane();

void wypiszListe();
void dodajNaPoczatku();
void dodajNaKoncu();
int licz();
void usunNaPoczatku();
void usunNaKoncu();

int main()
{
	setlocale(LC_ALL, "polish");

	fd = fopen("dane.txt", "r");
	list1(fd);

	if (H == NULL)
		return 1;

	/*
	STUDENT *stypendium = najwiekszeStypendium();
	printf("\nUczen roku: %-12s %-12s %-10d %-40s %-10.2lf %-10d\n", stypendium->imie, stypendium->nazwisko,
		stypendium->rok, stypendium->adres, stypendium->stypendium, stypendium->n);
		*/

	wypiszListe();
	printf("PO\n");
	//dodajNaPoczatku();
	//dodajNaKoncu();
	//printf("Dlugosc listy: %d\n", licz());
	usunNaKoncu();
	wypiszListe();

	system("pause");
	return 0;
}

void list1(FILE *plik) {

	unsigned len;
	STUDENT *B = NULL, *P = NULL;
	char bufor[MAX_BUFOR];
	H = (STUDENT *)NULL;
	while (fgets(bufor, MAX_BUFOR, fd)) {
		B = (STUDENT *)malloc(sizeof(STUDENT));

		if (H == (STUDENT *)NULL) {
			H = B;
		}
		else {
			P->n = B;
		}

		B->n = (STUDENT *)NULL;

		len = (unsigned)strlen(bufor);
		bufor[len - 1] = '\0';
		B->imie = (char*)malloc(len);
		strcpy(B->imie, bufor);

		if (fgets(bufor, MAX_BUFOR, fd) == (char*)NULL)break;
		len = (unsigned)strlen(bufor);
		bufor[len - 1] = '\0';
		B->nazwisko = (char*)malloc(len);
		strcpy(B->nazwisko, bufor);

		if (fgets(bufor, MAX_BUFOR, fd) == (char*)NULL) break;
		B->rok = atoi(bufor);

		if (fgets(bufor, MAX_BUFOR, fd) == (char*)NULL)break;
		len = (unsigned)strlen(bufor);
		bufor[len - 1] = '\0';
		B->adres = (char*)malloc(len);
		strcpy(B->adres, bufor);

		if (fgets(bufor, MAX_BUFOR, fd) == (char*)NULL) break;
		B->stypendium = atof(bufor);

		P = B;//ważne
	}

}

STUDENT *najwiekszeStypendium() {
	STUDENT *wsk = NULL;
	int max = 0;

	for (wsk = H; wsk != (STUDENT *)NULL; wsk = wsk->n) {
		if (wsk->stypendium > max)
			max = wsk->stypendium;
	}

	for (wsk = H; wsk != (STUDENT *)NULL; wsk = wsk->n)
		if (wsk->stypendium == max)
			return wsk;

}

void wypiszListe() {

	STUDENT *wsk = NULL;
	for (wsk = H; wsk != (STUDENT *)NULL; wsk = wsk->n) {
		printf("%-12s %-12s %-10d %-40s %-10.2lf %-10d\n", wsk->imie, wsk->nazwisko, wsk->rok, wsk->adres, wsk->stypendium, wsk->n);
	}

}

STUDENT *DodajDane() {
	STUDENT *A = NULL;
	A = (STUDENT *)malloc(sizeof(STUDENT));
	unsigned len;
	char bufor[MAX_BUFOR];

	printf("Dodaj uzytkownika\nPodaj imie: ");
	fgets(bufor, MAX_BUFOR, stdin);
	len = (unsigned)strlen(bufor);
	bufor[len - 1] = '\0';
	A->imie = (char*)malloc(len);
	strcpy(A->imie, bufor);

	printf("Podaj nazwisko: ");
	fgets(bufor, MAX_BUFOR, stdin);
	len = (unsigned)strlen(bufor);
	bufor[len - 1] = '\0';
	A->nazwisko = (char*)malloc(len);
	strcpy(A->nazwisko, bufor);

	printf("Podaj rok urodzenia: ");
	fgets(bufor, MAX_BUFOR, stdin);
	A->rok = atoi(bufor);

	printf("Podaj adres: ");
	fgets(bufor, MAX_BUFOR, stdin);
	len = (unsigned)strlen(bufor);
	bufor[len - 1] = '\0';
	A->adres = (char*)malloc(len);
	strcpy(A->adres, bufor);

	printf("Podaj rok stypendium: ");
	fgets(bufor, MAX_BUFOR, stdin);
	A->stypendium = atof(bufor);


	return A;

}

void dodajNaPoczatku() {
	STUDENT *A = DodajDane();
	A->n = H;
	H = A;
}

void dodajNaKoncu() {
	STUDENT *A = DodajDane();
	STUDENT *wsk = NULL;
	for (wsk = H; wsk != (STUDENT *)NULL; wsk = wsk->n) {
		if (wsk->n == 0) {
			wsk->n = A;
			A->n = 0;
		}
	}
}

int licz() {
	STUDENT *wsk = NULL;
	int licznik = 0;
	for (wsk = H; wsk != (STUDENT *)NULL; wsk = wsk->n, licznik++);

	return licznik;
}

void usunNaPoczatku() {
	STUDENT *U = NULL;
	U = H;
	H = H->n;
	free(U);
}

void usunNaKoncu() {
	STUDENT *wsk = NULL;
	for (wsk = H; wsk != (STUDENT *)NULL; wsk = wsk->n) {
		STUDENT *wskb = wsk->n;

		if (wskb->n == 0) {
			wsk->n = 0;
			free(wskb);
		}
	}
}