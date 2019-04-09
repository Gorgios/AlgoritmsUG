#include<iostream>
using namespace std;

struct Wezel {
	int x;
	Wezel* lewy;
	Wezel* prawy;
};

Wezel* dodajWezel(int x) {
	Wezel* nowyKorzen = new Wezel();
	nowyKorzen->x = x;
	nowyKorzen->lewy = nowyKorzen->prawy = NULL;
	return nowyKorzen;
}

Wezel* Wstaw(Wezel* korzen,int x) {
	if(korzen == NULL) {
		korzen = dodajWezel(x);
	}
	else if(x <= korzen->x) {
		korzen->lewy = Wstaw(korzen->lewy,x);
	}
	else {
		korzen->prawy = Wstaw(korzen->prawy,x);
	}
	return korzen;
}
void drukuj(Wezel* korzen) //POSTORDER
{
  if(korzen != NULL )
  {
    drukuj(korzen->lewy);
    drukuj(korzen->prawy);
    cout << korzen->x << " ";
  }
}
void Szukaj(Wezel* korzen,int x) {
	if(korzen == NULL) {
		cout << "BRAK ELEMENTU" << endl;
	}
	else if(korzen->x == x) {
		cout << "ZNALEZIONO" << endl;
	}
	else if(x <= korzen->x) {
		Szukaj(korzen->lewy,x);
	}
	else {
		Szukaj(korzen->prawy,x);
	}
}


int main() {
	Wezel* korzen = NULL;
	korzen = Wstaw(korzen,15);
	korzen = Wstaw(korzen,12);
	korzen = Wstaw(korzen,17);
	korzen = Wstaw(korzen,40);
	korzen = Wstaw(korzen,11);
	korzen = Wstaw(korzen,3);
    drukuj(korzen);
}
