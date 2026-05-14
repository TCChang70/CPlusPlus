#include <iostream>
using namespace std;
int main()
{
	int ts, h, m, s;
	cout << "½Ğ¿é¤J¬í¼Æ ";
	cin >> ts;
	h = ts / 3600;
	m = (ts - h * 3600) / 60;
	s = ts % 60;
	cout << h << ":" << m << ":" << s << endl;
	return 0;
}
