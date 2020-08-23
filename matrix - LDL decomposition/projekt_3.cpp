// projekt3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <stdio.h>
#pragma warning(disable:4996) 

double** UtworzMacierz(int, int);
double* UtworzWektor(int);
extern void WypiszMacierz(double**, int, int);
extern void WypiszWektor(double*, int);

extern void** PobierzMacierz(double**, FILE*, int, int);
extern void* PobierzWektor(double*, FILE*, int);
extern double** TransponujMacierz(double**, double**, int, int);

double ObliczanieMatD(double**, double**, double**, int);
double ObliczanieMatL(double**, double**, double**, int, int);

int main()
{
	FILE* fd;
	int n;
	double** matA, * vekX, * vekB, * vekY, * vekZ, * test;
	double** matL, ** matD;

	if (!(fd = fopen("dane.txt", "r"))) exit(3);
	fscanf(fd, "%d", &n);

	matA = UtworzMacierz(n, n);
	vekB = UtworzWektor(n);
	PobierzMacierz(matA, fd, n, n);
	PobierzWektor(vekB, fd, n);

	fclose(fd);
	vekX = UtworzWektor(n);
	vekY = UtworzWektor(n);
	vekZ = UtworzWektor(n);
	matL = UtworzMacierz(n, n);
	matD = UtworzMacierz(n, n);

	matD[0][0] = matA[0][0];

	for (int j = 0; j < n; j++) {
		matD[j][j] = ObliczanieMatD(matA, matD, matL, j);

		for (int i = 0; i < n; i++) {
			if (i != j)
				matD[i][j] = 0;

			if (i < j)
				matL[i][j] = 0;
			else
				matL[i][j] = ObliczanieMatL(matA, matD, matL, i, j);
		}
	}

	printf("Macierz A: \n");
	WypiszMacierz(matA, n, n);
	printf("Wektor b: \n");
	WypiszWektor(vekB, n);
	printf("Macierz D: \n");
	WypiszMacierz(matD, n, n);
	printf("Macierz L: \n");
	WypiszMacierz(matL, n, n);



	vekY[0] = vekB[0];
	for (int i = 0; i < n; i++) {
		double odjemna = 0;
		for (int k = 0; k < i; k++) {
			odjemna = odjemna + matL[i][k] * vekY[k];
		}
		vekY[i] = vekB[i] - odjemna;
	}

	for (int i = 0; i < n; i++) {
		vekZ[i] = vekY[i] / matD[i][i];
	}


	for (int i = n - 1; i >= 0; i--) {
		double odjemna = 0;
		for (int k = i + 1; k < n; k++) {
			odjemna = odjemna + (matL[k][i] * vekX[k]);
		}
		vekX[i] = (vekZ[i] - odjemna) / matL[i][i];

	}
	printf("Wektor x:\n");
	WypiszWektor(vekX, n);

	system("pause");

}

double ObliczanieMatD(double** matA, double** matD, double** matL, int i) {
	double wynik = matA[i][i];
	double odjemna = 0;

	for (int k = 0; k < i; k++) {
		odjemna = odjemna + (matD[k][k] * matL[i][k] * matL[i][k]);
	}

	return wynik - odjemna;
}

double ObliczanieMatL(double** matA, double** matD, double** matL, int i, int j) {
	double wynik = matA[i][j];
	double odjemna = 0;

	for (int k = 0; k < j; k++) {
		odjemna = odjemna + (matD[k][k] * matL[i][k] * matL[j][k]);

	}
	wynik = wynik - odjemna;

	return wynik / matD[j][j];
}
