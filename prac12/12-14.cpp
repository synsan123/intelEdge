#include <iostream>
#include <fstream>
using namespace std;

int main() {
	const char* file = "c:\\windows\\system.ini";

	ifstream fin;
	fin.open(file, ios::in | ios::binary); // 바이너리 읽기 모드로 파일 열기
	if (fin.fail()) { // 열기 실패 검사
		cout << "파일 열기 오류";
		return 0;
	}

	int count = 0;
	char buf[1024];
	while (!fin.eof()) {
		fin.read(buf, 1024);
		int n = fin.gcount();
		count += n;
	}
	cout << file << " 파일의 크기는 " << count << "바이트" << endl;
}