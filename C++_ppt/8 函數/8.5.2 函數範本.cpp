#include <iostream>
using namespace std;
template <class T>
T add(T a, T b)
{
	T c;
	c = a + b;
	return c;
}
int main ()
{
	cout << "8 + 6 = " << add(8, 6) << endl;
	cout << "2.5 + 3.5 = " << add(2.5, 3.5) << endl;
	return 0;
}
