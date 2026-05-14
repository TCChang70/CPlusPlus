#include <iostream>
using namespace std;

int main()
{
	int n;
	cout << "請輸入一個整數 ";
	cin >> n;

	if (n % 2)
		cout << "odd" << endl;
	else
		cout << "even" << endl;

	return 0;
}
