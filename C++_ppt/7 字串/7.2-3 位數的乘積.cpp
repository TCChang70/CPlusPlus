#include <iostream>
#include <string>
using namespace std;
int main ()
{
	int n, value;
	string str;
	cout << "輸入資料筆數 ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "輸入第 " << i + 1 << " 筆資料 ";
		cin >> str;
		value = 1;
		for (int j = 0; j < str.length(); j++)
			value *= (str[j] - '0');
		cout << "乘積為 " << value << endl;
	}
	return 0;
}
