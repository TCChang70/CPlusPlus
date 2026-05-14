#include <iostream>
using namespace std;
int main()
{
	const int stud = 6, subject = 5;
	int score[stud][subject + 1] =
	{{86, 92, 57, 81, 65}, {96, 98, 81, 67, 74}, {91, 73, 92, 78, 67},
	 {68, 88, 90, 89, 78}, {87, 96, 70, 62, 68}, {84, 75, 94, 80, 90}};
	for (int i = 0; i < stud; i++) {
		for (int j = 0; j < subject; j++){
			cout << score[i][j] << "\t";
			score[i][subject] += score[i][j];
		}
		cout << (double)score[i][subject] / subject << endl;
	}

	return 0;
}
