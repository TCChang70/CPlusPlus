#include <iostream>
using namespace std;
int main()
{
	int h, w;
	double bmi, m;
	cout << "請輸入身高（cm）";
	cin >> h;
	cout << "請輸入體重（kg）";
	cin >> w;
	m = (double) h / 100;
	bmi = w /(m * m);
	cout << "BMI = " << bmi << endl;
	return 0;
}
