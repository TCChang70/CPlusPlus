#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
	int n = 7;
	int f[n] = {};
	srand(time(NULL));
	for ( int roll = 1; roll <= 10000; roll++ )
		++f[ rand() % 6 + 1 ];
	cout << "點數\t次數" << endl;
	for ( int face = 1; face < n; face++ )
		cout << face << "\t" << f[ face ] << endl;
	return 0;
}
