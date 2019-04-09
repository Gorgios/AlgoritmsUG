#include <stdio.h>
#include <stdlib.h>
//REKURSYWNY
/*void Heapify(int * tab, int i,int heapsize) {
	int l = 2 * i;
	int r = 2 * i + 1;
	int largest,temp;
	if (l <= heapsize && tab[l] > tab[i])
		largest = l;
	else
		largest = i;
	if (r <= heapsize && tab[r] > tab[largest])
		largest = r;
	if (largest != i) {
		temp = tab[i];
		tab[i] = tab[largest];
		tab[largest] = temp;
		Heapify(tab, largest, heapsize);
	}
}*/
//ITERACYJNY
void Heapify(int * tab, int i, int heapsize) {
	int l, r, largest, temp;
	while(1) {
		largest = i;
		l = i * 2;
		r = i * 2 + 1;
		if (l <= heapsize && tab[largest] < tab[l])
			largest = l;
		if (r <= heapsize && tab[largest] < tab[r])
			largest = r;
		if (largest != i) {
			temp = tab[i];
			tab[i] = tab[largest];
			tab[largest] = temp;
			i = largest;
		}
		else
			break;
	} ;
}
void BuildHeap(int *tab, int heapsize) {
	for (int i = heapsize / 2; i >= 0; i--)
		Heapify(tab, i, heapsize);
}
void heapSort(int *tab, int heapsize) {
	int temp;
	BuildHeap(tab,heapsize);
	for (int i = heapsize; i >= 1; i--) {
		temp = tab[heapsize];
		tab[heapsize] = tab[0];
		tab[0] = temp;
		heapsize -= 1;
		Heapify(tab, 0, heapsize);
	}

}

int main() {
    int licznik =1;
    char znak;
    FILE *test = fopen("plik.txt","r");
    while ((znak = getc(test))!=EOF){
        if (znak == '\n')
            licznik ++;
    }
    fclose(test);
    FILE *plik = fopen("plik.txt","r");
	int  tab[licznik];
	for (int i=0; i<licznik; i++){
        fscanf(plik,"%d",&tab[i]);
	}
	fclose(plik);
	heapSort(tab, licznik-1);
	FILE *plik2 = fopen("plik2.txt","w");
	for (int i = 0; i < licznik; i++) {
		fprintf(plik2,"%d\n",tab[i]);
	}
	fclose(plik2);
	return 0;
}
