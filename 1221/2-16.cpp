#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char buf[10000]; // �ؽ�Ʈ ���� �����
	int count = 0; // �ؽ�Ʈ �� ����
	int alphabet[27] = { 0 }; // ������ ���ĺ� ���� �����ϱ� ���� �迭

	cout << "���� �ؽ�Ʈ�� �Է��ϼ���. ������׷��� �׸��ϴ�." << endl;
	cout << "�ؽ�Ʈ�� ���� ; �Դϴ�. 10,000������ �����մϴ�." << endl;
	cin.getline(buf, 10000, ';');

	for (int i = 0; i < strlen(buf); i++)
	{
		if (isalpha(tolower(buf[i])) != 0)
		{
			count++;
			alphabet[buf[i] - 97]++;
		}
	}
	cout << "�� ���ĺ� �� = " << count << endl << endl;

	for (int i = 0; i < 26; i++)
	{
		char alpha = i + 'a';
		cout << alpha << '(' << alphabet[i] << ')' << " : ";
		for (int k = 1; k <= alphabet[i]; k++)
		{
			cout << "*";
		}
		cout << endl;
	}
	return 0;
}

