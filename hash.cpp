#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;
struct dane {
	int liczba;
	string nazwisko;
};
long unsigned int zamiana(string slowo) {
	long unsigned int wynik, a;
	wynik = 1;
	a = slowo[0] * 111 + slowo[1];
	for (int i = 2; i < slowo.length(); i++) {
		wynik = 111 * a + slowo[i];
		a = wynik;
	}
	return wynik;
}
void zmianaTablic(dane tab1[], long unsigned int tab2[], int length) {
	for (int i = 0; i < length; i++)
		tab2[i] = zamiana(tab1[i].nazwisko);
}
int H(long unsigned int k, int m, int i) {
	int mod1, mod2, wyjscie,m2;
	m2 = m - 2;
	mod1 = k % m;
	mod2 = i * (1 + k % m2);
	wyjscie = (mod1 + mod2) % m;
	return wyjscie;
}
int hashInsert(dane * tab, dane * tab2, int m, int x, int miejsce) {
	int i = 0;
	int j;
	string nazwisko;
	do {
		j = H(x, m, i);
		nazwisko = tab[j].nazwisko;
		if (nazwisko == "") {
			tab[j].nazwisko = tab2[miejsce].nazwisko;
			tab[j].liczba = tab2[miejsce].liczba;
			return i;
		}
		i++;

	} while (i < m);
	cout << "BRAK MIEJSCA" << endl;
}
int main() {

	string linia;
	string nazwisko = "";
	string liczba = "";
	fstream plik;
	int licznik = 0;
	plik.open("nazwiska.txt");
	while (getline(plik, linia))
		licznik++;
	dane * tablica = new dane[licznik];
	unsigned long int * tabKluczy = new unsigned long int[licznik];
	plik.close();
	plik.open("nazwiska.txt");
	licznik = 0;
	int i, k;
	while (getline(plik, linia)) {
		nazwisko = "";
		liczba = "";
		i = 0;
		while (isspace(linia[i]) == 0) {
			liczba += linia[i];
			i++;
		}
		k = 0;
		for (int j = i + 1; j <= linia.length(); j++) {
			nazwisko += linia[j];
			k++;
		}

		tablica[licznik].liczba = atoi(liczba.c_str());
		tablica[licznik].nazwisko = nazwisko;
		licznik++;
	}
	zmianaTablic(tablica, tabKluczy, licznik);
	//Dla talicyHaszujacej wypelnionej do 50 %
	dane * tabHaszujaca = new dane[licznik + 11]; // +11 bo to 20011 czyli liczba pierwsza
	cout << "SREDNIA WSTAWIEN DLA WYPELNIENIA TABLICY 50% :  " << endl;
	int suma = 0;
	float srednia;
	for (int i = 0; i < licznik + 11; i++) {
		tabHaszujaca[i].nazwisko = "";
	}
	for (int i = 0; i < licznik / 2; i++) {
		suma+= hashInsert(tabHaszujaca, tablica, licznik + 11, tabKluczy[i], i) + 1;
	}
	srednia = float(suma) / float(licznik / 2);
	cout << srednia << endl;
	cout << "SREDNIA WSTAWIEN DLA WYPELNIENIA TABLICY 70% :  " << endl;
	suma = 0;
	for (int i = 0; i < licznik + 11; i++) {
		tabHaszujaca[i].nazwisko = "";
	}
	for (int i = 0; i < licznik * 0.7 ; i++) {
		suma += hashInsert(tabHaszujaca, tablica, licznik + 11, tabKluczy[i], i) + 1;
	}
	srednia = float(suma) / float(licznik * 0.7);
	cout << srednia << endl;
	cout << "SREDNIA WSTAWIEN DLA WYPELNIENIA TABLICY 90% :  " << endl;
	suma = 0;
	for (int i = 0; i < licznik +11; i++) {
		tabHaszujaca[i].nazwisko = "";
	}
	for (int i = 0; i < licznik * 0.9; i++) {
		suma += hashInsert(tabHaszujaca, tablica, licznik + 11, tabKluczy[i], i) + 1;
	}
	srednia = float(suma) / float(licznik * 0.9);
	cout << srednia << endl;
	getchar();
}