#include <iostream>
using namespace std;

int main()
{
	cout << "���ڵ��� �Է��϶�(100�� �̸�)." << endl;

	char input_string[100];
	cin.getline(input_string, 100, '\n');

	int count = 0;
	for (int i = 0; i <= 100; i++)
	{
		if (input_string[i] == 'x')
		{
			count++;
		}
	}
	cout << "x�� ������ " << count << endl;

	return 0;
}