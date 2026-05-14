#include <iostream>
#include <cmath>
using namespace std;

int main( )
{
	double a, b;
	cout << "請輸入底數 ";
	cin >> a;
	cout << "請輸入指數 ";
	cin >> b;

	cout << "值為 " << pow(a,b) << endl;
	return 0;
}
