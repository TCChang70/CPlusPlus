#include <iostream>
using namespace std;
int main()
{
	int n;
	cout << "輸入一個正整數 ";
	cin >> n;
	cout << "倒轉的數值為 ";
	while (n > 0) 
	{
		cout << n % 10;
		n /= 10;
	}
	cout << endl;

	return 0;
}
