#include <iostream>
using namespace std;
void fillArray(int a[], int);
void printArray(int a[], int);
int sumArray (int a[], int);
int largArray(int a[], int);
const int N = 8;

int main()
{
	int a[N];
	cout << "請輸入陣列元素的值 ";
	fillArray(a, N);
	cout << "陣列元素之和為 "
		  << sumArray(a, N) << endl;
	cout << "陣列元素之最大值為 " 
		  << a[largArray(a, N)];
	return 0;
}

void fillArray(int a[], int N)
{
	for (int i = 0; i < N; i++)
		cin >> a[i];
}

void printArray(int a[], int N)
{
	for (int i = 0; i < N; i++)
		cout << a[i] << " ";
	cout << endl;	
}

int sumArray(int a[], int N)
{
	int i, sum = 0;
	for (i = 0; i < N; i++)
		sum += a[i];
	return sum;
}

int largArray(int a[], int N)
{
	int i, maxi = 0;
	for (i = 1; i < N; i++)
		if (a[maxi] < a[i])
			maxi = i;
	return maxi;
}
