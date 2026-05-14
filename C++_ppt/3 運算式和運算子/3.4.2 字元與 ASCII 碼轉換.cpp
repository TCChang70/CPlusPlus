#include <iostream>
using namespace std;

int main()
{
	int a;
	char c;
	cout << "輸入一個 ASCII 碼 (33~126)：";
	cin >> a;
	cout << "它所代表的字元為 " << (char)a << endl << endl;

	cout << "輸入一個字元：";
	cin >> c;
	cout << "它所代表的 ASCII 碼為 " << (int)c << endl;

	return 0;
}
