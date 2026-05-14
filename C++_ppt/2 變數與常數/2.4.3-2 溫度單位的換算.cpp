#include <iostream>
#include <iomanip> 
using namespace std;
int main()
{
	double f;
	cout << "請輸入華氏度數 ";
	cin >> f;
    
	cout << "攝氏度數為 " << fixed << setprecision(3)
		 << (f - 32) * 5 / 9 << endl;

	return 0;
}
