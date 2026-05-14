#include <iostream>
using namespace std;
int main()
{
	int n, d1, d2, d3;
	cout << "請輸入一個三位數的整數：";
	cin >> n;
	d1 = n % 10;
	d2 = n /10 % 10;
	d3 = n / 100;
	cout << d3 << "\t" << d2 << "\t" << d1;
	return 0;
}
