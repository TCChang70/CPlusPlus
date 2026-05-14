#include <iostream>
using namespace std;

int main()
{
	int s;
	cout << "學生成績 ";
	cin >> s;

	cout << "處理後的成績 " << s + (s == 59) << endl;
	return 0;
}
