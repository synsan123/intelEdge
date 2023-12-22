#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char buf[10000]; // 텍스트 적는 저장소
	int count = 0; // 텍스트 수 세기
	int alphabet[27] = { 0 }; // 각각의 알파벳 수를 저장하기 위한 배열

	cout << "영문 텍스트를 입력하세요. 히스토그램을 그립니다." << endl;
	cout << "텍스트의 끝은 ; 입니다. 10,000개까지 가능합니다." << endl;
	cin.getline(buf, 10000, ';');

	for (int i = 0; i < strlen(buf); i++)
	{
		if (isalpha(tolower(buf[i])) != 0)
		{
			count++;
			alphabet[buf[i] - 97]++;
		}
	}
	cout << "총 알파벳 수 = " << count << endl << endl;

	for (int i = 0; i < 26; i++)
	{
		char alpha = i + 'a';
		cout << alpha << '(' << alphabet[i] << ')' << " : ";
		for (int k = 1; k <= alphabet[i]; k++)
		{
			cout << "*";
		}
		cout << endl;
	}
	return 0;
}

