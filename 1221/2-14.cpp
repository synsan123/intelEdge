#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char coffee[100];
	int cups_number;
	int coffee_value = 0;
	int total_coffee_value = 0;

	cout << "���������� 2000��, �Ƹ޸�ī�� 2300��, īǪġ�� 2500���Դϴ�." << endl;
	while (true)
	{
		cout << "�ֹ� >> ";
		cin >> coffee >> cups_number;
		if (strcmp(coffee, "����������") == 0)
		{
			coffee_value = cups_number * 2000;
			cout << coffee_value << "�Դϴ�. ���ְ� �弼��." << endl;
			total_coffee_value += coffee_value;
		}
		else if (strcmp(coffee, "�Ƹ޸�ī��") == 0)
		{
			coffee_value = cups_number * 2300;
			cout << coffee_value << "�Դϴ�. ���ְ� �弼��." << endl;
			total_coffee_value += coffee_value;
		}
		else if (strcmp(coffee, "īǪġ��") == 0)
		{
			coffee_value = cups_number * 2500;
			cout << coffee_value << "�Դϴ�. ���ְ� �弼��." << endl;
			total_coffee_value += coffee_value;
		}
		if (total_coffee_value >= 20000)
		{
			cout << "���� " << total_coffee_value << "���� �Ǹ��Ͽ� ī�並 �ݽ��ϴ�. ���� ����~~~" << endl;
			break;
		}
	}
	return 0;
}