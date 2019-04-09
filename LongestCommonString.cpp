

#include <iostream>
#include <string>
using namespace std;
string convert(string x) {
	string y = " ";
	y += x;
	return y;
}
int LCSPrint(string x, string y, char ** b, int i, int j) {
	if (i == 0 || j == 0)
		return 0;
	if (b[i][j] == '\\') {
		LCSPrint(x, y, b, i - 1, j - 1);
		cout << x[i];
	}
	else if (b[i][j] == '|')
		LCSPrint(x, y, b, i - 1, j);
	else
		LCSPrint(x, y, b, i, j - 1);

}
void LCSLength(string x, string y) {
	x = convert(x);
	y = convert(y);
	int m = x.length();
	int n = y.length();
	int i, j;
	int ** c = new int *[m];
	char ** b = new char *[m];
	for (int k = 0; k < m; k++) {
		c[k] = new int[n ];
		b[k] = new char[n ];
	}
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			c[i][j] = 0;
		}
	for (i = 1; i < m; i++) {
		for (j = 1; j < n; j++) {
			if (x[i] == y[j]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = '\\';
			}
			else  if (c[i-1][j] > c[i][j-1]) {
					c[i][j] = c[i-1][j];
					b[i][j] = '|';
				}
			else {
					c[i][j] = c[i][j-1];
					b[i][j] = '-';
				}
		}
	}
	LCSPrint(x, y, b, i-1 , j-1 );
	cout << endl;
	cout << endl;
	for (i = 0; i < n; i++)
		cout << y[i] <<"  ";
	cout << endl;
	for (i = 1; i < m; i++) {
		
			cout << x[i] << " ";
		for (j = 1; j < n; j++) {
			cout << b[i][j] ;
			cout << c[i][j] << " ";
		}
		cout << endl << endl;
	
	}
}
int main() {

	LCSLength("sowa", "slowo");
	
	cout << endl;
	system("pause");
}
