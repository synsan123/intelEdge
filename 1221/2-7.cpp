#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	cout << "�����ϰ� ������ yes�� �Է��ϼ��� >> ";

	char final[100];
	while (true) 
	{
		cin.getline(final, 100, '\n');
		if (strcmp(final,"yes") == 0)
		{
			cout << "�����մϴ�..." << endl;
			break;
		}
		else cout << "�����ϰ� ������ yes�� �Է��ϼ��� >> ";
	}
	return 0;
}