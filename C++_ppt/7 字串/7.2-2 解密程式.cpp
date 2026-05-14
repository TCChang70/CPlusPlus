#include <iostream>
#include <string>
using namespace std;
int main ()
{
	int len, i;
	string s;
	while(getline(cin, s))
	{
		len = s.length();
		for(i = 0; i <= len; i++)
			s[i] = char(int(s[i]) - 7);
		cout << s << endl;
	}
	return 0;
}
