#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	cout << "5명의 이름을 ';'으로 구분하여 입력하세요" << endl;
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
	cout << "가장 긴 이름은 " << long_name << " 입니다." << endl;

	return 0;
}