#include <iostream>
#include <string>
using namespace std;
int main()
{
	int i = 0, p = 0;
	char str[50];
	cin >> str;
	while (str[i])
	{
		if (str[i] == '{')
			p++;
		if (str[i] == '}')
			p--;
		if (p < 0) break;
		i++;
	}
	if (!p)
		cout << "YES";
	else
		cout << "NO";
	return 0;
}
