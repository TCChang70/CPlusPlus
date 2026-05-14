#include <iostream>
using namespace std;
int main ()
{
	int i, num, ans = 15;
	while (cout << "請輸入一個整數 ", i = 0, cin >> num)
	{
		i++;
		if (num == ans)
			cout << "猜對了！真厲害！" << endl;
		else if (num < ans)
			cout << "數值太小，請再輸入一次" << endl;
		else if (num > ans)
			cout<< "數值太大，請再輸入一次！" << endl;

		cout << "您共猜了 " << i << " 次" << endl;
	}
	return 0;
}
