#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
	string text;
	cout << "�Ʒ��� �� ���� �Է��ϼ���.(exit�� �Է��ϸ� �����մϴ�.)" << endl;
	while (true)
	{
		srand((unsigned)time(0));

		cout << " >> ";
		getline(cin, text, '\n');

		if (text == "exit") break;

		int length = text.length();
		int index = rand() % length; // ���ڿ� �ڸ��� �����ϰ� ����, length - 1
		int c = rand() % 26; // 26 - 1, 0 ~ 25������ ������ ���� �߻�. a + 0 = a ~ a + 25 = z

		char change = 'a' + c; // �ƽ�Ű�ڵ� �� ����(�ҹ��� ����)
		if (text[index] == change)// text�迭�� index�ڸ��� ���� ������ ���� ���� ���� ���
			change = 'A' + c; // �빮�ڷ� �ٲ۴�.
		text[index] = change; // ������ ���� text �迭 index�� ����.
		cout << text << endl;
	}
	
}