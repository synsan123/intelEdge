#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	string first, second;
	cout << "�� ��ȣ�� �Է��ϼ��� >> ";
	cin >> first;
	
	cout << "�� ��ȣ�� �ٽ� �� �� �Է��ϼ��� >> ";
	cin >> second;

	if (first == second) cout << "�����ϴ�." << endl;
	else cout << "���� �ʽ��ϴ�." << endl;

	return 0;
}