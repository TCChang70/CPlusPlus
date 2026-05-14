#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	int M = 1000;
	int len, i, j, n, a, b;
	int c[M] = {};
	
	fstream fin("2.txt");
	if (fin){
		fin >> n;
		for (i = 0; i < n; i++)	{
			fin >> a >> b;
			for (j = a; j < b; j++) c[j] = 1;
		}
		for (i = 0; i < M; i ++) len += c[i];
		cout << len;
		fin.close();
	}
	else
		cout << "¶}±ÒÀÉ®×¥¢±Ñ¡I" << endl;
	return 0;
} 
