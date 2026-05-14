#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	int M = 10000000;
	int len = 0, i, j, n, a, b;
	int* c = new int[M];
	
	fstream fin("2.txt");
	if (fin){
		fin >> n;
		for (i = 0; i < n; i++)
		{
			fin >> a >> b;
			for (j = a; j < b; j++)
				c[j] = 1;
		}
		for (i = 0; i < M; i ++)
			len += c[i];
		cout << len;
		fin.close();
	}
	else
		cout << "¶}±ÒÀÉ®×¥¢±Ñ¡I" << endl;
	delete [] c;
	return 0;
} 
