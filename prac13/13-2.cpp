#include <iostream>
using namespace std;

char decideGrade(int score) throw(int) {
	if (score < 0 || score > 100)
		throw score;
	if (score < 60) return 'F';
	else if (score < 70) return 'D';
	else if (score < 80) return 'C';
	else if (score < 90) return 'B';
	else return 'A';
}

int main() {
	int score;
	while (true) {
		cout << "0~100 사이의 점수를 입력하세요>>";
		cin >> score;
		try {
			char c = decideGrade(score);
			cout << c << "학점" << endl;
		}
		catch (int s) {
			cout << s << " : 점수 입력이 잘못되었습니다." << endl;
		}
	}
}