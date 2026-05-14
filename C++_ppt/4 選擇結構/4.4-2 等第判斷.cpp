#include <iostream>
using namespace std;
int main()
{
	int score;
	cout << "¿é¤J¦¨ÁZ ";
	cin >> score;
	switch (score) {
		case 100 .. 90:
			cout << "Àu" << endl;
			break;
		case 80 ... 89 :
			cout << "¥Ò" << endl;
			break;
		case 70 ... 79 :
			cout << "¤A" << endl;
			break;
		case 60 ... 69 :
			cout << "¤þ" << endl;
			break;
		default :
			cout << "¤B" << endl;
	}
	return 0;
}
