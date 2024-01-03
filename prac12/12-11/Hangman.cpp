#include <iostream>
using namespace std;

#include "Hangman.h"
#include "Console.h"
#include "Words.h"

Hangman::Hangman(Console* c, int hiddenCount) {
	pConsole = c;
	this->hiddenCount = hiddenCount;
	pWords = NULL;
	pWords = new Words("words.txt");
}

Hangman::~Hangman() {
	if (pWords)
		delete pWords;
}

void Hangman::run() {
	pConsole->write("--------------------------------");
	pConsole->write("지금부터 행맨 개임을 시작합니다.");
	pConsole->write("--------------------------------");

	while (true) {
		answerWord = pWords->getNext(); // 게임에 사용할 단어를 리턴한다.
		pConsole->beep(); // 시스템 beep를 울린다.
		makeHidden(answerWord); // 정답 단어에 2 개의 글자가 숨겨진 단어를 만들어 hiddenWord에 설정한다.
		//		pConsole->write(answerWord); // 정답 단어를 보여준다.

		go(); // 사용자로부터 키를 입력받고 게임을 진행한다.
		char ans = pConsole->prompt("Next(y/n)?");
		if (ans != 'y')
			break;
	}
}

void Hangman::makeHidden(string word) { // word에 2개의 글자를 숨겨 '-'로 대치하여 hiddenWord를 만든다.
	hiddenWord = word;
	int length = word.length();
	for (int k = 0; k < hiddenCount; k++) { // hiddenCount 개수 만큼 글자 숨김
		int n = rand() % length; // 숨긴 단어의 위치를 랜덤하게 선택
		char c = word[n];
		for (int i = 0; i < length; i++) {
			if (hiddenWord[i] == c)
				hiddenWord[i] = '-'; // 숨긴 글자 위치에 '-' 문자 삽입
		}
	}
}

void Hangman::go() {
	failCount = 0;
	char key;
	do {
		if (failCount == 5) {
			pConsole->write("5번 실패 하였습니다.");
			break;
		}
		pConsole->write(hiddenWord); // 숨겨진 글자가 있는 단어를 보여준다.
		key = pConsole->prompt(">>"); // 사용자로부터 키를 입력받는다.
	} while (!complete(key)); // 사용자가 입력한 키가 숨겨진 키인지 검사한다.
	// 숨겨진 키가 모두 찾아지면 complete()는 true를 리턴한다.

	// 게임이 끝나면 정답을 보여준다.
	pConsole->write(answerWord);
}

bool Hangman::complete(char key) { // key는 입력된 문자
	bool hit = false;
	int length = hiddenWord.length();
	for (int i = 0; i < length; i++) { // 숨겨진 단어의 '-'의 모든 문자를 key 문자와 비교하여 변경
		if (hiddenWord[i] == '-')
			if (answerWord[i] == key) {  // key 문자가 숨겨진 문자에 해당하면
				hiddenWord[i] = key; // hiddenWord의 '-' 문자를 key로 변경
				hit = true;
			}
	}
	if (!hit)
		failCount++; // 실패 회수 증가
	for (int i = 0; i < length; i++) {
		if (hiddenWord[i] == '-') // 아직도 '-' 문자가 남아 있으면 
			return false;
	}
	return true; // '-' 문자가 하나도 없으면 성공
}