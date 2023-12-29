#include <iostream>
#include <string>
using namespace std;

#include "MorseSignal.h"

int main() {
	MorseSignal m;
	string text, morse;
	cout << "아래에 영문 텍스트를 입력하세요. 모스 부호로 바꿉니다." << endl;
	getline(cin, text, '\n');
	m.text2Morse(text, morse);
	cout << morse << endl;

	text = ""; // 영문 텍스트 지우기
	cout << endl << "모스 부호를 다시 영문 텍스트로 바꿉니다." << endl;
	if (!m.morse2Text(morse, text))
		cout << "틀린 모스 부호입니다" << endl;
	else
		cout << text << endl << endl;
}