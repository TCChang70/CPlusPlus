#include <iostream>
using namespace std;

int main()
{
	char letter;
	cout << "請輸入一個英文字母 ";
	cin >> letter;

	if (letter >= 'A' && letter <= 'Z')
		cout << "這是大寫英文字母 " << letter << endl;
	else
		cout << "這不是大寫英文字母" << endl;

	return 0;
}
