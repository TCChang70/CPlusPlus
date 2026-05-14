#include <iostream>
using namespace std;

int f(int n)
{
	if (n == 1)
		return 1;
	else
		return f(n - 1) + n;
}

int main ()
{
	cout << "f(5) = " << f(5) << endl;
	return 0;
}
