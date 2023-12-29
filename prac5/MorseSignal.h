#ifndef MORSESIGNAL_H
#define MORSESIGNAL_H

#include <iostream>
#include <string>
using namespace std;

class MorseSignal {
	string alphabet[26]; // 알파벳의 모스 부호 저장
	string digit[10]; // 숫자의 모스 부호 저장
	string slash, question, comma, period, plus, equal; // 특수 문자의 모스 부호 저장
public:
	MorseSignal(); // alphabet[], digit[] 배열 및 특수 문자의 부호 초기화
	void text2Morse(string text, string& morse); // 영문 텍스트를 모스 부호로 변환
	bool morse2Text(string morse, string& text); // 모스 부호를 영문 텍스트로 변환
	bool morseWord2Text(string morse, string& text);
	bool morse2Letter(string morseLetter, char& letter);
};

#endif