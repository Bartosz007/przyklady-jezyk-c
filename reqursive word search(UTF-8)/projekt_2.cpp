
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#pragma warning (disable: 4996)

#define MAX_LINE 21
#define MAX_LINES 100

FILE* fd = NULL;
int ile_slow(char*);
void ex_ex(char*);
int szukaj(int, int, int, char*, char*);
int moj_srtcmp(char*, char*);
float check(char* slowo);

void asci() {
	char i = ' ';

	while (i++ < 255)
	{
		printf("%3d %c ", i, i);
		if (!((i - 32) % 4)) printf("\n");
	}
	printf("\n");
}

int main()
{

	setlocale(LC_ALL, "polish");
	//asci();
	printf("Podaj slowo:");

	char slowo[MAX_LINE], * dd;

	gets(slowo);

	char* d[MAX_LINES], bufor[MAX_LINE];
	int len, i, l;
	if (!(fd = fopen("tekst.txt", "r")))
	{
		ex_ex("Blad otwarcia zbioru\n");
	}

	i = 0;//od petli
	l = 0;//licznik słów

	while (i < MAX_LINES && fgets(bufor, MAX_LINE, fd))
	{
		len = strlen(bufor);
		bufor[len - 1] = '\0';
		if ((d[i] = (char*)malloc((unsigned)len)) == (char*)NULL)
		{
			ex_ex("Brak pamieci\n");
		}
		strcpy(d[i], bufor);
		//puts(bufor);
		l += ile_slow(d[i]);
		i++;
	}

	fclose(fd);
	fd = NULL;

	l = l - 1;
	//printf("%d", l);

	int wynik = szukaj(0, l, (int)l / 2, d, slowo);

	if (wynik > -1)
		printf("Wiersz tego slowa w tekscie: %d\n", wynik + 1);
	else
		printf("Tego slowa nie ma w tekscie\n");

	system("pause");

	return 1;

}

int szukaj(int start, int koniec, int srodek, char** tab, char* slowo) {

	int val = moj_srtcmp(tab[srodek], slowo);

	if (val == 0)
		return srodek;
	else if ((koniec - start) <= 0)
		return -1;
	else if (val > 0)
		szukaj(start, srodek - 1, (int)(start + (srodek - 1)) / 2, tab, slowo);
	else
		szukaj(srodek + 1, koniec, (int)((srodek + 1) + koniec) / 2, tab, slowo);

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

int moj_srtcmp(char* ciaga, char* ciagb) {
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

int ile_slow(char* te)
{
	char p, b = ' ';
	int l = 0;
	while (p = b, b = *te++)
		if (b != ' ' && p == ' ') l++;
	return(l);
}

void ex_ex(char* ex) {
	printf("%s", ex);
	exit(1);
}