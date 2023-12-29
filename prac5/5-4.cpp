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
	cout << "두 수를 입력하시오 : ";
	cin >> a >> b;

	if (bigger(a, b, big)) cout << "오류" << endl;
	else cout << "두 수 중 더 큰 값은 "<< big << endl;
}


