#include <iostream>
using namespace std;
int main ()
{
	int a[10], i, *p;
	p = a;
	for (i = 0; i < 10; i++)
		*(p + i) = i;
	for (i = 0; i < 10; i++)
		cout << *(p + i) << "  ";
	return 0;
}
