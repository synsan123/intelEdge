#include <iostream>
#include <string>
using namespace std;

#include "MorseSignal.h"

int main() {
	MorseSignal m;
	string text, morse;
	cout << "�Ʒ��� ���� �ؽ�Ʈ�� �Է��ϼ���. �� ��ȣ�� �ٲߴϴ�." << endl;
	getline(cin, text, '\n');
	m.text2Morse(text, morse);
	cout << morse << endl;

	text = ""; // ���� �ؽ�Ʈ �����
	cout << endl << "�� ��ȣ�� �ٽ� ���� �ؽ�Ʈ�� �ٲߴϴ�." << endl;
	if (!m.morse2Text(morse, text))
		cout << "Ʋ�� �� ��ȣ�Դϴ�" << endl;
	else
		cout << text << endl << endl;
}