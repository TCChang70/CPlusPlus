#include <iostream>
using namespace std;
int main()
{
	int a, b;
	cout << "叫块 a, b ㄢ俱计 ";
	cin >> a >> b;
	if (a % 2)
		a++;
	if (b % 2)
		b--;
	cout << "ㄢ计丁案计 "<< (b - a) / 2 + 1 << " " << endl;
    return 0;
}
