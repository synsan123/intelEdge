#include <iostream>
using namespace std;

int main()
{
	int n = 0;
	int sum = 0;

	cout << "�� ���� �Է��ϼ��� >> ";
	cin >> n;

	for (int k = 1; k <= n; k++)
	{
		sum += k;
	}

	cout << "1���� " << n << "������ ���� " << sum << " �Դϴ�." << endl;
	return 0;
}