#include <iostream>
using namespace std;
int main ()
{
	int n, i, temp, a[20];
	cout << "請輸入資料 ";
	cin >> n;
	for (i = 0; i < n; i++) 
		cin >> a[i];
	for (i = 0; i < n / 2; ++i ){
		temp = a [i];
		a[i] = a[n - 1 - i];
		a[n -1 - i] = temp;
	}
	cout << "反轉後為 ";
	for (i = 0; i < n; ++i)
		cout << a[i] << " ";
	return 0;
}
