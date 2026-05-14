#include <iostream>
#include <fstream>
using namespace std;

void swap(int& x, int& y)
{
	int temp;
	temp = x; x = y; y = temp;
}

int main()
{
	int r, c, n, i, j, k;
	int N = 10;
	int a[N][N], b[N][N], op[N];
	
	ifstream fn("3.txt");
	if (fn)
	{
		fn >> r >> c >> n;

		for (i = 0; i < r; i++)
			for (j = 0; j < c; j++)
				fn >> a[i][j];
			
		for (k = 0; k < n; k++)
			fn >> op[k];
		
		for (k = n - 1; k >= 0; k--)
			if (op[k])
			{
				for (i = 0; i < r/2; i++)
					for (j = 0; j < c; j++)
						swap(a[i][j], a[r-1-i][j]);
			}
			else
			{
				for (i = 0; i< r; i++)
					for (j = 0; j < c; j++)	
						b[c-1-j][i] = a[i][j];
				swap(r, c);
				for (i = 0; i < r; i++)
					for (j = 0; j < c; j++)	
						a[i][j] = b[i][j];		
			}
		cout << r << " " << c << endl;
		for (i = 0; i < r; i++)
		{
			for (j = 0; j < c; j++)	
				cout << a[i][j] << " ";
			cout << endl;
		}
		fn.close();	
	}
	else
		cout << "¶}±ÒÀÉ®×¥¢±Ñ¡I" << endl; 
	return 0;
}
