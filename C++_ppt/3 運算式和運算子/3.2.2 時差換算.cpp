#include <iostream>
using namespace std;

int main()
{
	int h;

	cout << "台灣時間（點） ";
	cin >> h;

	cout << "美國時間（點） " <<  (h + 24 - 15) % 24  << endl;

	return 0;
}
