#include <iostream>
using namespace std;
int main()
{
	int n = 8;
	int a[ n ] = {3, 5, 7, 8, 2, 1, 6, 4};
	int temp, i, j, k;
	for(i = 1; i < n; i++) {
		for(k = 0; k < n; k++)
			cout << a[k] << "\t";
		cout << endl;
		for(j = 0; j < n - i; j++) {
			if(a[j] > a[j + 1]) {
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	return 0;
}
