#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int main ()
{
	int n = 6;
	int a[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		a[i] = (rand() % 6) + 1;
	for (int i = 0; i < n; i++)
		cout << "a[" << i << "] = " << a[i] << "\t";
	cout << endl;
	return 0;
}
