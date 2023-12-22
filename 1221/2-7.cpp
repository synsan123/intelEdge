#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	cout << "종료하고 싶으면 yes를 입력하세요 >> ";

	char final[100];
	while (true) 
	{
		cin.getline(final, 100, '\n');
		if (strcmp(final,"yes") == 0)
		{
			cout << "종료합니다..." << endl;
			break;
		}
		else cout << "종료하고 싶으면 yes를 입력하세요 >> ";
	}
	return 0;
}