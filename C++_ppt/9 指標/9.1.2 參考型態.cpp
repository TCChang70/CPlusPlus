#include <iostream>
using namespace std;

int main()
{
	int b = 5;
	int& a = b;

	a = 6;
	cout << b << endl;

	return 0;
}
