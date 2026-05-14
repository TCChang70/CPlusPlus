#include <iostream>
using namespace std;

int main()
{
	int  i = 100, j =200;
	int*prti = &i, *prtj = &j;
	
	cout << "i = " << i << "  j = " << j << endl
		  << "	&i = " << &i	 << "		&j = " << &j << endl
		  << " ptri = " <<  prti << "	 prtj = " <<  prtj << endl
		  << "*prti = " << *prti << "\t	*ptrj = " << *prtj << endl
		  << "&ptri = " << &prti << "	&ptrj = " << &prtj << endl;

	return 0;
}
