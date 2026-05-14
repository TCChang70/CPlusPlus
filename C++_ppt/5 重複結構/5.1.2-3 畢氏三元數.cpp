#include <iostream>
using namespace std;
int main()
{
	int n, a, b, c, total = 0;
	cout << "請輸入一正整數 ";
	cin >> n;
	for (a = 1; a <= n; a++)
		for (b = 1; b <= n; b++) 
			for (c = 1; c <= n; c++)
				if ((a * a)+(b * b) == c * c)
					if (a < b && b < c && a < c) {
						cout << a << ", " << b << ", " << c << endl;
						total++;
					}
	cout << "小於等於 " << n << " 的畢氏三元數共有以上 "
		  << total << " 組" << endl;

	 return 0;
}
