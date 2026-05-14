#include <iostream>
using namespace std;
int main ()
{
	const int n = 50;
	char sent[n];
	int i = 0;
	cout << "輸入一個英文句子： ";
	cin.getline(sent, 50);
	while (sent[i])
		cout << char(toupper(sent[i++]));
}
