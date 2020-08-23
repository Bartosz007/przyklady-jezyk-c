
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning (disable: 4996)
#define LP 100000000

//sort
 void sort_wstawianie(int *, int);
 void sort_selekcja(int *, int);
 void sort_babelkowe(int *, int);
 void sort_quicksort(int *, int);
 int dzielenie(int *, int, int);
 void sort_shell(int *, int n);

 void kopanie_kopca(int *, int, int);
 void sort_kopcowanie(int *, int);

//utils
 void wpisz_do_pliku(int *, int);
 void swap(int *, int, int);
 void wypisz(int *, int);
 void t_dane(int*, int, int);

int main(int argc, char **argv)
{
	int metoda = 0;			//0-wstawianie,1-selekcja,2-bąbelkowe,3-quicksort,4-shell,5-kopcowanie
	int typ_danych = 0;		//0-losowe,1-posortowane malejąco, 2-posortowane rosnąco
	int n = 10;			//liczba polowy elementow

	printf("Podaj rozmiar tablicy: ");
	scanf("%d", &n);	//zmienna od rozmiaru tablicy

	FILE *dane;			//zmienna od pliku
	dane = fopen("dane.txt", "w");  //otwacie pliku w trybie zapisu

	while (metoda < 6) {	//pętla, dzięki której program sortuje na 6 sposobów
		typ_danych = 0;

		while (typ_danych < 3) {  //pętla, dzięki której program sortuje 3 typy danych

			int *tab;
			tab = (int *)malloc(sizeof(int *) * n);  //dynamiczna alokacja pamięci na tablicę
			t_dane(tab, n, typ_danych);		//wpisanie do tablicy danych (tablica,liczba elementów tablicy,typ danych)

			char *metoda_char[20];  //zmienna, dzięki której program wypisuje tekstowo metodę sortowania

			clock_t start, stop;    //typ zmiennej, która przechowuje liczbę cykli procesora od uruchomienia programu

			switch (metoda) {  //switch, w zależności od zmiennej metoda, program wykonuje sortowanie odpowiednią metodą
			case 0:
				*metoda_char = "Wstawianie";
				start = clock();        //pobranie cyklu procesora przed wykonaniem sortowania
				sort_wstawianie(tab, n);  //wywołanie sortowania, w tym przypadku przez wstawianie
				stop = clock();	        //pobranie cyklu procesora po wykonaniu sortowania
				break;
			case 1:
				*metoda_char = "Selekcja";
				start = clock();
				sort_selekcja(tab, n);
				stop = clock();
				break;
			case 2:
				*metoda_char = "Babelkowe";
				start = clock();
				sort_babelkowe(tab, n);
				stop = clock();
				break;
			case 3:
				*metoda_char = "Quicksort";
				start = clock();
				sort_quicksort(tab, 0, n - 1);
				stop = clock();
				break;
			case 4:
				*metoda_char = "Shell   ";
				start = clock();
				sort_shell(tab, n);
				stop = clock();
				break;
			case 5:
				*metoda_char = "Kopcowanie";
				start = clock();
				sort_kopcowanie(tab, n);
				stop = clock();
				break;
			}


			char *typ_danych_char[20];   //zmienne od typu danych
			if (typ_danych == 0) {
				wpisz_do_pliku(tab, n);  //po wykonaniu sortowania tablica tab jest posortowana, więc wpisujemy ją do pliku
				*typ_danych_char = "losowe";
			}
			else if (typ_danych == 1)
				*typ_danych_char = "malejaco";
			else if (typ_danych == 2)
				*typ_danych_char = "rosnaco";

			free(tab);  //zwolnienie pamięci tablicy

			double czas = (double)(stop - start) / CLOCKS_PER_SEC;  //obliczenie czasu trwania sortowania poszczególnymi metodami
			printf("l_danych: %-12d \ttyp danych: %s \tmetoda: %s \t czas %10.3lf\n", n, *typ_danych_char, *metoda_char, czas);//wypisanie danych w konsoli
			fprintf(dane, "l_danych: %-12d \ttyp danych: %s \tmetoda: %s \t czas %10.3lf\n", n, *typ_danych_char, *metoda_char, czas);//wpisanie danych do pliku

			typ_danych++;
		}
		metoda++;
	}



	fclose(dane);	//zamknięcie pliku
	system("pause");

	return 1;
}


void sort_wstawianie(int *tab, int n) {

	int i, x, j;
	for (i = 1; i < n; i++) // główna pętla przelatująca od 2 elementu tablicy do ostatniego
	{
		x = tab[i];//zmienne pomocnicz
		j = i - 1;
		while (tab[j] > x && j >= 0) 
		{
			tab[j + 1] = tab[j];
			j--;
		}
		tab[j + 1] = x;

	}
}

void sort_selekcja(int *tab, int n) {

	int min = 0, max = 0;

	for (int i = 0; i < (n - i); i++) {
		min = i;
		max = i;
		for (int j = i + 1; j < (n - i); j++) {//funckja sprawadza jednocześnie najmniejszy element tablicy i największy
			if (tab[j] < tab[min])
				min = j;
			if (tab[j] > tab[max])
				max = j;
		}
		swap(tab, i, min); //potem je zamienia miejscami

		swap(tab, n - 1 - i, max);		//bo ostatni element w tablicy tab ma indeks n-1

	}
}

