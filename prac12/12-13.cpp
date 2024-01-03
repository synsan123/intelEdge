#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Words {
	ifstream fin;
	vector<string> wordVector;
	void search(string word);
public:
	Words();
	void gamerun();
	~Words();
};

Words::Words() {
	fin.open("words.txt");
	if (!fin) {
		cout << "words.txt" << " 열기 실패" << endl;
		exit(0); // 프로그램 종료
	}

	// words.txt 파일을 읽어 wordVector에 저장
	string word;
	while (getline(fin, word)) {
		wordVector.push_back(word);
	}
	cout << "... words.txt 파일 로딩 완료" << endl;
}

void Words::search(string word) {
	int count = 0;
	int length = word.length();
	for (int i = 0; i < wordVector.size(); i++) {
		string tmp = wordVector[i];
		if ((int)tmp.length() >= length) { // 길이가 word 보다 작은 단어는 배제
			int index = tmp.find(word);
			if (index == 0) { // 첫 글자부터 같음. 찾았음. 
				cout << tmp << endl;
				count++;
			}
		}
	}
	if (count == 0)
		cout << "발견할 수 없음" << endl;
}

Words::~Words() {
	fin.close();
}

void Words::gamerun() {
	cout << "검색을 시작합니다. 단어를 입력해 주세요." << endl;
	while (true) {
		cout << "단어>> ";
		string word;
		getline(cin, word); // 키보드에서 한 라인을 읽는다.
		if (word == "exit")
			return; // 게임 종료
		search(word);
	}
}

int main() {
	Words w;
	w.gamerun();
}