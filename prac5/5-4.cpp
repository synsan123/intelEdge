#include <iostream>
using namespace std;

bool bigger(int a, int b, int& big)
{
	if (a == b) return true;
	else
	{
		if (a > b)
			big = a;
		else 
			big = b;
		return false;
	}
}

int main()
{
	int a = 0, b = 0;
	int big;
	cout << "�� ���� �Է��Ͻÿ� : ";
	cin >> a >> b;

	if (bigger(a, b, big)) cout << "����" << endl;
	else cout << "�� �� �� �� ū ���� "<< big << endl;
}


