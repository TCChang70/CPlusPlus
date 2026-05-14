#include <iostream>
using namespace std;
int main ()
{
	int a, b, sum = 0;
	cout << "块ㄢ俱计 ";
	cin >> a >> b;
	for (int i = a ; i <= b ; i++)
	 	if (!(i % 2)) sum += i;
	cout << "ㄢ俱计丁案计㎝ " << sum;

	return 0;
}
