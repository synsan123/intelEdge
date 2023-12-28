#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	cout << "아래에 한 줄을 입력하세요.(exit를 입력하면 종료합니다.)" << endl;

	while (true)
	{
		cout << " >> ";
		getline(cin, s, '\n');

		if (s == "exit") break;
		for (int i = s.length() - 1; i >= 0; i--)
		{
			cout << s[i];
		}
		cout << endl;
	}
}