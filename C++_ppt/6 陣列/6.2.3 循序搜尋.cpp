#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
	int n = 8, i, key, loc = -1;
	int a[n] ;
	srand(time(NULL));
	for (i = 0; i < n; i++)
	{
		a[i] = rand() % 11 + 20;
		cout << "a[" << i << "] = " << a[i] << "\t";
	}
	cout << endl;
	cout << "輸入欲搜尋的整數 ";
	cin >> key;
	for (i = 0; i < n; ++i)
		if (a[i] == key)
		{
			loc = i;
			break;
		}
	if (loc != -1)
		cout << "a[ " << loc << " ] = " << key << endl;
	else
		cout << "沒搜尋到" << key << endl;
	return 0;
}
