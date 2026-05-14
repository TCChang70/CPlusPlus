#include <iostream>
using namespace std;
int main()
{
	int x, y, z, sum;
	cout << "請輸入整數 x ";
	cin >> x;
	sum = x;
	cout << "sum = " << sum << endl;
	cout << "請輸入整數 y ";
	cin >> y;
	sum += y;
	cout << "sum = " << sum << endl;
	cout << "請輸入整數 z ";
	cin >> z;
	sum += z;
	cout << "sum = " << sum << endl;
	return 0;
}
