#include <iostream>
using namespace std;
int main ()
{
	int all, n, s, i;
	int a[100] = {};
	cout << "請輸入應到人數、實到人數、已到座號 ";
	cin >> all >> n;
	for (i = 1; i <= n; i++){
	  	cin >> s;
		a[ s ] = 1;
	}
	cout << "缺席座號 ";
	for (i = 1; i <= all; i++)
		if (a[i] != 1) cout << i << " ";		
	return 0;
}
