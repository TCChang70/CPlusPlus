#include <iostream>
using namespace std;

int main()
{
	int money;
	cout << "請輸入購物金額 ";
	cin >> money;
	cout << "應付金額 ";

	(money >= 2000) ? cout << money * 0.9 : cout << money * 0.95;

	cout << endl;
	return 0;
}
