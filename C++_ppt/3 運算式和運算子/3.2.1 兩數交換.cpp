#include <iostream>
using namespace std;
int main()
{
	int a, b, temp;
	cout << "請輸入兩個整數 ";
	cin >> a >> b;
	temp = a;
	a = b;
	b = temp;
	cout << "兩個整數交換後 a = " << a << "\tb = " << b << endl;
	return 0;
}
