#include <iostream>
using namespace std;

int main()
{
	const double pi = 3.1415926;
	float r;
	
	cout << "請輸入半徑：";
	cin >> r;
	
	cout << "此圓的面積為 " << pi * r * r << endl;
	cout << "此圓的周長為 " << 2 * pi * r << endl;

	return 0;
}
