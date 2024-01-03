#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

#include "Words.h"

Words::Words(const char* fileName) {
	fin.open(fileName);
	if (!fin) {
		cout << fileName << " 열기 실패" << endl;
		exit(0); // 프로그램 종료
	}

	// words.txt 파일을 읽어 wordVector에 저장
	string word;
	while (getline(fin, word)) { // 파일에서 한 라인을 읽는다.
		wordVector.push_back(word); // 읽은 단어를 벡터에 삽입한다.
	}

	// 랜덤 수 발생을 위한 seed 변경
	srand((unsigned)time(0));
}

Words::~Words() {
	fin.close();
}

string Words::getNext() { // 게임에 사용할 단어를 벡터에서 선택하여 리턴한다.
	string word;
	int n = rand() % wordVector.size(); // 벡터의 범위 내에서 랜덤한 위치 선택
	return wordVector[n]; // 선택된 위치의 단어를 리턴한다.
}