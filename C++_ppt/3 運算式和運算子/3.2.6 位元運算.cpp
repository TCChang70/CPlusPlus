#include <iostream>
using namespace std;
int main()
{
	int a, b;
	cout << "輸入兩個整數：";
	cin >> hex >> a >> b;
	cout << hex << a << " & " << b << "= " << (a & b) << endl
		  << a << " | " << b << "= " << (a | b) << endl
		  << a << " ^ " << b << "= " << (a ^ b) << endl
		  << "~" << a << " = " << (~a) << endl
		  << "~" << b << " = " << (~b) << endl;
	return 0;
}
