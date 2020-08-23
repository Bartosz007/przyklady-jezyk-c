
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>/
#pragma warning (disable: 4996)
#define MAX_BUFOR 100

typedef struct stud {
	char *imie;
	char *nazwisko;
	int rok;
	char *adres;
	double stypendium;
	struct stud *n;
	struct stud *p;
}STUDENT;

STUDENT *H, *P;
FILE *fd = NULL;
void list1(FILE *);
STUDENT *najwiekszeStypendium();
STUDENT *DodajDane();
//1 zajecia
void wypiszListe();
void wypiszListeOdTylu();
void dodajNaPoczatku();
void dodajNaKoncu();
int licz();
void usunNaPoczatku();
void usunNaKoncu();
//2 zajęcia
void sortujListe(char *tab);
void dodajDowolnie(char *tab);

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
	printf("\n-------------\n");
	//wypiszListeOdTylu();
	//printf("\n");
	//dodajNaPoczatku();
	//dodajNaKoncu();
	//printf("Dlugosc listy: %d\n", licz());
	//usunNaPoczatku();
	//usunNaKoncu();
	//
	char nazwa[20];
	printf("Sortowanie po: imie, nazwisko, adres, rok, stypendium\n");
	gets(nazwa);

	sortujListe(nazwa);

	wypiszListe();
	dodajDowolnie(nazwa);
	//wypiszListeOdTylu();
	wypiszListe();
	system("pause");
	return 0;
}

