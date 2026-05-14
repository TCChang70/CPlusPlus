#include <iostream>
using namespace std;

int main ()
{
	int n = 5;
	int a[n] = {7, 8, 4, 9, 2};
	int maxI = 0, i;
	for ( i = 0; i < n; i++ ) 
		if (a[i] > a[maxI])
			maxI = i;
	 
	for ( i = 0; i < n; i++ )
		cout << a[i] << " "; 
	cout << endl;
	cout << ³Ì¤j­Èa[" << maxI << "]="<< a[maxI] << endl; 
	
	return 0;
}
