#include <iostream>
using namespace std;
int main ()
{
	const int n = 15;
	char name[n], drink[n];
	cout << "輸入你的名字： ";
	cin >> name;
	cout << "輸入你最喜歡喝的飲料： ";
	cin >> drink;
	cout << name << "！下課可以去買一杯" << drink << endl;
	return 0;
}
