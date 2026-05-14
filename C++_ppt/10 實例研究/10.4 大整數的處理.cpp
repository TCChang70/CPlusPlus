#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int N = 1000;

void dump(int a[], int r)
{
	int i = r - 1;
	while (!a[i] && i > 0) i--;
	while (i >= 0)	cout << a[i--];
	cout << endl;
}

int larger(int a[], int b[])
{
	int i = N - 1;
	while (!(a[i] || b[i])) i--;
	return a[i] > b[i];
}

void add(int a[], int b[])
{
	int c[N] = {}, carry = 0, i;
	for (i = 0; i < N; i++)	
	{
		c[i] = a[i] + b[i] + carry;
		carry = c[i] / 10;
		c[i] %= 10;
	}
	dump(c, N);
}

void sub(int a[], int b[])
{
	int c[N] = {}, borrow = 0, i;
	for (i = 0; i < N; i++)
	{
		c[i] = a[i] - b[i] - borrow;
		if (c[i] < 0)
		{
			c[i] += 10;
			borrow = 1;
		}
		else
			borrow = 0;
	}
	dump(c, N);	
}

void multi(int a[], int b[])
{
	int c[N] = {}, i, j;
	for (i = 0; i < N; i++)
	{ 
		if(!a[i]) continue;	
		for (j = 0; j < N; j++)
			c[i+j] += a[i] * b[j];
	} 
	for (i = 0; i < N; i++)
	{
		c[i+1] += c[i] / 10;
      c[i] %= 10;
	}
	dump(c, N);
}

int main()
{
	string s1, s2;
	char op;
	int i, lena, lenb;
		
	ifstream fin("4.txt");
	if (fin)
	{
		int a[N] = {}, b[N] = {};	
	
		fin >> s1 >> op >> s2;

		lena = s1.length();
		lenb = s2.length();
		for (i = 0; i < lena; i++) 
			a[lena-1-i] = s1[i] - '0';
		for (i = 0; i < lenb; i++) 
			b[lenb-1-i] = s2[i] - '0';
		switch (op)
		{
			case '+' : add(a, b);
				break;
			case '-' : 
				if (larger(a, b))
					sub(a, b);
				else
				{
					cout << "-";
					sub(b, a);
				}
				break;
			case '*' : multi(a, b);
				break;
		}
		fin.close();
	}
	else
		cout << "¶}±ÒÀÉ®×¥¢±Ñ¡I" << endl; 
	return 0;
}
