#include <iostream>
using namespace std;
int main()
{
	int a[] = {1, 2, 3, 4, 5, 6};
	int i, temp, n = 6;
	for (i = 0; i <= n - 2; i++)
	{
		temp = a[i];
		a[i] = a[i + 1];
		a[i + 1] = temp;
	}
	for (i = 0; i < n - 1; i++)
		cout << a[i] << ", ";
	cout << a[n - 1];
	return 0;
}
