#include <iostream>
using namespace std;

int main()
{
	cout << "문자열 입력 >> ";
	char input_string[100];
	cin >> input_string;
	
	for (int i = 1; i <= strlen(input_string); i++)
	{
		for (int j = 0; j < i; j++) 
		{
			cout << input_string[j];
		}
		if (input_string[i] == '\n')
			break;
		cout << endl;
	}
	return 0;
}