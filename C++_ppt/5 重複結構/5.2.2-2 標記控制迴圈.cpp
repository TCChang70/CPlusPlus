#include <iostream>
using namespace std;
int main ()
{
	int a;
	bool replay;
	do
	{
		cout << "輸入整數值：";
		cin >> a;
		cout << "絕對值為 " << ((a >= 0) ? a : -a) << endl;
		cout << "請選擇 (1 : 繼續 0 : 結束) ";
		cin >> replay;
	} while(replay);
	return 0;
}
