#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class Word {
    string engWord, korWord;
public:
    Word(string engWord = 0, string korWord = 0) {
        this->engWord = engWord;
        this->korWord = korWord;
    }
    void inputWord(string engWord, string korWord) {
        this->engWord = engWord;
        this->korWord = korWord;
    }
    string getEngWord() { return engWord; }
    string getKorWord() { return korWord; }
};

void inputWord(vector<Word>& v) {
    cout << "영어 단어에 exit을 입력하면 입력 끝\n";
    string engWord, korWord;

    while (true) {
        cout << "영어 >>"; cin >> engWord;
        if (engWord == "exit")
            break;
        cout << "한글 >>"; cin >> korWord;
        v.push_back(Word(engWord, korWord));
    }
}

void gameStart(vector<Word>& v) {
    srand((unsigned)time(0));
    int num;

    cout << "영어 어휘 테스트를 시작합니다. 1~4 외 다른 입력시 종료.\n";

    while (true) {
        int randNum = rand() % v.size();
        cout << v.at(randNum).getEngWord() << "?\n";
        string ex[4] = " ";
        int tmp = rand() % 4;
        ex[tmp] = v.at(randNum).getKorWord();
        for (int i = 0; i < 4; i++) {
            if (tmp == i)
                continue;
            while (true) { // 중복되는 숫자가 없게 처리
                int numChosen = rand() % v.size();
                if (ex[0] != v.at(numChosen).getKorWord() && ex[1] != v.at(numChosen).getKorWord() &&
                    ex[2] != v.at(numChosen).getKorWord() && ex[3] != v.at(numChosen).getKorWord()) {
                    ex[i] = v.at(numChosen).getKorWord();
                    break;
                }
            }
        }
        for (int i = 0; i < 4; i++)
            cout << "(" << i + 1 << ") " << ex[i] << ' ';
        cout << ":>";
        cin >> num; // 숫자만 입력 
        if (num == -1 || num == 0 || num > 4) { // 입력받은 값이 -1이거나 1~4 외 다른 입력시 종료 
            break;
        }
        else {
            if (ex[num - 1] == v.at(randNum).getKorWord()) // 정답이면 실행
                cout << "Excellent !!\n";
            else
                cout << "No. !!\n";
        }
    }
}

int main() {
    int num;

    vector<Word> v;
    v.push_back(Word("honey", "애인"));
    v.push_back(Word("dall", "인형"));
    v.push_back(Word("painting", "그림"));
    v.push_back(Word("stock", "주식"));
    v.push_back(Word("bear", "곰"));
    v.push_back(Word("deal", "거래"));

    cout << "***** 영어 어휘 테스트를 시작합니다. *****\n";
    while (true) {
        cout << "어휘 삽입: 1, 어휘 테스트 : 2, 프로그램 종료:그외키 >> ";
        cin >> num;
        switch (num) {
        case 1:
            inputWord(v);
            cout << endl;
            break;
        case 2:
            gameStart(v);
            cout << endl;
            break;
        default:
            return 0;
        }
    }
}