#include <iostream>
using namespace std;

int main()
{
	char c;
	int a;
    
	cout << "請輸入一個字元：";
	cin >> c;
	a = c;
	cout << "此字元的 ASCII 碼為 " << a << endl;

	cout << "請輸入一個 ASCII 碼：";
	cin >> a;
	c = a;
	cout << "此 ASCII 碼的字元為 " << c << endl;

    return 0;
}
