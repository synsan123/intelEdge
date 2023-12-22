#include <iostream>
using namespace std;

int main()
{
	cout << "두 수를 입력하라 >> ";

	int first, second;
	cin >> first >> second;
	
	cout << "제일 큰 수 = ";

	if (first > second)
		cout << first;
	else cout << second;

	return 0;
}