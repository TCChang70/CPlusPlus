#include <iostream>
using namespace std;

int main()
{
	int a, b, c;
	double m, p;
	cout << "輸入三角形三邊長 ";
	cin >> a >> b >> c;

	if ((a + b > c) && (b + c > a) && (c + a > b))
	{
		m = 0.5 * (a + b + c);
		p = m * (m - a) * (m - b) * (m - c);
		cout << "土地總價為 " << p << endl;
	}
	else
    	cout << a << "," << b << "," << c 
		     << " 無法構成三角形三邊長" << endl;

	return 0;
}
