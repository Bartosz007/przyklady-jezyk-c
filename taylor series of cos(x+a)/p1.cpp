#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#pragma warning (disable:4996)
#define PI 3.14159265358979323846

double f_scisla(double x, double a);
double f_szereg(double x, double a, double scisla, double epsilon, int M, int* powtorzenia);

int main()
{

	double begin = 0, end = 10;
	int dx = 5;
	double a = 2;

	double epsilon = 0.001;
	int powtorzenia, M = 100;

	char pod_t[50];
	do {
		printf("\nPodaj poczatek przedzialu: \n");
		gets(pod_t);
	} while (!sprawdzaj(pod_t));
	begin = atof(pod_t);

	do {
		printf("\nPodaj koniec przedzialu: \n");
		gets(pod_t);
	} while (!sprawdzaj(pod_t));
	end = atof(pod_t);

	if (begin > end) {
		printf("%lf > %lf - zamieniono je miejscami \n", begin, end);
		double tmp = begin;
		begin = end;
		end = tmp;
	}

	if (begin == end) {
		printf("%lf = %lf - pierwszy wyraz zredukowano o 1 \n", begin, end);
		begin--;
	}

	do {
		printf("\nPodaj podzial przedzialu: \n");
		gets(pod_t);
	} while (!sprawdzaj(pod_t));
	dx = atoi(pod_t);

	if (dx < 0) {
		printf("|%d|- obliczono wartosc bezwzgledna dx \n", dx);
		dx = fabs(dx);
	}

	do {
		printf("\nPodaj stala A: \n");
		gets(pod_t);
	} while (!sprawdzaj(pod_t));
	a = atof(pod_t);


	do {
		printf("\nPodaj dokladnosc episilon: ");
		gets(pod_t);
	} while (!sprawdzaj(pod_t));
	epsilon = atof(pod_t);

	if (epsilon < 0) {
		printf("|%lf|- obliczono wartosc bezwzgledna epsilon \n", epsilon);
		epsilon = fabs(epsilon);
	}


	do {
		printf("\nPodaj maksymalna ilosc wyrazow M: ");
		gets(pod_t);
	} while (!sprawdzaj(pod_t));
	M = atoi(pod_t);

	if (epsilon < 0) {
		printf("|%d|- obliczono wartosc bezwzgledna M :\n", M);
		M = fabs(M);
	}


	double podzial = (end - begin) / dx;

	FILE* fp = NULL;
	fp = fopen("tabela.txt", "w");
	if (fp == NULL) {
		printf("Nie mogę otworzyć pliku tabela.txt do zapisu!\n");
		getchar();
		exit(1);
	}

	printf("\n-----------------------------------------------------------------------------------------------------------------\n");
	printf("|\tx\t|\tf_szereg(x)\t|\tf_scisle(x)\t|\tl_wyr_szer\t|\twar_stopu\t|\n");
	printf("-----------------------------------------------------------------------------------------------------------------\n");

	fprintf(fp, "\n-----------------------------------------------------------------------------------------------------------------\n");
	fprintf(fp, "|\tx\t|\tf_szereg(x)\t|\tf_scisle(x)\t|\tl_wyr_szer\t|\twar_stopu\t|\n");
	fprintf(fp, "-----------------------------------------------------------------------------------------------------------------\n");


	for (double x = begin; x <= end; x = x + podzial) {

		double scisla = f_scisla(x, a);
		double szereg = f_szereg(x, a, scisla, epsilon, M, &powtorzenia);

		printf("|%15.4lf|%23.6lf|%23.6lf|%23d", x, szereg, scisla, powtorzenia);
		fprintf(fp, "|%15.4lf|%23.6lf|%23.6lf|%23d", x, szereg, scisla, powtorzenia);

		if (powtorzenia < M || fabs(scisla - szereg) < epsilon) {
			printf("|\tepsilon\n");		
			fprintf(fp, "|\tepsilon\n");
		}			
		else {
			printf("|\tograniczenie\n");
			fprintf(fp, "|\tograniczenie\n");
		}
			


	}

	fclose(fp);
	fp = NULL;

	system("pause");
	return 0;
}

double f_scisla(double x, double a) {
	return cos(x + a);
}

double f_szereg(double x, double a, double scisla, double epsilon, int M, int* powtorzenia) {
	if (M == 0) {
		*powtorzenia = 0;
		return 0;
	}
	else if (M == 1) {
		*powtorzenia = 1;
		return cos(a);
	}

	int rest_b = (int)x / (2 * PI);

	x = x - (rest_b * 2 * PI);


	double wyr1 = cos(a);
	double wyr2 = -x * sin(a);

	double suma = wyr1 + wyr2;

	*powtorzenia = 2;

	int pary = 1;
	int licznik = *powtorzenia;

	while (M - 2 > 0 && fabs(scisla - suma) > epsilon) {
		if (pary) {
			wyr1 = -wyr1 * x * x / (licznik * (licznik - 1));
			suma = suma + wyr1;
			pary = 0;
		}
		else {
			wyr2 = -wyr2 * x * x / (licznik * (licznik - 1));
			suma = suma + wyr2;
			pary = 1;
		}
		licznik++;
		M--;
	}

	*powtorzenia = licznik;

	return suma;
}

int sprawdzaj(char* tablica) {

	int l = 0, l1 = 0;
	for (int i = 0; i < strlen(tablica); i++) {
		if (tablica[i] > 43 && tablica[i] < 58 && tablica[i] != '/') {}
		else return 0;

		if (tablica[i] == ',')
			tablica[i] = '.';

		if (tablica[i] == '-')
			l++;
		if (tablica[i] == '.')
			l1++;
	}
	if (l > 1 || l1 > 1)
		return 0;

	return 1;
}
