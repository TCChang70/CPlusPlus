#include <iostream>
using namespace std;
void swap(int *, int *);
int main()
{
	int a, b;
	cout << "請輸入 a, b 兩個整數 ";
	cin >> a >> b;
	swap(&a, &b);
	cout << "兩個整數交換後 a = " << a << "\tb = " << b << endl;
	return 0;
}

void swap(int *i, int *j)
{
	 int temp;
	 temp = *i;
	 *i = *j;
	 *j = temp;
}
