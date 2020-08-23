
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//dodadnie odpowiednich bibliotek
#define PODZIAL 1000000 //stała odpowiedzialna za dokładność całkowania
#define FUNCKJA 0  //stała odpowiedzialna za typ funkcji

double funkcja(double x) { //funckja wyboru typu całkowanej funkcji
	switch (FUNCKJA) //w zależności od stałej FUNCKJA, wybierana jest funckja do całkowania
	{
	case 0:
		return (((2 * x)*x + 2)*x + 5)*x + 4;
		break;
	case 1:
		return (2 * x + 4) / (x*x + 4 * x + 4);
		break;
	case 2:
		return 4. / (3 + 5*cos(x));
		break;
	case 3:
		return pow(exp(x) - 1, 1. / 2);
		break;
	default: //domyślnie
		return x;
		break;
	}
}

double losowanie(double a, double b) {//funckja odpowiedzialna za losowanie liczb z przedziału a...b

	double x = rand();

	x = x / RAND_MAX;
	x = x * (b - a);	
	x = x + a;

	return x;

}

double calka_prostokat1(double a, double b) {//funckja odpowiedzialna za całkowanie metodą prostokątów, pierwszym sposobem

	double dx = (b - a) / PODZIAL; //zmienna odpowiedzialna za rozmiar podprzedziałów
	double calka = 0; //przetrzymuje wartośc całki

	for (double f = a; f < b; f += dx) // pętla zliczająca wysokości prostokątów o podstawie dx
		calka += funkcja(f);

	return  dx* calka; //zwrot wartości całki
}


double calka_trapez(double a, double b) { //funckja odpowiedzialna za całkowanie metodą trapezów,

	double dx = (b - a) / PODZIAL; //zmienna odpowiedzialna za rozmiar podprzedziałów

	double calka = (funkcja(a)+funkcja(b))/2; // wykorzystanie algorytmu wykazanego na zajęciach

	for (double f = a; f < b; f += dx)
		calka += funkcja(f);

	return  dx * calka; //zwrot wartości całki
}

double calka_mCarlo(double a, double b) { //funckja odpowiedzialna za całkowanie metodą Monte Carlo

	double dx = (b - a) / PODZIAL; //zmienna odpowiedzialna za rozmiar podprzedziałów
	double min = 0, max = 0; //zmienne od ekstremów w przedziałach a...b
	int calka = 0; //zmienna odpowiedzialna za liczbę trafionych strzałów

	for (double f = a; f < b; f += dx) { // pętlą obliczająca ekstema w przedziałach a...b o dokładności dx
		if (funkcja(f) < min)
			min = funkcja(f);
		if (funkcja(f) > max)
			max = funkcja(f);
	}

	if (min > 0 && max > 0) { //sprawdzanie poprawności wartości minimalnej
		min = 0;
	}
	if (max < 0 && min < 0) {//sprawdzanie poprawności wartości maksymalnej
		max = 0;
	}

	srand(time(0)); //ziarno liczby pseudolosowej 

	
	for (double f = a; f < b; f += dx) { //pętlą strzelająca w określonym prostokącie a...b x min...max
		double x = losowanie(a, b); //losowanie liczby z przedziału a...b
		double y = losowanie(min, max); //losowanie liczby z przedziału min...max

		if (funkcja(x) > 0 && funkcja(x) > y) { // warunki sprawdzające czy udało trafić się nam pod wykres dla f(x)>0
			calka++;
		}

		if (funkcja(x) < 0 && funkcja(x) < y) {  // warunki sprawdzające czy udało trafić się nam nad wykres dla f(x)<0
			calka--;
		}
		
		
	}
	double pole = (b - a)*(max - min); // obliczanie pola prostokąta o bokach b - a i min - max

	return (double)calka/PODZIAL*pole; // zwrot wartości: liczba_trafionych_strzałów/liczba_wszystkich_strzałów * pole_prostokąta

	//return min;
}


int main()
{

	double a = 0;
	double b = 10;//zmienne od zakresu, mają wpisane na start wartości, żeby w przypadku źle wpisanej liczby nie wyrzuciło błędu
	double zap;//zmienna zapasowa

	printf("Program calkujacy 2000\nPodaj zakres:\n");
	scanf_s("%lf %lf",&a,&b);

	if (a > b) {//warunek sprawdzający poprawność wprowadzonych przedziałów, w razie konieczności zamienia je miejscami
		zap = a;
		a = b;
		b = zap;
	}
	//wypisanie wartości całki różnymi sposobami

	printf("Calka prostokat #1: %10.5lf\n", calka_prostokat1(a, b));
	printf("Calka trapez:       %10.5lf\n", calka_trapez(a, b));
	printf("Calka Monte Carlo:  %10.5lf\n", calka_mCarlo(a, b));
	
}
