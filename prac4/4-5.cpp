#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
	string text;
	cout << "아래에 한 줄을 입력하세요.(exit를 입력하면 종료합니다.)" << endl;
	while (true)
	{
		srand((unsigned)time(0));

		cout << " >> ";
		getline(cin, text, '\n');

		if (text == "exit") break;

		int length = text.length();
		int index = rand() % length; // 문자열 자릿수 랜덤하게 변경, length - 1
		int c = rand() % 26; // 26 - 1, 0 ~ 25사이의 랜덤한 정수 발생. a + 0 = a ~ a + 25 = z

		char change = 'a' + c; // 아스키코드 값 변경(소문자 변경)
		if (text[index] == change)// text배열의 index자리의 값과 변경한 곳의 값이 같을 경우
			change = 'A' + c; // 대문자로 바꾼다.
		text[index] = change; // 변경한 값을 text 배열 index에 대입.
		cout << text << endl;
	}
	
}