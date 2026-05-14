#include <iostream>
using namespace std;
int main()
{
	int a[6];
	int i, sum = 0;
	for (i = 0; i < 6; i++)
	{
		cout << "輸入 " << i + 1 << " 號成績 "; cin >> a[i];
		sum += a[i];
	}
	cout << "總成績為 " << sum << endl;
	cout << "平均為 " << (float)sum / 6 << endl;
	return 0;  	
}
