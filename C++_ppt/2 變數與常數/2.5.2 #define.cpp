#include <iostream>
#define PI 3.1415926

using namespace std;

int main()
{
	float r;
	cout << "請輸入半徑：";
	cin >> r;
	
	cout << "此圓的面積為 " << PI * r * r << endl;
	cout << "此圓的周長為 " << 2 * PI * r << endl;

	return 0;
}
