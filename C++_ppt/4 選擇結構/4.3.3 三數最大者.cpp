#include <iostream>
using namespace std;
int main()
{
	int a, b, c, max, min;
	cout << "块俱计 ";
	cin >> a >> b >> c;
	if (a > b && a > c)
		max = a;
	else if (b > c)
	 	max = b;
	else
	 	max = c;
	if (a < b && a < c) 
		min = a;
	else if (b < c)
	 	min = b;
	else
	 	min = c;
	cout << a << ", " << b << ", " << c << " 计ぇ程计 " << max
	     << " 程计 " << min << endl;
	return 0;
}
