#include <stdio.h>
#pragma warning(disable:4996) 

void WypiszMacierz(double** tab, int n, int m) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%10.3lf ", tab[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void WypiszWektor(double* vek, int n) {

	for (int i = 0; i < n; i++) {
		printf("%10.3lf ", vek[i]);
	}
	printf("\n");
	printf("\n");
}

double** UtworzMacierz(int n, int m) {
	double** tab;

	if (!(tab = (double**)malloc(sizeof(double*) * n))) {
		printf("Blad z tablica\n kod: 2\n");
		exit(2);
	}

	for (int i = 0; i < n; i++)
		if (!(tab[i] = (double*)malloc(sizeof(double) * m))) exit(2);

	return tab;
}

double* UtworzWektor(int n) {
	double* vek;
	if (!(vek = (double*)malloc(sizeof(double) * n))) {
		printf("Blad z wektorem\n kod: 2\n");
		exit(2);
	}

	return vek;
}

void** PobierzMacierz(double** tab, FILE* fd, int n, int m) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			fscanf(fd, "%lf", &tab[i][j]);
	}

}

void* PobierzWektor(double* vek, FILE* fd, int n) {

	for (int i = 0; i < n; i++)
		fscanf(fd, "%lf", &vek[i]);

}