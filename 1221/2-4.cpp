#include <iostream>
using namespace std;

int main()
{
	cout << "5���� �Ǽ��� �Է��϶� >> ";

	double a, b, c, d, e;
	cin >> a >> b >> c >> d >> e;

	cout << "���� ū �� = ";
	
	double max;
	max = a;

	if (max < b)
		cout << b;
	else if (max < c)
		cout << c;
	else if (max < d)
		cout << d;
	else if (max < e)
		cout << e;
	else cout << a;

	return 0;
}