#include <iostream>
#include <string>
using namespace std;

#if 0
int main()
{
	string s;
	cout << "���ڿ� �Է� >> ";
	getline(cin, s, '\n');
	int number = s.length();
	int count = 0;
	for (int i = 0; i < number; i++)
	{
		if (s[i] == 'a') count++;
	}
	cout << "���� a�� " << count << "�� �ֽ��ϴ�." << endl;
}
#endif

int main() {
    string str;
    cout << "���ڿ� �Է�>>";
    getline(cin, str);

    int num = 0;
    int j = -1;
    while (true) {
        j = (int)str.find('a', j + 1); // index 0 ���� 'a'�� Ž�� 
        if (j == -1) break; // 'a'�� ã�� �������� break 
        num++;
    }
    cout << "���� a�� " << num << "�� �ֽ��ϴ�.";
}