#include <iostream>
using namespace std;

int main()
{
	int a = 0, b = 1;
	int i, temp, N = 12;
	
	cout << "f(1) = 1" << endl;
	for (i = 2; i <= N; i++) 
	{
		temp = b;
		b = a + b;
		a = temp;
		cout << "f(" << i << ") = " << b << endl;
	}
	return 0;
}
