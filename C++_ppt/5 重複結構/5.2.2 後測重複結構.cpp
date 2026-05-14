#include <iostream>
#include <climits>
using namespace std;
int main ()
{
	int n, count = 1, sum = 0;
	int Max = INT_MIN, Min = INT_MAX;

	do {
		cout << "块材 " << count << " 俱计 ";
		cin >> n;
		Max = (Max < n) ? n : Max;
		Min = (Min > n) ? n : Min;
		sum += n;
		count++;
	} while (count <= 5);

	cout << "程计 " << Max << endl << "程计 " << Min << endl
		  << "キА " << sum / 5.0 << endl;

	return 0;
}
