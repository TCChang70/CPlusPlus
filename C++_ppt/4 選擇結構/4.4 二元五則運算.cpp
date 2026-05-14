#include <iostream>
using namespace std;
int main()
{
	int n1, n2;
	char op;
	cout << "依序輸入第 1 個數、運算子、第 2 個數 ";
	cin >> n1 >> op >> n2;
	switch (op)
	{
	   case '+': cout << n1 + n2 << endl;
			break;
	   case '-': cout << n1 - n2 << endl;
			break;
	   case '*': cout << n1 * n2 << endl;
			break;
	   case '/': cout << n1 / n2 << endl;
			break;
	   case '%': cout << n1 % n2 << endl;
			break;
	   default: cout << "輸入錯誤！" << endl;
	}
	return 0;
}
