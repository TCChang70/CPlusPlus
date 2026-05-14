#include <iostream>
using namespace std;

int main()
{
	int n;
	cout << "班級學生人數 n = ";
	cin >> n;
    
	cout << "所需的費用為 " 
		 << (n / 12) * 50 + (n % 12) * 5 << " 元" << endl;
    
	return 0;
}
