#include <iostream>
#include <string>

using namespace std;
int main()
{
	string s;
	while (getline(cin, s))
	{
		int n = 0, i;
		int len = s.length();

		for (i = 0; i < len; i++)
			if (isalpha(s[i]) && !isalpha(s[i + 1]))
				n++;
		cout << n << endl;
  	}
  	return 0;
}
