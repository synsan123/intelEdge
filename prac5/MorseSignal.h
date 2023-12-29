#ifndef MORSESIGNAL_H
#define MORSESIGNAL_H

#include <iostream>
#include <string>
using namespace std;

class MorseSignal {
	string alphabet[26]; // ���ĺ��� �� ��ȣ ����
	string digit[10]; // ������ �� ��ȣ ����
	string slash, question, comma, period, plus, equal; // Ư�� ������ �� ��ȣ ����
public:
	MorseSignal(); // alphabet[], digit[] �迭 �� Ư�� ������ ��ȣ �ʱ�ȭ
	void text2Morse(string text, string& morse); // ���� �ؽ�Ʈ�� �� ��ȣ�� ��ȯ
	bool morse2Text(string morse, string& text); // �� ��ȣ�� ���� �ؽ�Ʈ�� ��ȯ
	bool morseWord2Text(string morse, string& text);
	bool morse2Letter(string morseLetter, char& letter);
};

#endif