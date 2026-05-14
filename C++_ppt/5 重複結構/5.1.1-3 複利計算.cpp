#include <iostream>
using namespace std;

int main ()
{
	int y, i;
	double p, r;

	cout << "請輸入本金 ";
	cin >> p;
	cout << "請輸入年利率 % ";
	cin >> r;
	cout << "請輸入年數 ";
	cin >> y;

	for (i = 0; i < y; i++)
		p = p * (1 + r / 100);
	cout << y << " 年後金額為 " << p;

	return 0;
}
