#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	cout << "5���� �̸��� ';'���� �����Ͽ� �Է��ϼ���" << endl;
	cout << ">> ";

	char name[100];
	char long_name[100];
	int Min_name_number = 0;

	for (int i = 1; i <= 5; i++)
	{
		cin.getline(name, 100, ';');
		cout << i << ':' << name << endl;
		if (Min_name_number < strlen(name))
		{
			Min_name_number = strlen(name);
			strcpy_s(long_name, name);
		}
	}
	
	cout << endl;
	cout << "���� �� �̸��� " << long_name << " �Դϴ�." << endl;

	return 0;
}