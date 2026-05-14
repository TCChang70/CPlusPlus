#include <iostream>
using namespace std;

int maxn(int, int);
float maxn(float, float, float);
int main ()
{
	cout << "8, 6 較大者為 " << maxn(8, 6) << endl;
	cout << "2.5, 3.9, 1.6 較大者為 " << maxn(2.5, 3.9, 1.6)
		  << endl;

	return 0;
}

int maxn(int x, int y)
{
	return (x > y) ? x : y;
}

float maxn(float x, float y, float z)
{
	float m;
	m = (x > y) ? x : y;
	return (z > m) ? z : m;
}
