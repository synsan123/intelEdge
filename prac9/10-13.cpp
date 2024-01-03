#include<iostream>
#include<string>
#include<map>
using namespace std;

int main() {
    map<string, int> Score; // map 컨테이너 생성. 키는 한글 이름, 값은 정수 점수 

    cout << "***** 점수관리 프로그램 HIGH SCORE을 시작합니다 *****\n";
    while (true) {
        int num;
        int score;
        string name;
        cout << "입력:1, 조회:2, 종료:3 >> ";
        cin >> num;
        switch (num) {
        case 1:
            cout << "이름과 점수>> ";
            cin >> name >> score;
            Score.insert(make_pair(name, score)); // map에 저장 
            break;
        case 2:
            cout << "이름 >> ";
            cin >> name;
            if (Score.find(name) == Score.end()) // name '키'를 끝까지 찾았는데 없음 
                cout << "없음" << endl;
            else
                cout << name << "의 점수는 " << Score[name] << endl; // Score에서 name의 값을 찾아 출력 
            break;
        case 3:
            cout << "프로그램을 종료합니다...\n";
            return 0;
        default:
            cout << "제대로 입력해\n";
            break;
        }
    }
}
