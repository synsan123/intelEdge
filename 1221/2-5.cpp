#include <iostream>
using namespace std;

int main()
{
	cout << "문자들을 입력하라(100개 미만)." << endl;

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
	cout << "x의 개수는 " << count << endl;

	return 0;
}