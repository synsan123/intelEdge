#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class HexViewer {
	ifstream fin;
	void printHexLine(char* buf, int n);
	void printCharLine(char* buf, int n);
public:
	HexViewer(const char* f);
	~HexViewer();
	void show();
};

HexViewer::HexViewer(const char* f) {
	fin.open(f, ios::in | ios::binary);
	if (!fin) {
		cout << f << " 열기 오류";
		exit(0); // 프로그램 종료
	}
	cout << f << " 출력" << endl << endl;
}

HexViewer::~HexViewer() {
	fin.close();
}

void HexViewer::show() {
	char buf[16];
	while (true) {
		fin.read(buf, 16); // 한 번에 16 바이트씩 읽음
		int real = fin.gcount(); // 실제 읽은 바이트 알아내기
		printHexLine(buf, real); // 16진수로 한 줄 출력
		printCharLine(buf, real); // 문자로 한 줄 출력
		if (real < 16)
			break; // 마지막 줄이므로 끝낸다.
		cout << endl; // 다음 줄로 넘어가기
	} // end of while

	cout << endl;
}

void HexViewer::printHexLine(char* buf, int n) { // 현재 줄에 n 개 바이트만 유효
	// print one line as hex codes
	for (int i = 0; i < 16; i++) {
		cout << setw(2) << setfill('0') << hex << (int)buf[i];
		if (i == n - 1) { // i는 index이고 n은 현재 줄에 유효한 바이트 수
			// 나머지 모자라는 부분을 빈 칸으로 채운다.
			cout << ' ';
			for (int j = i + 1; j < 16; j++) {
				cout << setw(2) << setfill(' ') << hex << ' ';
				cout << ' ';
			}
			break;
		}
		if (i == 7) cout << setw(4) << setfill(' ') << ' ';
		else cout << ' ';
	}
}

void HexViewer::printCharLine(char* buf, int n) {
	// hex 라인 출력 후 띄기 위해
	cout << setw(4) << setfill(' ') << ' ';

	// print one line as characters
	for (int i = 0; i < 16; i++) {
		if (isprint(buf[i]))
			cout << buf[i];
		else
			cout << '.';
		if (i == n - 1) {  // i는 index이고 n은 현재 줄에 유효한 바이트 수
			// 더 이상 출력할 데이터가 없으므로 루프를 빠져 나온다.
			break;
		}
		if (i == 7) cout << setw(4) << setfill(' ') << ' ';
		else cout << ' ';
	}
}

int main() {
	HexViewer viewer("c:\\windows\\system.ini");
	viewer.show();
}