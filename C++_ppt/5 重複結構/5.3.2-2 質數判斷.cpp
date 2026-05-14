#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int n, root, i, prime = 1;
	cout << "輸入一個整數 ";
	cin >> n;

	root = sqrt(n);
	for (i = 2; i <= root; i++)
		if (n % i == 0)	{
			prime = 0;
			break;
		}
	cout << n;
	prime ? cout << "是質數" : cout << "不是質數";
	return 0;
}
