#include <iostream>
using namespace std;

int main ()
{
	int col, row;

	for (col = 2; col <= 9; col++)
	{
		for (row = 2; row <= 9; row++)
			cout << col << "X" << row << "="
				  << col * row << "\t";
		cout << endl;
	}

	return 0;
}
