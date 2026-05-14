#include <iostream>
using namespace std;
int a;
void fun()
{
	int b = 0; 
	static int c = 3;
	a = a + 1;
	b = b + 1;
	c = c + 1;
	cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
} 
int main( )
{
	for (int i = 0; i < 3; i++)
		fun ( );
	return 0;
}
