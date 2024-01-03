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
    cout << "���� �ܾ exit�� �Է��ϸ� �Է� ��\n";
    string engWord, korWord;

    while (true) {
        cout << "���� >>"; cin >> engWord;
        if (engWord == "exit")
            break;
        cout << "�ѱ� >>"; cin >> korWord;
        v.push_back(Word(engWord, korWord));
    }
}

void gameStart(vector<Word>& v) {
    srand((unsigned)time(0));
    int num;

    cout << "���� ���� �׽�Ʈ�� �����մϴ�. 1~4 �� �ٸ� �Է½� ����.\n";

    while (true) {
        int randNum = rand() % v.size();
        cout << v.at(randNum).getEngWord() << "?\n";
        string ex[4] = " ";
        int tmp = rand() % 4;
        ex[tmp] = v.at(randNum).getKorWord();
        for (int i = 0; i < 4; i++) {
            if (tmp == i)
                continue;
            while (true) { // �ߺ��Ǵ� ���ڰ� ���� ó��
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
        cin >> num; // ���ڸ� �Է� 
        if (num == -1 || num == 0 || num > 4) { // �Է¹��� ���� -1�̰ų� 1~4 �� �ٸ� �Է½� ���� 
            break;
        }
        else {
            if (ex[num - 1] == v.at(randNum).getKorWord()) // �����̸� ����
                cout << "Excellent !!\n";
            else
                cout << "No. !!\n";
        }
    }
}

int main() {
    int num;

    vector<Word> v;
    v.push_back(Word("honey", "����"));
    v.push_back(Word("dall", "����"));
    v.push_back(Word("painting", "�׸�"));
    v.push_back(Word("stock", "�ֽ�"));
    v.push_back(Word("bear", "��"));
    v.push_back(Word("deal", "�ŷ�"));

    cout << "***** ���� ���� �׽�Ʈ�� �����մϴ�. *****\n";
    while (true) {
        cout << "���� ����: 1, ���� �׽�Ʈ : 2, ���α׷� ����:�׿�Ű >> ";
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