void list1(FILE *plik) {

	unsigned len;
	STUDENT *B = NULL;
	char bufor[MAX_BUFOR];
	H = (STUDENT *)NULL;
	P = (STUDENT *)NULL;
	while (fgets(bufor, MAX_BUFOR, fd)) {
		B = (STUDENT *)malloc(sizeof(STUDENT));

		if (H == (STUDENT *)NULL) {
			H = B;
			B->p = 0;
		}
		else {
			P->n = B;
			B->p = P;
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
		printf("%-12s %-12s %-10d %-35s %-10.2lf %-10d %-10d %-10d\n", wsk->imie, wsk->nazwisko, wsk->rok, wsk->adres, wsk->stypendium, wsk->n, wsk, wsk->p);
	}

}

void wypiszListeOdTylu() {
	STUDENT *wsk = NULL;
	for (wsk = P; wsk != (STUDENT *)NULL; wsk = wsk->p) {
		printf("%-12s %-12s %-10d %-35s %-10.2lf %-10d %-10d %-10d\n", wsk->imie, wsk->nazwisko, wsk->rok, wsk->adres, wsk->stypendium, wsk->n, wsk, wsk->p);
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

	printf("Podaj stypendium: ");
	fgets(bufor, MAX_BUFOR, stdin);
	A->stypendium = atof(bufor);


	return A;

}

void dodajNaPoczatku() {
	STUDENT *A = DodajDane();
	H->p = A;
	A->n = H;
	A->p = 0;
	H = A;
}

void dodajNaKoncu() {
	STUDENT *A = DodajDane();
	STUDENT *wsk = NULL;

	for (wsk = H; wsk != (STUDENT *)NULL; wsk = wsk->n) {
		STUDENT *wskb = wsk->n;

		if (wskb->n == 0) {
			wskb->n = A;
			A->n = 0;
			A->p = wsk;
			P = A;
			break;
		}
	}

}

void dodajDowolnie(char *tab) {
	STUDENT *A = DodajDane();
	STUDENT *B, *A0, *A1, *A2;
	int warunek;

	for (B = H; B != (STUDENT *)NULL; B = B->n) {

		A0 = B->p;
		A1 = B;
		A2 = B->n;

		warunek = moj_strcmp(A->imie, A1->imie);

		if (!strcmp(tab, "imie")) {
			warunek = moj_strcmp(A->imie, A1->imie);
			if (warunek > 0)
				warunek = 0;
		}
		else if (!strcmp(tab, "nazwisko")) {
			warunek = moj_strcmp(A->nazwisko, A1->nazwisko);
			if (warunek > 0)
				warunek = 0;
		}
		else if (!strcmp(tab, "adres")) {
			warunek = moj_strcmp(A->adres, A1->adres);
			if (warunek > 0)
				warunek = 0;
		}
		else if (!strcmp(tab, "rok")) {
			warunek = A1->rok > A->rok;
		}
		else if (!strcmp(tab, "stypendium")) {
			warunek = A1->stypendium > A->stypendium;
		}
		else {
			printf("Podales zly kod::::\n");
		}


		if (warunek <= 0) {

			if (A0 == (STUDENT *)0) {
				A->p = 0;
				A->n = H;//H=A1;
				A1->p = A;
				H = A;
			}
			else {
				A0->n = A;
				A->p = A0;
				A->n = A1;
				A1->p = A;
			}

			break;
		}
		else if (A2 == (STUDENT *)0) {//nie wchodzi w warunek przez to && B->n->n!=(STUDENT*)NULL

			A->n = 0;
			A->p = A1;
			A1->n = A;
			P = A;

			break;
		}

		/*
		int warunek;
		if (!strcmp(tab, "imie")) {
			warunek = strcmp(A2->imie, A1->imie);
			if (warunek > 0)
				warunek = 0;
		}
		else if (!strcmp(tab, "nazwisko")) {
			warunek = strcmp(A2->nazwisko, A1->nazwisko);
			if (warunek > 0)
				warunek = 0;
		}
		else if (!strcmp(tab, "adres")) {
			warunek = strcmp(A2->adres, A1->adres);
			if (warunek > 0)
				warunek = 0;
		}
		else if (!strcmp(tab, "rok")) {
			warunek = A2->rok > A1->rok;
		}
		else if (!strcmp(tab, "stypendium")) {
			warunek = A2->stypendium > A1->stypendium;
		}
		else {
			printf("Podales zly kod::::\n");
		}
		*/
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
	H->p = 0;
	free(U);
}

void usunNaKoncu() {
	STUDENT *wsk = NULL;
	for (wsk = H; wsk != (STUDENT *)NULL; wsk = wsk->n) {
		STUDENT *wskb = wsk->n;

		if (wskb->n == 0) {
			wsk->n = 0;
			free(wskb);
			P = wsk;
		}
	}
}

void sortujListe(char *tab) {

	STUDENT *B, *A0, *A1, *A2, *A3;

	int is;

	do {
		is = 0;
		B = H;
		while (B->n != (STUDENT *)0) {
			A0 = B->p;
			A1 = B;
			A2 = B->n;
			A3 = A2->n;

			int warunek;
			if (!moj_strcmp(tab, "imie")) {
				warunek = moj_strcmp(A2->imie, A1->imie);
				if (warunek > 0)
					warunek = 0;
			}
			else if (!moj_strcmp(tab, "nazwisko")) {
				warunek = moj_strcmp(A2->nazwisko, A1->nazwisko);
				if (warunek > 0)
					warunek = 0;
			}
			else if (!moj_strcmp(tab, "adres")) {
				warunek = moj_strcmp(A2->adres, A1->adres);
				if (warunek > 0)
					warunek = 0;
			}
			else if (!moj_strcmp(tab, "rok")) {
				warunek = A2->rok > A1->rok;
			}
			else if (!moj_strcmp(tab, "stypendium")) {
				warunek = A2->stypendium > A1->stypendium;
			}
			else {
				printf("Podales zly kod::::\n");
				return;
			}


			if (warunek) {
				is++;
				if (A0 == (STUDENT *)0)
					H = A2;
				else
					A0->n = A2;

				A1->p = A2;
				A1->n = A3;
				A2->p = A0;
				A2->n = A1;

				if (A3 == (STUDENT *)0)
					P = A1;
				else
					A3->p = A1;

				B = A1;

			}
			else
				B = A2;
		}

	} while (is);

}

float check(float litera) {
	float zwrot = litera;

	if (litera == -120 || litera == -77)//ł
		zwrot = 108.5;
	else if (litera == -99 || litera == -93)//Ł
		zwrot = 76.5;
	else if (litera == -87 || litera == -22)//ę
		zwrot = 101.5;
	else if (litera == -88 || litera == -54)//Ę
		zwrot = 69.5;
	else if (litera == -191 || litera == -71)//ą
		zwrot = 97.5;
	else if (litera == -92 || litera == -91)//Ą
		zwrot = 65.5;
	else if (litera == -94 || litera == -13)//ó
		zwrot = 111.5;
	else if (litera == -32 || litera == -45)//Ó
		zwrot = 79.5;
	else if (litera == -66 || litera == -65)//ż
		zwrot = 122.5;
	else if (litera == -67 || litera == -81)//Ż
		zwrot = 90.5;
	else if (litera == -104 || litera == -100)//ś
		zwrot = 115.5;
	else if (litera == -105 || litera == -116)//Ś
		zwrot = 83.5;
	else if (litera == -122 || litera == -26)//ć
		zwrot = 99.5;
	else if (litera == -114 || litera == -58)//Ć
		zwrot = 67.5;
	else if (litera == -28 || litera == -15)//ń
		zwrot = 110.5;
	else if (litera == -29 || litera == -47)//Ń
		zwrot = 78.5;
	else if (litera == -85 || litera == -97)//ź
		zwrot = 122.5;
	else if (litera == -115 || litera == -113)//Ź
		zwrot = 90.25;

	return zwrot;
}

int moj_strcmp(char *ciaga, char* ciagb) {
	int i = 0;
	while (i < (int)strlen(ciaga) && i < (int)strlen(ciagb)) {
		float val1 = (float)ciaga[i];
		float val2 = (float)ciagb[i];
		float a = val1;
		if (val2 == -113)//kolizja znaków Ź i Ć
			val2 = -114;
		if (val2 == -91)//kolizja znaków Ą i ą
			val2 = -191;

		//printf("%c - %c\n", ciaga[i], ciagb[i]);

		if (val1 < 0)
			val1 = check(val1);
		if (val2 < 0)
			val2 = check(val2);

		//	printf("%f - %f\n", val1, val2);


		if (val1 > val2)
			return 1;
		else if (val1 < val2)
			return -1;


		i++;
	}

	if (strlen(ciaga) == strlen(ciagb))
		return 0;
	else if (strlen(ciaga) > strlen(ciagb))
		return 1;
	else if (strlen(ciaga) < strlen(ciagb))
		return -1;
}