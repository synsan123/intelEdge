#include <iostream>
using namespace std;

int main()
{
	int number;
	int people_number;
	cout << "***** �¸��忡 ���� ���� ȯ���մϴ�. *****" << endl;
	
	while (true)
	{
		cout << "«��:1, ¥��:2, ������:3, ����:4 >> ";
		cin >> number;

		if (number == 4)
		{
			cout << "���� ������ �������ϴ�.";
			break;
		}
		else if(number > 4)
		{
			cout << "�ٽ� �ֹ��ϼ���!!" << endl;
			continue;
		}

		cout << "�� �κ�? ";
		cin >> people_number;

		if (number == 1)
		{
			cout << "«�� " << people_number << "�κ� ���Խ��ϴ�." << endl;
		}
		else if (number == 2)
		{
			cout << "¥�� " << people_number << "�κ� ���Խ��ϴ�." << endl;
		}
		else if (number == 3) 
		{
			cout << "������ " << people_number << "�κ� ���Խ��ϴ�." << endl;
		}
	}
	return 0;
}