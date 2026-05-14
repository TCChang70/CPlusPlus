#include <iostream>
using namespace std;
int fib(int);
main()
{
	int i;
	for (i = 0; i < 15; i++)
		cout << "fib(" << i << ") = " << fib(i) << "\t";
}
int fib (int n)
{
	if (n <= 1)
		return n;
	else
		return fib(n - 1) + fib(n - 2);
}
