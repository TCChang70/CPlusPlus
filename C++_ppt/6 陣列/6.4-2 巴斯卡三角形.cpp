#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int i, j, n = 6, p[n][n] ={};
	p[0][0] = p[0][1] = 1;
	for (i = 1; i < n; i++){
		p[i][0] = 1;
		for (j = 1; j <= i + 1; j++)
			p[i][j] = p[i-1][j-1] + p[i-1][j];
	}
	
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++)
			if (p[i][j] != 0)
				cout << setw(4) << p[i][j];
			cout << endl;
	}
	return 0;
}
