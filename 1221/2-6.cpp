#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	string first, second;
	cout << "새 암호를 입력하세요 >> ";
	cin >> first;
	
	cout << "새 암호를 다시 한 번 입력하세요 >> ";
	cin >> second;

	if (first == second) cout << "같습니다." << endl;
	else cout << "같지 않습니다." << endl;

	return 0;
}