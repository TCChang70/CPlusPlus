#include <iostream>
using namespace std;
int main ()
{
	int mon;
	cout << "½Ð¿é¤J¤ë¥÷ ";
	cin >> mon;

	switch(mon){
		case 3 ... 5:
			cout << "¬K©u";  break;
		case 6 ... 8:
			cout << "®L©u"; break;
		case 9 ... 11:
			cout << "¬î©u"; break;
		case 12:
		case 1 ... 2:
			cout << "¥V©u"; break;
		default:
			cout << "¿ù»~¤ë¥÷"; break;
	}
	return 0;
}
