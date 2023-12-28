#include <iostream>
#include "3-10.h"
using namespace std;

int main()
{
	Add a;
	Sub s;
	Mul m;
	Div d;
	int x, y;
	char c;
	while (true)
	{
		cout << "두 정수와 연산자를 입력하세요 >> ";
		cin >> x >> y >> c;
		if (c == '+')
		{
			a.setvalue(x, y);
			cout << a.calculate() << endl;
		}
		else if (c == '-')
		{
			s.setvalue(x, y);
			cout << s.calculate() << endl;
		}
		else if (c == '*')
		{
			m.setvalue(x, y);
			cout << m.calculate() << endl;
		}
		else if (c == '/')
		{
			d.setvalue(x, y);
			cout << d.calculate() << endl;
		}
		else break;
	}
}