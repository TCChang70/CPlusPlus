#include <iostream>
using namespace std;
int main ()
{
	int n, sum = 0;
	cout << "½Ð¿é¤J n ( > 1) = ";
	cin >> n;
	for (int i = 1; i <= n; i++)
		sum += i;
	cout << "1 + ... + " << n << " = " << sum << endl;

	return 0;
}