void sort_babelkowe(int *tab, int n) {

	for (int i = 0; i < n - 1; i++) {
		int k = n -  1;

		for (int j = 0; j < k; j++, k--) {//bubble sort, porównuje odrazu dwie pary sąsiadujących elementów
			if (tab[j + 1] < tab[j]) {		//od początku
				swap(tab, j, j + 1);
			}

			if (tab[k - 1] > tab[k]) {		//od końca
				swap(tab, k, k - 1);
			}
			
		}

	}
}

void sort_quicksort(int *tab, int s, int n) {
	if (n <= s) return;

	int i = s - 1, j = n + 1,
		pivot = tab[(s + n) / 2]; //wybieramy pivot, w tym przypadku element środkowy tablicy

	while (1)
	{
		while (pivot > tab[++i]);  //

		while (pivot < tab[--j]);
		if (i <= j)
			swap(tab, i, j); //zamiana dwóch elementów tablicy o indeksach ioraz j
		else
			break;
	}

	if (j > s)
		sort_quicksort(tab, s, j);  //wywołanie rekurencyjne dla lewej części tablicy
	if (i < n)
		sort_quicksort(tab, i, n);  //wywołanie rekurencyjne dla prawej części tablicy
}

void sort_shell(int *tab, int n) {
	int d = n / 2;		//orginalne sortowanie shella, gdzie d = n/2^k
	while (d >= 1) {
		for (int i = d; i < n; i++) {
			int tmp = tab[i];
			int j = i;
			while (j >= d && tab[j - d] > tmp) {//jesli j<d, to braknie tablicy, tab[j-d] - sprawdzanie wsteczne wielkosci
				tab[j] = tab[j - d];
				j = j - d;
			}
			tab[j] = tmp;
		}
		d = d / 2;
	}
}

void kopanie_kopca(int *tab, int n, int i)
{
	int max = i;		//rodzic
	int l = 2 * i + 1; //lewe dziecko
	int r = 2 * i + 2; //prawe dziecko

	if (l < n && tab[l] > tab[max]) //sprawdzanie czy lewe dziecko jest większe od tego więszkego
		max = l;

	if (r < n && tab[r] > tab[max]) //sprawdzanie czy prawe dziecko jest większe od tego większego
		max = r;

	if (max != i) // jeśli ten maksymalny 
	{
		swap(tab, i, max);  //zamiana 2 elementów tablicy i oraz max
		kopanie_kopca(tab, n, max); //wywołanie rekurencyjne funkcji która będzie budować kopiec
	}
}
void sort_kopcowanie(int *tab, int n)
{

	for (int i = n / 2 - 1; i >= 0; i--)
		kopanie_kopca(tab, n, i);//pierwsze wywołanie funkcji rekurencyjne, zaczynając od ostatniego rodzica

	for (int i = n - 1; i >= 0; i--)
	{
		swap(tab, 0, i);
		kopanie_kopca(tab, i, 0);
	}
}

void wypisz(int *tab, int n) {//funkcja wypisująca w konsoli tablice o długości n
	for (int i = 0; i < n; i++) {
		printf("%d ", tab[i]);
	}
	printf("\n");
}

void wpisz_do_pliku(int *tab, int n) {//funckja, która otrzymuje dane posortowane i wpisuje je do pliku

	FILE *fASC;//zmienne plikowe
	FILE *fDESC;

	if (!(fASC = fopen("posortowaneASC.txt", "w")))//otwarcie pliku w trypie zapisu
	{
		printf("Blad otwarcia zbioru\n");
		exit(1);
	}

	if (!(fDESC = fopen("posortowaneDESC.txt", "w")))//otwarcie pliku w trypie zapisu
	{
		printf("Blad otwarcia zbioru\n");
		exit(1);
	}

	for (int i = 0; i < n; i++) {	//wpisanie danych do pliku
		fprintf(fASC, "%d ", tab[i]);	//ascending
		fprintf(fDESC, "%d ", -tab[i]);	//descending
		//fprintf(fDESC, "%d ", tab[n-1-i]);	//jak daję tak to zapisują się krzaki 
	}

	fclose(fASC);	//zamknięcie plików
	fclose(fDESC);

	//printf("Zapisano do plikow posortowane dane\n");
}

void swap(int *tab, int a, int b) {//funckja zamieniająca wartości w tablicy
	int tmp = tab[a];
	tab[a] = tab[b];
	tab[b] = tmp;
}

void t_dane(int *tab, int n, int typ_danych) {  //funckja pobierająca odpowiednie dane

	if (typ_danych == 0) {  //dane losowe
		for (int i = 0; i < n; i++) {
			tab[i] = (rand() % 201) - 100;
			//tab[i] = (rand() % (dwa_n+1)) - dwa_n/2;
		}
	}
	else if (typ_danych == 1) {//dane posortowane malejąco
		FILE *fd;

		if (!(fd = fopen("posortowaneDESC.txt", "r")))
		{
			printf("Blad otwarcia zbioru\n");
			exit(1);
		}

		int i = 0;
		while (feof(fd) == 0)  //zczytywanie liczb z pliku
		{
			fscanf(fd, "%d", &tab[i]);
			i++;
		}
		i--;

		fclose(fd);

		//	printf("-=Dane posortowane malejaco=-\n");
	}
	else if (typ_danych == 2) {//dane posortowane rosnąco
		FILE *fd;

		if (!(fd = fopen("posortowaneASC.txt", "r")))
		{
			printf("Blad otwarcia zbioru\n");
			exit(1);
		}

		int i = 0;
		while (feof(fd) == 0)
		{
			fscanf(fd, "%d", &tab[i]);
			i++;
		}
		i--;

		fclose(fd);
		//	printf("-=Dane posortowane rosnaco=-\n");
	}

}


