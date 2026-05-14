#include <iostream>
using namespace std;

int main()
{
	float r;
	cout << "請輸入半徑：";
	cin >> r;
    
	cout << "此圓的面積為 " << 3.14 * r * r << endl;
	cout << "此圓的周長為 " << 2 * 3.14 * r << endl;

	return 0;
}
