#include <iostream>
using namespace std;

int main()
{
	int n;
    
	cout << "輸入西元年（大於 1911 的整數） ";
	cin >> n;
    
	cout << "民國 " << n - 1911 << " 年" << endl;
    
	return 0;
}
