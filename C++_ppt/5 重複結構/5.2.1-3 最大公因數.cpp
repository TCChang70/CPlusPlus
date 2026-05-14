#include <iostream>
using namespace std;

int main()
{
	int x, y, k;
	while (cout << "請輸入兩整數 ", cin >> x >> y)
	{
		while (x % y)
		{
			k = x % y;
			x = y;
			y = k;
		}
		cout << "最大公因數 = " << y << endl;
	}
	return 0;
}
