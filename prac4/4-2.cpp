#include <iostream>
using namespace std;

int main()
{
	int* p = new int[5];
	int sum = 0;
	double avg = 0;

	cout << "���� 5�� �Է� >> ";
	for (int i = 0; i < 5; i++)
	{
		cin >> p[i];
		sum += p[i];
	}
	
	avg = (double)sum / 5;
	
	cout << "��� " << avg;

	delete[] p;
}